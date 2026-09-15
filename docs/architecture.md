# PGVortex Architecture v1

## Status

This is the architecture baseline for the first open-source PGVortex release.
The repository currently implements only the extension build skeleton and
interface boundaries described here.

The design is informed by the decoupled vector-index architecture presented in
[PostgreSQL-V 2.0](https://arxiv.org/abs/2608.15994), but extends the segment
boundary toward hybrid search, multiple ANN families, quantization, cloud
stores, and worker-group deployment. PGVortex is not a PostgreSQL-V fork.

## Positioning

```text
PostgreSQL                         PGVortex
SQL and planner                   native vector execution
heap and MVCC                     mutable vector delta
transaction outcome               immutable ANN segments
catalog and object lifecycle      SIMD / PQ / RaBitQ / PCA
WAL correctness boundary          RAM / mmap / disk residency
```

PGVortex depends on pgvector for `vector`, `halfvec`, `sparsevec`, `bit`,
distance operators, and established opclass naming. The extension is
`pgvortex`; the planned access method is `vortex`. No PostgreSQL core patch or
pgvector implementation copy is permitted.

## Three planes

### Control Plane

The PostgreSQL-facing C layer owns IndexAM integration, catalog interaction,
heap/MVCC checks, WAL ordering, status pages, the versioned segment manifest,
VACUUM coordination, planner hooks, and backend/worker IPC.

### Delta Plane

A byte-bounded shared-memory memtable accepts recent vectors. Writers reserve a
slot, fill its TID and vector payload, then atomically publish a ready state.
Readers ignore incomplete slots. The first implementation uses SIMD brute force
instead of a mutable graph. Heap visibility remains authoritative for commit,
abort, HOT chains, and old tuple versions.

### Search Plane

The PostgreSQL-independent native engine searches immutable segments using
HNSW, IVF, and later Vamana or DiskANN. Transform and quantization models are
generation-scoped. Segment search may use native worker threads, but those
threads cannot call Buffer Manager, catalog, memory-context, SPI, `elog`,
`Relation`, or `Snapshot` APIs.

## Process model

```text
PostgreSQL backend
  |-- scan shared memtable concurrently
  |-- serialize vector request
  +-- versioned IPC --> PGVortex vector worker
                           |-- dispatcher
                           |-- native thread pool
                           +-- segment cache/runtime

backend <-- candidates --- worker
  |-- merge delta and segment TopK
  |-- heap fetch and MVCC
  |-- scalar quals and rerank
  +-- continue search until final TopK
```

The protocol uses stable identifiers and owned serialized buffers, never shared
process addresses. One worker is sufficient for v0.1; the protocol must allow
future worker groups or an external vector service without changing IndexAM
semantics.

## Segment boundary

Storage and algorithm code meet only at complete immutable segments:

```text
SegmentStore -- open/load --> native contiguous SegmentView
                                      |
                               native ANN Search()
                                      |
                         pointer/offset traversal only
```

There is one native implementation of each ANN algorithm. Native files,
PostgreSQL page blobs, and object storage are SegmentStore choices, not separate
HNSW/IVF implementations. Read-only mmap and RAM are residency choices after a
segment is opened.

## Correctness anchors

- Heap and transaction state determine whether a returned TID is visible.
- Status pages identify logical vectors not yet covered by a durable segment.
- The WAL-backed manifest identifies the active physical segment generation.
- A segment becomes publishable only after its bytes and checksum are durable.
- Status entries are reclaimable only after manifest publication is durable.
- A side-channel segment is a performance artifact, never correctness authority.

Detailed contracts are in [control-plane.md](control-plane.md),
[segment-architecture.md](segment-architecture.md), and
[durability-recovery.md](durability-recovery.md).

## Non-goals for the skeleton

The initial code does not register the access method, initialize shared memory,
launch a worker, define persisted C structs, implement replication, or bind a
native ANN library. Those changes require focused design and tests.

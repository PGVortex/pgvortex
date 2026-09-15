# Control and Delta Planes

## PostgreSQL-facing responsibilities

The C layer owns every PostgreSQL API interaction:

- IndexAM build, insert, scan, cost, and VACUUM callbacks
- pgvector Datum/opclass adaptation
- heap snapshot and scalar qualification
- status and manifest relation pages
- WAL insertion and recovery integration
- shared-memory allocation and worker supervision
- cancellation, errors, and backend/worker IPC

Native threads receive serialized, owned request data. They never receive a
`Relation`, `Snapshot`, `MemoryContext`, Buffer, or PostgreSQL Datum.

## Mutable memtable

The memtable is sized by bytes rather than vector count. A conceptual entry
contains a stable slot ID, heap TID, state, and inline vector payload:

```text
EMPTY -> WRITING -> READY -> DELETED
```

A writer reserves a slot, writes all content, and publishes `READY` with the
required memory ordering. Searchers read only ready entries. This state is an
indexing accelerator, not transaction visibility; candidates still pass heap
MVCC checks.

The v0.1 memtable uses contiguous storage and SIMD brute force. Seal prevents
new reservations, captures a logical boundary, and hands an immutable snapshot
to the segment builder. Rotation makes a new mutable memtable available before
expensive ANN construction.

## Status versus manifest

Status answers which logical vectors have not crossed a durable segment
boundary. It is grouped by memtable ID so recovery work is bounded by recent
mutable state, not total index size.

Manifest answers which physical, versioned segments constitute the active index
generation. It records algorithm, memtable range, model/codec IDs, store
location, checksums, and publication LSNs.

The two structures are related but must not be conflated: a physical artifact
can be durable but unpublished, and logical status cannot be reclaimed merely
because a builder finished.

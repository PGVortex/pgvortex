# Architecture

## Status and goals

This document records the target architecture for PGVortex. The current tree
is a buildable extension skeleton; the access methods, planner hooks, storage
formats, and algorithms described here are not implemented yet.

PGVortex is a pgvector-compatible PostgreSQL extension. pgvector owns the
`vector`, `halfvec`, `sparsevec`, and `bit` types, their distance operators,
and the established SQL/client ecosystem. PGVortex owns new index access
methods and hybrid execution. It neither modifies PostgreSQL core nor replaces
or joins pgvector extension objects.

The intended access methods are:

| Access method | Storage | Algorithms selected by reloptions |
| --- | --- | --- |
| `pgvortex_graph` | SharedBuffer | HNSW, Vamana |
| `pgvortex_ivf` | SharedBuffer | IVF |
| `pgvortex_mmap_graph` | immutable MMAP base plus SharedBuffer delta | HNSW, Vamana |
| `pgvortex_mmap_ivf` | immutable MMAP base plus SharedBuffer delta | IVF |

Algorithm, quantizer, and transform variants remain reloptions rather than
separate access methods. These SQL names are reserved design targets and are
not registered by the phase-one skeleton.

```sql
CREATE INDEX documents_embedding_idx
ON documents
USING pgvortex_ivf (embedding vector_cosine_ops)
WITH (
    quantizer = 'pq',
    transform = 'pca',
    transform_dim = 384
);
```

## Separation of storage engines

```text
                         pgvector adapter
                                |
        distance / SIMD / PCA / KMeans / PQ / RaBitQ / TopK
                                |
                 coarse iterative-search cursor
                         /              \
      SharedBuffer-specific engines   MMAP-specific engines
        IVF / HNSW / Vamana             IVF / HNSW / Vamana
        PostgreSQL pages, WAL,           offsets, pointers,
        VACUUM, locks, prefetch          cache lines, prefetch
```

SharedBuffer and MMAP do not share their main search loops, page/pointer
traversal, physical layouts, locks, WAL, VACUUM, or compaction machinery. A
node lookup must not pay for a polymorphic storage-provider call. Mathematical
neighbor selection, robust-prune math, and budget calculations may be shared
when benchmarks show that doing so does not constrain either layout.

## Major boundaries

### pgvector compatibility

`src/pgvector_compat/` is the only code allowed to know pgvector Datum layouts
or ABI details. It exposes borrowed, storage-neutral vector views to the math
and engine layers. Operator and opfamily discovery will use PostgreSQL
catalogs. Version-specific behavior is isolated and tested; pgvector source is
not copied into this repository.

### SharedBuffer

The primary product path uses ordinary PostgreSQL index relations and Buffer
Manager pages. It must define WAL, crash recovery, VACUUM, locking, REINDEX,
physical replication, and PITR behavior before format stabilization. Generic
WAL is the first implementation target. See [shared-buffer.md](shared-buffer.md).

### MMAP

PostgreSQL remains the persistence authority. Published base generations are
relation-backed and mapped read-only. Mutations go through SharedBuffer delta
or overlay structures; compaction builds and validates a new generation before
an atomic manifest switch. Backend-local mappings contain process addresses,
while shared memory contains identity, generation metadata, and reader counts
only. See [mmap.md](mmap.md).

### Planner and executor

Planner integration will use supported extension hooks, `CustomPath`, and
`CustomScan`. It estimates scalar selectivity using PostgreSQL statistics and
offers a bounded set of pre-filter, inline-filter, and post-filter plans. The
executor consumes candidates through a coarse iterative cursor and may switch
only among alternatives prepared by the planner. A blocking TopK prevents
strategy changes from emitting rows out of order. See
[hybrid-query.md](hybrid-query.md).

### Statistics

PostgreSQL `pg_statistic` and extended statistics remain the source of scalar
selectivity. Index-local statistics will cover live/dead entries, list-size
histograms, graph degree, tombstone ratio, pages and nodes visited, quantizer
error, PCA retained energy, base/delta ratio, and overlay hit rate. Runtime
observations are maintained as bounded EWMA feedback, not unbounded per-query
state.

## Lifecycle and compatibility

Each persisted format will carry a magic value, format version, algorithm and
feature identifiers, dimensional metadata, and checksums where appropriate.
Readers reject unknown or incompatible versions rather than guessing. Format
changes before the first frozen version may require `REINDEX`; upgrade policy
must be documented with every release.

The logical format inventory is in [index-format.md](index-format.md). No C
struct in the phase-one skeleton is a frozen disk representation.

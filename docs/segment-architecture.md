# Immutable Segment Architecture

## Logical contents

```text
Segment
  meta and checksums
  native ANN body
  TID mapping
  mutable deletion sidecar
  optional raw vector or quantized codes
  statistics
```

The ANN body is write-once. Inserts enter a later memtable; delete/VACUUM sets a
sidecar bit; merge or rebuild creates another segment version. An active index
generation uses one transform and codec model so distances from its segments
remain comparable.

## Lifecycle

```text
BUILDING -- bytes durable --> DURABLE -- manifest WAL --> ACTIVE
ACTIVE -- replacement published --> OBSOLETE -- no readers --> GC
```

Builders write an unpublished artifact, finalize checksums, synchronize bytes,
and only then request manifest publication. A crash before publication leaves
an orphan that can be ignored and garbage-collected. Reclamation requires both
manifest obsolescence and zero readers.

## Merge

The initial merge policy is size-tiered with a bounded search fanout. Merge
extracts live vectors from selected segments, builds a replacement, durably
publishes it, and retires inputs without in-place ANN mutation.

## Algorithm adapters

`IndexAdapter` exposes coarse build, load, search, batch-search, save, and
memory-estimation operations. A complete HNSW, IVF, Vamana, or DiskANN traversal
runs inside the adapter call. It does not call a SegmentStore or PostgreSQL API
for each neighbor.

The initial implementation order is native HNSW, then IVF-Flat. PQ, PCA,
RaBitQ, Vamana, and DiskANN follow after durability and benchmarking gates.

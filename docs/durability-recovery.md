# Durability and Recovery

## Publication ordering

The required order is:

```text
logical vector/status WAL
  -> build immutable segment
  -> segment bytes and checksum durable
  -> manifest publication WAL durable
  -> status range reclaimable
```

Completing a build is not publication. Neither an in-memory worker response nor
a side-channel copy can advance the correctness boundary.

## Recovery inputs

```text
heap + WAL-replayed status + WAL-replayed manifest
```

Recovery reconciles three principal cases:

- Status exists but no published segment: fetch visible heap tuples and rebuild
  the recent memtable or segment.
- Segment bytes exist but no manifest entry: treat the artifact as an orphan and
  ignore it until safe garbage collection.
- A physical artifact is ahead of the recovered logical boundary: reject, mask,
  or rebuild it according to manifest generation and WAL-authoritative deletes.

## Deletes and VACUUM

Heap MVCC remains authoritative at query time. VACUUM converts dead heap TIDs
into memtable deletion state or a segment deletion bitmap. The bitmap's durable
ordering must precede heap tuple reuse. High delete ratios schedule immutable
segment rebuild rather than in-place graph editing.

## Required fault injection

Tests must crash after status WAL, memtable publication, segment byte sync,
before and after manifest publication, during bitmap flush, during merge, and
before obsolete-segment reclamation. Recovery time should scale with recent
mutable state rather than total ANN size.

# SharedBuffer Design

SharedBuffer is PGVortex's primary storage path. Every durable mutation uses a
standard PostgreSQL relation page and participates in PostgreSQL locking,
recovery, replication, and checkpoint semantics. Generic WAL is preferred for
the first implementation.

## Logical page roles

- meta and model pages
- directory pages
- graph node and edge pages
- quantized-code and optional raw-vector pages
- IVF compacted-base and append-only-delta posting pages
- tombstone and retired-page tracking

Physical layouts are intentionally not fixed by the initial skeleton. Page
locality, pin duration, prefetch, and access amplification must be measured on
local storage and page-based remote storage before fields are frozen.

## IVF first

The first index implementation uses a compacted base plus append-only delta
and tombstones. Base postings use a structure-of-arrays organization so a TID
filter can reject entries before PQ or RaBitQ distance work:

```text
centroid -> base posting:  TIDs | codes | flags
         -> delta chain:   appended entries
         -> tombstones:    deleted entry identities
```

Search keeps the ordered centroid list and current posting position, allowing
additional probes without restarting. Compaction merges visible live entries
into a replacement base and retires old pages under a recovery-safe protocol.

## Graph direction

HNSW uses logical NodeIDs independent of physical block numbers. A directory
resolves a NodeID to the latest node, vector/code, and edge version. Edge
updates use append or copy-on-write rather than in-place chains where that
simplifies WAL and concurrent readers. Candidate lifecycle states are:

```text
ALLOCATED -> VECTOR_WRITTEN -> OUT_EDGES_WRITTEN -> LIVE
                                              \-> BACKLINKS_PARTIAL
                                                  -> BACKLINKS_COMPLETE
```

Vamana initially uses a stable base, mutable delta nodes, edge-replacement
overlay, and periodic consolidation. Fully online dynamic Vamana is deferred.

## Required correctness work

Before an index is considered usable, tests must cover torn or interrupted
builds, WAL replay, standby reads, PITR, concurrent insert/delete/VACUUM,
failed compaction, page recycling, relfilenode changes, and REINDEX.

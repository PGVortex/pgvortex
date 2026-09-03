# Index Format Inventory

This is a logical inventory, not a frozen on-disk specification. The initial
C headers intentionally define page and generation categories without
persisted structs.

## SharedBuffer pages

| Page kind | Responsibility |
| --- | --- |
| Meta | format/version, algorithm, feature flags, active roots |
| Model | centroids, PCA, PQ, or RaBitQ model chunks |
| Directory | logical ID to current physical version |
| Graph node | node metadata and visibility state |
| Graph edge | versioned adjacency data |
| Code | quantized vector codes |
| Raw vector | optional rerank material |
| IVF base posting | compacted structure-of-arrays postings |
| IVF delta posting | append-only recent postings |
| Tombstone | logical deletions awaiting consolidation |
| Retired | pages awaiting safe reclamation |

All pages will use PostgreSQL page headers. Any special-space header must carry
a page type and format version. Cross-page references must define validation,
locking, and recovery rules before implementation.

## MMAP generations

A generation manifest identifies immutable extents and their logical kinds.
Published extents are read-only. The manifest switch is the publication point;
incomplete generations are unreachable and recoverable as build garbage.
Offsets, lengths, alignment, checksums, endian policy, and maximum dimensions
must be specified before an experimental format is written.

## Compatibility policy

- never interpret an unknown magic, version, algorithm, or feature flag
- reject a generation if its bounds or checksum validation fails
- use overflow-safe arithmetic for all dimensions, counts, and offsets
- keep process addresses out of pages, WAL, manifests, and shared memory
- require `REINDEX` until an explicit format upgrade path exists

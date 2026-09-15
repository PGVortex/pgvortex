# ADR 0001: One Native ANN Implementation over Immutable Segments

- Status: accepted
- Date: 2026-09-15

## Context

The initial PGVortex skeleton separated SharedBuffer-specific and MMAP-specific
HNSW, IVF, and Vamana engines. That avoided a per-node storage abstraction but
multiplied algorithm, WAL, VACUUM, layout, and compaction work.

## Decision

PGVortex will implement each ANN algorithm once against a native immutable
`SegmentView`. Storage is abstracted at whole-segment write and load boundaries.

- Native files may be read-only mapped or promoted to RAM.
- PageSegmentStore may persist opaque segment bytes in PostgreSQL pages and
  materialize them before search.
- Future object stores may distribute immutable segment artifacts.
- Mutable vectors live in a small shared-memory delta and use brute-force search
  initially.
- PostgreSQL WAL persists status and manifest correctness boundaries, not graph
  edge mutations.

## Consequences

ANN hot loops remain pointer/offset based and storage-independent. MMAP becomes
a residency policy; SharedBuffer becomes an optional segment persistence mode.
Correct recovery, backup, PITR, replication, and garbage collection now depend
on a carefully ordered Status + Manifest protocol and cannot be delegated to
the ANN implementation.

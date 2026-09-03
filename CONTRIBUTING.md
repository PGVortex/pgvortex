# Contributing to PGVortex

PGVortex is in early development. Design discussion before a large change is
strongly encouraged, especially for persisted formats, WAL, planner hooks, or
public SQL objects.

## Development setup

Install PostgreSQL 17 or 18 with server development headers, GNU Make, a C
compiler, and pgvector for the same PostgreSQL installation. Select the target
installation explicitly when more than one version is installed:

```sh
make PG_CONFIG=/path/to/pg_config
sudo make PG_CONFIG=/path/to/pg_config install
```

The compile step uses PostgreSQL headers and PGXS but does not use pgvector
source or private headers. Runtime installation testing requires pgvector:

```sql
CREATE EXTENSION pgvortex CASCADE;
SELECT pgvortex_version();
```

`make clean` removes PGXS build products. The CI workflow performs the build
and extension smoke test against both supported PostgreSQL majors.

## Design rules

- Keep SharedBuffer and MMAP traversal, layout, locking, and lifecycle code
  separate. Do not route hot loops through a unified storage-provider API.
- Share only storage-independent math, training, TopK, sampling, compatibility,
  and coarse search-budget logic.
- Keep all pgvector ABI knowledge inside `src/pgvector_compat/`.
- Do not replace pgvector operators, functions, access methods, or extension
  members.
- Prefer extension hooks and supported PostgreSQL APIs; do not require a core
  patch.
- Treat an on-disk change as a compatibility decision. Document versioning,
  WAL, recovery, VACUUM, and upgrade consequences.
- Keep patches narrowly scoped and avoid speculative implementation.

## C style

Follow PostgreSQL coding style: tabs for indentation where PostgreSQL uses
them, PostgreSQL types and memory contexts, declarations near the start of a
block, and project-prefixed external symbols. New compatibility branches
belong in `src/pg_compat/`, not throughout engine code.

## Testing expectations

Add the smallest appropriate coverage under:

- `test/regression/` for SQL behavior
- `test/isolation/` for concurrency and locking
- `test/crash/` for WAL and recovery
- `test/recall/` for ANN quality
- `test/benchmark/` for reproducible performance work

Correctness, crash safety, and format validation are required before a
performance optimization is considered complete.

# Contributing to PGVortex

PGVortex is in early development. Discuss changes to persistence, WAL, IPC,
public SQL, or native segment formats before implementing them.

## Development setup

Install PostgreSQL 17 or 18 with server development headers, GNU Make, a C
compiler, and pgvector for the same PostgreSQL installation.

```sh
make PG_CONFIG=/path/to/pg_config
sudo make PG_CONFIG=/path/to/pg_config install
```

Compilation uses PostgreSQL headers and PGXS but not pgvector source or private
headers. Runtime smoke testing requires pgvector:

```sql
CREATE EXTENSION pgvortex CASCADE;
SELECT pgvortex_version();
```

## Architecture rules

- PostgreSQL heap/MVCC and WAL-backed metadata are the correctness authority.
- Native ANN bodies are immutable. Deletes use a separately durable sidecar.
- Abstract storage only at segment write/load boundaries, never per ANN node.
- MMAP is a read-only segment residency policy, not an ANN storage engine.
- Native worker threads must not call PostgreSQL backend APIs.
- IPC and persisted formats contain stable identifiers and offsets, not process
  pointers.
- Keep all pgvector ABI knowledge in `src/pg/pgvector_compat.h`.
- Do not replace pgvector operators, functions, access methods, or members.
- Do not require PostgreSQL core patches.
- Treat every format or publication change as a recovery and replication
  decision before treating it as a performance optimization.

PostgreSQL-facing code is C and follows PostgreSQL coding style. The native
engine is C++ behind a narrow C/IPC boundary and must not expose C++ objects or
exceptions to PostgreSQL.

## Testing expectations

- `test/regression/`: SQL and planner behavior
- `test/isolation/`: concurrency and publication ordering
- `test/crash/`: WAL, recovery, and fault injection
- `test/recall/`: exactness and ANN quality
- `test/benchmark/`: reproducible performance workloads

Correctness, crash safety, and format validation precede optimization.

# PGVortex

PGVortex is an **early-development** PostgreSQL extension for high-performance
vector indexes and adaptive scalar/vector hybrid search. The PostgreSQL
extension and shared library are both named `pgvortex`.

The project is designed to remain compatible with the pgvector ecosystem.
pgvector continues to own vector data types, distance operators, SQL syntax,
and client integrations. PGVortex will provide separate access methods and
execution strategies; it will not replace pgvector operators or modify
pgvector extension members.

> PGVortex is not ready for production use. The current `0.1.0` tree is a
> compilable project skeleton: it installs a version function, but does not
> yet register an index access method or implement an ANN algorithm. On-disk
> formats and internal APIs may change without compatibility guarantees.

## Intended scope

- SharedBuffer-native IVF, HNSW, and Vamana indexes with WAL and VACUUM
- relation-backed, read-only MMAP base generations with SharedBuffer deltas
- IVF-Flat, PQ, RaBitQ, and optional PCA transforms
- pre-filter, inline-filter, post-filter, and iterative search
- planner cost models and executor-time adaptive strategy selection
- PostgreSQL 17 and 18, implemented as an extension without core patches

SharedBuffer and MMAP engines deliberately have independent hot loops and
physical layouts. They share mathematical primitives and a coarse search
cursor boundary, not a per-node storage abstraction.

## Build

Prerequisites:

- PostgreSQL 17 or 18 server development files (`pg_config` and PGXS)
- a C compiler and GNU Make
- pgvector installed in the target PostgreSQL installation for runtime use

Build with the desired PostgreSQL installation:

```sh
make PG_CONFIG=/path/to/pg_config
sudo make PG_CONFIG=/path/to/pg_config install
```

Then create the extension. `CASCADE` installs pgvector when its extension
files are available but it has not yet been created in the database:

```sql
CREATE EXTENSION pgvortex CASCADE;
SELECT pgvortex_version();
```

Compilation does not include or copy pgvector internals. Future type and
operator integration must go through `src/pgvector_compat/`.

## Repository map

```text
src/common/             shared math and training contracts
src/shared/             SharedBuffer-specific engines and lifecycle code
src/mmap/               relation-backed immutable MMAP engines
src/planner/            planner path and cost-model boundary
src/executor/           CustomScan and iterative cursor boundary
src/stats/              persistent and runtime feedback contracts
src/pgvector_compat/    centralized pgvector ABI adapter
src/pg_compat/          PostgreSQL-version compatibility boundary
docs/                   architecture and subsystem design notes
test/                   regression, crash, recall, and benchmark suites
```

Start with [the architecture](docs/architecture.md), then see
[the roadmap](ROADMAP.md) and [contribution guide](CONTRIBUTING.md).

## License

PGVortex is licensed under the Apache License 2.0. See [LICENSE](LICENSE).

# PGVortex

PGVortex is an **early-development** native vector search engine for
PostgreSQL. It combines PostgreSQL SQL, MVCC, catalog, and durability semantics
with immutable native ANN segments designed for pointer-based search, SIMD,
read-only mmap, and future disk or accelerator backends.

The PostgreSQL extension and shared library are named `pgvortex`. The planned
index access method is `vortex`.

> The current `0.1.0` tree is an architecture and build skeleton. It installs
> `pgvortex_version()` but does not yet register `USING vortex`, start a vector
> worker, persist a segment, or implement an ANN algorithm. It is not suitable
> for production use, and no on-disk compatibility is promised yet.

## Architecture in one view

```text
PostgreSQL Control Plane       Mutable Delta Plane       Native Search Plane
catalog / IndexAM / WAL        shared memtable           immutable segments
status / manifest / MVCC       insert / delete           HNSW / IVF / Vamana
            |                         |                  DiskANN / PQ / PCA
            +---------- correctness boundary -------------------+
                                                               |
                                                        SegmentStore
                                                 native file / PG pages / object
```

PostgreSQL remains the correctness authority. PGVortex WAL records logical
delta and publication boundaries rather than individual graph mutations.
Native ANN bodies are immutable; deletes live in a separately durable sidecar,
and rebuild/merge publishes a new versioned segment generation.

Storage is abstracted only when a complete segment is written or loaded. Once
loaded, an algorithm traverses a native `SegmentView` without `ReadBuffer()`,
PostgreSQL APIs, or per-node storage virtual calls. MMAP is a residency policy,
not a second ANN implementation.

## pgvector compatibility

PGVortex depends on pgvector and reuses its types, operators, SQL syntax, and
client ecosystem. It does not redefine pgvector objects or copy its internal
implementation. All ABI-sensitive adaptation belongs in `src/pg/pgvector_compat.h`.

The intended SQL is:

```sql
CREATE EXTENSION vector;
CREATE EXTENSION pgvortex;

CREATE INDEX documents_embedding_idx
ON documents
USING vortex (embedding vector_cosine_ops)
WITH (algorithm = 'hnsw', storage = 'native');
```

Only extension creation and the version function work in the current skeleton:

```sql
CREATE EXTENSION pgvortex CASCADE;
SELECT pgvortex_version();
```

## Build

Prerequisites are PostgreSQL 17 or 18 server development files, PGXS, a C
compiler, GNU Make, and pgvector installed for runtime testing.

```sh
make PG_CONFIG=/path/to/pg_config
sudo make PG_CONFIG=/path/to/pg_config install
```

CI builds and loads the skeleton against PostgreSQL 17 and 18.

## Repository map

```text
src/pg/              PostgreSQL-facing C code and correctness metadata
src/engine/          PostgreSQL-independent native engine interfaces
src/storage/         coarse SegmentStore implementations
src/include/         stable C boundary between layers
docs/                architecture, durability, and roadmap decisions
test/                SQL, isolation, crash, recall, and benchmark suites
```

Start with [Architecture v1](docs/architecture.md), the
[native-segment decision](docs/adr/0001-native-segments.md), and the
[roadmap](ROADMAP.md).

## License

PGVortex is licensed under the Apache License 2.0. See [LICENSE](LICENSE).

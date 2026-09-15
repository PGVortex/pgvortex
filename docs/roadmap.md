# Engineering Roadmap

## 1. Access-method vertical slice

Register `USING vortex`, resolve pgvector types/opclasses through the central
adapter, establish scan memory/cancellation rules, and complete a tiny exact
segment from build through heap-MVCC-checked query.

## 2. Worker and delta plane

Version the IPC envelope, supervise one vector worker, implement a byte-bounded
ready-state memtable, search delta and immutable segments concurrently, and
rotate/seal without blocking new inserts for ANN build duration.

## 3. Correctness metadata

Specify meta/status/manifest page layouts, Generic WAL or custom logical
records, durable publication order, delete bitmap/VACUUM order, reader epochs,
orphan discovery, and safe segment reclamation.

## 4. Native segment path

Integrate native HNSW behind the coarse adapter, add size-tiered merge, mmap
cold start, RAM residency budgets, concurrent segment search, and deterministic
recall baselines. Add IVF-Flat only after the shared lifecycle is stable.

## 5. Hybrid execution

Implement iterative batches and filter-aware budgets, then basic sidecar
filtering. PostgreSQL bitmap fusion follows behind `CustomPath`/`CustomScan`
cost and correctness tests.

## 6. Release hardening

Run static, concurrent, dynamic, crash-recovery, cold-start, and hybrid
benchmarks. Document operational limits, supported PostgreSQL/pgvector versions,
format policy, upgrade/reindex requirements, and known failure modes.

Quantization, Vamana, DiskANN, replication, page/object stores, cloud
integration, worker groups, and GPU execution proceed only after the core
vertical slice passes its correctness and recovery gates.

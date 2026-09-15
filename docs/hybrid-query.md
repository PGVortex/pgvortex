# Hybrid Query Design

PGVortex preserves pgvector query syntax:

```sql
SELECT *
FROM documents
WHERE tenant_id = 100
  AND category_id IN (1, 3, 7)
ORDER BY embedding <=> $1
LIMIT 20;
```

## Level 0: iterative ANN

The segment cursor retains algorithm state across batches. After heap MVCC and
scalar quals reject candidates, the executor increases the budget and continues
instead of restarting. A blocking TopK returns no tuple until ordering is final.

## Level 1: filter-aware budget

The planner estimates scalar selectivity `s`, visibility pass rate `pvis`, and
limit `k`. An initial candidate budget starts near:

```text
k / (s * pvis) * safety_factor
```

Runtime pass rates refine later batches. The budget maps to HNSW `ef`, IVF
probes, Vamana width, or DiskANN beam parameters.

## Level 2: segment sidecars

Optional tenant/category bitmaps and timestamp zone maps can reject candidates
inside a segment. Graph search distinguishes traversal from emission: a node
excluded by a scalar filter may still be expanded to reach eligible neighbors.

## Level 3: PostgreSQL bitmap fusion

A future `CustomPath`/`CustomScan` can turn B-tree, BRIN, `BitmapAnd`, or
`BitmapOr` output into a TID filter passed to native search. The planner compares
this with scalar-first exact search and iterative post-filtering.

Cost includes algorithm parameters, segment fanout and residency, dimensions,
delete ratio, candidate merge, heap fetches, and filter/MVCC rejection. A highly
selective scalar predicate should be allowed to beat ANN.

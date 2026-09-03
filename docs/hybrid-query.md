# Hybrid Query Design

PGVortex targets unchanged pgvector query syntax:

```sql
SELECT *
FROM documents
WHERE tenant_id = 100
  AND category_id IN (1, 3, 7)
ORDER BY embedding <=> $1
LIMIT 20;
```

## Strategies

Pre-filter obtains matching heap tuples through a scalar index, bitmap, or
sequential path, computes exact distances, and maintains TopK. It is favored
when the filtered cardinality is small.

Inline-filter turns scalar bitmap output into a TID filter set. IVF tests TID
membership before quantized distance. Graph search separates reachability from
eligibility: a filtered-out node may still be expanded, but it may not be
emitted as a result.

Post-filter asks ANN for a batch, performs heap visibility and scalar quals,
reranks when needed, then advances the same ANN cursor until TopK is final or
the search is exhausted.

## Iterative cursor

`src/executor/search_cursor.h` defines the coarse executor/engine contract:

```text
begin search (engine entry point)
next_candidates
increase_budget
attach_filter
get_progress
end_search
```

The cursor is not used for per-node storage access. HNSW retains its frontier,
visited set, and discarded candidates; Vamana retains its beam/frontier; IVF
retains centroid ordering and posting positions.

## Cost model

Let `N` be table rows, `s` scalar selectivity, `F = N * s`, `k` the limit, and
`pvis` the expected MVCC pass rate.

```text
pre-filter cost = scalar path + F * heap access
                + F * exact distance + TopK

post-filter candidate budget = k / (s * pvis) * safety factor

inline-IVF cost = bitmap + centroid routing + posting membership tests
                + matching code distances + rerank
```

The candidate budget maps to HNSW `ef`, Vamana search width, or IVF probes.
Estimates also include quantizer and heap-fetch cost.

## Runtime adaptation

The planner records a bounded set of valid alternatives. The blocking executor
observes actual bitmap cardinality, filter and MVCC pass rates, visited nodes,
postings scanned, and rerank work. It may increase an engine budget or switch
to a prepared alternative before returning any tuple. This preserves distance
ordering and avoids an executor inventing an uncosted plan.

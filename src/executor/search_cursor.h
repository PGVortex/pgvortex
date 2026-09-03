#ifndef PGVORTEX_EXECUTOR_SEARCH_CURSOR_H
#define PGVORTEX_EXECUTOR_SEARCH_CURSOR_H

#include "postgres.h"

#include "storage/itemptr.h"
#include "utils/rel.h"
#include "utils/snapshot.h"

typedef enum PgvFilterResult
{
	PGV_FILTER_NO,
	PGV_FILTER_MAYBE,
	PGV_FILTER_YES
} PgvFilterResult;

typedef struct PgvFilterSet PgvFilterSet;
typedef struct PgvSearchCursor PgvSearchCursor;

typedef PgvFilterResult (*PgvFilterTest) (const PgvFilterSet *filter,
											 ItemPointer tid);

struct PgvFilterSet
{
	PgvFilterTest test;
	void	   *private_data;
};

typedef struct PgvSearchRequest
{
	Datum		query;
	Oid			query_type;
	uint32		limit;
	double		initial_budget;
	Snapshot	snapshot;
	const PgvFilterSet *filter;
} PgvSearchRequest;

typedef struct PgvSearchCandidate
{
	ItemPointerData tid;
	double		distance;
	bool		recheck_distance;
	bool		recheck_filter;
} PgvSearchCandidate;

typedef struct PgvSearchProgress
{
	uint64		visited_nodes;
	uint64		scanned_postings;
	uint64		emitted_candidates;
	double		current_budget;
} PgvSearchProgress;

typedef struct PgvSearchCursorOps
{
	uint32		(*next_candidates) (PgvSearchCursor *cursor,
									 PgvSearchCandidate *candidates,
									 uint32 capacity);
	void		(*increase_budget) (PgvSearchCursor *cursor, double new_budget);
	void		(*attach_filter) (PgvSearchCursor *cursor,
								  const PgvFilterSet *filter);
	void		(*get_progress) (const PgvSearchCursor *cursor,
								 PgvSearchProgress *progress);
	void		(*end_search) (PgvSearchCursor *cursor);
} PgvSearchCursorOps;

struct PgvSearchCursor
{
	const PgvSearchCursorOps *ops;
};

/* Graph engines use filters to control emission, never reachability. */
static inline bool
pgv_search_may_expand(PgvFilterResult result)
{
	(void) result;
	return true;
}

static inline bool
pgv_search_may_emit(PgvFilterResult result)
{
	return result != PGV_FILTER_NO;
}

#endif /* PGVORTEX_EXECUTOR_SEARCH_CURSOR_H */

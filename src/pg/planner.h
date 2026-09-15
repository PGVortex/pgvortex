#ifndef PGVORTEX_PG_PLANNER_H
#define PGVORTEX_PG_PLANNER_H

#include "postgres.h"

typedef enum PgvHybridStrategy
{
	PGV_HYBRID_ITERATIVE_POST_FILTER,
	PGV_HYBRID_FILTER_AWARE,
	PGV_HYBRID_SEGMENT_FILTER,
	PGV_HYBRID_BITMAP_FILTER
} PgvHybridStrategy;

extern void pgv_planner_initialize(void);
extern void pgv_planner_shutdown(void);

#endif /* PGVORTEX_PG_PLANNER_H */

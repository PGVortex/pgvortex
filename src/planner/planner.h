#ifndef PGVORTEX_PLANNER_H
#define PGVORTEX_PLANNER_H

#include "postgres.h"

typedef enum PgvHybridStrategy
{
	PGV_STRATEGY_PRE_FILTER_EXACT,
	PGV_STRATEGY_INLINE_FILTER,
	PGV_STRATEGY_POST_FILTER
} PgvHybridStrategy;

typedef struct PgvCostInput
{
	double		table_rows;
	double		scalar_selectivity;
	double		limit_tuples;
	double		mvcc_pass_rate;
	double		quantizer_cost;
	double		heap_fetch_cost;
} PgvCostInput;

typedef struct PgvPlanAlternatives
{
	PgvHybridStrategy initial_strategy;
	uint32		allowed_strategies;
	double		initial_candidate_budget;
} PgvPlanAlternatives;

extern void pgv_planner_initialize(void);
extern void pgv_planner_shutdown(void);

#endif /* PGVORTEX_PLANNER_H */

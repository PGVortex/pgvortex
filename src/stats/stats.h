#ifndef PGVORTEX_STATS_H
#define PGVORTEX_STATS_H

#include "postgres.h"

typedef struct PgvIndexStats
{
	uint64		live_entries;
	uint64		dead_entries;
	double		average_visited_nodes;
	double		average_pages;
	double		quantizer_error;
	double		pca_retained_energy;
	double		base_delta_ratio;
	double		overlay_hit_ratio;
} PgvIndexStats;

typedef struct PgvRuntimeFeedback
{
	double		filter_pass_rate;
	double		mvcc_pass_rate;
	double		average_candidates;
} PgvRuntimeFeedback;

#endif /* PGVORTEX_STATS_H */

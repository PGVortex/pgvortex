#ifndef PGVORTEX_COMMON_DISTANCE_H
#define PGVORTEX_COMMON_DISTANCE_H

#include "postgres.h"

#include "common/vector.h"

typedef enum PgvMetricKind
{
	PGV_METRIC_L2,
	PGV_METRIC_INNER_PRODUCT,
	PGV_METRIC_COSINE,
	PGV_METRIC_L1,
	PGV_METRIC_HAMMING,
	PGV_METRIC_JACCARD
} PgvMetricKind;

typedef double (*PgvDistanceFunction) (const PgvVectorView *left,
									   const PgvVectorView *right);

/* SIMD dispatch is selected once; index hot loops call the resolved function. */
extern PgvDistanceFunction pgv_distance_resolve(PgvVectorKind vector_kind,
												 PgvMetricKind metric);

#endif /* PGVORTEX_COMMON_DISTANCE_H */

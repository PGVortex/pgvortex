#ifndef PGVORTEX_COMMON_TRAINING_H
#define PGVORTEX_COMMON_TRAINING_H

#include "postgres.h"

#include "common/vector.h"

typedef struct PgvSampleSet PgvSampleSet;
typedef struct PgvKmeansModel PgvKmeansModel;

typedef struct PgvTrainingOptions
{
	uint64		random_seed;
	uint32		max_samples;
	uint32		max_iterations;
} PgvTrainingOptions;

#endif /* PGVORTEX_COMMON_TRAINING_H */

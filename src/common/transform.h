#ifndef PGVORTEX_COMMON_TRANSFORM_H
#define PGVORTEX_COMMON_TRANSFORM_H

#include "postgres.h"

#include "common/vector.h"

typedef enum PgvTransformKind
{
	PGV_TRANSFORM_NONE,
	PGV_TRANSFORM_PCA
} PgvTransformKind;

typedef struct PgvTransformModel PgvTransformModel;

extern int32 pgv_transform_output_dimensions(const PgvTransformModel *model);

#endif /* PGVORTEX_COMMON_TRANSFORM_H */

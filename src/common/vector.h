#ifndef PGVORTEX_COMMON_VECTOR_H
#define PGVORTEX_COMMON_VECTOR_H

#include "postgres.h"

typedef enum PgvVectorKind
{
	PGV_VECTOR_FLOAT32,
	PGV_VECTOR_FLOAT16,
	PGV_VECTOR_SPARSE_FLOAT32,
	PGV_VECTOR_BIT
} PgvVectorKind;

/* Borrowed, read-only view; ownership remains with the adapter or caller. */
typedef struct PgvVectorView
{
	PgvVectorKind kind;
	int32		dimensions;
	int32		nonzero;
	const void *data;
} PgvVectorView;

#endif /* PGVORTEX_COMMON_VECTOR_H */

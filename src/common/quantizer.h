#ifndef PGVORTEX_COMMON_QUANTIZER_H
#define PGVORTEX_COMMON_QUANTIZER_H

#include "postgres.h"

#include "common/vector.h"

typedef enum PgvQuantizerKind
{
	PGV_QUANTIZER_NONE,
	PGV_QUANTIZER_PQ,
	PGV_QUANTIZER_RABITQ
} PgvQuantizerKind;

typedef struct PgvQuantizerModel PgvQuantizerModel;
typedef struct PgvQuantizerQuery PgvQuantizerQuery;

extern Size pgv_quantizer_code_size(const PgvQuantizerModel *model);
extern void pgv_quantizer_encode(const PgvQuantizerModel *model,
								 const PgvVectorView *vector, void *code);

#endif /* PGVORTEX_COMMON_QUANTIZER_H */

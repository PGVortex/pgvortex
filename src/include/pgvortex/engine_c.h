#ifndef PGVORTEX_ENGINE_C_H
#define PGVORTEX_ENGINE_C_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t PgvIndexId;
typedef uint64_t PgvGenerationId;
typedef uint64_t PgvSegmentId;
typedef uint64_t PgvMemtableId;

typedef struct PgvEngine PgvEngine;
typedef struct PgvSearchHandle PgvSearchHandle;

typedef enum PgvEngineCode
{
	PGV_ENGINE_OK = 0,
	PGV_ENGINE_EXHAUSTED,
	PGV_ENGINE_CANCELLED,
	PGV_ENGINE_UNAVAILABLE,
	PGV_ENGINE_INVALID_ARGUMENT,
	PGV_ENGINE_INTERNAL_ERROR
} PgvEngineCode;

/* Coarse C ABI only; PostgreSQL types must not cross this boundary. */

#ifdef __cplusplus
}
#endif

#endif /* PGVORTEX_ENGINE_C_H */

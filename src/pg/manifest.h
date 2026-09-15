#ifndef PGVORTEX_PG_MANIFEST_H
#define PGVORTEX_PG_MANIFEST_H

#include "postgres.h"

#include "pgvortex/engine_c.h"

typedef enum PgvManifestState
{
	PGV_MANIFEST_BUILDING,
	PGV_MANIFEST_DURABLE,
	PGV_MANIFEST_ACTIVE,
	PGV_MANIFEST_OBSOLETE
} PgvManifestState;

/* The manifest is the WAL-backed authority for the active segment set. */
typedef struct PgvManifestContext PgvManifestContext;

#endif /* PGVORTEX_PG_MANIFEST_H */

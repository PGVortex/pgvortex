#ifndef PGVORTEX_SHARED_VACUUM_H
#define PGVORTEX_SHARED_VACUUM_H

#include "postgres.h"

typedef struct PgvVacuumStats
{
	uint64		live_entries;
	uint64		dead_entries;
	uint64		retired_pages;
} PgvVacuumStats;

#endif /* PGVORTEX_SHARED_VACUUM_H */

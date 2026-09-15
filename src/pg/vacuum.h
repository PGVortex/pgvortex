#ifndef PGVORTEX_PG_VACUUM_H
#define PGVORTEX_PG_VACUUM_H

#include "postgres.h"

typedef struct PgvVacuumStats
{
	uint64		memtable_deletes;
	uint64		segment_deletes;
	uint64		obsolete_segments;
} PgvVacuumStats;

#endif /* PGVORTEX_PG_VACUUM_H */

#ifndef PGVORTEX_MMAP_MAPPING_H
#define PGVORTEX_MMAP_MAPPING_H

#include "postgres.h"

#include "storage/relfilelocator.h"

typedef struct PgvMmapHandle PgvMmapHandle;

/* Safe for shared memory: it contains identity and counts, never pointers. */
typedef struct PgvMmapSharedState
{
	Oid			index_oid;
	RelFileLocator locator;
	uint64		generation;
	uint32		reader_count;
} PgvMmapSharedState;

/* PgvMmapHandle is backend-local and may contain the mapped address. */

#endif /* PGVORTEX_MMAP_MAPPING_H */

#ifndef PGVORTEX_MMAP_LAYOUT_H
#define PGVORTEX_MMAP_LAYOUT_H

#include "postgres.h"

typedef struct PgvMmapExtent
{
	uint64		file_offset;
	uint64		length;
	uint32		kind;
} PgvMmapExtent;

typedef struct PgvMmapGeneration
{
	uint64		generation;
	uint32		extent_count;
} PgvMmapGeneration;

#endif /* PGVORTEX_MMAP_LAYOUT_H */

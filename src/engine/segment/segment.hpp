#ifndef PGVORTEX_ENGINE_SEGMENT_HPP
#define PGVORTEX_ENGINE_SEGMENT_HPP

#include <cstdint>

#include "engine/quant/quantizer.hpp"
#include "engine/transform/transform.hpp"
#include "pgvortex/engine_c.h"

namespace pgvortex {

enum class Algorithm
{
	kHnsw,
	kIvfFlat,
	kVamana,
	kDiskAnn
};

enum class SegmentState
{
	kBuilding,
	kDurable,
	kActive,
	kObsolete,
	kGarbageCollectable
};

/* Logical in-memory description; this is not a persisted disk struct. */
struct SegmentDescriptor
{
	PgvSegmentId id;
	std::uint64_t version;
	PgvGenerationId generation;
	Algorithm algorithm;
	std::uint64_t row_count;
	PgvMemtableId first_memtable;
	PgvMemtableId last_memtable;
	std::uint64_t build_lsn;
	std::uint64_t publish_lsn;
	CodecId codec_id;
	ModelId model_id;
	SegmentState state;
};

class SegmentView;

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_SEGMENT_HPP */

#ifndef PGVORTEX_STORAGE_SEGMENT_STORE_HPP
#define PGVORTEX_STORAGE_SEGMENT_STORE_HPP

#include <cstdint>

#include "engine/common/status.hpp"
#include "pgvortex/engine_c.h"

namespace pgvortex {

class SegmentReader;
class SegmentWriter;

/* Storage is abstracted once per segment, never once per ANN node. */
class SegmentStore
{
public:
	virtual ~SegmentStore() = default;

	virtual Status BeginWrite(PgvSegmentId id, std::uint64_t version,
							  SegmentWriter **writer) = 0;
	virtual Status OpenRead(PgvSegmentId id, std::uint64_t version,
							 SegmentReader **reader) = 0;
	virtual Status Exists(PgvSegmentId id, std::uint64_t version,
						   bool *exists) = 0;
	virtual Status Remove(PgvSegmentId id, std::uint64_t version) = 0;
};

} // namespace pgvortex

#endif /* PGVORTEX_STORAGE_SEGMENT_STORE_HPP */

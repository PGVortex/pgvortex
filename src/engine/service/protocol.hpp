#ifndef PGVORTEX_ENGINE_SERVICE_PROTOCOL_HPP
#define PGVORTEX_ENGINE_SERVICE_PROTOCOL_HPP

#include <cstdint>

#include "pgvortex/engine_c.h"

namespace pgvortex {

enum class Command
{
	kLoadGeneration,
	kSearch,
	kContinueSearch,
	kCancelSearch,
	kBuildSegment,
	kReleaseGeneration
};

/* IPC messages are serialized and versioned; they never contain pointers. */
struct ProtocolVersion
{
	std::uint16_t major;
	std::uint16_t minor;
};

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_SERVICE_PROTOCOL_HPP */

#ifndef PGVORTEX_ENGINE_COMMON_STATUS_HPP
#define PGVORTEX_ENGINE_COMMON_STATUS_HPP

namespace pgvortex {

enum class StatusCode
{
	kOk,
	kExhausted,
	kCancelled,
	kInvalidArgument,
	kIoError,
	kCorruption,
	kInternalError
};

struct Status
{
	StatusCode code;
	const char *message;
};

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_COMMON_STATUS_HPP */

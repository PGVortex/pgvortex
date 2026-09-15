#ifndef PGVORTEX_ENGINE_TRANSFORM_HPP
#define PGVORTEX_ENGINE_TRANSFORM_HPP

#include <cstdint>

namespace pgvortex {

enum class Transform
{
	kNone,
	kNormalize,
	kPca
};

using ModelId = std::uint64_t;

class TransformPipeline
{
public:
	virtual ~TransformPipeline() = default;
};

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_TRANSFORM_HPP */

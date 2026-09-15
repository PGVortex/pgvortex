#ifndef PGVORTEX_ENGINE_COMMON_DISTANCE_HPP
#define PGVORTEX_ENGINE_COMMON_DISTANCE_HPP

#include "engine/common/vector.hpp"

namespace pgvortex {

enum class Metric
{
	kL2,
	kInnerProduct,
	kCosine,
	kL1,
	kHamming,
	kJaccard
};

using DistanceFunction = double (*)(const VectorView &, const VectorView &);

/* Resolve SIMD dispatch before entering an ANN search hot loop. */
DistanceFunction ResolveDistance(VectorKind vector_kind, Metric metric);

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_COMMON_DISTANCE_HPP */

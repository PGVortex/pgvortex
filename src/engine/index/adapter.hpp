#ifndef PGVORTEX_ENGINE_INDEX_ADAPTER_HPP
#define PGVORTEX_ENGINE_INDEX_ADAPTER_HPP

#include <cstddef>

#include "engine/common/status.hpp"

namespace pgvortex {

struct BuildRequest;
struct LoadRequest;
struct SearchRequest;
struct BatchSearchRequest;
struct SaveRequest;
struct MemoryEstimate;
class SearchCursor;

/* Coarse algorithm boundary; traversal stays entirely inside each call. */
class IndexAdapter
{
public:
	virtual ~IndexAdapter() = default;

	virtual Status Build(const BuildRequest &request) = 0;
	virtual Status Load(const LoadRequest &request) = 0;
	virtual Status Search(const SearchRequest &request,
						  SearchCursor **cursor) const = 0;
	virtual Status BatchSearch(const BatchSearchRequest &request) const = 0;
	virtual Status Save(const SaveRequest &request) const = 0;
	virtual MemoryEstimate EstimateMemory() const = 0;
};

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_INDEX_ADAPTER_HPP */

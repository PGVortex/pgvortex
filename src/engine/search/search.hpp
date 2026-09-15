#ifndef PGVORTEX_ENGINE_SEARCH_HPP
#define PGVORTEX_ENGINE_SEARCH_HPP

#include <cstddef>

#include "engine/common/status.hpp"
#include "engine/common/topk.hpp"

namespace pgvortex {

struct SearchProgress
{
	std::uint64_t visited_nodes;
	std::uint64_t scanned_postings;
	std::uint64_t emitted_candidates;
	double current_budget;
};

class Filter;

class SearchCursor
{
public:
	virtual ~SearchCursor() = default;

	virtual Status Next(Candidate *output, std::size_t capacity,
						std::size_t *count) = 0;
	virtual Status IncreaseBudget(double budget) = 0;
	virtual Status AttachFilter(const Filter *filter) = 0;
	virtual SearchProgress Progress() const = 0;
};

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_SEARCH_HPP */

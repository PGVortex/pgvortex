#ifndef PGVORTEX_STORAGE_NATIVE_FILE_HPP
#define PGVORTEX_STORAGE_NATIVE_FILE_HPP

namespace pgvortex {

class SegmentStore;

/* Local files support read-only mmap, RAM promotion, and native I/O. */
SegmentStore *CreateNativeFileStore();

} // namespace pgvortex

#endif /* PGVORTEX_STORAGE_NATIVE_FILE_HPP */

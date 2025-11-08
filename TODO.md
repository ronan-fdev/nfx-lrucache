# nfx-lrucache TODO

Project roadmap and task tracking for the nfx-lrucache library.

### Todo

- [ ] Add optional capacity limits by memory (bytes) in addition to item count
- [ ] Expose runtime metrics (hits, misses, evictions, average latency)
- [ ] Add an eviction observer callback API for resource cleanup
- [ ] Stress-test thread-safety with sanitizers (ASan, TSan, UBSan) in CI

### v2.0.0 (Breaking changes)

- [ ] Add optional lock-striping or sharded caches for lower contention
- [ ] Standardize API naming conventions
  - [ ] Rename tryGet() → find()
  - [ ] Add overload: bool find(const TKey& key, TValue& out)
  - [ ] Rename updateAccess() → touch()
  - [ ] Update all related tests, samples, benchmarks, and documentation

### In Progress

- NIL

### Done ✓

#### v1.0.7 (2025-10-30)

- [x] Automated package verification and artifact uploads in release workflow
- [x] SHA256 checksums for release packages
- [x] Renamed NFX_LRUCACHE_ROOT_DIR to NFX_LRUCACHE_DIR

#### v1.0.6 (2025-10-28)

- [x] Doxygen uses project-local variables (NFX_LRUCACHE_DIR instead of CMAKE_SOURCE_DIR)

#### v1.0.5 through v1.0.1 (2025-10-27)

- [x] CI/CD workflow fixes and improvements

# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- NIL

### Changed

- NIL

### Deprecated

- NIL

### Removed

- NIL

### Fixed

- NIL

### Security

- NIL

## [1.0.4] - 2025-10-27

### Fixed

- Fixed release workflow to upload assets without updating immutable release metadata

## [1.0.3] - 2025-10-27

### Fixed

- Fixed release workflow upload steps to handle immutable releases by adding continue-on-error

## [1.0.2] - 2025-10-27

### Fixed

- Fixed release workflow to handle immutable releases by allowing creation step to continue on error

## [1.0.1] - 2025-10-27

### Fixed

- Fixed release workflow race condition where multiple jobs tried to create the same release simultaneously

## [1.0.0] - 2025-10-26 - Initial Release

### Added

- **LRU Cache Core Features**

  - Thread-safe LRU (Least Recently Used) cache with mutex-based synchronization
  - Sliding expiration policy - entries expire after configurable idle time
  - Configurable size limits with automatic LRU eviction
  - O(1) cache operations using intrusive doubly-linked list
  - Background cleanup support for automatic expired entry removal
  - Factory function pattern with `getOrCreate()` for lazy value creation

- **Build System**

  - CMake 3.20+ configuration with modular structure
  - Header-only interface library target
  - Cross-platform support (Linux GCC/Clang, Windows MinGW/Clang/MSVC)
  - Google Test integration for unit testing
  - Google Benchmark integration for performance benchmarking
  - Doxygen documentation generation with GitHub Pages deployment
  - CPack packaging for distribution (DEB, RPM, ZIP, MSI)
  - Installation support with CMake package config

- **Documentation**

  - README with feature overview and usage examples
  - Detailed API documentation with Doxygen comments
  - Sample applications
  - Build and installation instructions

- **Testing & Benchmarking**

  - Unit test suite
  - Performance benchmarks for all operations
  - Cross-compiler performance validation

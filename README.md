# nfx-lrucache

<!-- Project Info -->

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)](https://github.com/ronan-fdev/nfx-lrucache/blob/main/LICENSE.txt) [![GitHub release (latest by date)](https://img.shields.io/github/v/release/ronan-fdev/nfx-lrucache?style=flat-square)](https://github.com/ronan-fdev/nfx-lrucache/releases) [![GitHub tag (latest by date)](https://img.shields.io/github/tag/ronan-fdev/nfx-lrucache?style=flat-square)](https://github.com/ronan-fdev/nfx-lrucache/tags)<br/>

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue?style=flat-square) ![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg?style=flat-square) ![Cross Platform](https://img.shields.io/badge/Platform-Linux_Windows-lightgrey?style=flat-square)

<!-- CI/CD Status -->

[![Linux GCC](https://img.shields.io/github/actions/workflow/status/ronan-fdev/nfx-lrucache/build-linux-gcc.yml?branch=main&label=Linux%20GCC&style=flat-square)](https://github.com/ronan-fdev/nfx-lrucache/actions/workflows/build-linux-gcc.yml) [![Linux Clang](https://img.shields.io/github/actions/workflow/status/ronan-fdev/nfx-lrucache/build-linux-clang.yml?branch=main&label=Linux%20Clang&style=flat-square)](https://github.com/ronan-fdev/nfx-lrucache/actions/workflows/build-linux-clang.yml) [![Windows MinGW](https://img.shields.io/github/actions/workflow/status/ronan-fdev/nfx-lrucache/build-windows-mingw.yml?branch=main&label=Windows%20MinGW&style=flat-square)](https://github.com/ronan-fdev/nfx-lrucache/actions/workflows/build-windows-mingw.yml) [![Windows MSVC](https://img.shields.io/github/actions/workflow/status/ronan-fdev/nfx-lrucache/build-windows-msvc.yml?branch=main&label=Windows%20MSVC&style=flat-square)](https://github.com/ronan-fdev/nfx-lrucache/actions/workflows/build-windows-msvc.yml) [![CodeQL](https://img.shields.io/github/actions/workflow/status/ronan-fdev/nfx-lrucache/codeql.yml?branch=main&label=CodeQL&style=flat-square)](https://github.com/ronan-fdev/nfx-lrucache/actions/workflows/codeql.yml)

> A C++20 thread-safe LRU cache library with sliding expiration support

## Overview

nfx-lrucache is a modern C++20 header-only library providing a thread-safe Least Recently Used (LRU) cache with sliding expiration policy. It offers O(1) cache operations using an intrusive doubly-linked list, perfect for performance-critical applications like database query caching, API response caching, and session management.

## Features

### 🗄️ High-Performance LRU Cache

- **Thread-Safe Operations**: Mutex-based synchronization for concurrent access
- **O(1) Cache Operations**: Constant-time get, put, and eviction using intrusive linked list
- **Sliding Expiration**: Automatic entry expiration with configurable time-to-live
- **Background Cleanup**: Optional periodic cleanup of expired entries
- **Factory Pattern**: Convenient factory function support for cache miss scenarios

### 📊 Real-World Applications

- **Database Query Caching**: Cache expensive database query results
- **API Response Caching**: Store and retrieve API responses efficiently
- **Session Management**: Manage user sessions with automatic expiration
- **Computed Value Caching**: Cache expensive computations and calculations
- **Resource Management**: Control resource lifetime with automatic cleanup

### ⚡ Performance Optimized

- **Header-only library** with zero runtime dependencies
- **O(1) complexity** for all cache operations (get, put, evict)
- **Intrusive linked list** design for minimal memory overhead
- **Efficient LRU tracking** with constant-time promotion
- **Minimal lock contention** with optimized synchronization
- **Cache-friendly** memory layout for better performance

### 🌍 Cross-Platform Support

- Linux, Windows
- GCC 14+, Clang 19+, MSVC 2022+
- Thread-safe operations
- Consistent behavior across platforms

## Quick Start

### Requirements

- C++20 compatible compiler:
  - **GCC 14+** (14.2.0 tested)
  - **Clang 18+** (19.1.7 tested)
  - **MSVC 2022+** (19.44+ tested)
- CMake 3.20 or higher

### CMake Integration

```cmake
# Development options
option(NFX_LRUCACHE_BUILD_TESTS          "Build tests"                        ON  )
option(NFX_LRUCACHE_BUILD_SAMPLES        "Build samples"                      ON  )
option(NFX_LRUCACHE_BUILD_BENCHMARKS     "Build benchmarks"                   ON  )
option(NFX_LRUCACHE_BUILD_DOCUMENTATION  "Build Doxygen documentation"        ON  )

# Installation and packaging
option(NFX_LRUCACHE_INSTALL_PROJECT      "Install project"                    ON  )
option(NFX_LRUCACHE_PACKAGE_SOURCE       "Enable source package generation"   ON  )
option(NFX_LRUCACHE_PACKAGE_ARCHIVE      "Enable TGZ/ZIP package generation"  ON  )
option(NFX_LRUCACHE_PACKAGE_DEB          "Enable DEB package generation"      ON  )
option(NFX_LRUCACHE_PACKAGE_RPM          "Enable RPM package generation"      ON  )
option(NFX_LRUCACHE_PACKAGE_WIX          "Enable WiX MSI installer"           ON  )
```

### Using in Your Project

#### Option 1: Using FetchContent (Recommended)

```cmake
include(FetchContent)
FetchContent_Declare(
  nfx-lrucache
  GIT_REPOSITORY https://github.com/ronan-fdev/nfx-lrucache.git
  GIT_TAG        main  # or use specific version tag like "1.0.0"
)
FetchContent_MakeAvailable(nfx-lrucache)

# Link with header-only interface library
target_link_libraries(your_target PRIVATE nfx-lrucache::nfx-lrucache)
```

#### Option 2: As a Git Submodule

```bash
# Add as submodule
git submodule add https://github.com/ronan-fdev/nfx-lrucache.git third-party/nfx-lrucache
```

```cmake
# In your CMakeLists.txt
add_subdirectory(third-party/nfx-lrucache)
target_link_libraries(your_target PRIVATE nfx-lrucache::nfx-lrucache)
```

#### Option 3: Using find_package (After Installation)

```cmake
find_package(nfx-lrucache REQUIRED)
target_link_libraries(your_target PRIVATE nfx-lrucache::nfx-lrucache)
```

### Building

```bash
# Clone the repository
git clone https://github.com/ronan-fdev/nfx-lrucache.git
cd nfx-lrucache

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the library
cmake --build . --config Release --parallel

# Run tests (optional)
ctest -C Release --output-on-failure

# Run benchmarks (optional)
./build/bin/benchmarks/BM_LruCache
```

### Documentation

nfx-lrucache includes comprehensive API documentation generated with Doxygen.

#### 📚 Online Documentation

The complete API documentation is available online at:
**https://ronan-fdev.github.io/nfx-lrucache**

#### Building Documentation Locally

```bash
# Configure with documentation enabled
cmake .. -DCMAKE_BUILD_TYPE=Release -DNFX_LRUCACHE_BUILD_DOCUMENTATION=ON

# Build the documentation
cmake --build . --target documentation
```

#### Requirements

- **Doxygen** - Documentation generation tool
- **Graphviz Dot** (optional) - For generating class diagrams

#### Accessing Local Documentation

After building, open `./build/doc/html/index.html` in your web browser.

## Usage Examples

### Basic Cache Operations

```cpp
#include <iostream>
#include <string>
#include <nfx/memory/LruCache.h>

using namespace nfx::memory;

// Simple string cache
	LruCache<int, std::string> cache( 100 ); // Max 100 entries

	// Add entries
	cache.getOrCreate( 1, []() { return "John Doe"; } );
	cache.getOrCreate( 2, []() { return "Jane Smith"; } );

	// Retrieve entries
	if ( auto value = cache.tryGet( 1 ) )
	{
		std::cout << "Found: " << value->get() << std::endl;
	}

	// Cache with expiration
	LruCacheOptions options( 1000, std::chrono::seconds( 300 ) ); // 1000 max, 5 minutes TTL

	LruCache<std::string, std::string> sessionCache( options );
	sessionCache.getOrCreate( "user123", []() { return "Session Data"; } );
```

### Advanced Usage Patterns

```cpp
#include <chrono>
#include <memory>
#include <nfx/memory/LruCache.h>

using namespace nfx::memory;
using namespace std::chrono_literals;

// Database query cache
struct QueryResult
{
	std::vector<std::string> rows;
	std::chrono::system_clock::time_point timestamp;
};

	LruCacheOptions dbCacheOpts( 500, 10min ); // 500 max, 10 minute cache

	LruCache<std::string, QueryResult> queryCache( dbCacheOpts );

	// Cache miss with factory
	auto result = queryCache.getOrCreate( "SELECT * FROM users", []() {
		QueryResult qr;
		// Execute expensive database query
		qr.timestamp = std::chrono::system_clock::now();
		return qr;
	} );

	// Manual cache management
	queryCache.clear(); // Remove all entries
	std::cout << "Cache size: " << queryCache.size() << std::endl;
	std::cout << "Is empty: " << queryCache.isEmpty() << std::endl;

	// Cleanup expired entries
	queryCache.cleanupExpired();
```

### Real-World Applications

```cpp
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <nfx/memory/LruCache.h>

using namespace nfx::memory;

// API response cache
struct ApiResponse
{
	int statusCode;
	std::string body;
	std::map<std::string, std::string> headers;
};

class ApiClient
{
	LruCache<std::string, ApiResponse> responseCache_;

public:
	ApiClient() : responseCache_( 1000 ) {} // Cache 1000 responses

	ApiResponse Get( const std::string& url )
	{
		return responseCache_.getOrCreate( url, [&]() {
			// Expensive HTTP request only on cache miss
			return MakeHttpRequest( url );
		} );
	}

private:
	ApiResponse MakeHttpRequest( const std::string& url )
	{
		// Actual HTTP implementation
		return ApiResponse{ 200, "response body", {} };
	}
};

// Session manager with expiration
class SessionManager
{
	LruCache<std::string, std::string> sessions_;

public:
	SessionManager()
		: sessions_( LruCacheOptions( 10000, std::chrono::minutes( 30 ) ) ) // 10000 max, 30-min sessions
	{
	}

	void CreateSession( const std::string& sessionId, const std::string& userData )
	{
		sessions_.getOrCreate( sessionId, [&]() { return userData; } );
	}

	std::optional<std::string> GetSession( const std::string& sessionId )
	{
		if ( auto ref = sessions_.tryGet( sessionId ) )
		{
			return ref->get();
		}
		return std::nullopt;
	}
};
```

### Complete Example

```cpp
#include <iostream>
#include <chrono>
#include <string>

#include <nfx/memory/LruCache.h>

using namespace nfx::memory;
using namespace std::chrono_literals;

int main()
{
	// Basic cache usage
	LruCache<int, std::string> cache( 3 ); // Max 3 entries

	std::cout << "=== Basic Cache Operations ===" << std::endl;

	// Add entries with factory
	cache.getOrCreate( 1, []() { return "First"; } );
	cache.getOrCreate( 2, []() { return "Second"; } );
	cache.getOrCreate( 3, []() { return "Third"; } );

	std::cout << "Cache size: " << cache.size() << std::endl;

	// Access existing entry (cache hit)
	if ( auto value = cache.tryGet( 1 ) )
	{
		std::cout << "Key 1: " << value->get() << " (cache hit)" << std::endl;
	}

	// LRU eviction - adding 4th entry evicts least recently used
	cache.getOrCreate( 4, []() { return "Fourth"; } );
	std::cout << "After adding 4th entry, size: " << cache.size() << std::endl;

	// Key 2 was evicted (least recently used)
	if ( !cache.tryGet( 2 ) )
	{
		std::cout << "Key 2 was evicted (LRU)" << std::endl;
	}

	// Cache with expiration
	std::cout << "\n=== Cache with Expiration ===" << std::endl;

	LruCacheOptions options{ 100, 2s }; // 100 max entries, 2 second TTL

	LruCache<std::string, int> expiringCache( options );

	expiringCache.getOrCreate( "temp", []() { return 42; } );
	std::cout << "Added entry with 2s expiration" << std::endl;

	// Immediate access works
	if ( auto val = expiringCache.tryGet( "temp" ) )
	{
		std::cout << "Immediate access: " << val->get() << std::endl;
	}

	// Clean up
	cache.clear();
	std::cout << "\nCache cleared, is empty: " << cache.isEmpty() << std::endl;

	return 0;
}
```

**Sample Output:**

```
=== Basic Cache Operations ===
Cache size: 3
Key 1: First (cache hit)
After adding 4th entry, size: 3
Key 2 was evicted (LRU)

=== Cache with Expiration ===
Added entry with 2s expiration
Immediate access: 42

Cache cleared, is empty: 1
```

## Installation & Packaging

nfx-lrucache provides comprehensive packaging options for distribution.

### Package Generation

```bash
# Configure with packaging options
cmake .. -DCMAKE_BUILD_TYPE=Release \
		 -DNFX_LRUCACHE_PACKAGE_ARCHIVE=ON \
		 -DNFX_LRUCACHE_PACKAGE_DEB=ON \
		 -DNFX_LRUCACHE_PACKAGE_RPM=ON

# Generate binary packages
cmake --build . --target package
# or
cd build && cpack

# Generate source packages
cd build && cpack --config CPackSourceConfig.cmake
```

### Supported Package Formats

| Format      | Platform       | Description                        | Requirements |
| ----------- | -------------- | ---------------------------------- | ------------ |
| **TGZ/ZIP** | Cross-platform | Compressed archive packages        | None         |
| **DEB**     | Debian/Ubuntu  | Native Debian packages             | `dpkg-dev`   |
| **RPM**     | RedHat/SUSE    | Native RPM packages                | `rpm-build`  |
| **WiX**     | Windows        | Professional MSI installer         | `WiX 3.11+`  |
| **Source**  | Cross-platform | Source code distribution (TGZ+ZIP) | None         |

### Installation

```bash
# Linux (DEB-based systems)
sudo dpkg -i nfx-lrucache_*_amd64.deb

# Linux (RPM-based systems)
sudo rpm -ivh nfx-lrucache-*-Linux.rpm

# Windows
# Run the .exe installer with administrator privileges
nfx-lrucache-*-win64.exe

# Manual installation (extract archive)
tar -xzf nfx-lrucache-*-Linux.tar.gz -C /usr/local/
```

## Project Structure

```
nfx-lrucache/
├── benchmark/             # Performance benchmarks with Google Benchmark
├── cmake/                 # CMake modules and configuration
├── include/nfx/           # Public headers: LRU cache implementation
├── samples/               # Example usage and demonstrations
└── test/                  # Comprehensive unit tests with GoogleTest
```

## Performance

nfx-lrucache is optimized for high performance with:

- **O(1) cache operations** - constant time get, put, and eviction
- **Intrusive linked list** - minimal memory overhead and allocations
- **Efficient LRU tracking** - constant-time entry promotion on access
- **Thread-safe synchronization** - optimized mutex usage with minimal contention
- **Sliding expiration** - automatic cleanup of expired entries

For detailed performance metrics and benchmarks, see the [benchmark documentation](benchmark/README.md).

## Changelog

See the [changelog](CHANGELOG.md) for a detailed history of changes, new features, and bug fixes.

## License

This project is licensed under the MIT License.

## Dependencies

- **[GoogleTest](https://github.com/google/googletest)**: Testing framework (BSD 3-Clause License) - Development only
- **[Google Benchmark](https://github.com/google/benchmark)**: Performance benchmarking framework (Apache 2.0 License) - Development only

All dependencies are automatically fetched via CMake FetchContent when building tests or benchmarks.

---

_Updated on October 26, 2025_

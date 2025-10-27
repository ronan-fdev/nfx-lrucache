#==============================================================================
# nfx-lrucache - Top-level CMake configuration
#==============================================================================

#----------------------------------------------
# Project definition
#----------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(nfx-lrucache
	VERSION 1.0.5
	DESCRIPTION "High-performance C++20 thread-safe LRU cache with sliding expiration"
	HOMEPAGE_URL "https://github.com/ronan-fdev/nfx-lrucache"
	LANGUAGES CXX
)

#----------------------------------------------
# Installation prefix configuration
#----------------------------------------------

# Set default installation path to nfx/memory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	if(WIN32)
		set(CMAKE_INSTALL_PREFIX "C:/Program Files/nfx/memory" CACHE PATH "Installation directory" FORCE)
	else()
		set(CMAKE_INSTALL_PREFIX "/usr/local/nfx/memory" CACHE PATH "Installation directory" FORCE)
	endif()
	message(STATUS "Setting install prefix to '${CMAKE_INSTALL_PREFIX}'")
endif()

#----------------------------------------------
# Build type configuration
#----------------------------------------------

# Set default build type for single-config generators
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
	message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}' as none was specified")
endif()

# For multi-config generators (Visual Studio, Xcode), set available configurations
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel" CACHE STRING "Available build configurations" FORCE)
	message(STATUS "Multi-config generator detected: ${CMAKE_CONFIGURATION_TYPES}")
else()
	message(STATUS "Single-config generator - Build type: ${CMAKE_BUILD_TYPE}")
endif()

#----------------------------------------------
# Version configuration
#----------------------------------------------

set(NFX_LRUCACHE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR} CACHE INTERNAL "nfx-lrucache major version")
set(NFX_LRUCACHE_VERSION_MINOR ${PROJECT_VERSION_MINOR} CACHE INTERNAL "nfx-lrucache minor version")
set(NFX_LRUCACHE_VERSION_PATCH ${PROJECT_VERSION_PATCH} CACHE INTERNAL "nfx-lrucache patch version")
set(NFX_LRUCACHE_VERSION       ${PROJECT_VERSION}       CACHE INTERNAL "nfx-lrucache version")

#----------------------------------------------
# Project metadata
#----------------------------------------------

set(NFX_LRUCACHE_LICENSE "MIT")
set(NFX_LRUCACHE_LICENSE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")

#----------------------------------------------
# Testing setup
#----------------------------------------------

enable_testing()

#----------------------------------------------
# Build options
#----------------------------------------------

# --- Build components (header-only library) ---
option(NFX_LRUCACHE_BUILD_TESTS          "Build tests"                        ON )
option(NFX_LRUCACHE_BUILD_SAMPLES        "Build samples"                      ON )
option(NFX_LRUCACHE_BUILD_BENCHMARKS     "Build benchmarks"                   ON )
option(NFX_LRUCACHE_BUILD_DOCUMENTATION  "Build Doxygen documentation"        ON )

# --- Installation ---
option(NFX_LRUCACHE_INSTALL_PROJECT      "Install project"                    ON )

# --- Packaging ---
option(NFX_LRUCACHE_PACKAGE_SOURCE       "Enable source package generation"   ON )
option(NFX_LRUCACHE_PACKAGE_ARCHIVE      "Enable TGZ/ZIP package generation"  ON )
option(NFX_LRUCACHE_PACKAGE_DEB          "Enable DEB package generation"      ON )
option(NFX_LRUCACHE_PACKAGE_RPM          "Enable RPM package generation"      ON )
option(NFX_LRUCACHE_PACKAGE_WIX          "Enable WiX Windows installer (MSI)" ON )

#----------------------------------------------
# CMake modules configuration
#----------------------------------------------

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#----------------------------------------------
# Main configuration
#----------------------------------------------

include(nfxLruCacheBuildConfig)
include(nfxLruCacheDependencies)
include(nfxLruCacheSources)

#----------------------------------------------
# Installation and packaging
#----------------------------------------------

include(nfxLruCacheInstall)
include(nfxLruCachePackaging)

#----------------------------------------------
# Targets
#----------------------------------------------

add_subdirectory(test)
add_subdirectory(samples)
add_subdirectory(benchmark)
add_subdirectory(doc)

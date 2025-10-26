#==============================================================================
# nfx-lrucache - CMake Sources
#==============================================================================

#----------------------------------------------
# Conditional headers and sources
#----------------------------------------------

set(PUBLIC_HEADERS)

list(APPEND PUBLIC_HEADERS
	# --- LRU Cache headers ---
	${NFX_LRUCACHE_INCLUDE_DIR}/nfx/memory/LruCache.h

	# --- LRU Cache implementations ---
	${NFX_LRUCACHE_INCLUDE_DIR}/nfx/detail/memory/LruCache.inl
)

#----------------------------------------------
# Library definition
#----------------------------------------------

# --- Create header-only interface library ---
add_library(${PROJECT_NAME} INTERFACE)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

#----------------------------------------------
# Target properties
#----------------------------------------------

# --- Configure interface library ---
target_include_directories(${PROJECT_NAME}
	INTERFACE
		$<BUILD_INTERFACE:${NFX_LRUCACHE_INCLUDE_DIR}>
		$<INSTALL_INTERFACE:include>
)

# Set interface compile features for C++20
target_compile_features(${PROJECT_NAME}
	INTERFACE
		cxx_std_20
)

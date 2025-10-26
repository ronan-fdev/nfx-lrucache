/**
 * @file BM_LruCache.cpp
 * @brief Benchmark LruCache performance for cache operations
 */

#include <benchmark/benchmark.h>

#include <string>
#include <vector>

#include <nfx/memory/LruCache.h>

namespace nfx::memory::benchmark
{
	//=====================================================================
	// LruCache benchmark suite
	//=====================================================================

	//----------------------------------------------
	// Construction
	//----------------------------------------------

	static void BM_LruCache_Construction_Default( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			LruCache<int, std::string> cache;
			::benchmark::DoNotOptimize( cache );
		}
	}

	static void BM_LruCache_Construction_WithOptions( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			LruCacheOptions options{ 1000, std::chrono::minutes( 5 ) };
			LruCache<int, std::string> cache{ options };
			::benchmark::DoNotOptimize( cache );
		}
	}

	//----------------------------------------------
	// Cache operations - getOrCreate
	//----------------------------------------------

	static void BM_LruCache_GetOrCreate_NewEntry( ::benchmark::State& state )
	{
		LruCache<int, std::string> cache;
		int key{ 0 };

		for ( auto _ : state )
		{
			auto& value = cache.getOrCreate( key++, []() { return std::string{ "test_value" }; } );
			::benchmark::DoNotOptimize( value );
		}

		state.SetItemsProcessed( state.iterations() );
	}

	static void BM_LruCache_GetOrCreate_ExistingEntry( ::benchmark::State& state )
	{
		LruCache<int, std::string> cache;
		cache.getOrCreate( 42, []() { return std::string{ "cached_value" }; } );

		for ( auto _ : state )
		{
			auto& value = cache.getOrCreate( 42, []() { return std::string{ "should_not_create" }; } );
			::benchmark::DoNotOptimize( value );
		}

		state.SetItemsProcessed( state.iterations() );
	}

	static void BM_LruCache_GetOrCreate_WithConfig( ::benchmark::State& state )
	{
		LruCache<int, std::string> cache;
		int key{ 0 };

		for ( auto _ : state )
		{
			auto& value = cache.getOrCreate(
				key++,
				[]() { return std::string{ "configured_value" }; },
				[]( CacheEntry& entry ) {
					entry.slidingExpiration = std::chrono::minutes( 10 );
					entry.size = 100;
				} );
			::benchmark::DoNotOptimize( value );
		}

		state.SetItemsProcessed( state.iterations() );
	}

	//----------------------------------------------
	// Lookup - tryGet
	//----------------------------------------------

	static void BM_LruCache_TryGet_Hit( ::benchmark::State& state )
	{
		LruCache<int, std::string> cache;

		// Populate cache
		for ( int i = 0; i < 1000; ++i )
		{
			cache.getOrCreate( i, [i]() { return std::string{ "value_" + std::to_string( i ) }; } );
		}

		int key{ 0 };
		for ( auto _ : state )
		{
			auto result = cache.tryGet( key % 1000 );
			::benchmark::DoNotOptimize( result );
			key++;
		}

		state.SetItemsProcessed( state.iterations() );
	}

	static void BM_LruCache_TryGet_Miss( ::benchmark::State& state )
	{
		LruCache<int, std::string> cache;

		// Populate cache with some entries
		for ( int i = 0; i < 100; ++i )
		{
			cache.getOrCreate( i, [i]() { return std::string{ "value_" + std::to_string( i ) }; } );
		}

		int key{ 1000 };
		for ( auto _ : state )
		{
			auto result = cache.tryGet( key++ );
			::benchmark::DoNotOptimize( result );
		}

		state.SetItemsProcessed( state.iterations() );
	}

	//----------------------------------------------
	// Modification operations
	//----------------------------------------------

	static void BM_LruCache_Remove( ::benchmark::State& state )
	{
		for ( auto _ : state )
		{
			state.PauseTiming();
			LruCache<int, std::string> cache;
			for ( int i = 0; i < 1000; ++i )
			{
				cache.getOrCreate( i, [i]() { return std::string{ "value_" + std::to_string( i ) }; } );
			}
			state.ResumeTiming();

			bool removed = cache.remove( 500 );
			::benchmark::DoNotOptimize( removed );
		}

		state.SetItemsProcessed( state.iterations() );
	}

	static void BM_LruCache_Clear( ::benchmark::State& state )
	{
		const int numEntries = state.range( 0 );

		for ( auto _ : state )
		{
			state.PauseTiming();
			LruCache<int, std::string> cache;
			for ( int i = 0; i < numEntries; ++i )
			{
				cache.getOrCreate( i, [i]() { return std::string{ "value_" + std::to_string( i ) }; } );
			}
			state.ResumeTiming();

			cache.clear();
		}

		state.SetItemsProcessed( state.iterations() * numEntries );
	}

	//----------------------------------------------
	// State inspection
	//----------------------------------------------

	static void BM_LruCache_Size( ::benchmark::State& state )
	{
		LruCache<int, std::string> cache;
		for ( int i = 0; i < 1000; ++i )
		{
			cache.getOrCreate( i, [i]() { return std::string{ "value_" + std::to_string( i ) }; } );
		}

		for ( auto _ : state )
		{
			auto size = cache.size();
			::benchmark::DoNotOptimize( size );
		}

		state.SetItemsProcessed( state.iterations() );
	}

	static void BM_LruCache_IsEmpty( ::benchmark::State& state )
	{
		LruCache<int, std::string> cache;

		for ( auto _ : state )
		{
			auto empty = cache.isEmpty();
			::benchmark::DoNotOptimize( empty );
		}

		state.SetItemsProcessed( state.iterations() );
	}

	//----------------------------------------------
	// LRU eviction
	//----------------------------------------------

	static void BM_LruCache_LRU_Eviction( ::benchmark::State& state )
	{
		const int cacheSize = 100;
		LruCacheOptions options{ static_cast<std::size_t>( cacheSize ), std::chrono::hours( 1 ) };

		for ( auto _ : state )
		{
			state.PauseTiming();
			LruCache<int, std::string> cache{ options };
			// Fill cache to capacity
			for ( int i = 0; i < cacheSize; ++i )
			{
				cache.getOrCreate( i, [i]() { return std::string{ "value_" + std::to_string( i ) }; } );
			}
			state.ResumeTiming();

			// Add one more entry, triggering LRU eviction
			cache.getOrCreate( cacheSize, []() { return std::string{ "eviction_trigger" }; } );
			::benchmark::DoNotOptimize( cache );
		}

		state.SetItemsProcessed( state.iterations() );
	}

	static void BM_LruCache_LRU_Access_Pattern( ::benchmark::State& state )
	{
		const int cacheSize = 100;
		const int accessCount = 100;
		LruCacheOptions options{ static_cast<std::size_t>( cacheSize ), std::chrono::hours( 1 ) };

		for ( auto _ : state )
		{
			state.PauseTiming();
			LruCache<int, std::string> cache{ options };
			state.ResumeTiming();

			// Access pattern: 80% hit rate on hot keys
			for ( int i = 0; i < accessCount; ++i )
			{
				int key = ( i % 10 < 8 ) ? ( i % 20 ) : ( i % 200 );
				auto& value = cache.getOrCreate( key, [key]() { return std::string{ "value_" + std::to_string( key ) }; } );
				::benchmark::DoNotOptimize( value );
			}
		}

		state.SetItemsProcessed( state.iterations() * accessCount );
	}

	//----------------------------------------------
	// Expiration
	//----------------------------------------------

	static void BM_LruCache_CleanupExpired( ::benchmark::State& state )
	{
		const int numExpiredEntries = static_cast<int>( state.range( 0 ) );
		LruCacheOptions options{ 0, std::chrono::milliseconds( 0 ) }; // Instant expiration

		for ( auto _ : state )
		{
			state.PauseTiming();
			LruCache<int, std::string> cache{ options };

			// Add entries
			for ( int i = 0; i < numExpiredEntries; ++i )
			{
				cache.getOrCreate( i, [i]() { return std::string{ "value_" + std::to_string( i ) }; } );
			}

			// Entries expire instantly with zero expiration
			state.ResumeTiming();

			cache.cleanupExpired();
		}

		state.SetItemsProcessed( state.iterations() * numExpiredEntries );
	}

	//----------------------------------------------
	// Complex value types
	//----------------------------------------------

	static void BM_LruCache_ComplexValue_Vector( ::benchmark::State& state )
	{
		LruCache<int, std::vector<int>> cache;
		int key{ 0 };

		for ( auto _ : state )
		{
			auto& value = cache.getOrCreate( key++, []() {
				std::vector<int> data( 1000 );
				for ( int i = 0; i < 1000; ++i )
				{
					data[i] = i;
				}
				return data;
			} );
			::benchmark::DoNotOptimize( value );
		}

		state.SetItemsProcessed( state.iterations() );
		state.SetBytesProcessed( state.iterations() * 1000 * sizeof( int ) );
	}

	static void BM_LruCache_ComplexValue_String( ::benchmark::State& state )
	{
		LruCache<std::string, std::string> cache;
		int key{ 0 };

		for ( auto _ : state )
		{
			std::string keyStr = "key_" + std::to_string( key++ );
			auto& value = cache.getOrCreate( keyStr, []() {
				return std::string( 1000, 'x' );
			} );
			::benchmark::DoNotOptimize( value );
		}

		state.SetItemsProcessed( state.iterations() );
		state.SetBytesProcessed( state.iterations() * 1000 );
	}

	//----------------------------------------------
	// Realistic workload scenarios
	//----------------------------------------------

	static void BM_LruCache_Scenario_DatabaseCache( ::benchmark::State& state )
	{
		const int cacheSize = 100;
		const int uniqueKeys = 500;
		LruCacheOptions options{ static_cast<std::size_t>( cacheSize ), std::chrono::minutes( 5 ) };
		LruCache<int, std::string> cache{ options };

		int accessCounter{ 0 };
		for ( auto _ : state )
		{
			// Simulate database query cache with Zipf-like distribution
			int key = ( accessCounter % 10 == 0 ) ? ( accessCounter % uniqueKeys ) : ( accessCounter % ( cacheSize / 2 ) );

			auto& value = cache.getOrCreate( key, [key]() {
				return std::string{ "db_result_" + std::to_string( key ) };
			} );
			::benchmark::DoNotOptimize( value );
			accessCounter++;
		}

		state.SetItemsProcessed( state.iterations() );
	}

	static void BM_LruCache_Scenario_WebCache( ::benchmark::State& state )
	{
		const int cacheSize = 100;
		LruCacheOptions options{ static_cast<std::size_t>( cacheSize ), std::chrono::seconds( 30 ) };
		LruCache<std::string, std::string> cache{ options };

		std::vector<std::string> endpoints = {
			"/api/users",
			"/api/products",
			"/api/orders",
			"/api/analytics",
			"/api/reports" };

		int accessCounter{ 0 };
		for ( auto _ : state )
		{
			const auto& endpoint = endpoints[accessCounter % endpoints.size()];
			auto& response = cache.getOrCreate( endpoint, [&endpoint]() {
				return std::string{ "response_for_" + endpoint };
			} );
			::benchmark::DoNotOptimize( response );
			accessCounter++;
		}

		state.SetItemsProcessed( state.iterations() );
	}

	//=====================================================================
	// Benchmarks registration
	//=====================================================================

	//----------------------------------------------
	// Construction
	//----------------------------------------------

	BENCHMARK( BM_LruCache_Construction_Default );
	BENCHMARK( BM_LruCache_Construction_WithOptions );

	//----------------------------------------------
	// Cache operations - getOrCreate
	//----------------------------------------------

	BENCHMARK( BM_LruCache_GetOrCreate_NewEntry );
	BENCHMARK( BM_LruCache_GetOrCreate_ExistingEntry );
	BENCHMARK( BM_LruCache_GetOrCreate_WithConfig );

	//----------------------------------------------
	// Lookup - tryGet
	//----------------------------------------------

	BENCHMARK( BM_LruCache_TryGet_Hit );
	BENCHMARK( BM_LruCache_TryGet_Miss );

	//----------------------------------------------
	// Modification operations
	//----------------------------------------------

	BENCHMARK( BM_LruCache_Remove );
	BENCHMARK( BM_LruCache_Clear )
		->Arg( 10 )
		->Arg( 100 )
		->Arg( 1000 )
		->Arg( 10000 );

	//----------------------------------------------
	// State inspection
	//----------------------------------------------

	BENCHMARK( BM_LruCache_Size );
	BENCHMARK( BM_LruCache_IsEmpty );

	//----------------------------------------------
	// LRU eviction
	//----------------------------------------------

	BENCHMARK( BM_LruCache_LRU_Eviction );
	BENCHMARK( BM_LruCache_LRU_Access_Pattern );

	//----------------------------------------------
	// Expiration
	//----------------------------------------------

	BENCHMARK( BM_LruCache_CleanupExpired )
		->Arg( 10 )
		->Arg( 100 )
		->Arg( 1000 );

	//----------------------------------------------
	// Complex value types
	//----------------------------------------------

	BENCHMARK( BM_LruCache_ComplexValue_Vector );
	BENCHMARK( BM_LruCache_ComplexValue_String );

	//----------------------------------------------
	// Realistic workload scenarios
	//----------------------------------------------

	BENCHMARK( BM_LruCache_Scenario_DatabaseCache );
	BENCHMARK( BM_LruCache_Scenario_WebCache );
} // namespace nfx::memory::benchmark

BENCHMARK_MAIN();

# Benchmarks

---

## Test Environment

### Hardware Configuration

| Component                | Specification                                                 |
| ------------------------ | ------------------------------------------------------------- |
| **CPU**                  | 12th Gen Intel Core i7-12800H (20 logical, 14 physical cores) |
| **Base Clock**           | 2.80 GHz                                                      |
| **Turbo Clock**          | 4.80 GHz                                                      |
| **L1 Data Cache**        | 48 KiB (×6 P-cores) + 32 KiB (×8 E-cores)                     |
| **L1 Instruction Cache** | 32 KiB (×6 P-cores) + 64 KiB (×2 E-core clusters)             |
| **L2 Unified Cache**     | 1.25 MiB (×6 P-cores) + 2 MiB (×2 E-core clusters)            |
| **L3 Unified Cache**     | 24 MiB (×1 shared)                                            |
| **RAM**                  | DDR4-3200 (32GB)                                              |
| **GPU**                  | NVIDIA RTX A2000 4GB GDDR6                                    |

### Software Configuration

| Platform    | Benchmark Framework     | C++ Compiler              | nfx-lrucache Version |
| ----------- | ----------------------- | ------------------------- | -------------------- |
| **Linux**   | Google Benchmark v1.9.4 | GCC 14.2.0-x64            | v1.0.0               |
| **Linux**   | Google Benchmark v1.9.4 | Clang 19.1.7-x64          | v1.0.0               |
| **Windows** | Google Benchmark v1.9.4 | MinGW GCC 14.2.0-x64      | v1.0.0               |
| **Windows** | Google Benchmark v1.9.4 | Clang-GNU-CLI 19.1.5-x64  | v1.0.0               |
| **Windows** | Google Benchmark v1.9.4 | Clang-MSVC-CLI 19.1.5-x64 | v1.0.0               |
| **Windows** | Google Benchmark v1.9.4 | MSVC 19.44.35217.0-x64    | v1.0.0               |

---

# Performance Results

## LRU Cache Operations

| Operation                 | Linux GCC     | Linux Clang   | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ------------------------- | ------------- | ------------- | ----------------- | --------------------- | ---------------------- | ------------ |
| Construction_Default      | **14.7 ns**   | 16.2 ns       | 49.0 ns           | 118 ns                | 116 ns                 | 106 ns       |
| Construction_WithOptions  | **127 ns**    | 138 ns        | 331 ns            | 414 ns                | 339 ns                 | 526 ns       |
| GetOrCreate_NewEntry      | **84.3 ns**   | 93.1 ns       | 222 ns            | 367 ns                | 430 ns                 | 364 ns       |
| GetOrCreate_ExistingEntry | **35.7 ns**   | 38.9 ns       | 115 ns            | 57.6 ns               | 54.9 ns                | 60.6 ns      |
| GetOrCreate_WithConfig    | **112 ns**    | 119 ns        | 290 ns            | 444 ns                | 430 ns                 | 429 ns       |
| TryGet_Hit                | **37.1 ns**   | 37.3 ns       | 110 ns            | 64.1 ns               | 58.1 ns                | 58.7 ns      |
| TryGet_Miss               | **5.35 ns**   | 6.66 ns       | 18.4 ns           | 23.9 ns               | 21.5 ns                | 19.8 ns      |
| Remove                    | **9,026 ns**  | 9,791 ns      | 21,635 ns         | 16,521 ns             | 16,213 ns              | 17,692 ns    |
| Clear/10                  | **277 ns**    | 304 ns        | 619 ns            | 576 ns                | 564 ns                 | 579 ns       |
| Clear/100                 | **1,106 ns**  | 1,259 ns      | 2,442 ns          | 2,364 ns              | 2,025 ns               | 2,144 ns     |
| Clear/1000                | **9,363 ns**  | 9,872 ns      | 19,399 ns         | 16,437 ns             | 16,048 ns              | 16,970 ns    |
| Clear/10000               | **144,093 ns**| 150,956 ns    | 170,916 ns        | 189,165 ns            | 179,467 ns             | 190,216 ns   |
| Size                      | **2.91 ns**   | 3.06 ns       | 13.4 ns           | 15.9 ns               | 15.6 ns                | 16.9 ns      |
| IsEmpty                   | **2.91 ns**   | 3.31 ns       | 13.1 ns           | 15.4 ns               | 15.0 ns                | 16.4 ns      |
| LRU_Eviction              | **1,189 ns**  | 1,265 ns      | 2,189 ns          | 2,289 ns              | 2,041 ns               | 2,242 ns     |
| LRU_Access_Pattern        | **4,951 ns**  | 5,248 ns      | 11,537 ns         | 9,002 ns              | 8,748 ns               | 8,940 ns     |
| CleanupExpired/10         | **440 ns**    | 441 ns        | 981 ns            | 824 ns                | 793 ns                 | 815 ns       |
| CleanupExpired/100        | **2,504 ns**  | 2,802 ns      | 6,152 ns          | 4,956 ns              | 4,460 ns               | 4,663 ns     |
| CleanupExpired/1000       | **23,642 ns** | 25,945 ns     | 58,001 ns         | 46,317 ns             | 43,325 ns              | 45,162 ns    |
| ComplexValue_Vector       | **1,013 ns**  | 1,051 ns      | 1,694 ns          | 1,834 ns              | 1,813 ns               | 1,807 ns     |
| ComplexValue_String       | 580 ns        | **556 ns**    | 986 ns            | 821 ns                | 748 ns                 | 788 ns       |
| Scenario_DatabaseCache    | **42.1 ns**   | 45.5 ns       | 115 ns            | 62.2 ns               | 61.5 ns                | 63.5 ns      |
| Scenario_WebCache         | **38.5 ns**   | 44.0 ns       | 103 ns            | 65.4 ns               | 63.5 ns                | 67.5 ns      |

---

_Benchmarks executed on October 26, 2025_

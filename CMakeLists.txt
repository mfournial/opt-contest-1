cmake_minimum_required(VERSION 3.10)
link_directories(${Project_BINARY_DIR}/deps/lib)
include(ExternalProject)
add_executable(OptOne OptOne.cpp)
set_property(TARGET OptOne PROPERTY CXX_STANDARD 17)
ExternalProject_Add(googlebenchmark
	URL "https://github.com/google/benchmark/archive/v1.4.1.tar.gz"
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${Project_BINARY_DIR}/deps -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=Release
  )
add_dependencies(OptOne googlebenchmark)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(OptOne Threads::Threads)
target_link_libraries(OptOne ${Project_BINARY_DIR}/deps/lib/${CMAKE_SHARED_LIBRARY_PREFIX}benchmark.a)
target_link_libraries(OptOne ${Project_BINARY_DIR}/deps/lib/${CMAKE_SHARED_LIBRARY_PREFIX}benchmark_main.a)
target_link_libraries(OptOne /opt/intel/lib/libittnotify64.a)
target_link_libraries(OptOne dl)
target_include_directories(OptOne SYSTEM PUBLIC ${Project_BINARY_DIR}/deps/include)
target_include_directories(OptOne SYSTEM PUBLIC /opt/intel/include)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

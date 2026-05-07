cmake_minimum_required (VERSION 3.30)
include(FindPkgConfig)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

project (MutexShootout)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${BOOST_LIBRARYDIR})

if (UNIX)
	find_package(Threads)
	find_package(Boost COMPONENTS system REQUIRED)
endif()

add_executable(MutexShootout main.cpp MurmurHash3.cpp lru_cache.hpp MurmurHash3.h hashing.hpp alt_mutex.hpp stopwatch.hpp)

if(UNIX)
	target_link_libraries(MutexShootout ${Boost_SYSTEM_LIBRARY})
	target_link_libraries(MutexShootout ${CMAKE_THREAD_LIBS_INIT})
endif()

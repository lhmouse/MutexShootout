cmake_minimum_required (VERSION 2.6)
include(FindPkgConfig)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project (MutexShootout)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${BOOST_LIBRARYDIR})
	
if (UNIX)
	find_package(Threads)
	find_package(Boost COMPONENTS system REQUIRED)
endif()

if (WIN32)
	pkg_check_modules(mcfgthread mcfgthread)
endif()

add_executable(MutexShootout main.cpp MurmurHash3.cpp lru_cache.hpp MurmurHash3.h hashing.hpp alt_mutex.hpp stopwatch.hpp)

if(UNIX)
	target_link_libraries(MutexShootout ${Boost_SYSTEM_LIBRARY})
	target_link_libraries(MutexShootout ${CMAKE_THREAD_LIBS_INIT})
	set(CMAKE_BUILD_TYPE Release)
endif()

if (mcfgthread_FOUND)
	target_link_libraries(MutexShootout ${mcfgthread_LINK_LIBRARIES})
	target_compile_definitions(MutexShootout PUBLIC HAS_MCFGTHREAD)
endif()

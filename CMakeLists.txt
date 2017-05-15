cmake_minimum_required(VERSION 2.8)

set(TARGET remoto_wifi)
set(OS_TYPE_OPTION "$ENV{OS_TYPE}")
set(ARCH_TYPE_OPTION "$ENV{ARCH_TYPE}")
set(BUILD_TEST $ENV{BUILD_TESTS})
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: Debug Release")

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message(AUTHOR_WARNING "OS_LINUX")
  add_definitions(-DOS_LINUX)
  add_definitions(-DOS_POSIX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "QNX")
  message(AUTHOR_WARNING "OS_QNX")
  add_definitions(-DOS_QNX)
  add_definitions(-DOS_POSIX)
  set(RTLIB)
endif()

if (ARCH_TYPE_OPTION)
  if (NOT (${ARCH_TYPE_OPTION} STREQUAL "x86") AND NOT (${ARCH_TYPE_OPTION} STREQUAL "armv7"))
    message(AUTHOR_WARNING "HW architecture is not defined, using x86. Allowed values are x86/armv7 (case sensitive)")
    set(ARCH_TYPE_OPTION  "x86")
  endif ()
else ()
    set(ARCH_TYPE_OPTION  "x86")
endif()
# print HW type

project(${TARGET})

set(RTLIB rt)
set(COMPONENTS_DIR ${CMAKE_SOURCE_DIR}/components)

cmake_policy(PUSH)
# make link_directories() treat paths relative to the source dir
# info: cmake --help-policy CMP0015
cmake_policy(SET CMP0015 NEW)
cmake_policy(POP)

SET(CMAKE_C_FLAGS_DEBUG "-g")
SET(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
SET(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

# must be called before link_directories
include_directories (
  ${CMAKE_SOURCE_DIR}/components
)

# must be called before link_directories
add_subdirectory(3rd_party_static)
add_subdirectory(components)

LINK_DIRECTORIES(${LINK_DIRECTORIES} ${PROJECT_BINARY_DIR})

set(LIBRARIES
  Logger
  Utils
  Profile
)

set(TEST_APP_LIBRARIES
  Logger
  Utils
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  list(APPEND LIBRARIES pthread)
  list(APPEND LIBRARIES dl)
endif()

add_executable(${TARGET} main.c)
target_link_libraries(${TARGET} ${LIBRARIES})

add_executable(demo_app demo_app.c)
target_link_libraries(demo_app ${TEST_APP_LIBRARIES})


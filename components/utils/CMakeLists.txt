set(UTILS_DIR ${COMPONENTS_DIR}/utils)

file(GLOB SOURCES
  ${UTILS_DIR}/src/*
)

set(LIBRARIES
)

add_library("Utils" ${SOURCES})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_link_libraries("Utils" pthread ${RTLIB})
endif()

#target_link_libraries("Utils" ${LIBRARIES})
target_link_libraries("Utils")
set(LOGGER_DIR ${COMPONENTS_DIR}/logger)

file(GLOB SOURCES
  ${LOGGER_DIR}/src/*
)

set(LIBRARIES
)

add_library("Logger" ${SOURCES})

#target_link_libraries("Logger" ${LIBRARIES})
target_link_libraries("Logger")

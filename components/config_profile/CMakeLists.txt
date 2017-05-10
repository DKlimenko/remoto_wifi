set(PROFILE_DIR ${COMPONENTS_DIR}/config_profile)

file(GLOB SOURCES
  ${PROFILE_DIR}/src/*
)

set(LIBRARIES
  Utils
)

add_library("Profile" ${SOURCES})

#target_link_libraries("Profile" ${LIBRARIES})
target_link_libraries("Profile")

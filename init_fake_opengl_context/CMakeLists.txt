cmake_minimum_required(VERSION 2.8.3)
project(init_fake_opengl_context)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

find_package(GLEW)
find_package(OpenGL)
if((NOT GLEW_FOUND) OR (NOT OpenGL_FOUND))
  message(WARNING "init_fake_opengl_context: GLEW or OpenGL not found! Package won't be built!")
  message(WARNING "GLEW: ${GLEW_FOUND}")
  message(WARNING "OpenGL: ${OpenGL_FOUND}")
  catkin_package(
    CATKIN_DEPENDS roscpp
  )
  return()
endif()

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES init_fake_opengl_context
  CATKIN_DEPENDS roscpp
  DEPENDS GLEW OpenGL
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(init_fake_opengl_context
  src/fake_opengl_context.cpp
)

add_dependencies(init_fake_opengl_context ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(init_fake_opengl_context
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

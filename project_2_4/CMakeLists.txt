cmake_minimum_required(VERSION 3.10)
project(project_2_4)

set(CMAKE_CXX_STANDARD 17)

add_executable(light_controller project_2_4.cpp)

add_custom_target(
  copy_resources_to_build
  ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/test_cases/ $<TARGET_FILE_DIR:light_controller>/test_cases
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/runner.sh $<TARGET_FILE_DIR:light_controller>/runner.sh
  DEPENDS ${CMAKE_SOURCE_DIR}/runner.sh
)

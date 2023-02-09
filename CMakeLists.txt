cmake_minimum_required(VERSION 3.10)
project(MINI_LEVELDB VERSION 1.0.0 LANGUAGES C CXX DESCRIPTION "leetcode")

# for clangd, generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specified the language standard
# C standard can be overridden when this is used as a sub-project.
if(NOT CMAKE_C_STANDARD)
  # This project can use C11, but will gracefully decay down to C89.
  set(CMAKE_C_STANDARD 11)
  set(CMAKE_C_STANDARD_REQUIRED OFF)
  set(CMAKE_C_EXTENSIONS OFF)
endif(NOT CMAKE_C_STANDARD)

# C++ standard can be overridden when this is used as a sub-project.
if(NOT CMAKE_CXX_STANDARD)
  # This project requires C++11.
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

##--------------------- Compile Options ------------------------------------##
# Configure compile options
add_compile_options(-Wall)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

# message build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
  # Compile options for Debug variant
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
else( CMAKE_BUILD_TYPE STREQUAL "Release" )
  # Compile options for Release variant
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fopenmp")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

message(STATUS "Compile options for c++: ${CMAKE_CXX_FLAGS}")

##--------------------- Global Macros --------------------------------------##
# add_definitions(-DYOUR_MACRO_DEFINE)

##--------------------- Include directories --------------------------------##
# include_directories(.)

##--------------------- Source files ---------------------------------------##
aux_source_directory(src SRC)

##--------------------- Build target ---------------------------------------##
# Merge library
link_libraries(pthread)
add_library(
  leetcode
  ${SRC}
)
target_link_libraries(leetcode gtest gmock gtest_main)

##--------------------- Build unit tests -----------------------------------##
function(my_add_test TEST_FILE)
  get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
  add_executable(${TEST_NAME} ${TEST_FILE})
  # target_link_libraries(${TEST_NAME} gtest gtest_main benchmark)
  target_link_libraries(${TEST_NAME} leetcode)
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

function(add_dir_test DIR_PATH)
  file(GLOB CPP_SRC_LIST ${DIR_PATH}/*.cc)
  foreach(file ${CPP_SRC_LIST})
    # unit test
    my_add_test(${file})
  endforeach(file ${CPP_SRC_LIST})

  # Regression Testing
  add_executable("${DIR_PATH}-all-test" ${CPP_SRC_LIST})
  target_link_libraries("${DIR_PATH}-all-test" leetcode)
endfunction()

# google test
option(LEETCODE_ENABLE_TEST "Whether to enable unit tests" ON)
if (LEETCODE_ENABLE_TEST)
  message(STATUS "Unit tests enabled")
  enable_testing()
  add_subdirectory("third_party/googletest" EXCLUDE_FROM_ALL)
  include_directories("third_party/googletest/googletest/include")
  include_directories("third_party/googletest/googlemock/include")
  set(GTEST_LIB gtest gmock gtest_main)

  # add test
  add_dir_test(src)
endif()

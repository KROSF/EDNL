cmake_minimum_required(VERSION 3.1.3)

project(EDNL VERSION 0.2.3.3 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)
# --------------------------------------------------------------------------------
#                          Compile flags
# --------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")  
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
if(APPLE)
SET(CMAKE_CXX_FLAGS_DEBUG "-g -fstandalone-debug -O0")
else()
SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
endif()
message(STATUS "Building with the following extra flags: ${CMAKE_CXX_FLAGS}")

# --------------------------------------------------------------------------------
#                         Locate files
# --------------------------------------------------------------------------------
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/tests
    ${PROJECT_SOURCE_DIR}/external/googletest/googlemock
    ${PROJECT_SOURCE_DIR}/external/googletest/googlemock/include
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest/include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB TESTFILES "tests/*.cpp")
set(TEST_MAIN unit_tests.x)

# --------------------------------------------------------------------------------
#                            Build!
# --------------------------------------------------------------------------------
add_library( engine ${SOURCES})
add_executable(main.x app/main.cpp)
add_dependencies(main.x engine)
target_link_libraries(main.x engine)

add_executable(dijkstra.x app/dijkstra.cpp)
add_dependencies(dijkstra.x engine)
target_link_libraries(dijkstra.x engine)

add_executable(feat.x app/feat.cpp)
add_dependencies(feat.x engine)
target_link_libraries(feat.x engine)

add_executable(diam_center.x app/diam_center.cpp)
add_dependencies(diam_center.x engine)
target_link_libraries(diam_center.x engine)

add_executable(laberinto.x app/laberinto.cpp)
add_dependencies(laberinto.x engine)
target_link_libraries(laberinto.x engine)

add_executable(cemento.x app/cemento.cpp)
add_dependencies(cemento.x engine)
target_link_libraries(cemento.x engine)

# --------------------------------------------------------------------------------
#                         Make Tests
# --------------------------------------------------------------------------------
add_executable(${TEST_MAIN} ${TESTFILES})
add_dependencies(${TEST_MAIN} googletest googlemock engine)
target_link_libraries(${TEST_MAIN} googletest googlemock engine pthread)
add_custom_target(gtest 
    COMMAND "${PROJECT_BINARY_DIR}/${TEST_MAIN}"
    DEPENDS engine ${TEST_MAIN})
include(CTest)
enable_testing()
add_test(unit_tests ${PROJECT_BINARY_DIR}/${TEST_MAIN})

# --------------------------------------------------------------------------------
#                         Code Coverage
# --------------------------------------------------------------------------------
include(CodeCoverage)

# --------------------------------------------------------------------------------
#                         Google Test (no change needed).
# --------------------------------------------------------------------------------
add_custom_target( git_update
    COMMAND git submodule init
    COMMAND git submodule update
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} )
add_library( googletest
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest/src/gtest_main.cc )
add_library( googlemock
    ${PROJECT_SOURCE_DIR}/external/googletest/googlemock/src/gmock-all.cc
    ${PROJECT_SOURCE_DIR}/external/googletest/googlemock/src/gmock_main.cc )
add_dependencies(googletest git_update)
add_dependencies(googlemock git_update)
set_source_files_properties(${PROJECT_SOURCE_DIR}/external/googletest/googletest/src/gtest-all.cc  PROPERTIES GENERATED 1)
set_source_files_properties(${PROJECT_SOURCE_DIR}/external/googletest/googletest/src/gtest_main.cc PROPERTIES GENERATED 1)
set_source_files_properties(${PROJECT_SOURCE_DIR}/external/googletest/googlemock/src/gmock-all.cc  PROPERTIES GENERATED 1)
set_source_files_properties(${PROJECT_SOURCE_DIR}/external/googletest/googlemock/src/gmock_main.cc PROPERTIES GENERATED 1)
# --------------------------------------------------------------------------------
#                            Misc
# --------------------------------------------------------------------------------
configure_file (
  "${PROJECT_SOURCE_DIR}/include/configversion.h.in"
  "${PROJECT_BINARY_DIR}/configversion.h")

file(GLOB FILES "${PROJECT_SOURCE_DIR}/files/arboles/*.txt")
file(COPY ${FILES} DESTINATION "${PROJECT_BINARY_DIR}/files/arboles/")
file(GLOB FILES "${PROJECT_SOURCE_DIR}/files/grafos/*.txt")
file(COPY ${FILES} DESTINATION "${PROJECT_BINARY_DIR}/files/grafos/")

include_directories("${PROJECT_BINARY_DIR}")
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

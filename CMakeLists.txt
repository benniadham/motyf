cmake_minimum_required(VERSION 3.22)

# Set the project name
project(motyf VERSION 0.0.1)

# Set path variables
set(ROOT_DIR ${PROJECT_SOURCE_DIR})
set(INC_DIR ${ROOT_DIR}/include)
set(SRC_DIR ${ROOT_DIR}/source)
set(TEST_DIR ${ROOT_DIR}/tests) 

# Add source files
file(GLOB SOURCES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${INC_DIR}/*.hpp)

# Create libltd.a static library
add_library(motyf STATIC ${SOURCES})
target_include_directories(motyf PUBLIC ${INC_DIR})

# Create test executable test_unit
add_executable(rex ${TEST_DIR}/rex.cpp)
target_include_directories(rex PUBLIC ${INC_DIR})
target_link_libraries(rex motyf)

# Create test executable test_unit
add_executable(scanner ${TEST_DIR}/scanner.cpp)
target_include_directories(scanner PUBLIC ${INC_DIR})
target_link_libraries(scanner motyf ltd)


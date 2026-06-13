cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(Focus_Analysis)

find_package(ROOT CONFIG REQUIRED)

# Locate sources and headers for this project
#

include_directories(${PROJECT_SOURCE_DIR}/Inc)

file(GLOB sources ${PROJECT_SOURCE_DIR}/Src/*.cpp ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/Inc/*.h  ${PROJECT_SOURCE_DIR}/*.h)

# ---Build executable------------------------------------------------------------
add_executable(main main.cpp ${sources} ${headers})
target_link_libraries(main  ${ROOT_LIBRARIES})
target_include_directories(main SYSTEM PUBLIC ${ROOT_INCLUDE_DIRS})


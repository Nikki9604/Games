cmake_minimum_required(VERSION 3.10)
project(BowlingGame)

# Executable and sources
set(BOWLING_EXECUTABLE bowling)
set(BOWLING_SRC
    src/Bowling_main.cpp
    src/Bowling.cpp
)

# Create executable
add_executable(${BOWLING_EXECUTABLE} ${BOWLING_SRC})

# Include directories
target_include_directories(${BOWLING_EXECUTABLE} PUBLIC include)

# Link pthread library
find_package(Threads REQUIRED)
target_link_libraries(bowling PRIVATE Threads::Threads)

# Copy master file
if(EXISTS ${CMAKE_SOURCE_DIR}/include/master)
    configure_file(include/master ${CMAKE_BINARY_DIR}/master COPYONLY)
endif()
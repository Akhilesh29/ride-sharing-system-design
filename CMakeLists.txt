cmake_minimum_required(VERSION 3.10)
project(RideSharing)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable IDE folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add source files
set(SOURCES
    src/main.cpp
    src/RideManager.cpp
    src/models/Location.cpp
    src/models/User.cpp
    src/models/Trip.cpp
)

# Add header files
set(HEADERS
    src/RideManager.hpp
    src/models/Location.hpp
    src/models/User.hpp
    src/models/Trip.hpp
)

# Create source groups for better organization in Visual Studio
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

# Create executable
add_executable(ride_sharing ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(ride_sharing PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Set startup project in Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ride_sharing) 
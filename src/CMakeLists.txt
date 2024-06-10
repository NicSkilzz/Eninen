cmake_minimum_required(VERSION 3.10)
project(Eninen)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

add_executable(foo foo.cpp)
target_link_libraries(foo ${wxWidgets_LIBRARIES})
cmake_minimum_required(VERSION 3.10)
project(Eninen)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

include_directories(${wxWidgets_INCLUDE_DIRS})
include_directories(include)

add_executable(chess src/gui/app.cpp src/gui/frame.cpp src/gui/square_panel.cpp src/gui/board_panel.cpp src/move.cpp src/chess_board.cpp src/chess_piece.cpp)
target_link_libraries(chess ${wxWidgets_LIBRARIES})
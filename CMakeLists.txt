cmake_minimum_required(VERSION 3.10)
project(Eninen)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

add_executable(chess src/gui/app.cpp src/gui/frame.cpp src/gui/board_panel.cpp src/chess_board.cpp src/chess_piece src/moves)
target_link_libraries(chess ${wxWidgets_LIBRARIES})
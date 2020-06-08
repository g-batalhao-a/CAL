cmake_minimum_required(VERSION 3.15)
project(Entrega_II)

set(CMAKE_CXX_STANDARD 14)
# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
link_libraries(ws2_32 wsock32)
include_directories(src)
include_directories(Mapas)

add_executable(Entrega_II main.cpp src/graph/Graph.h src/menu/menus.cpp src/util/utils.cpp src/prison/Prisoner.cpp
        src/graphviewer/connection.cpp src/graphviewer/edgetype.h src/graphviewer/graphviewer.cpp
        src/util/Parser.cpp src/gui/GUI.cpp src/graph/Path.h src/graph/Path.cpp src/prison/Vehicle.cpp src/prison/Vehicle.h src/util/Time.h src/util/Time.cpp)
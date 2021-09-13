cmake_minimum_required(VERSION 3.5)

project(Test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCE_LIST
  main.cpp
  
  vis/graphscene.cpp
  vis/graphview.cpp
  vis/node.cpp
  vis/edge.cpp

  core/vis/displaynode.cpp
)

set(INCLUDE_LIST
  vis/graphscene.h
  vis/graphview.h
  vis/node.h
  vis/edge.h

  core/vis/displaynode.cpp
)

qt5_add_resources(SOURCE_LIST vis/res/res.qrc)

add_executable(Test
  ${SOURCE_LIST}
  ${INCLUDE_LIST}
)

target_link_libraries(Test PRIVATE Qt5::Widgets)

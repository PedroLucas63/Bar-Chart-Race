cmake_minimum_required(VERSION 3.10)
project(barchart VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(config/BarChartConfig.h.in BarChartConfig.h)
include_directories(barchart PUBLIC "${PROJECT_BINARY_DIR}")

set(PROJECT_SOURCE_DIR src/)

include_directories("${PROJECT_SOURCE_DIR}/classes"
"${PROJECT_SOURCE_DIR}/functions/clioptions"
"${PROJECT_SOURCE_DIR}/functions/utils"
"${PROJECT_SOURCE_DIR}/libs/format"
"${PROJECT_SOURCE_DIR}/libs/fileini")

add_executable(barchart ${PROJECT_SOURCE_DIR}/main.cpp
                    ${PROJECT_SOURCE_DIR}/classes/Bar.cpp
                    ${PROJECT_SOURCE_DIR}/classes/BarChart.cpp
                    ${PROJECT_SOURCE_DIR}/classes/GameController.cpp
                    ${PROJECT_SOURCE_DIR}/functions/clioptions/clioptions.cpp
                    ${PROJECT_SOURCE_DIR}/libs/fileini/fileini.cpp
                    ${PROJECT_SOURCE_DIR}/libs/format/fstring.cpp)

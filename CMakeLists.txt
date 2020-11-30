cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 17) # c++17以上支持Template argument deduction for class templates,c++17以下可以显示声明使用，参考：https://gcc.gnu.org/projects/cxx-status.html
set (CMAKE_CXX_COMPILER /usr/bin/clang++-11) # 指定clang++编译，使用c++17的标准的话gcc需要8以上的版本，参考：https://gcc.gnu.org/projects/cxx-status.html
project (Util)
include_directories(${CMAKE_JS_INC} ${CMAKE_CURRENT_SOURCE_DIR}/src/includes/)
file(GLOB SOURCE_FILES ./src/main.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
# Include N-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE NODE_ADDON_API_DIR
  )

string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_JS_LIB})
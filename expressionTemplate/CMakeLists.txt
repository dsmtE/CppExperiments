# ///////////////////////////////// SETTINGS //////////////////////////////////

# Set standards
cmake_minimum_required(VERSION 3.0)
project(expressionTemplate C CXX)
set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

file(GLOB_RECURSE MY_SOURCES "src/*")
FOREACH(item ${MY_SOURCES}) #remove 
  IF(${item} MATCHES "src/main*")
    LIST(REMOVE_ITEM MY_SOURCES ${item})
  ENDIF(${item} MATCHES "src/main*")
ENDFOREACH(item)

# /////////////////////////////////// BUILD ///////////////////////////////////

file(GLOB_RECURSE MAIN_FILES src/main*.cpp)
foreach(MAIN_FILE ${MAIN_FILES})

    get_filename_component(FILE_NAME ${MAIN_FILE} NAME_WE)
    add_executable(${FILE_NAME} ${MAIN_FILE} ${MY_SOURCES})

endforeach()
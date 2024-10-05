aux_source_directory(. SRC_LoggerManager_DIR)

INCLUDE_DIRECTORIES(./)
include_directories(${PROJECT_SOURCE_DIR}/App/ABCInclude)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(LoggerManager SHARED
    ${SRC_LoggerManager_DIR}
    LoggerManager.h
    LoggerManager_global.h
)

target_link_libraries(LoggerManager PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(LoggerManager PRIVATE LOGGERMANAGER_LIBRARY)

set(LIBRARY_OUTPUT_PATH ${BUILD_SHARED_LIBS_DIR})

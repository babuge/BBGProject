aux_source_directory(. SRC_PluginsManager_DIR)

INCLUDE_DIRECTORIES(./)
include_directories(${PROJECT_SOURCE_DIR}/App/ABCInclude)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(PluginsManager SHARED
    ${SRC_PluginsManager_DIR}
    PluginsStatusCheck.h
    PluginsManager.h
    PluginsManager_global.h
    PluginsManager_zh_CN.ts
    PluginSpace.h
    PluginsStatusCheck.cpp
)

target_link_libraries(PluginsManager PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(PluginsManager PRIVATE PLUGINSMANAGER_LIBRARY)

set(LIBRARY_OUTPUT_PATH ${BUILD_SHARED_LIBS_DIR})

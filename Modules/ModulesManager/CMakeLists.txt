aux_source_directory(. SRC_MODULESMANAGER_DIR)

INCLUDE_DIRECTORIES(./)
include_directories(${PROJECT_SOURCE_DIR}/App/ABCInclude)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(ModulesManager SHARED
    ${SRC_MODULESMANAGER_DIR}
    ModulesManager.h
    ModulesManager_global.h
    ModulesManager_zh_CN.ts
)

target_link_libraries(ModulesManager PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(ModulesManager PRIVATE MODULESMANAGER_LIBRARY)

set(LIBRARY_OUTPUT_PATH ${BUILD_SHARED_LIBS_DIR})


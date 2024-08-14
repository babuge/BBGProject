aux_source_directory(. SRC_ResourceManagerModule_DIR)

INCLUDE_DIRECTORIES(./)
include_directories(${PROJECT_SOURCE_DIR}/App/ABCInclude)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(ResourceManagerModule SHARED
    ${SRC_ResourceManagerModule_DIR}
    ResourceManagerModule.h
    ResourceManagerModule_global.h
    ResourceManagerModule_zh_CN.ts
)

target_link_libraries(ResourceManagerModule PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(ResourceManagerModule PRIVATE RESOURCEMANAGERMODULE_LIBRARY)

set(LIBRARY_OUTPUT_PATH ${BUILD_SHARED_LIBS_DIR})


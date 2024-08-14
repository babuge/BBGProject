aux_source_directory(. SRC_TryModule_DIR)

INCLUDE_DIRECTORIES(./)
include_directories(${PROJECT_SOURCE_DIR}/App/ABCInclude)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(TryModule SHARED
    ${SRC_TryModule_DIR}
    TryModule.h
    TryModule_global.h
    TryModule_zh_CN.ts


)

target_link_libraries(TryModule PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(TryModule PRIVATE TRYMODULE_LIBRARY)

set(LIBRARY_OUTPUT_PATH ${BUILD_SHARED_LIBS_DIR})

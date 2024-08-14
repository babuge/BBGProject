aux_source_directory(. SRC_BUSSINESSMODULE_DIR)

INCLUDE_DIRECTORIES(./)
include_directories(${PROJECT_SOURCE_DIR}/App/ABCInclude)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(BussinessModule SHARED
    ${SRC_BUSSINESSMODULE_DIR}
    BussinessModule.h
    BussinessModule_global.h
    BussinessModule_zh_CN.ts
)

target_link_libraries(BussinessModule PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(BussinessModule PRIVATE BUSSINESSMODULE_LIBRARY)

set(LIBRARY_OUTPUT_PATH ${BUILD_SHARED_LIBS_DIR})

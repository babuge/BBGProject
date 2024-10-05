find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(APP_DIR ${PROJECT_SOURCE_DIR}/App)
include_directories(${APP_DIR}/ABCInclude)
include_directories(${APP_DIR}/EntryExtends)
include_directories(${APP_DIR}/UiFrame)
# 导入库头文件
include_directories(${APP_DIR}/../Modules/ModulesManager)
include_directories(${APP_DIR}/../Modules/BussinessModule)
include_directories(${APP_DIR}/../Modules/ResourceManagerModule)
include_directories(${APP_DIR}/../Modules/TryModule)
include_directories(${APP_DIR}/../Plugins/PluginsManager)

source_group("App")
set(PROJECT_SOURCES
        ${APP_DIR}/ABCInclude/CommonBase.h
        ${APP_DIR}/ABCInclude/FramWorkExtend.h
        ${APP_DIR}/ABCInclude/IBaseExport.h
        ${APP_DIR}/ABCInclude/ResouceLoadCommon.h
        ${APP_DIR}/ABCInclude/TryUtil.h
        ${APP_DIR}/ABCInclude/GlobalDef.h
        ${APP_DIR}/EntryExtends/BootstrapEntry.cpp
        ${APP_DIR}/EntryExtends/BootstrapEntry.h
        ${APP_DIR}/EntryExtends/MainConfig.cpp
        ${APP_DIR}/EntryExtends/MainConfig.h
        ${APP_DIR}/main.cpp
        ${APP_DIR}/MainWindow.cpp
        ${APP_DIR}/MainWindow.h
        ${APP_DIR}/MainWindow.ui
)

# add subDir, resources
add_subdirectory(${APP_DIR}/UiFrame)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_resources(QRC_TRAGET ${APP_DIR}/res.qrc)
    qt_add_executable(App
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES} ${QRC_TRAGET}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET cmake_ui APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(${QT_VERSION_MAJOR} GREATER_EQUAL 5)
        qt5_add_resources(QRC_TRAGET ${APP_DIR}/res.qrc)
    endif()
    if(ANDROID)
        add_library(App SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(App
            ${PROJECT_SOURCES} ${QRC_TRAGET}
        )
    endif()
endif()

if(WIN32)
    target_link_libraries(App
        PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libgtest.dll
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libPluginsManager.dll
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libTryModule.dll
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libBussinessModule.dll
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libModulesManager.dll
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libResourceManagerModule.dll
    )
elseif(UNIX)
    target_link_libraries(App
        PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libgtest.so
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libPluginsManager.so
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libTryModule.so
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libBussinessModule.so
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libModulesManager.so
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libResourceManagerModule.so
    )
endif()

set_target_properties(App PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS App
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(EXECUTABLE_OUTPUT_PATH ${BUILD_APP_DIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(App)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${PROJECT_SOURCE_DIR}/App/ABCInclude)
include_directories(${PROJECT_SOURCE_DIR}/App/EntryExtends)
include_directories(${PROJECT_SOURCE_DIR}/Modules/ModulesManager)
include_directories(${PROJECT_SOURCE_DIR}/Modules/BussinessModule)
include_directories(${PROJECT_SOURCE_DIR}/Modules/ResourceManagerModule)
include_directories(${PROJECT_SOURCE_DIR}/Modules/TryModule)
include_directories(${PROJECT_SOURCE_DIR}/Plugins/PluginsManager)


set(PROJECT_SOURCES
        ABCInclude/CommonBase.h
        ABCInclude/FramWorkExtend.h
        ABCInclude/IBaseExport.h
        ABCInclude/ResouceLoadCommon.h
        ABCInclude/TryUtil.h
        ABCInclude/GlobalDef.h
        EntryExtends/BootstrapEntry.cpp
        EntryExtends/BootstrapEntry.h
        EntryExtends/MainConfig.cpp
        EntryExtends/MainConfig.h
        App_zh_CN.ts
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BBGProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET cmake_ui APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BBGProject SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BBGProject
            ${PROJECT_SOURCES}
        )
    endif()
endif()

if(WIN32)
    target_link_libraries(BBGProject
        PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libgtest.dll
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libPluginsManager.dll
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libTryModule.dll
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libBussinessModule.dll
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libModulesManager.dll
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libResourceManagerModule.dll
    )
elseif(UNIX)
    target_link_libraries(BBGProject
        PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libgtest.so
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libPluginsManager.so
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libTryModule.so
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libBussinessModule.so
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libModulesManager.so
        PRIVATE ${BUILD_SHARED_LIBS_DIR}/libResourceManagerModule.so
    )
endif()

set_target_properties(BBGProject PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS BBGProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BBGProject)
endif()

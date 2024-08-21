cmake_minimum_required(VERSION 3.5)
project(BBGProject VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 3rdparty libraray
set(DIR_3RDPARTY_LIBRARAY ${GoogleTestApp_SOURCE_DIR}/3rdparty)
set(DIR_3RDPARTY_GTEST ${DIR_3RDPARTY_LIBRARAY}/GTest-1.8.x)
include_directories(${DIR_3RDPARTY_GTEST}/include)
if(WIN32)
   if(MINGW)
        set(DIR_3RDPARTY_GTEST_LIB ${DIR_3RDPARTY_GTEST}/lib/mingw/libgtest.dll)
   else()
        set(DIR_3RDPARTY_GTEST_LIB ${DIR_3RDPARTY_GTEST}/lib/win/libgtest.dll)
   endif()
elseif(UNIX)
    set(DIR_3RDPARTY_GTEST_LIB ${DIR_3RDPARTY_GTEST}/lib/linux/libgtest.so)
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy ${DIR_3RDPARTY_GTEST_LIB} ${BBGProject_SOURCE_DIR}/Build/App/lib/
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BBGProject_SOURCE_DIR}/Build
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BBGProject_SOURCE_DIR}/Build/App
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BBGProject_SOURCE_DIR}/Build/App/lib
    COMMAND ${CMAKE_COMMAND} -E copy ${BBGProject_SOURCE_DIR}/.config.json ${BBGProject_SOURCE_DIR}/Build/App/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${BBGProject_SOURCE_DIR}/QtLibs/ ${BBGProject_SOURCE_DIR}/Build/App/lib/
)

set(CMAKE_LIBRARY_PATH ${BBGProject_SOURCE_DIR}/Build/App/lib)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(CMAKE_PREFIX_PATH ${BBGProject_SOURCE_DIR}/Build)
set(BUILD_SHARED_LIBS_DIR ${BBGProject_SOURCE_DIR}/Build/App/lib)


add_subdirectory(Modules)
add_subdirectory(Plugins)
add_subdirectory(App)


cmake_minimum_required(VERSION 3.5)
project(App VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3rdparty libraray
set(DIR_THIRDPARTY_LIBRARAY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)
set(DIR_THIRDPARTY_GTEST ${DIR_THIRDPARTY_LIBRARAY}/GTest-1.8.x)
include_directories(${DIR_THIRDPARTY_GTEST}/include)
if(WIN32)
   if(MINGW)
        set(DIR_THIRDPARTY_GTEST_LIB ${DIR_THIRDPARTY_GTEST}/lib/mingw/libgtest.dll)
   else()
        set(DIR_THIRDPARTY_GTEST_LIB ${DIR_THIRDPARTY_GTEST}/lib/win/libgtest.dll)
   endif()
elseif(UNIX)
    set(DIR_THIRDPARTY_GTEST_LIB ${DIR_THIRDPARTY_GTEST}/lib/linux/libgtest.so)
endif()


execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/build
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/build/App
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/build/lib
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/.config.json ${CMAKE_CURRENT_SOURCE_DIR}/build/App/
    # copy thirdparty libraray
    COMMAND ${CMAKE_COMMAND} -E copy ${DIR_THIRDPARTY_GTEST_LIB} ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/
)

set(CMAKE_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/lib)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(BUILD_APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(BUILD_SHARED_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/lib)


add_subdirectory(Modules)
add_subdirectory(Plugins)
add_subdirectory(App)



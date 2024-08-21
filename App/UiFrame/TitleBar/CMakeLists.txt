# 将所有资源文件赋给SRC_TitleBar_DIR

set(SRC_TitleBar_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/CBtnOnlyIcon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MainTitleBar.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TitleBar.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CBtnOnlyIcon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MainTitleBar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TitleBar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MainTitleBar.ui
)

# 将当前目录源文件追加到PROJECT_SOURCES
list(APPEND SRC_UiFrame_DIR ${SRC_TitleBar_DIR})
# SRC_UiFrame_DIR 能被根目录访问
set(SRC_UiFrame_DIR ${SRC_UiFrame_DIR} PARENT_SCOPE)



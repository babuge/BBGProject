#添加子目录
add_subdirectory(TitleBar)

source_group("App\\\\UiFrame" "UiFrame\\\\TitleBar")
# 将所有资源文件赋给SRC_UiFrame_DIR
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_UiFrame_DIR)
# 将当前目录源文件追加到PROJECT_SOURCES
list(APPEND PROJECT_SOURCES ${SRC_UiFrame_DIR})
# SRC_UiFrame_DIR 能被根目录访问
set(PROJECT_SOURCES ${PROJECT_SOURCES} PARENT_SCOPE)

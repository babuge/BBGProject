QT -= gui

TEMPLATE = lib
DEFINES += TRYMODULE_LIBRARY

CONFIG += c++11
CONFIG -= c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($${ProConfig}/ModuleConfig.pri)

SOURCES += \
        TryModule.cpp

HEADERS += \
        TryModule.h \
        TryModule_global.h \
        BaseExport.h
	
TRANSLATIONS += \
    TryModule_zh_CN.ts

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

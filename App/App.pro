QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG -= c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/UiFrame/UiFrame.pri)

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    EntryExtends/MainConfig.cpp \
    EntryExtends/BootstrapEntry.cpp


HEADERS += \
    ABCInclude/CommonBase.h \
    ABCInclude/GlobalDef.h \
    ABCInclude/IBaseExport.h \
    ABCInclude/ResouceLoadCommon.h \
    MainWindow.h \
    ABCInclude/FramWorkExtend.h \
    EntryExtends/MainConfig.h \
    EntryExtends/BootstrapEntry.h \
    ABCInclude/TryUtil.h

FORMS += \
        MainWindow.ui

TRANSLATIONS += \
    App_zh_CN.ts

CONFIG += lrelease
CONFIG += embed_translations

TARGET = Framework

DESTDIR = $${OUTDIR}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += \
    $$PWD/ABCInclude \
    $$PWD/UiFrame \
    $${ProjectRootDir}/Modules/BussinessModule \
    $${ProjectRootDir}/Modules/ModulesManager \
    $${ProjectRootDir}/Modules/ResourceManagerModule \
    $${ProjectRootDir}/Modules/TryModule \
    $${ProjectRootDir}/Plugins/PluginsManager

DEPENDPATH += \
    $${OUTDIR}/lib
    
win32-msvc{
    QMAKE_CXXFLAGS += /utf-8
    LibPath = $$absolute_path($${OUTDIR}/lib/*.dll)
    FileList = $$files($${LibPath})
    FileList = $$replace(FileList, '$${OUTDIR}/lib/', '')
    FileList = $$replace(FileList, '\.dll', '')
    dllList = $$join(FileList, " -l", -l)
    for(var, $$list($${dllList})) {
        item = $${var}
        LIBS += -L$${OUTDIR}/lib/ $${item}
    }

}

unix:!mac{
    LibPath = $$absolute_path($${OUTDIR}/lib/*.so)
    FileList = $$files($${LibPath})
    FileList = $$replace(FileList, '$${OUTDIR}/lib/lib', '')
    FileList = $$replace(FileList, '\.so', '')
    dllList = $$join(FileList, " -l", -l)
    for(var, $$list($${dllList})) {
        item = $${var}
        LIBS += -L$${OUTDIR}/lib/ $${item}
    }
}

RESOURCES += \
    res.qrc


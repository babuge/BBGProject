ABCIncludeDir = $${ProjectRootDir}/App/ABCInclude

INCLUDEPATH += \
    $${ABCIncludeDir}

DESTDIR = $${OUTLIBSDIR}

win32-msvc{
    QMAKE_CXXFLAGS += /utf-8
}

unix:!mac{
    QMAKE_LFLAGS += -Wl,--rpath='$${OUTDIR}/lib'
}


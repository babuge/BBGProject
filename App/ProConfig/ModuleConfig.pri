win32-msvc {
    QMAKE_CXXFLAGS += /utf-8
}

ABCIncludeDir = $${AppDir}/ABCInclude

INCLUDEPATH += \
    $${ABCIncludeDir}

DESTDIR = $${OUTLIB}

unix:!mac{
    QMAKE_LFLAGS += -Wl,--rpath='$${OUTDIR}/lib'
}


defineReplace(headersLibCopyFunc) {
    var1 = $$1
    var2 = $$2
    variable = $$3

    includedir = $$clean_path("$$var1$$escape_expand(/)$$var2$$escape_expand(/)")
    headers = $$unique(variable)

    includedir = $$system_path($$includedir)
    headers = $$system_path($$headers)

    !exists($$includedir)
    {
        mkpath("$$includedir")
        !exists($$includedir):return (true)
    }

    for(header, $$list($${headers})){
        exists(header)
        {
            cpLink = "$$QMAKE_COPY $$system_path($$header) $$system_path($$includedir)$$escape_expand(\\n)"
            RESULT_CODE = $$system("$${cpLink}")
        }
    }

    return (true)
}

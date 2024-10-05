
win32-msvc {
    QMAKE_CXXFLAGS += /utf-8
}


DESTDIR = $${OUTDIR}

if(win32){
    if (msvc | mingw){
        LibPath = $$absolute_path($${OUTLIB}/*.dll)
        FileList = $$files($${LibPath})
        FileList = $$replace(FileList, '$${OUTLIB}/', '')
        FileList = $$replace(FileList, '\.dll', '')
        dllList = $$join(FileList, " -l", -l)
        for(var, $$list($${dllList})) {
            item = $${var}
            LIBS += -L$${OUTLIB}/ $${item}
        }
    }
} else{
    unix:!mac{
        LibPath = $$absolute_path($${OUTLIB}/*.so)
        FileList = $$files($${LibPath})
        FileList = $$replace(FileList, '$${OUTLIB}/', '')
        FileList = $$replace(FileList, '\.so', '')
        dllList = $$join(FileList, " -l", -l)
        for(var, $$list($${dllList})) {
            item = $${var}
            LIBS += -L$${OUTLIB}/ $${item}
        }
    }
}

defineReplace(headersCopyFunc) {
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


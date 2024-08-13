TEMPLATE = subdirs

App.depends += Modules Plugins

SUBDIRS += \
    App \
    Modules \
    Plugins

OTHER_FILES += \
    .clang-format \
    README.MD \
    .config.json

DISTFILES += \
    .qmake.conf


win32-msvc{
    path = "copy /y $$system_path($${ProjectRootDir}/.config.json) $$system_path($${OUTDIR}/)"
    system($${path})
}

unix:!mac{
    path = "cp $$system_path($${ProjectRootDir}/.config.json) $$system_path($${OUTDIR}/)"
    system("$${path}")
}

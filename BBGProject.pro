TEMPLATE = subdirs

App.depends += Modules Plugins

SUBDIRS += \
    App \
    Modules \
    Plugins

OTHER_FILES += \
    .clang-format \
    .qmake.conf \
    .config.json

win32-msvc{
    path = "copy /y $$system_path($${ProjectRootDir}/.config.json) $$system_path($${OUTDIR}/)"
    system($${path})
}

unix{
    path = "cp $$system_path($${ProjectRootDir}/.config.json) $$system_path($${OUTDIR}/)"
    system("$${path}")
}

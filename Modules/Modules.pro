TEMPLATE = subdirs

TryModule.depends += BussinessModule \
    ModulesManager \
    ResourceManagerModule

SUBDIRS += \
    BussinessModule \
    ModulesManager \
    ResourceManagerModule \
    TryModule

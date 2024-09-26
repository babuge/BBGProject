TEMPLATE = subdirs

TryModule.depends += BussinessModule \
    ModulesManager \
    ResourceManagerModule \
    LoggerManager

BussinessModule.depends += LoggerManager
ModulesManager.depends += LoggerManager
ResourceManagerModule.depends += LoggerManager

SUBDIRS += \
    BussinessModule \
    LoggerManager \
    ModulesManager \
    ResourceManagerModule \
    TryModule

#include "nordpy_plugin.h"
#include "nordpyconnectionmanager.h"

#include <qqml.h>

void NordpyPlugin::registerTypes(const char *uri)
{
    // @uri org.kde.private.nordpy
    qmlRegisterType<NordPyConnectionManager>(uri, 1, 0, "NordPyConnectionManager");
}


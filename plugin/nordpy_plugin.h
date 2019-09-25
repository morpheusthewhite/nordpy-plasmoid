#ifndef NORDPY_PLUGIN_H
#define NORDPY_PLUGIN_H

#include <QQmlExtensionPlugin>

class NordpyPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // NORDPY_PLUGIN_H

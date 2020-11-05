#pragma once
#include "eirExe.h"

#include <QObject>

#include <QIcon>
#include <QMap>
class QAction;

#include <eirType/MultiName.h>

class EIREXE_EXPORT ActionManager : public QObject
{
    Q_OBJECT
public:
    explicit ActionManager(QObject *parent = nullptr);
    QAction * action(const MultiName &name) const;
    QAction * add(const MultiName &name, QAction *act);
    QAction * add(const MultiName &name, const QIcon icon=QIcon());
    QAction * add(const MultiName &name, const QString &text, const QIcon icon=QIcon());


signals:

private:
    QMap<MultiName, QAction*> mNameActionMap;

};


// file: {EIRC2 Repo}./src/libs/eirExe/ConfigObject.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <eirType/MultiName.h>
#include <eirType/VarMap.h>

#include "Configuration.h"

class EIREXE_EXPORT ConfigObject : public QObject
{
    Q_OBJECT

public:
    typedef Configuration ConfigSegment;

public:
    explicit ConfigObject(QObject *parent = nullptr);
    bool contains(const MultiName &key) const;
    bool equals(const Var &var) const;
    Var at(const MultiName &key);
    QVariant currentValue(const MultiName &key);
    QVariant defaultValue(const MultiName &key);
    bool isDefault(const MultiName &key) const;
    Configuration configuration() const;
    Configuration configuration(const MultiName &groupName) const;

signals:
    void varAdded(Var var);
    void varSet(Var var);
    void currentSet(Var var);
    void defaultSet(Var var);

public slots:
    void set(VarMap varMap);
    void set(VarMap varMap, MultiName groupName);
    void set(Var var);
//    void setDefault(Var var);
    void setDefault(MultiName key,
                    QVariant defaultVari);
//    void setCurrent(Var var);
    void setCurrent(MultiName key,
                    QVariant currentVari);

protected slots:

private:
    Configuration mConfiguration;
};


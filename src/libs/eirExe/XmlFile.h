//! \file XmlFile.h
#pragma once
#include "eirExe.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNamedNodeMap>
class QFile;

#include "FileName.h"

class EIREXE_EXPORT XmlFile
{
public:
    XmlFile();
    XmlFile(const FileName &fileName);
    bool load(const FileName &fileName);
    bool load();
    void close();
    QDomDocument document() const;
    QDomElement rootElement() const;

    static QStringList dumpList(const QDomNamedNodeMap &namedNodeMap);

private:
    FileName mFileName;
    QFile * mpFile=nullptr;
    QDomDocument mDomDocument;
    QDomElement mRootElement;
};


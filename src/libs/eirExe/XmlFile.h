//! \file XmlFile.h
#pragma once
#include "eirExe.h"

#include <QDomDocument>
#include <QDomElement>
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

private:
    FileName mFileName;
    QFile * mpFile=nullptr;
    QDomDocument mDomDocument;
    QDomElement mRootElement;
};


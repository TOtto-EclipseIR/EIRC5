#include "XmlFile.h"

#include <QFile>

#include <eirXfr/Debug.h>
#include <eirType/Success.h>

XmlFile::XmlFile()
{
    TRACEFN;
}

XmlFile::XmlFile(const FileName &fileName)
    : mFileName(fileName)
{
    TRACEQFI << fileName;
    WEXPECT(load());
}

bool XmlFile::load(const FileName &fileName)
{
    mFileName = fileName;
    return load();
}

bool XmlFile::load()
{
    TRACEQFI << mFileName;
    Success success(true);
    success.testNot(mFileName().isEmpty());
    mpFile = new QFile(mFileName);
    TSTALLOC(mpFile);
    EXPECT(mpFile->open(QIODevice::ReadOnly));
    QByteArray qba= mpFile->readAll();
    EXPECTNOT(qba.isEmpty());
    close();
    success.testNot(qba.isEmpty());
    success.test(mDomDocument.setContent(qba));
    success.testNot(mDomDocument.isNull());
    mRootElement = mDomDocument.documentElement();
    success.testNot(mRootElement.isNull());
    TRACE << "===" << mFileName;
    TRACE << "---" << mRootElement.tagName();
    QDomNode dn = mRootElement.firstChild();
    while(! dn.isNull())
    {
        QDomElement de = dn.toElement();if( ! de.isNull())
        TRACE << de.tagName();
        dn = dn.nextSibling();
    }
    return success;
}

void XmlFile::close()
{
    TRACEFN;
    if (mpFile)
    {
        mpFile->close();
        delete mpFile;
        mpFile = nullptr;
    }
}

QDomDocument XmlFile::document() const
{
    return mDomDocument;
}

QDomElement XmlFile::rootElement() const
{
    return mRootElement;
}


QStringList XmlFile::dumpList(const QDomNamedNodeMap &namedNodeMap)
{
    QStringList nameList;
    for (int ix = 0; ix < namedNodeMap.length(); ++ix)
        nameList << QString("%1. %2").arg(ix+1).arg(namedNodeMap.item(ix).nodeName());
    return nameList;
}

#include "BaseImagePak.h"

#include <QFileInfo>
#include <QImage>

#include <eirType/QQImage.h>
#include <eirXfr/Debug.h>

BaseImagePak::BaseImagePak(const Id id)
    : VarPak(id)
{
    TRACEQFI << id;
}

BaseImagePak::BaseImagePak(const QByteArray &ba, const Id id)
    : VarPak(id)
{
    TRACEQFI << ba << id;
    set(ba);
    QImage i = QImage::fromData(ba);
    Var vi("Original/Image", i);
    set(Original, vi);
}

BaseImagePak::BaseImagePak(const QString &fileName, const Id id)
{
    TRACEQFI << fileName << id;
    QQImage i(fileName);
    Var vi("Original/Image", i);
    Var vfn("Original/FileName", fileName);
    set(Original, vi);
    insert(vfn);
}

QQImage BaseImagePak::image(const BaseImagePak::ImageIndex iix) const
{
    QVariant vari = get(iix);
    QQImage qqi(qvariant_cast<QImage>(vari));
    return qqi;
}

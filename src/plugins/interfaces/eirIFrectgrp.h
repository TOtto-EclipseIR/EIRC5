// file: {EIRC2repo}./src/plugins/interfaces/eirIFrectgrp.h
#pragma once

class eirIFrectdet
{
protected: // virtual
    virtual bool configure(const QVariantMap &configuration);
    virtual QVariantMap groupRectangles(const QList<QRect> &rectangleList);
};

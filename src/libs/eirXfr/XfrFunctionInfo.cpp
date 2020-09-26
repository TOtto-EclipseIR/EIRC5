#include "XfrFunctionInfo.h"
DEFINE_DATAPROPS(XfrFunctionInfo, XfrFunctionInfoData)
void XfrFunctionInfo::ctor(void) {;}
void XfrFunctionInfo::dtor(void) {;}

XfrFunctionInfo::XfrFunctionInfo(const char *qFuncInfo)
    : cmQfiString(qFuncInfo)
{
    qDebug() << Q_FUNC_INFO << qFuncInfo;
    parse();
}

void XfrFunctionInfo::parse()
{
    qDebug() << Q_FUNC_INFO << cmQfiString;
    setPrettyFunction(cmQfiString);
    // ex: const TInputType& myMin(const TInputType&, const TInputType&) [with TInputType = int]
    mElements = cmQfiString.simplified().split(" ", Qt::SkipEmptyParts);

}


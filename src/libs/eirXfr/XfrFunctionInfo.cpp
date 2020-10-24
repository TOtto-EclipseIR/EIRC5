#include "XfrFunctionInfo.h"
DEFINE_DATAPROPS(XfrFunctionInfo, XfrFunctionInfoData)
void XfrFunctionInfo::ctor(void) {;}
void XfrFunctionInfo::dtor(void) {;}


XfrFunctionInfo::XfrFunctionInfo(const char *qFuncInfo)
    : data(new XfrFunctionInfoData)
    , cmQfiString(qFuncInfo)
    , mWorkingQfi(cmQfiString)
{
    qDebug() << Q_FUNC_INFO << qFuncInfo;
    parse();
}

void XfrFunctionInfo::clear()
{
    qDebug() << Q_FUNC_INFO;
    *this = XfrFunctionInfo("");
}

bool XfrFunctionInfo::isNull() const
{
    return getPrettyFunction().isEmpty();
}

bool XfrFunctionInfo::isFlag(const Flags flags) const
{
    return getFlags() & flags;
}

bool XfrFunctionInfo::argumentCount() const
{
    return getArgumentCount();
}

void XfrFunctionInfo::parse()
{
    qDebug() << Q_FUNC_INFO << cmQfiString;
    setPrettyFunction(cmQfiString);
    // ex: const TInputType& myMin(const TInputType&, const TInputType&) [with TInputType = int]
    parseArguments();
    parseClassFunctionNames();
    parsePrefix();
    parseSuffix();
}

void XfrFunctionInfo::parseArguments()
{
    qDebug() << Q_FUNC_INFO << mWorkingQfi;
    int insideBeginParen = 1 + mWorkingQfi.indexOf('(');
    int insideEndParen = mWorkingQfi.lastIndexOf(')');
    QString arguments = mWorkingQfi.mid(insideBeginParen,
                                        insideEndParen - insideBeginParen);
    mWorkingQfi.remove(insideBeginParen, insideEndParen - insideBeginParen);
    qDebug() << insideBeginParen << insideEndParen
             << insideEndParen - insideBeginParen;
    qDebug() << arguments << mWorkingQfi;
    QStringList argList = arguments.split(", ", Qt::SkipEmptyParts);
    QStringList nameList;
    foreach (QString arg, argList) nameList << arg.replace(' ', '-');
    QString typeNames = nameList.join(',');
    setArgumentTypeNames(typeNames);
    if ("void" == typeNames)
    {
        setArgumentCount(0);
        orFlag(VoidArgument);
    }
    else
    {
        setArgumentCount(nameList.size());
    }
    qDebug() << typeNames << nameList.size() << Qt::hex << getFlags() << Qt::dec;
}

void XfrFunctionInfo::parseClassFunctionNames()
{
    qDebug() << Q_FUNC_INFO << mWorkingQfi;
    QString localWorking;
    QString funcNames = mWorkingQfi;

    int argumentLeftParen = funcNames.indexOf('(');
    localWorking = funcNames.mid(argumentLeftParen);
    funcNames.truncate(argumentLeftParen);
    if ( ! localWorking.isEmpty()) if (localWorking[0] == '(') localWorking.remove(0, 1);
    if ( ! localWorking.isEmpty()) if (localWorking[0] == ')') localWorking.remove(0, 1);
    if ( ! localWorking.isEmpty()) if (localWorking[0] == ' ') localWorking.remove(0, 1);
    qDebug() << argumentLeftParen << funcNames << localWorking;

    int lastSpace = 1 + funcNames.lastIndexOf(' ');
    localWorking.prepend("|");
    localWorking.prepend(funcNames.left(lastSpace - 1));
    funcNames.replace(0, lastSpace, "");
    int lastDoubleColon = funcNames.lastIndexOf("::");
    qDebug() << funcNames << lastDoubleColon << lastSpace << localWorking;
    //qDebug() << "+0123456789_123456789_123456789_123456789_123456789";

    if (lastDoubleColon < 2)
    {
        setFunctionName(funcNames);
        initClassName();
    }
    else
    {
        setFunctionName(funcNames.mid(2 + lastDoubleColon));
        setClassName(funcNames.left(lastDoubleColon));
    }
    qDebug() << getClassName() << getFunctionName() << localWorking;
    mWorkingQfi = localWorking;
}

void XfrFunctionInfo::parsePrefix()
{
    QString prefix = mWorkingQfi.left(mWorkingQfi.indexOf('|'));
    qDebug() << Q_FUNC_INFO << mWorkingQfi << prefix;
    int splitterPos = mWorkingQfi.indexOf('|');
    if (findAndRemove("const"), splitterPos) orFlag(ConstFunction);
    if (findAndRemove("volatile")) orFlag(Volatile);
    if (findAndRemove("static")) orFlag(Static);
    if (findAndRemove("void")) orFlag(ReturnsVoid);
    if (findAndRemove("bool")) orFlag(ReturnsBool);
    if (findAndRemove("__cdecl")) orFlag(CDecl);
    splitterPos = mWorkingQfi.indexOf('|');
    QString returnType;
    if (splitterPos >= 0)
    {
        returnType = mWorkingQfi.left(splitterPos).simplified();
        mWorkingQfi.remove(0, splitterPos);
    }
    qDebug() << Qt::hex << mWorkingQfi << returnType << getFlags() << Qt::dec;
}

void XfrFunctionInfo::parseSuffix()
{
    qDebug() << Q_FUNC_INFO << mWorkingQfi;
    int leftBracketWith = mWorkingQfi.indexOf("[with ");
    int rightBracket = mWorkingQfi.indexOf("]");
    if (leftBracketWith > 0 && rightBracket > leftBracketWith)
    {
        QString templateWith = mWorkingQfi.mid(6 + leftBracketWith,
                                -6 + rightBracket - leftBracketWith);
        mWorkingQfi.remove(leftBracketWith, 1 + rightBracket - leftBracketWith);
        templateWith.remove(' ');
        qDebug() << templateWith << mWorkingQfi;
        setTemplateWith(templateWith);
    }
    if (findAndRemove("const")) orFlag(ConstFunction);
    int equalPos = mWorkingQfi.indexOf("=");
    int zeroPos = mWorkingQfi.indexOf("0", equalPos);
    if (equalPos >= 0 && zeroPos > equalPos)
    {
        orFlag(PureVirtual);
        mWorkingQfi.remove(equalPos, zeroPos - equalPos);
    }
    QStringList suffixList = mWorkingQfi.simplified().split(' ');
    qDebug() << mWorkingQfi << suffixList << Qt::hex << getFlags() << Qt::dec;
    setSuffixes(suffixList);
}

void XfrFunctionInfo::orFlag(const Flags flags)
{
    qDebug() << Q_FUNC_INFO << Qt::hex << getFlags() << flags << Qt::dec;
    *ptrFlags() |= flags;
}

bool XfrFunctionInfo::findAndRemove(const QString &target, const int beforePos)
{
    qDebug() << Q_FUNC_INFO << target << mWorkingQfi;
    int pos = mWorkingQfi.indexOf(target);
    if (pos >= 0 && pos < beforePos)
    {
        mWorkingQfi.remove(pos, target.length());
        return true;
    }
    else
    {
        return false;
    }
}


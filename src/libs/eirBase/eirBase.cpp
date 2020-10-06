#include "eirBase.h"

eirBase::eirBase()
{
}

void eirBase::registerErrors()
{
#if 0
    ErrorHandler::Item::registerCode(
                 "ErrorHandler/tryFileMode/NotExist",
                 QtCriticalMsg,
                 "%What %FileName at %FilePath does not exist",
                 VarMap() << Var("What", "File's purpose")
                     << Var("FileName", "File's Name")
                     << Var("FilePath", "File's Directory"));
    ErrorHandler::Item::registerCode(
                 "ErrorHandler/tryFileMode/NotReadable",
                 QtCriticalMsg,
                 "%What %FileName at %FilePath is not readable",
                 VarMap() << Var("What", "File's purpose")
                     << Var("FileName", "File's Name")
                     << Var("FilePath", "File's Directory"));
    ErrorHandler::Item::registerCode(
                 "ErrorHandler/tryFileMode/NotWritable",
                 QtCriticalMsg,
                 "%What %FileName at %FilePath is not writable",
                 VarMap() << Var("What", "File's purpose")
                     << Var("FileName", "File's Name")
                     << Var("FilePath", "File's Directory"));
    ErrorHandler::Item::registerCode("ErrorHandler"
                "/Expect/Critical",
                QtCriticalMsg,
                "Critical Expectation %what failed",
                VarMap() << Var("What", "Expected Operation"));
#endif
}

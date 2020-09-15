// file: {repo: EIRC2}./src/libs/eirExe/CommandLineClientInterface.h
#pragma once
#include "eirExe.h"

class QCommandLineParser;


class EIREXE_EXPORT CommandLineClientInterface
{
public:
    CommandLineClientInterface();
    virtual void setup(QCommandLineParser * parser);
};


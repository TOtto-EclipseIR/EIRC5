#pragma once

#include <eirExe/CommandLineClientInterface.h>

class If2CommandLine : public CommandLineClientInterface
{
public:
    If2CommandLine();
    virtual void setup(QCommandLineParser * parser) override;
};


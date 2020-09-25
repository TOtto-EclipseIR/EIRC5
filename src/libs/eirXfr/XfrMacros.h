//! @file {EIRC5 repo}./src/libs/eirXfr/XfrMacros.h
#pragma once
#include "eirXfr.h"

#include "XfrEntry.h"

#define XFRENTRY(level) XfrEntry::from(Q_FUNC_INFO, level)
#define XFRENTRY1(level, var1) XfrEntry::from(Q_FUNC_INFO, level, #var1, var1)

#define XENTER() XFRENTRY("FunctionEntry")
#define XARG1(var) XFRENTRY1("FunctionArg1", var)
#define XARG2(var) XFRENTRY1("FunctionArg2", var)

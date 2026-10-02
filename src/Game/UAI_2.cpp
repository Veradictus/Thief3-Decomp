// Game/UAI_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10E5B578
{
public:
    virtual void FUN_10bbe970() = 0;
};

class USubsystem : public UObject, public Class_10E5B578
{
    DECLARE_CLASS(USubsystem, UObject, 0x9, Core)

public:
    ~USubsystem();
};

class UAISubsystem : public USubsystem
{
    DECLARE_CLASS(UAISubsystem, USubsystem, 0xD, Engine)

public:
    ~UAISubsystem();

    BYTE Pad30[0x4];
};

class UAI : public UAISubsystem
{
    DECLARE_CLASS(UAI, UAISubsystem, 0x4, AICore)

public:
    ~UAI();

    virtual void FUN_10bbe970();
};

// FUNCTION: 0x10BBE680 ??1UAI@@UAE@XZ
UAI::~UAI()
{
    ConditionalDestroy();
}

// Game/Unsorted_10C1AE80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10E98D08
{
public:
    ~Class_10E98D08() {}

    virtual int Virtual0() = 0;
};

class Class_10E98D50 : public Class_10E98D08
{
public:
    ~Class_10E98D50();

    virtual int Virtual0();

    char Unknown04[0x44];
    UObject* Unknown48;
};

// FUNCTION: 0x10C1AE80 ??1Class_10E98D50@@QAE@XZ
Class_10E98D50::~Class_10E98D50()
{
    Unknown48->ConditionalDestroy();
}

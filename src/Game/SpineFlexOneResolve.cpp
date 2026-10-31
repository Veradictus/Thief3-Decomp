// Game/SpineFlexOneResolve.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/cString.h"

int FUN_10c28480(int A, cString* B, cString* C);

class Class_10C28680
{
public:
    void FUN_10c28680();
    int Unknown00;
    char Unknown04[0x20];
    int SpineFlex;
};

// FUNCTION: 0x10C28680 ?FUN_10c28680@Class_10C28680@@QAEXXZ
void Class_10C28680::FUN_10c28680()
{
    cString Spine("M1 Spine");
    {
        cString Flex("spine_flex1");
        SpineFlex = FUN_10c28480(Unknown00, &Flex, &Spine);
    }
    if (SpineFlex)
        return;
}

// Game/ObjectRangeEligibility.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/cIntArray.h"
#include "Game/Class_10978090.h"
#include "Game/Class_1098E330.h"
#include <math.h>

class Class_1098E0F0;

class Class_10BB3190_Result;

Class_10BB3190_Result* FUN_10983cf0(int Object);

class cUObjectLinkManager {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4(int Source, int Target, int Flavor, cIntArray* Out);
};

cUObjectLinkManager* GetUObjectLinkManager();

struct ObjectPosition333 {
    char Unknown00[0x2C];
    FVector Position;
};

inline float VectorLength333(const FVector& Value)
{
    return sqrtf(Value.X * Value.X + Value.Y * Value.Y + Value.Z * Value.Z);
}

// FUNCTION: 0x10B1F550 ?FUN_10b1f550@@YA_NPAVClass_1098E0F0@@PAPAX@Z
bool FUN_10b1f550(Class_1098E0F0* Object, void** PositionBits)
{
    int Blocked = 0;
    if (((Class_1098E330*)Object)->GetPropertyValue(0x80064B, &Blocked) && Blocked)
        return false;

    cIntArray Links;
    GetUObjectLinkManager()->Virtual4(0, (int)Object, 0x281B9D0, &Links);
    if (Links.Count) {
        Class_10978090* Link = (Class_10978090*)Links.Data[0];
        Class_10BB3190_Result* Linked = FUN_10983cf0((int)Link->FUN_10978090());
        if (Linked && !(unsigned char)((Class_1098E330*)Linked)->Virtual105())
            return false;
    }
    int Range = 0;
    ((Class_1098E330*)Object)->GetPropertyValue(0x2000BA, &Range);
    // The preserved legacy spelling is void**; native callers pass a borrowed FVector address.
    const FVector* Position = (const FVector*)PositionBits;
    return VectorLength333(((ObjectPosition333*)Object)->Position - *Position) <= Range;
}

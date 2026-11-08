// Game/AIAlertStateSerialization.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/FArchive.h"
#include "Game/Object_10BE58C0.h"

FArchive& FUN_10b052a0(FArchive& Ar, void* V);

class Class_10E8BE68 {
public:
    virtual void Serialize(FArchive& Ar);
};

// Existing caller-facing name; limited field view, no whole hierarchy claimed.
class Class_10E960D8 {
public:
    void FUN_10be4ef0(Object_10BE58C0* Ar);
    void** Unknown00;
    char Unknown04[0x3C];
    int Unknown40;
    int Unknown44;
    int Unknown48;
    int Unknown4C;
    int Unknown50;
    int Unknown54[3];
    int Unknown60;
    unsigned char Unknown64;
};

// FUNCTION: 0x10BE4EF0 ?FUN_10be4ef0@Class_10E960D8@@QAEXPAVObject_10BE58C0@@@Z
void Class_10E960D8::FUN_10be4ef0(Object_10BE58C0* Ar)
{
    FArchive& archive = *reinterpret_cast<FArchive*>(Ar);
    reinterpret_cast<Class_10E8BE68*>(this)->Class_10E8BE68::Serialize(archive);
    Ar->Virtual1(&Unknown40, 4);
    Ar->Virtual1(&Unknown44, 4);
    Ar->Virtual1(&Unknown48, 4);
    Ar->Virtual1(&Unknown4C, 4);
    Ar->Virtual1(&Unknown50, 4);
    FUN_10b052a0(archive, Unknown54);
    if (Ar->Unknown0C < 0x55) {
        int legacy[3];
        unsigned char legacyByte;
        FUN_10b052a0(archive, legacy);
        Ar->Virtual1(&legacyByte, 1);
    } else {
        Ar->Virtual1(&Unknown60, 4);
        Ar->Virtual1(&Unknown64, 1);
    }
}

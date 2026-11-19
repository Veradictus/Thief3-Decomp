// Game/AIPeriodicEffect.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10C1A950.h"

class Class_10A03780 {
public:
    void FUN_10a03780(const FVector& Value, float First, float Second, int Mode);
};

class Class_10AA82E0 {
public:
    Class_10C1A950* FUN_10aa82e0();
    char Unknown00[0x64];
};

double GetTimeSeconds();

class Class_10BBB410 {
public:
    void FUN_10bb88a0();
    char Unknown00[0x20];
    int Count;
    int Capacity;
    Class_10A03780** Data;
    char Unknown2C[4];
    Class_10AA82E0 Unknown30;
    char Unknown94[0x1BC];
    float LastTime;
};

// FUNCTION: 0x10BB88A0 ?FUN_10bb88a0@Class_10BBB410@@QAEXXZ
void Class_10BBB410::FUN_10bb88a0()
{
    if (!Count)
        return;
    double NextTime = LastTime + 3.0f;
    if (GetTimeSeconds() < NextTime)
        return;
    Class_10C1A950* Current = Unknown30.FUN_10aa82e0();
    if (!Current)
        return;
    double Expiry = Current->Class_10C1A950::FUN_10c1a950() + 1.0f;
    if (GetTimeSeconds() > Expiry)
        return;
    for (int i = 0; i < Count; ++i) {
        Class_10A03780* Item = Data[i];
        Item->FUN_10a03780(FVector(1.0f, 0.0f, 0.0f), 0.3f, 0.3f, 4);
    }
    LastTime = GetTimeSeconds();
}

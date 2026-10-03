// Game/Unsorted_10B8B5E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Object_10B8B760
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
};

class Class_10B8B760
{
public:
    bool FUN_10cad960();
    void FUN_10cad970();
    void FUN_10b8b760();

    char Unknown00[0x3C];
    Object_10B8B760* Unknown3C;
    char Unknown40[4];
    int Unknown44;
};

class FCoords
{
public:
    FCoords() {}

    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
};

class Object_10B8B6A0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual FCoords Virtual44();
};

struct Struct_10C09A10
{
    char Unknown00[4];
    int Unknown04;
};

class Class_10B8B660_Unknown0B0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual Struct_10C09A10* Virtual6();
};

struct Struct_10B8B660
{
    char Unknown00[0xB0];
    Class_10B8B660_Unknown0B0* Unknown0B0;
};

// FUNCTION: 0x10B8B660 ?FUN_10b8b660@@YAPAUStruct_10C09A10@@H@Z
Struct_10C09A10* FUN_10b8b660(int A)
{
    Struct_10B8B660* Obj = (Struct_10B8B660*)A;
    Class_10B8B660_Unknown0B0* Slot = Obj->Unknown0B0;
    if (Slot && Slot->Virtual6())
    {
        Struct_10C09A10* Item = Obj->Unknown0B0->Virtual6();
        return Item->Unknown04 == 3 ? Item : 0;
    }
    return 0;
}

// FUNCTION: 0x10B8B6A0 ?FUN_10b8b6a0@@YA?AVFVector@@PAVObject_10B8B6A0@@@Z
FVector FUN_10b8b6a0(Object_10B8B6A0* A)
{
    FCoords Coords = A->Virtual44();
    FVector Offset;
    Offset.X = Coords.XAxis.X * 32.0f;
    Offset.Y = Coords.XAxis.Y * 32.0f;
    Offset.Z = Coords.XAxis.Z * 32.0f;
    return Coords.Origin + Offset;
}

// FUNCTION: 0x10B8B760 ?FUN_10b8b760@Class_10B8B760@@QAEXXZ
void Class_10B8B760::FUN_10b8b760()
{
    if (!FUN_10cad960() && Unknown44)
        FUN_10cad970();
    Unknown3C->Virtual24();
}

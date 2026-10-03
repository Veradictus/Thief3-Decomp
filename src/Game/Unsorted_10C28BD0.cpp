// Game/Unsorted_10C28BD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C28CA0
{
public:
    ~Class_10C28CA0();

    char Unknown00[0xC];
    int Unknown0C;
};

extern Class_10C28CA0* DAT_10ff70a0;

class Class_10C28B70
{
public:
    ~Class_10C28B70();

    virtual void Virtual0();
};

struct Struct_10C28C60
{
    int Count;
    int Unknown04;
    Class_10C28B70** Items;
};

// FUNCTION: 0x10C28C60 ?FUN_10c28c60@@YAXPAUStruct_10C28C60@@@Z
void FUN_10c28c60(Struct_10C28C60* Array)
{
    for (int i = 0; i < Array->Count; i++)
        delete Array->Items[i];
    Array->Count = 0;
}

// FUNCTION: 0x10C28D90 ?FUN_10c28d90@@YAXXZ
void FUN_10c28d90()
{
    --DAT_10ff70a0->Unknown0C;
    if (DAT_10ff70a0->Unknown0C == 0)
    {
        delete DAT_10ff70a0;
        DAT_10ff70a0 = 0;
    }
}

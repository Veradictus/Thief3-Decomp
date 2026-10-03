// Game/Unsorted_10C2F4F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10C2F4F0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int Virtual5();

    char Unknown04[0x18];
    int Unknown1C;
    char Unknown20[0x10];
    int Unknown30;
    char Unknown34[8];
    int Unknown3C;
};

// FUNCTION: 0x10C2F4F0 ?FUN_10c2f4f0@@YGPAXPAVObject_10C2F4F0@@@Z
void* __stdcall FUN_10c2f4f0(Object_10C2F4F0* Obj)
{
    if (!Obj)
        return 0;
    switch (Obj->Virtual5())
    {
    case 0:
        return &Obj->Unknown30;
    case 1:
        return &Obj->Unknown3C;
    case 2:
        return &Obj->Unknown1C;
    default:
        return 0;
    }
}

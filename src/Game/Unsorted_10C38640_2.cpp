// Game/Unsorted_10C38640_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C20BC0 {
public:
    void FUN_10c20bc0();
};

class Class_10C386E0 {
public:
    char Unknown00[0xA0];
    int UnknownA0;
    char UnknownA4[8];
    int UnknownAC;
    int UnknownB0;
    Class_10C20BC0* UnknownB4;

    void FUN_10c386e0();
};

struct Struct_10C38700
{
    char Unknown00[4];
    int Unknown04;
};

class Object_10C38700_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual Struct_10C38700* Virtual6();
};

class Object_10C38700
{
public:
    char Unknown00[0xB0];
    Object_10C38700_Member* UnknownB0;
};

class Class_10C392B0
{
public:
    int FUN_10c392b0();

    char Unknown00[0xA0];
    int Unknown0A0;
    char Unknown0A4[0x5D];
    char Unknown101;
    char Unknown102;
    char Unknown103;
};

// FUNCTION: 0x10C386E0 ?FUN_10c386e0@Class_10C386E0@@QAEXXZ
void Class_10C386E0::FUN_10c386e0()
{
    UnknownA0 = 0;
    UnknownAC = 0;
    if (UnknownB4)
        UnknownB4->FUN_10c20bc0();
}

// FUNCTION: 0x10C38700 ?FUN_10c38700@@YA_NPAVObject_10C38700@@@Z
bool FUN_10c38700(Object_10C38700* Obj)
{
    Object_10C38700_Member* Member = Obj->UnknownB0;
    if (Member && Member->Virtual6()->Unknown04 == 3)
        return true;
    return false;
}

// FUNCTION: 0x10C392B0 ?FUN_10c392b0@Class_10C392B0@@QAEHXZ
int Class_10C392B0::FUN_10c392b0()
{
    if (!Unknown101 && Unknown0A0 == 0 && Unknown103)
        return 1;
    return 0;
}

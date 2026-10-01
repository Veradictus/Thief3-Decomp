// Game/Unsorted_10B4FD30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B22020
{
public:
    void FUN_10b22020(int A);
};

class Class_10B396A0
{
public:
    void FUN_10b396a0();
};

class Class_10AC92F0
{
public:
    void FUN_10ac92f0();
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x13C];
    Class_10AC92F0* Unknown13C;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();
};

class Class_10E81620 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10b4fd30(Class_10B22020* Param);
};

// FUNCTION: 0x10B4FD30 ?FUN_10b4fd30@Class_10E81620@@UAEXPAVClass_10B22020@@@Z
void Class_10E81620::FUN_10b4fd30(Class_10B22020* Param)
{
    Param->FUN_10b22020(0);
    ((Class_10B396A0*)FUN_10aa82d0())->FUN_10b396a0();
    DAT_10f3a3d8->Unknown13C->FUN_10ac92f0();
}

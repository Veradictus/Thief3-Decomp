// Game/Unsorted_10C13150.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10e499a0;

extern float DAT_10e5cb58;

extern float DAT_10e499a4;

extern float DAT_10e49c68;

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    void* Unknown00;
};

class Class_10E8C4A4
{
public:
    virtual void FUN_10c13150(const Class_10E8C4A4* p1);

    char Unknown04[4];
    int Field08;
    Class_109081E0 Field0c;
};

// FUNCTION: 0x10C13150 ?FUN_10c13150@Class_10E8C4A4@@UAEXPBV1@@Z
void Class_10E8C4A4::FUN_10c13150(const Class_10E8C4A4* p1)
{
    Field08 = p1->Field08;
    Field0c = p1->Field0c;
}

// FUNCTION: 0x10C13A00 ?FUN_10c13a00@@YAMXZ
float FUN_10c13a00()
{
    return DAT_10e499a0;
}

// FUNCTION: 0x10C13B10 ?FUN_10c13b10@@YAMXZ
float FUN_10c13b10()
{
    return DAT_10e5cb58;
}

// FUNCTION: 0x10C13BA0 ?FUN_10c13ba0@@YAMXZ
float FUN_10c13ba0()
{
    return DAT_10e499a4;
}

// FUNCTION: 0x10C13C30 ?FUN_10c13c30@@YAMXZ
float FUN_10c13c30()
{
    return DAT_10e49c68;
}

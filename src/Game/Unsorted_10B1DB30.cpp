// Game/Unsorted_10B1DB30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_10A18E80
{
public:
    float FUN_10a18e80(int Index);
};

class Object_10A18FC0 : public Class_10A18E80
{
};

Object_10A18FC0* FUN_10a18fc0();

class Class_10B21820
{
public:
    char Unknown00[0x450];
    unsigned Unknown450_0 : 1;
    unsigned Unknown450_1 : 1;
    unsigned Unknown450_2 : 1;
};

void FUN_10b20650(Class_10B21820* Object);

// FUNCTION: 0x10B1DBD0 ?FUN_10b1dbd0@@YAMMMMM@Z
float FUN_10b1dbd0(float A, float B, float C, float D)
{
    return ((D - C) * A + C) * B;
}

// FUNCTION: 0x10B1DC40 ?FUN_10b1dc40@@YAHXZ
int FUN_10b1dc40()
{
    if (FUN_10a18fc0()->FUN_10a18e80(0) > DAT_10eafbdc)
        return 1;
    return 0;
}

// FUNCTION: 0x10B21170 ?FUN_10b21170@@YAXPAVClass_10B21820@@@Z
void FUN_10b21170(Class_10B21820* Object)
{
    if (Object->Unknown450_2)
        FUN_10b20650(Object);
}

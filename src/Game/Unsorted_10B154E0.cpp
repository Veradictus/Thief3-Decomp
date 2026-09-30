// Game/Unsorted_10B154E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C56E40
{
public:
    Class_10C56E40() : Unknown00(0) {}
    ~Class_10C56E40();

    int Unknown00;
};

struct Static_10B18DC0
{
    Static_10B18DC0() {}

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

struct Struct_10B19530_Item
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10B19530
{
public:
    Struct_10B19530_Item* FUN_10b19530(int Index);

    int Unknown00;
    Struct_10B19530_Item Items[1];
};

// FUNCTION: 0x10B18B20 ?FUN_10b18b20@@YAPAVClass_10C56E40@@XZ
Class_10C56E40* FUN_10b18b20()
{
    static Class_10C56E40 Instance;
    return &Instance;
}

// FUNCTION: 0x10B18DC0 ?FUN_10b18dc0@@YAPAUStatic_10B18DC0@@XZ
Static_10B18DC0* FUN_10b18dc0()
{
    static Static_10B18DC0 Instance;
    Instance.Unknown00 = 0x3f9c;
    Instance.Unknown04 = 0x4000;
    Instance.Unknown08 = 0x4000;
    Instance.Unknown0C = 0x3000;
    Instance.Unknown10 = 0x3000;
    return &Instance;
}

// FUNCTION: 0x10B19530 ?FUN_10b19530@Class_10B19530@@QAEPAUStruct_10B19530_Item@@H@Z
Struct_10B19530_Item* Class_10B19530::FUN_10b19530(int Index)
{
    return &Items[Index];
}

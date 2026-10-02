// Game/Unsorted_10C1B940.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109A6AA0
{
public:
    int FUN_109a6aa0();

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C1BE80
{
public:
    bool FUN_10c1be80(Class_109A6AA0* Out);

    char Unknown00[0x58];
    Class_109A6AA0 Unknown58;
};

class Class_10C1BEB0
{
public:
    bool FUN_10c1beb0(Class_109A6AA0* Out);

    char Unknown00[0x64];
    Class_109A6AA0 Unknown64;
};

extern void* DAT_10e98d98[];

class Class_10C1B840
{
public:
    Class_10C1B840(int A, int B, int C, int D, int E, float F);

    void** Unknown00;
    int Unknown04[17];
};

struct Struct_10C1B940
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Class_10E98D98 : public Class_10C1B840
{
public:
    Class_10E98D98* FUN_10c1b940(int A, int B, int C, const Struct_10C1B940& D);

    Struct_10C1B940 Unknown48;
};

// FUNCTION: 0x10C1B940 ?FUN_10c1b940@Class_10E98D98@@QAEPAV1@HHHABUStruct_10C1B940@@@Z
Class_10E98D98* Class_10E98D98::FUN_10c1b940(int A, int B, int C, const Struct_10C1B940& D)
{
    this->Class_10C1B840::Class_10C1B840(A, B, C, 0, 0, 1.0f);
    Unknown00 = DAT_10e98d98;
    Unknown48 = D;
    return this;
}

// FUNCTION: 0x10C1BE80 ?FUN_10c1be80@Class_10C1BE80@@QAE_NPAVClass_109A6AA0@@@Z
bool Class_10C1BE80::FUN_10c1be80(Class_109A6AA0* Out)
{
    if (Unknown58.FUN_109a6aa0() == 0)
    {
        *Out = Unknown58;
        return true;
    }
    return false;
}

// FUNCTION: 0x10C1BEB0 ?FUN_10c1beb0@Class_10C1BEB0@@QAE_NPAVClass_109A6AA0@@@Z
bool Class_10C1BEB0::FUN_10c1beb0(Class_109A6AA0* Out)
{
    if (Unknown64.FUN_109a6aa0() == 0)
    {
        *Out = Unknown64;
        return true;
    }
    return false;
}

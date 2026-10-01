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

// Game/Unsorted_10BF6A70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BBDB40
{
public:
    float FUN_10bbdc80();
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510(int Id);
};

struct Struct_10BD8630
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

class Class_10BF6AF0
{
public:
    float FUN_10bf6af0();

    char Unknown00[4];
    Struct_10BD8630* Unknown04;
};

struct Struct_10BF6B10
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

class Class_10BF6B10
{
public:
    float FUN_10bf6b10();

    char Unknown00[4];
    Struct_10BF6B10* Unknown04;
};

struct Struct_10BF6B30
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

class Class_10BF6B30
{
public:
    float FUN_10bf6b30();

    char Unknown00[4];
    Struct_10BF6B30* Unknown04;
};

struct Struct_10BD2D10
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

class Class_10BF6B50
{
public:
    float FUN_10bf6b50();

    char Unknown00[4];
    Struct_10BD2D10* Unknown04;
};

class Class_10BF6B70
{
public:
    float FUN_10bf6b70();

    char Unknown00[4];
    Struct_10BD2D10* Unknown04;
};

class Class_10BF6B90
{
public:
    float FUN_10bf6b90();

    char Unknown00[4];
    Struct_10BD2D10* Unknown04;
};

class Class_10BF6BB0
{
public:
    float FUN_10bf6bb0();

    char Unknown00[4];
    Struct_10BD2D10* Unknown04;
};

// FUNCTION: 0x10BF6AF0 ?FUN_10bf6af0@Class_10BF6AF0@@QAEMXZ
float Class_10BF6AF0::FUN_10bf6af0()
{
    return Unknown04->Unknown08->FUN_10dbd510(0x10045a)->FUN_10bbdc80() * 16.0f;
}

// FUNCTION: 0x10BF6B10 ?FUN_10bf6b10@Class_10BF6B10@@QAEMXZ
float Class_10BF6B10::FUN_10bf6b10()
{
    return Unknown04->Unknown08->FUN_10dbd510(0x100458)->FUN_10bbdc80() * 16.0f;
}

// FUNCTION: 0x10BF6B30 ?FUN_10bf6b30@Class_10BF6B30@@QAEMXZ
float Class_10BF6B30::FUN_10bf6b30()
{
    return Unknown04->Unknown08->FUN_10dbd510(0x100459)->FUN_10bbdc80() * 16.0f;
}

// FUNCTION: 0x10BF6B50 ?FUN_10bf6b50@Class_10BF6B50@@QAEMXZ
float Class_10BF6B50::FUN_10bf6b50()
{
    float Value = Unknown04->Unknown08->FUN_10dbd510(0x10043c)->FUN_10bbdc80();
    return Value;
}

// FUNCTION: 0x10BF6B70 ?FUN_10bf6b70@Class_10BF6B70@@QAEMXZ
float Class_10BF6B70::FUN_10bf6b70()
{
    float Value = Unknown04->Unknown08->FUN_10dbd510(0x100442)->FUN_10bbdc80();
    return Value;
}

// FUNCTION: 0x10BF6B90 ?FUN_10bf6b90@Class_10BF6B90@@QAEMXZ
float Class_10BF6B90::FUN_10bf6b90()
{
    float Value = Unknown04->Unknown08->FUN_10dbd510(0x100443)->FUN_10bbdc80();
    return Value;
}

// FUNCTION: 0x10BF6BB0 ?FUN_10bf6bb0@Class_10BF6BB0@@QAEMXZ
float Class_10BF6BB0::FUN_10bf6bb0()
{
    float Value = Unknown04->Unknown08->FUN_10dbd510(0x100444)->FUN_10bbdc80();
    return Value;
}

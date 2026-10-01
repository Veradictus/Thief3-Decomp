// Game/Unsorted_10BB0B10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10bb7570
{
public:
    char Unknown00[4];
    int Unknown04;

    bool FUN_10bb7570();
};

class Class_10bb7580
{
public:
    char Unknown00[4];
    int Unknown04;

    bool FUN_10bb7580();
};

class Class_10bb7590
{
public:
    char Unknown00[4];
    int Unknown04;

    bool FUN_10bb7590();
};

class Class_10bb75e0
{
public:
    char Unknown00[4];
    int Unknown04;

    bool FUN_10bb75e0();
};

class Class_10BB75F0 {
public:
    char Unknown00[4];
    int Unknown04;

    bool FUN_10bb75f0();
};

class Class_10BB7600 {
public:
    char Unknown00[4];
    int Unknown04;

    bool FUN_10bb7600();
};

class Class_10BB7610 {
public:
    char Unknown00[4];
    int Unknown04;

    bool FUN_10bb7610();
};

class Class_10BB7670 {
public:
    char Unknown00[4];
    int Unknown04;

    bool FUN_10bb7670();
};

class Class_10BB48E0
{
public:
    ~Class_10BB48E0();
};

extern Class_10BB48E0* DAT_10ff6694;

// FUNCTION: 0x10BB5630 ?FUN_10bb5630@@YAXXZ
void FUN_10bb5630()
{
    if (DAT_10ff6694)
    {
        delete DAT_10ff6694;
        DAT_10ff6694 = 0;
    }
}

// FUNCTION: 0x10BB7570 ?FUN_10bb7570@Class_10bb7570@@QAE_NXZ
bool Class_10bb7570::FUN_10bb7570()
{
    return Unknown04 <= 1;
}

// FUNCTION: 0x10BB7580 ?FUN_10bb7580@Class_10bb7580@@QAE_NXZ
bool Class_10bb7580::FUN_10bb7580()
{
    return Unknown04 <= 2;
}

// FUNCTION: 0x10BB7590 ?FUN_10bb7590@Class_10bb7590@@QAE_NXZ
bool Class_10bb7590::FUN_10bb7590()
{
    return Unknown04 == 3;
}

// FUNCTION: 0x10BB75E0 ?FUN_10bb75e0@Class_10bb75e0@@QAE_NXZ
bool Class_10bb75e0::FUN_10bb75e0()
{
    return Unknown04 != 3;
}

// FUNCTION: 0x10BB75F0 ?FUN_10bb75f0@Class_10BB75F0@@QAE_NXZ
bool Class_10BB75F0::FUN_10bb75f0()
{
    return Unknown04 >= 1;
}

// FUNCTION: 0x10BB7600 ?FUN_10bb7600@Class_10BB7600@@QAE_NXZ
bool Class_10BB7600::FUN_10bb7600()
{
    return Unknown04 < 2;
}

// FUNCTION: 0x10BB7610 ?FUN_10bb7610@Class_10BB7610@@QAE_NXZ
bool Class_10BB7610::FUN_10bb7610()
{
    return Unknown04 <= 0;
}

// FUNCTION: 0x10BB7670 ?FUN_10bb7670@Class_10BB7670@@QAE_NXZ
bool Class_10BB7670::FUN_10bb7670()
{
    return Unknown04 == 0;
}

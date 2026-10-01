// Game/Unsorted_10BB75A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BB75A0
{
public:
    int FUN_10bb75a0();

    char Unknown00[4];
    int Unknown04;
};

class Class_10BB75C0
{
public:
    int FUN_10bb75c0();

    char Unknown00[4];
    int Unknown04;
};

// FUNCTION: 0x10BB75A0 ?FUN_10bb75a0@Class_10BB75A0@@QAEHXZ
int Class_10BB75A0::FUN_10bb75a0()
{
    if (Unknown04 == 1 || Unknown04 == 2)
        return 1;
    return 0;
}

// FUNCTION: 0x10BB75C0 ?FUN_10bb75c0@Class_10BB75C0@@QAEHXZ
int Class_10BB75C0::FUN_10bb75c0()
{
    if (Unknown04 == 1 || Unknown04 == 0)
        return 1;
    return 0;
}

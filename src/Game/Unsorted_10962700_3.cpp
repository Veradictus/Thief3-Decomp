// Game/Unsorted_10962700_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4c578[];

class Class_10E70A50
{
public:
    void** Unknown00;
};

class AActor : public Class_10E70A50
{
public:
    AActor* FUN_1098cf10();
};

class Class_10E4C578 : public AActor
{
public:
    Class_10E4C578* FUN_10962c70();
};

extern void* DAT_10e4c6f0[];

class Class_10E4C6F0 : public AActor
{
public:
    Class_10E4C6F0* FUN_10962d10();
};

extern void* DAT_10e4c868[];

class Class_10E4C868 : public AActor
{
public:
    Class_10E4C868* FUN_10962db0();
};

// FUNCTION: 0x10962C70 ?FUN_10962c70@Class_10E4C578@@QAEPAV1@XZ
Class_10E4C578* Class_10E4C578::FUN_10962c70()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e4c578;
    return this;
}

// FUNCTION: 0x10962D10 ?FUN_10962d10@Class_10E4C6F0@@QAEPAV1@XZ
Class_10E4C6F0* Class_10E4C6F0::FUN_10962d10()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e4c6f0;
    return this;
}

// FUNCTION: 0x10962DB0 ?FUN_10962db0@Class_10E4C868@@QAEPAV1@XZ
Class_10E4C868* Class_10E4C868::FUN_10962db0()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e4c868;
    return this;
}

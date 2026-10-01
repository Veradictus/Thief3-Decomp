// Game/Unsorted_10B93F10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e8b640[];

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

class Class_10E8B640 : public AActor
{
public:
    Class_10E8B640* FUN_10b93f90();
};

extern void* DAT_10e8b7b8[];

class Class_10E8B7B8 : public AActor
{
public:
    Class_10E8B7B8* FUN_10b94030();
};

extern void* DAT_10e8b930[];

class Class_10E8B930 : public AActor
{
public:
    Class_10E8B930* FUN_10b940d0();
};

// FUNCTION: 0x10B93F90 ?FUN_10b93f90@Class_10E8B640@@QAEPAV1@XZ
Class_10E8B640* Class_10E8B640::FUN_10b93f90()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e8b640;
    return this;
}

// FUNCTION: 0x10B94030 ?FUN_10b94030@Class_10E8B7B8@@QAEPAV1@XZ
Class_10E8B7B8* Class_10E8B7B8::FUN_10b94030()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e8b7b8;
    return this;
}

// FUNCTION: 0x10B940D0 ?FUN_10b940d0@Class_10E8B930@@QAEPAV1@XZ
Class_10E8B930* Class_10E8B930::FUN_10b940d0()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e8b930;
    return this;
}

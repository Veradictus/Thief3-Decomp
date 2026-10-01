// Game/Unsorted_10B92C10_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class UAI
{
public:
    UAI();
};

extern void* DAT_10e89af8[];

class Class_10E52230
{
public:
    Class_10E52230* FUN_10994280();

    void** Unknown00;
};

class Class_10E89AF8 : public Class_10E52230
{
public:
    Class_10E89AF8* FUN_10b93410();
};

extern void* DAT_10e89c78[];

class Class_10E89C78 : public Class_10E52230
{
public:
    Class_10E89C78* FUN_10b934b0();
};

extern void* DAT_10e89df8[];

class Class_10E89DF8 : public Class_10E52230
{
public:
    Class_10E89DF8* FUN_10b93550();
};

extern void* DAT_10e89f78[];

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

class Class_10E89F78 : public AActor
{
public:
    Class_10E89F78* FUN_10b935f0();
};

extern void* DAT_10e8a0f0[];

class Class_10E8A0F0 : public AActor
{
public:
    Class_10E8A0F0* FUN_10b93690();
};

extern void* DAT_10e8a268[];

class Class_10E8A268 : public AActor
{
public:
    Class_10E8A268* FUN_10b93730();
};

// FUNCTION: 0x10B93400 ?FUN_10b93400@@YAXPAX@Z
void FUN_10b93400(void* Memory)
{
    new ((EInternal*)Memory) UAI();
}

// FUNCTION: 0x10B93410 ?FUN_10b93410@Class_10E89AF8@@QAEPAV1@XZ
Class_10E89AF8* Class_10E89AF8::FUN_10b93410()
{
    FUN_10994280();
    Unknown00 = DAT_10e89af8;
    return this;
}

// FUNCTION: 0x10B934B0 ?FUN_10b934b0@Class_10E89C78@@QAEPAV1@XZ
Class_10E89C78* Class_10E89C78::FUN_10b934b0()
{
    FUN_10994280();
    Unknown00 = DAT_10e89c78;
    return this;
}

// FUNCTION: 0x10B93550 ?FUN_10b93550@Class_10E89DF8@@QAEPAV1@XZ
Class_10E89DF8* Class_10E89DF8::FUN_10b93550()
{
    FUN_10994280();
    Unknown00 = DAT_10e89df8;
    return this;
}

// FUNCTION: 0x10B935F0 ?FUN_10b935f0@Class_10E89F78@@QAEPAV1@XZ
Class_10E89F78* Class_10E89F78::FUN_10b935f0()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e89f78;
    return this;
}

// FUNCTION: 0x10B93690 ?FUN_10b93690@Class_10E8A0F0@@QAEPAV1@XZ
Class_10E8A0F0* Class_10E8A0F0::FUN_10b93690()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e8a0f0;
    return this;
}

// FUNCTION: 0x10B93730 ?FUN_10b93730@Class_10E8A268@@QAEPAV1@XZ
Class_10E8A268* Class_10E8A268::FUN_10b93730()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e8a268;
    return this;
}

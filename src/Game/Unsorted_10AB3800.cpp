// Game/Unsorted_10AB3800.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e6e1f8[];

class Class_10E70A50
{
public:
    Class_10E70A50();

    void** Unknown00;
    char Unknown04[0x28];
};

class Class_10E6E1F8 : public Class_10E70A50
{
public:
    Class_10E6E1F8* FUN_10ab3cc0();
};

extern void* DAT_10e6e278[];

class AActor : public Class_10E70A50
{
public:
    AActor* FUN_1098cf10();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

class Class_10E6E278 : public AActor
{
public:
    Class_10E6E278* FUN_10ab3d60();
};

extern void* DAT_10e6e3f0[];

class Class_10E6E3F0 : public AActor
{
public:
    Class_10E6E3F0* FUN_10ab3e00();
};

extern void* DAT_10e6e6e0[];

class Class_10E6E6E0 : public AActor
{
public:
    Class_10E6E6E0* FUN_10ab4000();
};

class Class_10ab3ea0
{
public:
    void FUN_10ab3ea0();
};

class Class_10E55E78
{
public:
    Class_10E55E78();

    virtual void Virtual0();
};

class Class_10E6E868 : public Class_10E55E78
{
public:
    Class_10E6E868();
};

class Class_10E6E8F0 : public Class_10E55E78
{
public:
    Class_10E6E8F0();
};

class Class_10E6E978 : public Class_10E55E78
{
public:
    Class_10E6E978();
};

class Class_10E6EA88 : public Class_10E55E78
{
public:
    Class_10E6EA88();
};

class Class_10ab4f10
{
public:
    void FUN_10ab4f10();
};

// FUNCTION: 0x10AB3CC0 ?FUN_10ab3cc0@Class_10E6E1F8@@QAEPAV1@XZ
Class_10E6E1F8* Class_10E6E1F8::FUN_10ab3cc0()
{
    this->Class_10E70A50::Class_10E70A50();
    Unknown00 = DAT_10e6e1f8;
    return this;
}

// FUNCTION: 0x10AB3D60 ?FUN_10ab3d60@Class_10E6E278@@QAEPAV1@XZ
Class_10E6E278* Class_10E6E278::FUN_10ab3d60()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e6e278;
    return this;
}

// FUNCTION: 0x10AB3E00 ?FUN_10ab3e00@Class_10E6E3F0@@QAEPAV1@XZ
Class_10E6E3F0* Class_10E6E3F0::FUN_10ab3e00()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e6e3f0;
    return this;
}

// FUNCTION: 0x10AB4000 ?FUN_10ab4000@Class_10E6E6E0@@QAEPAV1@XZ
Class_10E6E6E0* Class_10E6E6E0::FUN_10ab4000()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e6e6e0;
    return this;
}

// FUNCTION: 0x10AB4D40 ?FUN_10ab4d40@@YAXPAVClass_10ab3ea0@@@Z
void FUN_10ab4d40(Class_10ab3ea0* p1)
{
    if (p1)
        p1->FUN_10ab3ea0();
}

// FUNCTION: 0x10AB4D60 ??0Class_10E6E868@@QAE@XZ
Class_10E6E868::Class_10E6E868()
{
}

// FUNCTION: 0x10AB4DF0 ??0Class_10E6E8F0@@QAE@XZ
Class_10E6E8F0::Class_10E6E8F0()
{
}

// FUNCTION: 0x10AB4E80 ??0Class_10E6E978@@QAE@XZ
Class_10E6E978::Class_10E6E978()
{
}

// FUNCTION: 0x10AB4FE0 ??0Class_10E6EA88@@QAE@XZ
Class_10E6EA88::Class_10E6EA88()
{
}

// FUNCTION: 0x10AB53E0 ?FUN_10ab53e0@@YAXPAVClass_10ab4f10@@@Z
void FUN_10ab53e0(Class_10ab4f10* p1)
{
    if (p1)
        p1->FUN_10ab4f10();
}

// Game/Unsorted_10B9BDB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B9C9C0
{
public:
    void FUN_10b9c9c0(void* A);

    char Unknown00[0x38];
    void* Unknown38;
};

class Class_10B9BEB0
{
public:
    void FUN_10b9beb0();
};

class Class_10B9C9A0
{
public:
    void FUN_10b9c9a0();

    Class_10B9BEB0* Unknown00;
};

class Class_10BFC190
{
public:
    void FUN_10bfc190();
};

class Class_10BE3FF0
{
public:
    void FUN_10be3ff0();
};

class Class_10BB89D0
{
public:
    Class_10BE3FF0* FUN_10bb89d0();

    char Unknown00[0x30];
    Class_10BFC190 Unknown30;
};

class Class_10BFB910
{
public:
    void FUN_10bfb910(int Index);
};

class Class_10FF667C
{
public:
    char Unknown00[0x28];
    Class_10BFB910* Unknown28;
};

extern Class_10FF667C* DAT_10ff667c;

struct Struct_10B9BDB0_Unknown118
{
    char Unknown00[4];
    Class_10BB89D0* Unknown04;
};

class Class_10B9BDB0
{
public:
    void FUN_10b9bdb0();

    char Unknown00[0x118];
    Struct_10B9BDB0_Unknown118* Unknown118;
};

class Class_10B9C030
{
public:
    bool FUN_10b9c030(int Value);

    // The index of the first element equal to Value, else -1.
    int FindIndex(int Value)
    {
        for (int i = 0; i < Unknown00; i++)
        {
            if (Unknown08[i] == Value)
                return i;
        }
        return -1;
    }

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

// FUNCTION: 0x10B9BDB0 ?FUN_10b9bdb0@Class_10B9BDB0@@QAEXXZ
void Class_10B9BDB0::FUN_10b9bdb0()
{
    Struct_10B9BDB0_Unknown118* Obj = Unknown118;
    if (Obj && Obj->Unknown04)
    {
        Obj->Unknown04->Unknown30.FUN_10bfc190();
        if (Obj->Unknown04->FUN_10bb89d0())
        {
            Obj->Unknown04->FUN_10bb89d0()->FUN_10be3ff0();
            DAT_10ff667c->Unknown28->FUN_10bfb910(4);
        }
    }
}

// FUNCTION: 0x10B9C030 ?FUN_10b9c030@Class_10B9C030@@QAE_NH@Z
bool Class_10B9C030::FUN_10b9c030(int Value)
{
    return FindIndex(Value) != -1;
}

// FUNCTION: 0x10B9C9A0 ?FUN_10b9c9a0@Class_10B9C9A0@@QAEXXZ
void Class_10B9C9A0::FUN_10b9c9a0()
{
    Class_10B9BEB0* Object = Unknown00;
    if (Object)
    {
        Unknown00 = 0;
        Object->FUN_10b9beb0();
        ::operator delete(Object);
    }
}

// FUNCTION: 0x10B9C9C0 ?FUN_10b9c9c0@Class_10B9C9C0@@QAEXPAX@Z
void Class_10B9C9C0::FUN_10b9c9c0(void* A)
{
    if (Unknown38)
        ::operator delete(Unknown38);
    Unknown38 = A;
}

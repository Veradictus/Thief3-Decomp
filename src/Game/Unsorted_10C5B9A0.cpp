// Game/Unsorted_10C5B9A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A32000
{
public:
    void FUN_10a32000(int NewCount);

    int Unknown00;
    int Unknown04;
    char* Unknown08;
};

class Class_10C5B9A0
{
public:
    void FUN_10c5b9a0(char Item);

    char Unknown00[0x3C];
    Class_10A32000 Unknown3C;
};

class Class_10C5BA80
{
public:
    Class_10C5BA80(const Class_10C5BA80& Other);
    ~Class_10C5BA80();

    char Unknown00[0x28];
};

struct Info_10C5BFA0
{
    int Unknown00;
    Class_10C5BA80 Unknown04;
};

class Class_10C5BFA0
{
public:
    Class_10C5BA80 FUN_10c5bfa0();

    Info_10C5BFA0* Unknown00;
};

class Class_10C5C3A0 {
public:
    char Unknown00[0x20];
    int Unknown20;
    void FUN_10c5bf20(int p1);
    void FUN_10c5c3a0();
};

// FUNCTION: 0x10C5B9A0 ?FUN_10c5b9a0@Class_10C5B9A0@@QAEXD@Z
void Class_10C5B9A0::FUN_10c5b9a0(char Item)
{
    Class_10A32000* Array = &Unknown3C;
    int Index = Array->Unknown00;
    Array->FUN_10a32000(Index + 1);
    Array->Unknown08[Index] = Item;
}

// FUNCTION: 0x10C5BFA0 ?FUN_10c5bfa0@Class_10C5BFA0@@QAE?AVClass_10C5BA80@@XZ
Class_10C5BA80 Class_10C5BFA0::FUN_10c5bfa0()
{
    return Class_10C5BA80(Unknown00->Unknown04);
}

// FUNCTION: 0x10C5C3A0 ?FUN_10c5c3a0@Class_10C5C3A0@@QAEXXZ
void Class_10C5C3A0::FUN_10c5c3a0()
{
    Unknown20 = -1;
    FUN_10c5bf20(0x40);
}

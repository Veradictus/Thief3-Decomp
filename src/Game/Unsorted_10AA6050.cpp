// Game/Unsorted_10AA6050.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6D8F0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int FUN_10aa6390();

    char Unknown04[0x14];
    int Unknown18;
};

typedef unsigned char BYTE;

class FVector
{
public:
    FVector() {}
    FVector(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}

    float X, Y, Z;
};

class FBox
{
public:
    FBox() {}
    FBox(int) { Init(); }

    void Init()
    {
        Min = Max = FVector(0, 0, 0);
        IsValid = 0;
    }

    FVector Min;
    FVector Max;
    BYTE IsValid;
};

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10AA6120
{
public:
    Class_10AA6120(int A);

    int Unknown00;
    FBox Unknown04;
    FArray Unknown20;
};

class Class_10B0AED0
{
public:
    ~Class_10B0AED0();

    int RefCount;
};

extern Class_10B0AED0* DAT_10f3a248;

struct Struct_10AA6050
{
    int Unknown00;
};

class Class_10AA6050
{
public:
    Struct_10AA6050* FUN_10aa6050(int Value);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Struct_10AA6050** Unknown0C;
};

// FUNCTION: 0x10AA6050 ?FUN_10aa6050@Class_10AA6050@@QAEPAUStruct_10AA6050@@H@Z
Struct_10AA6050* Class_10AA6050::FUN_10aa6050(int Value)
{
    for (int i = 0; i < Unknown04; i++)
    {
        Struct_10AA6050* Entry = Unknown0C[i];
        if (Entry->Unknown00 == Value)
            return Entry;
    }
    return 0;
}

// FUNCTION: 0x10AA6120 ??0Class_10AA6120@@QAE@H@Z
Class_10AA6120::Class_10AA6120(int A)
    : Unknown00(A)
{
    Unknown04.Init();
}

// FUNCTION: 0x10AA61D0 ?FUN_10aa61d0@@YAXXZ
void FUN_10aa61d0()
{
    --DAT_10f3a248->RefCount;
    if (DAT_10f3a248->RefCount == 0)
    {
        delete DAT_10f3a248;
        DAT_10f3a248 = 0;
    }
}

// FUNCTION: 0x10AA6390 ?FUN_10aa6390@Class_10E6D8F0@@UAEHXZ
int Class_10E6D8F0::FUN_10aa6390()
{
    bool Result = false;
    if (Unknown18)
        Result = true;
    return Result;
}

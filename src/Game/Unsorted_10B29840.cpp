// Game/Unsorted_10B29840.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <math.h>

extern void* DAT_10e7b120[];

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E6B078
{
public:
    Class_10E6B078();

    void** Unknown00;
    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[0xCC];
};

class Class_10E7B120 : public Class_10E6B078
{
public:
    Class_10E7B120* FUN_10b2ab70();

    FArray Unknown1B8;
    bool Unknown1C4;
    bool Unknown1C5;
    int Unknown1C8;
    FArray Unknown1CC;
    int Unknown1D8;
    int Unknown1DC;
    bool Unknown1E0;
    float Unknown1E4;
    float Unknown1E8;
    float Unknown1EC;
    int Unknown1F0;
    int Unknown1F4;
};

class FVector
{
public:
    float X;
    float Y;
    float Z;
};

class Class_10B28950
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();

    void FUN_10b28430(int A);

    float Unknown04;
    int Unknown08;
};

class Class_10E7AE9C_Second
{
public:
    virtual void SecondVirtual0();
    virtual void SecondVirtual1(float A);
};

class Class_10E7AE9C : public Class_10B28950, public Class_10E7AE9C_Second
{
public:
    virtual void FUN_10b29840(float A);

    FVector Unknown10;
    char Unknown1C[0x24];
    bool Unknown40;
    char Unknown41[0x3B];
    float Unknown7C;
};

// FUNCTION: 0x10B29840 ?FUN_10b29840@Class_10E7AE9C@@UAEXM@Z
void Class_10E7AE9C::FUN_10b29840(float A)
{
    SecondVirtual1(A);
    if (Unknown40)
    {
        if (fabs(Unknown7C - 1.0f) > 0.0001f)
        {
            if (Unknown7C > 1.0f)
                Unknown7C = (Unknown7C - 1.0f) * 0.5f + 1.0f;
            else
                Unknown7C = (1.0f - Unknown7C) * 0.5f + 1.0f;
        }
        FVector Position = Unknown10;
        FUN_10b28430((int)&Position);
    }
}

// FUNCTION: 0x10B2AB70 ?FUN_10b2ab70@Class_10E7B120@@QAEPAV1@XZ
Class_10E7B120* Class_10E7B120::FUN_10b2ab70()
{
    this->Class_10E6B078::Class_10E6B078();
    Unknown00 = DAT_10e7b120;
    Unknown1B8.FArray::FArray();
    Unknown1C4 = true;
    Unknown1C5 = false;
    Unknown1C8 = 0;
    Unknown1CC.FArray::FArray();
    Unknown1D8 = 0;
    Unknown1DC = 0;
    Unknown1E0 = true;
    Unknown1E4 = 18.0f;
    Unknown1E8 = 3.0f;
    Unknown1EC = 1.0f;
    Unknown1F0 = 3;
    Unknown1F4 = 0;
    return this;
}

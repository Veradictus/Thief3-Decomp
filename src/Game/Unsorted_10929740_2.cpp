// Game/Unsorted_10929740_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10929510
{
    int Pitch;
    unsigned char* Bits;
};

class Class_10E49AE0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void FUN_109298c0(Struct_10929510* p1, int p2, int p3, float* p4);
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8(Struct_10929510* p1, float* R, float* G, float* B, float* A, int p2, int p3);
};

class Class_10E49B08
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(float A, float B, float C, float* D, float* E, float* F, float* G);
    virtual void Virtual3();
    virtual void FUN_10929b10(float A, float B, float C, float* Out);
};

typedef unsigned long DWORD;

struct Struct_10929D60
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Class_10E49B28
{
public:
    virtual void Virtual0(int A, int B, int C, DWORD* Out);
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10929c90(int A, int B, int C, Struct_10929D60* Out);
};

// FUNCTION: 0x109298C0 ?FUN_109298c0@Class_10E49AE0@@UAEXPAUStruct_10929510@@HHPAM@Z
void Class_10E49AE0::FUN_109298c0(Struct_10929510* p1, int p2, int p3, float* p4)
{
    float R, G, B, A;
    Virtual8(p1, &R, &G, &B, &A, p2, p3);
    *p4 = R * 0.3f + G * 0.59f + B * 0.11f;
}

// FUNCTION: 0x10929B10 ?FUN_10929b10@Class_10E49B08@@UAEXMMMPAM@Z
void Class_10E49B08::FUN_10929b10(float A, float B, float C, float* Out)
{
    float Unused;
    Virtual2(A, B, C, &C, &B, &A, &Unused);
    float Sum = C * 0.3f;
    Sum += B * 0.59f;
    Sum += A * 0.11f;
    *Out = Sum;
}

// FUNCTION: 0x10929C90 ?FUN_10929c90@Class_10E49B28@@UAEXHHHPAUStruct_10929D60@@@Z
void Class_10E49B28::FUN_10929c90(int A, int B, int C, Struct_10929D60* Out)
{
    DWORD Packed;
    Virtual0(A, B, C, &Packed);
    const float Scale = 2.0f / 255.0f;
    Out->Unknown00 = (signed char)Packed * Scale;
    Out->Unknown04 = (signed char)(Packed >> 8) * Scale;
    Out->Unknown08 = (signed char)(Packed >> 16) * Scale;
}

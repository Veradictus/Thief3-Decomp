// Game/Unsorted_10C3EFD0_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FVector
{
public:
    float X, Y, Z;
};

class Class_10C3FF10
{
public:
    void FUN_10c3ff10(int A);
};

class Class_10C41420 : public Class_10C3FF10
{
public:
    void FUN_10c472d0(int A);
};

Class_10C41420* FUN_10c47d90();

class Class_10C62A40
{
public:
    void FUN_10c62a40(unsigned char A);
};

class Class_10C80360 : public Class_10C62A40
{
};

Class_10C80360* FUN_10c5f280();

class Class_10E9B5C0_Unknown1C
{
public:
    virtual int __stdcall Virtual0();
    virtual int __stdcall Virtual1();
    virtual int __stdcall Virtual2();
    virtual int __stdcall Virtual3();
    virtual int __stdcall Virtual4();
    virtual int __stdcall Virtual5();
    virtual int __stdcall Virtual6();
    virtual int __stdcall Virtual7();
    virtual int __stdcall Virtual8();
    virtual int __stdcall Virtual9();
    virtual int __stdcall Virtual10();
    virtual int __stdcall Virtual11();
    virtual int __stdcall Virtual12();
    virtual int __stdcall Virtual13();
    virtual int __stdcall Virtual14(float X, float Y, float Z, int Apply);
};

class Class_10E9B5C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10c3f050(FVector* Position);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void FUN_10c3f140(bool A);
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void FUN_10c3f220(unsigned char A);

    char Unknown04[4];
    FVector Unknown08;
    char Unknown14[8];
    Class_10E9B5C0_Unknown1C* Unknown1C;
    bool Unknown20;
    char Unknown21;
    unsigned char Unknown22;
};

struct Struct_10C3F090
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    char Unknown0C[0xC];
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

class Class_10C3F090_Member
{
public:
    virtual int __stdcall Virtual0();
    virtual int __stdcall Virtual1();
    virtual int __stdcall Virtual2();
    virtual int __stdcall Virtual3();
    virtual int __stdcall Virtual4();
    virtual int __stdcall Virtual5();
    virtual int __stdcall Virtual6();
    virtual int __stdcall Virtual7();
    virtual int __stdcall Virtual8();
    virtual int __stdcall Virtual9();
    virtual int __stdcall Virtual10();
    virtual int __stdcall Virtual11();
    virtual int __stdcall Virtual12();
    virtual int __stdcall Virtual13(int A, int B, int C, int D, int E, int F, int G);
};

class Class_10C3F090
{
public:
    void FUN_10c3f090(Struct_10C3F090* P);

    char Unknown00[0x1C];
    Class_10C3F090_Member* Unknown1C;
};

// FUNCTION: 0x10C3F050 ?FUN_10c3f050@Class_10E9B5C0@@UAEXPAVFVector@@@Z
void Class_10E9B5C0::FUN_10c3f050(FVector* Position)
{
    Unknown08 = *Position;
    if (Unknown1C)
        Unknown1C->Virtual14(Position->X, Position->Y, Position->Z, 1);
}

// FUNCTION: 0x10C3F090 ?FUN_10c3f090@Class_10C3F090@@QAEXPAUStruct_10C3F090@@@Z
void Class_10C3F090::FUN_10c3f090(Struct_10C3F090* P)
{
    if (Unknown1C)
        Unknown1C->Virtual13(P->Unknown00, P->Unknown04, P->Unknown08, P->Unknown18, P->Unknown1C, P->Unknown20, 1);
}

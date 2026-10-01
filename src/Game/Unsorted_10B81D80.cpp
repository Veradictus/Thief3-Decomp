// Game/Unsorted_10B81D80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef unsigned char BYTE;

struct Struct_10B859B0_Vector
{
    void SetZero() { X = Y = Z = W = 0.0f; }
    float& operator()(int I) { return (&X)[I]; }

    float X;
    float Y;
    float Z;
    float W;
};

struct Struct_10B859B0_Rotation
{
    void SetZero()
    {
        Col0.SetZero();
        Col1.SetZero();
        Col2.SetZero();
    }
    float& operator()(int Row, int Col) { return (&Col0)[Col](Row); }
    void SetIdentity()
    {
        SetZero();
        (*this)(0, 0) = 1.0f;
        (*this)(1, 1) = 1.0f;
        (*this)(2, 2) = 1.0f;
    }

    Struct_10B859B0_Vector Col0;
    Struct_10B859B0_Vector Col1;
    Struct_10B859B0_Vector Col2;
};

struct Struct_10B859B0_Transform
{
    void SetIdentity()
    {
        Rotation.SetIdentity();
        Translation.SetZero();
    }

    Struct_10B859B0_Rotation Rotation;
    Struct_10B859B0_Vector Translation;
};

struct Struct_10B859B0_0C
{
    Struct_10B859B0_0C() : Unknown00(0), Unknown04(0), Unknown08(0x80000000) {}

    int Unknown00;
    int Unknown04;
    unsigned int Unknown08;
};

class Class_10B859B0
{
public:
    Class_10B859B0* FUN_10b859b0();

    int Unknown00;
    int Unknown04;
    BYTE Unknown08;
    Struct_10B859B0_0C Unknown0C;
    int Unknown18;
    int Unknown1C;
    Struct_10B859B0_Transform Unknown20;
};

class Class_10B822C0_Member
{
public:
    char Unknown00[0x28];
    unsigned int Unknown28;
};

class Class_10B822C0
{
public:
    int FUN_10b822c0();

    char Unknown00[0x8C];
    Class_10B822C0_Member* Unknown8C;
};

class Allocator_10FFA700
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* A, int B, int C);
};

extern Allocator_10FFA700* DAT_10ffa700;

class Class_10B83820
{
public:
    void FUN_10b83820();

    void* Unknown00;
    int Unknown04;
    unsigned Unknown08 : 31;
    unsigned Unknown08Flag : 1;
};

// FUNCTION: 0x10B822C0 ?FUN_10b822c0@Class_10B822C0@@QAEHXZ
int Class_10B822C0::FUN_10b822c0()
{
    if (Unknown8C)
        return Unknown8C->Unknown28 & 0x1F;
    return 0;
}

// FUNCTION: 0x10B83820 ?FUN_10b83820@Class_10B83820@@QAEXXZ
void Class_10B83820::FUN_10b83820()
{
    if (!Unknown08Flag)
    {
        Allocator_10FFA700* Allocator = DAT_10ffa700;
        Allocator->Virtual5(Unknown00, Unknown08 * 16, 0x11);
    }
}

// FUNCTION: 0x10B859B0 ?FUN_10b859b0@Class_10B859B0@@QAEPAV1@XZ
Class_10B859B0* Class_10B859B0::FUN_10b859b0()
{
    Unknown0C.Struct_10B859B0_0C::Struct_10B859B0_0C();
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown20.SetIdentity();
    return this;
}

// Game/Unsorted_10B4FF40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B53A00
{
    char Unknown00[0x450];
    int Unknown450;
};

class Class_10E816E0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int FUN_10b53a00(Struct_10B53A00* P, int Code);

    void FUN_10b3b260(Struct_10B53A00* P);
};

class Class_1098E330;

class Class_10AC84B0
{
public:
    int FUN_10ac84b0(Class_1098E330* Obj);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x108];
    Class_10AC84B0* Unknown108;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class Class_10B50500
{
public:
    char Unknown00[0x320];
    Class_1098E330* Unknown320;
    int Unknown324;
    int Unknown328;
};

struct Struct_10B50500_Member
{
    int Unknown00;
    Class_1098E330* Unknown04;
};

struct Struct_10B50500
{
    Struct_10B50500()
        : Unknown00(0.0f), Unknown04(0.0f), Unknown08(0.0f), Unknown0C(0.0f), Unknown10(0.0f), Unknown14(0.0f),
          Unknown18(0.0f), Unknown1C(0), Unknown20(-1), Unknown24(-1)
    {
    }

    float Unknown00;
    float Unknown04;
    float Unknown08;
    float Unknown0C;
    float Unknown10;
    float Unknown14;
    float Unknown18;
    Struct_10B50500_Member* Unknown1C;
    int Unknown20;
    int Unknown24;
};

bool FUN_10b1ff00(int A, int B, Class_10B50500* Obj, Struct_10B50500* Out);

// FUNCTION: 0x10B50500 ?FUN_10b50500@@YG_NPAVClass_10B50500@@HH@Z
bool __stdcall FUN_10b50500(Class_10B50500* Obj, int A, int B)
{
    Struct_10B50500 Result;
    if (FUN_10b1ff00(A, B, Obj, &Result))
    {
        Class_1098E330* Target = Result.Unknown1C->Unknown04;
        if (DAT_10f3a3d8->Unknown108->FUN_10ac84b0(Target))
        {
            Obj->Unknown320 = Target;
            Obj->Unknown324 = 0;
            Obj->Unknown328 = 0;
            return true;
        }
    }
    return false;
}

// FUNCTION: 0x10B53A00 ?FUN_10b53a00@Class_10E816E0@@UAEHPAUStruct_10B53A00@@H@Z
int Class_10E816E0::FUN_10b53a00(Struct_10B53A00* P, int Code)
{
    if (Code == 0x52)
    {
        if (P->Unknown450 & 0x20)
        {
            P->Unknown450 &= ~0x20;
            FUN_10b3b260(P);
        }
    }
    return 2;
}

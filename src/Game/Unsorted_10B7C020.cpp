// Game/Unsorted_10B7C020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Allocator_10FFA700
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* p1, int p2, int p3);
};

extern Allocator_10FFA700* DAT_10ffa700;

struct Struct_10B7C150
{
    char Unknown00[4];
    unsigned short Unknown04;
};

struct Struct_10B7C3D0
{
    char Unknown00[4];
    unsigned short Unknown04;
};

extern void* DAT_10e47850[];

class Class_10AF4B90
{
public:
    Class_10AF4B90* FUN_10af4b90(int p1, void* p2);
};

class Class_10B7ECC0
{
public:
    Class_10B7ECC0* FUN_10b7ecc0();

    char Unknown00[0xC];
    Class_10AF4B90 Unknown0C;
};

struct Struct_10D9E5E0_Param;

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8(int A, int B);
    virtual void Virtual9();
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10D9B090
{
public:
    void FUN_10d9e5e0(Struct_10D9E5E0_Param* A);
};

Class_10D9B090* FUN_10d9dcb0();

struct Struct_10B7C030_Param
{
    char Unknown00[0xB0];
    Struct_10D9E5E0_Param* UnknownB0;
};

class Class_10E4B180_Unknown7C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4(int A);
};

class Class_10E4B180
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void FUN_10b7c6a0(int A);
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void FUN_10b7c030(Struct_10B7C030_Param* A);

    char Unknown04[0x70];
    int Unknown74;
    char Unknown78[4];
    Class_10E4B180_Unknown7C** Unknown7C;
};

// FUNCTION: 0x10B7C030 ?FUN_10b7c030@Class_10E4B180@@UAEXPAUStruct_10B7C030_Param@@@Z
void Class_10E4B180::FUN_10b7c030(Struct_10B7C030_Param* A)
{
    FUN_10905aa0()->Virtual8(0, 0);
    if (A && A->UnknownB0)
        FUN_10d9dcb0()->FUN_10d9e5e0(A->UnknownB0);
    FUN_10905aa0()->Virtual9();
}

// FUNCTION: 0x10B7C150 ?FUN_10b7c150@@YAXPAUStruct_10B7C150@@@Z
void FUN_10b7c150(Struct_10B7C150* p)
{
    DAT_10ffa700->Virtual5(p, p->Unknown04, 0xf);
}

// FUNCTION: 0x10B7C3D0 ?FUN_10b7c3d0@@YAXPAUStruct_10B7C3D0@@@Z
void FUN_10b7c3d0(Struct_10B7C3D0* p)
{
    DAT_10ffa700->Virtual5(p, p->Unknown04, 0x23);
}

// FUNCTION: 0x10B7ECC0 ?FUN_10b7ecc0@Class_10B7ECC0@@QAEPAV1@XZ
Class_10B7ECC0* Class_10B7ECC0::FUN_10b7ecc0()
{
    Unknown0C.FUN_10af4b90(0x27, DAT_10e47850);
    return this;
}

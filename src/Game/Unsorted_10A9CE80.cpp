// Game/Unsorted_10A9CE80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AActor
{
public:
    virtual void Virtual0();
};

class Class_1098E330 : public AActor
{
public:
    int FUN_1098e330(int Id, int* Out);
};

class Class_1098E3D0 : public Class_1098E330
{
public:
    void FUN_1098e3d0(int Id, void* Out);
};

class Class_10E6B764
{
public:
    void FUN_10a6ae00(AActor* A, int B);
};

struct Struct_10AA3520
{
    char Unknown00[0x7C];
    Class_10E6B764* Unknown7C;
};

extern Struct_10AA3520* DAT_10f35dec;

class Object_10A9CF40
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
    virtual Class_1098E3D0* Virtual8();
};

class Class_10E6D1D8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a9cf40(int A, Object_10A9CF40* B, int C);
};

// FUNCTION: 0x10A9CF40 ?FUN_10a9cf40@Class_10E6D1D8@@UAEHHPAVObject_10A9CF40@@H@Z
int Class_10E6D1D8::FUN_10a9cf40(int A, Object_10A9CF40* B, int C)
{
    Class_1098E3D0* Actor = B->Virtual8();
    int Position[3] = { 0, 0, 0 };
    Actor->FUN_1098e3d0(0x80017, Position);
    int Id = 0;
    Actor->FUN_1098e330(0x800526, &Id);
    DAT_10f35dec->Unknown7C->FUN_10a6ae00(Actor, Id);
    return 1;
}

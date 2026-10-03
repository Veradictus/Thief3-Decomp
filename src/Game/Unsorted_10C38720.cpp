// Game/Unsorted_10C38720.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C05A50
{
    float Unknown00;
    float Unknown04;
};

float FUN_10c05a50(const Struct_10C05A50* A, const Struct_10C05A50* B);

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

struct Struct_10C38F20_Target
{
    char Unknown00[0x2C];
    Struct_10C05A50 Unknown2C;
};

class Object_10C38F20
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
    virtual Class_10c7d570* Virtual34();
};

class Class_10C38F20
{
public:
    int FUN_10c38f20(const Struct_10C05A50* A, int B);

    char Unknown00[0x48];
    Object_10C38F20* Unknown48;
    char Unknown4C[0x14];
    float Unknown60;
};

// FUNCTION: 0x10C38F20 ?FUN_10c38f20@Class_10C38F20@@QAEHPBUStruct_10C05A50@@H@Z
int Class_10C38F20::FUN_10c38f20(const Struct_10C05A50* A, int B)
{
    float Radius = Unknown60;
    if (FUN_10c05a50(&((Struct_10C38F20_Target*)Unknown48->Virtual34()->FUN_10c7d570())->Unknown2C, A) < Radius * Radius)
        return 1;
    return 0;
}

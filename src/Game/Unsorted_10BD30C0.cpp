// Game/Unsorted_10BD30C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef float FLOAT;

class FVector
{
public:
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}

    FLOAT X, Y, Z;
};

class Class_10bb8960_Result
{
public:
    virtual void Virtual0();

    char Unknown04[0x7C];
    FVector Unknown80;
    FVector Unknown8C;
};

class Class_10BB8960
{
public:
    Class_10bb8960_Result* FUN_10bb8960();
};

class Class_10C2F090
{
public:
    void FUN_10c2f090(int p1);
};

class Class_10BC4BF0
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

    int FUN_10bc4bf0();
};

class Class_10E935F0 : public Class_10BC4BF0
{
public:
    virtual void FUN_10bd30c0();

    Class_10BB8960* Unknown04;
};

// FUNCTION: 0x10BD30C0 ?FUN_10bd30c0@Class_10E935F0@@UAEXXZ
void Class_10E935F0::FUN_10bd30c0()
{
    Class_10bb8960_Result* R = Unknown04->FUN_10bb8960();
    R->Unknown80 = R->Unknown8C;
    R->Unknown8C = FVector(0, 0, 0);
    ((Class_10C2F090*)FUN_10bc4bf0())->FUN_10c2f090(0x3f800000);
}

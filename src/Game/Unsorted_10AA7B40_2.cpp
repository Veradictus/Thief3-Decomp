// Game/Unsorted_10AA7B40_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10d3d990(void* Stream, int* Value);

void FUN_10d3d2d0(void* Stream, int Value);

class Class_10F46D9C
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
    virtual int Virtual34();
};

extern Class_10F46D9C* DAT_10f46d9c;

class Object_10AA7BA0
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
    virtual void Virtual16(int A, void* B);
};

class Class_10E6C104
{
public:
    Class_10E6C104();

    virtual ~Class_10E6C104();

    int Unknown04;
};

class Class_10E6D964 : public Class_10E6C104
{
public:
    virtual ~Class_10E6D964();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10aa7ba0(void* Stream, int A, int B);

    Object_10AA7BA0* Unknown08;
    void* Unknown0C;
    int Unknown10;
};

// FUNCTION: 0x10AA7BA0 ?FUN_10aa7ba0@Class_10E6D964@@UAEXPAXHH@Z
void Class_10E6D964::FUN_10aa7ba0(void* Stream, int A, int B)
{
    FUN_10d3d990(Stream, &Unknown10);
    FUN_10d3d2d0(Stream, DAT_10f46d9c->Virtual34());
    Unknown08->Virtual16(DAT_10f46d9c->Virtual34(), Stream);
}

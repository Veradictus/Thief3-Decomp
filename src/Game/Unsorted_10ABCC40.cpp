// Game/Unsorted_10ABCC40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <new>

extern void* DAT_10e47850[];

class Class_10AF4B90
{
public:
    Class_10AF4B90* FUN_10af4b90(int A, void* B);

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

// The member of Class_10ABCC20 at 4: a Class_10AF4B90 set up with (0x27, DAT_10e47850).
class Class_10ABCC20_Field04 : public Class_10AF4B90
{
public:
    Class_10ABCC20_Field04() { FUN_10af4b90(0x27, DAT_10e47850); }
};

// The item 0x10ABCC20 constructs.
class Class_10ABCC20
{
public:
    int Unknown00;
    Class_10ABCC20_Field04 Unknown04;
};

// An object the table below holds: slot 51 gives the memory for a new item,
// slot 45 takes the item.
class Class_10A73EF0_Object
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
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual void Virtual44();
    virtual void Virtual45(Class_10ABCC20* Item, int B, int C);
    virtual void Virtual46();
    virtual void Virtual47();
    virtual void Virtual48();
    virtual void Virtual49();
    virtual void Virtual50();
    virtual void* Virtual51();
};

// The global table of objects, indexed by a handle's low 16 bits.
class Class_10A73EF0_Table
{
public:
    int Unknown00;
    int Unknown04;
    Class_10A73EF0_Object** Unknown08;
};

extern Class_10A73EF0_Table* DAT_10f3eda4;

class Class_10B06220
{
public:
    int FUN_10b06220();
    void FUN_10ad9c90(int Handle, Class_10ABCC20* const& Item);
};

class Class_10ABCFE0 : public Class_10B06220
{
public:
    void FUN_10abcfe0(int Handle, int B);
};

// FUNCTION: 0x10ABCFE0 ?FUN_10abcfe0@Class_10ABCFE0@@QAEXHH@Z
void Class_10ABCFE0::FUN_10abcfe0(int Handle, int B)
{
    Class_10ABCC20* Item = 0;
    Class_10A73EF0_Object* Obj = DAT_10f3eda4->Unknown08[Handle & 0xffff];
    Item = (Class_10ABCC20*)Obj->Virtual51();
    new (Item) Class_10ABCC20;
    Obj->Virtual45(Item, B, 0);
    FUN_10b06220();
    FUN_10ad9c90(Handle, Item);
}

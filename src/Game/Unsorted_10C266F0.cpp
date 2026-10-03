// Game/Unsorted_10C266F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C266F0_Item
{
};

struct Struct_10C266F0
{
    int Unknown00;
    int Unknown04;
    Struct_10C266F0_Item** Unknown08;
};

class Class_109B6D50
{
public:
    bool FUN_109b6d50(int A);
    void FUN_109bf7f0(int A, float B);
};

class Class_10E9925C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10c26720();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual float Virtual13();
    virtual bool Virtual14();

    Class_109B6D50* FUN_10c26490();

    char Unknown04[8];
    int Unknown0C;
    char Unknown10[0x25];
    bool Unknown35;
};

// FUNCTION: 0x10C266F0 ?FUN_10c266f0@@YAXPAUStruct_10C266F0@@@Z
void FUN_10c266f0(Struct_10C266F0* List)
{
    for (int i = 0; i < List->Unknown00; i++)
        delete List->Unknown08[i];
    List->Unknown00 = 0;
}

// FUNCTION: 0x10C26720 ?FUN_10c26720@Class_10E9925C@@UAEXXZ
void Class_10E9925C::FUN_10c26720()
{
    if (Virtual14())
    {
        Class_109B6D50* P = FUN_10c26490();
        if (P && !Unknown35 && !P->FUN_109b6d50(Unknown0C))
        {
            P->FUN_109bf7f0(Unknown0C, Virtual13());
            Unknown35 = true;
        }
    }
}

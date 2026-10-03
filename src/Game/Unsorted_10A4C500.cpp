// Game/Unsorted_10A4C500.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E67938;

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Count;
    int Unknown04;
    struct Struct_10A4C500_Entry** Data;
};

struct Struct_10A4C500_Owner
{
    char Unknown00[8];
    Class_10E67938* Unknown08;
};

struct Struct_10A4C500_Entry
{
    int Unknown00;
    Struct_10A4C500_Owner* Unknown04;
};

struct Struct_10A4C500_Node
{
    Struct_10A4C500_Node* Next;
    Struct_10A4C500_Node* Prev;
    Struct_10A4C500_Entry Value;
};

extern int DAT_10f3a084;

class Class_10E67938
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual bool FUN_10a4c4d0(int A);
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void FUN_10a4c500(Class_10BFBD70* Array);
};

// FUNCTION: 0x10A4C500 ?FUN_10a4c500@Class_10E67938@@UAEXPAVClass_10BFBD70@@@Z
void Class_10E67938::FUN_10a4c500(Class_10BFBD70* Array)
{
    for (Struct_10A4C500_Node* It = ((Struct_10A4C500_Node*)DAT_10f3a084)->Next;
         It != (Struct_10A4C500_Node*)DAT_10f3a084; It = It->Next)
    {
        if (It->Value.Unknown04->Unknown08 == this)
        {
            int Index = Array->Count;
            Array->FUN_10bfbd70(Index + 1);
            Array->Data[Index] = &It->Value;
        }
    }
}

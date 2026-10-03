// Game/Unsorted_10A79800.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E77578
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A, int B, int C, int D, int E);
};

Class_10E77578* FUN_10b0b2b0();

class Class_10E6BD90
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
    virtual void FUN_10a7a390(int A, int B);
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int FindIndex(int Item)
    {
        for (int i = 0; i < Unknown00; i++)
        {
            if (Unknown08[i] == Item)
                return i;
        }
        return -1;
    }

    void Append(int Item)
    {
        int Index = Unknown00;
        FUN_10bfbd70(Index + 1);
        Unknown08[Index] = Item;
    }

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E6BD68_Unknown0C
{
public:
    virtual ~Class_10E6BD68_Unknown0C();
};

class Class_10E6BD68_Unknown18
{
public:
    virtual ~Class_10E6BD68_Unknown18();
};

class Class_10E6BD68
{
public:
    virtual void FUN_10a795d0();
    virtual void FUN_10a79610();
    virtual void Virtual2();
    virtual void FUN_10a79d30(int Item);
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void FUN_10a7a340(void* A, int B);

    int Unknown04;
    int Unknown08;
    Class_10E6BD68_Unknown0C** Unknown0C;
    int Unknown10;
    int Unknown14;
    Class_10E6BD68_Unknown18** Unknown18;
    char Unknown1C[0xC];
    Class_10BFBD70 Unknown28;
};

// FUNCTION: 0x10A79D30 ?FUN_10a79d30@Class_10E6BD68@@UAEXH@Z
void Class_10E6BD68::FUN_10a79d30(int Item)
{
    if (Unknown28.FindIndex(Item) < 0)
        Unknown28.Append(Item);
}

// FUNCTION: 0x10A7A390 ?FUN_10a7a390@Class_10E6BD90@@UAEXHH@Z
void Class_10E6BD90::FUN_10a7a390(int A, int B)
{
    FUN_10b0b2b0()->Virtual5(A, 0, 0x281b9d0, B, 3);
}

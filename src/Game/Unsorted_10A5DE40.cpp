// Game/Unsorted_10A5DE40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10AF7F80
{
public:
    const char* FUN_10af7f80();
};

class Class_10A5EF80_Item
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual Class_10AF7F80* Virtual5();
};

class Class_1096A960
{
public:
    char** FUN_1096a960(char** Out);
};

extern "C" unsigned int strlen(const char*);

class Class_10A5E8A0
{
public:
    void FUN_10a5e8a0(char* Text);
};

class Class_10A79E60
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A);

    void FUN_10a79e60(void* A, void* B, int C);
};

struct Struct_10AA3520
{
    char Unknown00[0x40];
    Class_10A79E60* Unknown40;
};

extern Struct_10AA3520* DAT_10f35dec;

struct Item_10A5E900
{
    char Unknown00[0x2C];
    char Unknown2C[0xC];
    char Unknown38[0xC];
};

struct List_10A5E900
{
    int Unknown00;
    char Unknown04[4];
    Item_10A5E900** Unknown08;
};

class Class_10A5E900
{
public:
    void FUN_10a5e900(List_10A5E900* List);
};

// FUNCTION: 0x10A5E8A0 ?FUN_10a5e8a0@Class_10A5E8A0@@QAEXPAD@Z
void Class_10A5E8A0::FUN_10a5e8a0(char* Text)
{
    int Length = strlen(Text);
    for (int i = 0; i < Length; i++)
    {
        if (Text[i] == '*')
            Text[i] = ' ';
    }
}

// FUNCTION: 0x10A5E900 ?FUN_10a5e900@Class_10A5E900@@QAEXPAUList_10A5E900@@@Z
void Class_10A5E900::FUN_10a5e900(List_10A5E900* List)
{
    DAT_10f35dec->Unknown40->Virtual5(3);
    for (int i = 0; i < List->Unknown00; i++)
    {
        Item_10A5E900* Item = List->Unknown08[i];
        DAT_10f35dec->Unknown40->FUN_10a79e60(Item->Unknown2C, Item->Unknown38, 3);
    }
}

// FUNCTION: 0x10A5EF80 ?FUN_10a5ef80@@YGXPAVClass_1096A960@@PAVClass_10A5EF80_Item@@H@Z
void __stdcall FUN_10a5ef80(Class_1096A960* Owner, Class_10A5EF80_Item* Item, int C)
{
    if (Item->Virtual5())
        Item->Virtual5()->FUN_10af7f80();
    char* Data;
    Owner->FUN_1096a960(&Data);
    if (Data)
    {
        char* Block = Data - 4;
        FUN_10905aa0()->Virtual5(Block);
    }
}

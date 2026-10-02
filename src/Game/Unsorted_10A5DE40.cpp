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

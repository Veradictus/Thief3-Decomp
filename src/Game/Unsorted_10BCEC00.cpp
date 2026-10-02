// Game/Unsorted_10BCEC00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E92C38
{
public:
    virtual void Virtual0();
    virtual void FUN_10bcef30();

    void FUN_10bced10();

    char Unknown04[0x44];
    bool Unknown48;
    char Unknown49[2];
    bool Unknown4B;
};

class Class_10D9B090
{
public:
    char Unknown00[0xB8];
    bool UnknownB8;
};

Class_10D9B090* FUN_10d9dcb0();

class Class_10BCFE10
{
public:
    void FUN_10bcfbd0();
    void FUN_10bcfe10(int A);
};

// FUNCTION: 0x10BCEF30 ?FUN_10bcef30@Class_10E92C38@@UAEXXZ
void Class_10E92C38::FUN_10bcef30()
{
    if (Unknown4B && Unknown48)
    {
        FUN_10bced10();
        Unknown48 = false;
    }
}

// FUNCTION: 0x10BCFE10 ?FUN_10bcfe10@Class_10BCFE10@@QAEXH@Z
void Class_10BCFE10::FUN_10bcfe10(int A)
{
    if (!FUN_10d9dcb0()->UnknownB8)
        FUN_10bcfbd0();
}

// Game/Unsorted_10C176E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E8D7A8
{
public:
    Class_10E8D7A8(const Class_10E8D7A8& Other);

    virtual ~Class_10E8D7A8();

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
};

class Class_10BAE080
{
public:
    int FUN_10c176e0(const Class_10E8D7A8& Item);
    void FUN_10bad9d0(int Count);

    int Unknown00;
    int Unknown04;
    Class_10E8D7A8* Unknown08;
};

// FUNCTION: 0x10C176E0 ?FUN_10c176e0@Class_10BAE080@@QAEHABVClass_10E8D7A8@@@Z
int Class_10BAE080::FUN_10c176e0(const Class_10E8D7A8& Item)
{
    int Index = Unknown00;
    FUN_10bad9d0(Index + 1);
    Unknown08[Index] = Item;
    return Index;
}

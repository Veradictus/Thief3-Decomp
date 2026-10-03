// Game/Unsorted_10BA14C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Item_10BA14C0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Group_10BA14C0
{
    int Count;
    int Unknown04;
    Item_10BA14C0* Data;
};

struct Entry_10C32C30
{
    int Count;
    int Unknown04;
    Group_10BA14C0* Data;
};

class Class_10C49740
{
public:
    bool FUN_10c49740(int* Key, Entry_10C32C30** Out);
};

class Class_10E8C144
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual Item_10BA14C0* FUN_10ba14c0(int Key, int Index, int Group);

    Class_10C49740 Unknown04;
};

// FUNCTION: 0x10BA14C0 ?FUN_10ba14c0@Class_10E8C144@@UAEPAUItem_10BA14C0@@HHH@Z
Item_10BA14C0* Class_10E8C144::FUN_10ba14c0(int Key, int Index, int Group)
{
    Entry_10C32C30* Entry = 0;
    Unknown04.FUN_10c49740(&Key, &Entry);
    if (Entry && Group < Entry->Count)
    {
        Group_10BA14C0* G = &Entry->Data[Group];
        if (Index < G->Count)
            return &G->Data[Index];
    }
    return 0;
}

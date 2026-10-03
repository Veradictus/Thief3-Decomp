// Game/Unsorted_10BD09D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

void* FUN_10b232e0(void* A, void* B);

class Class_10E93138
{
public:
    virtual void FUN_10bd10a0(FArchive& Ar);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    void* Unknown00;
};

struct Item_10BD1320
{
    int Unknown00;
    Class_109081E0 Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10BD1320
{
public:
    int FUN_10bd1320(const Item_10BD1320* Item);
    void FUN_10bd0410(int NewCount);

    int Unknown00;
    int Unknown04;
    Item_10BD1320* Unknown08;
};

// FUNCTION: 0x10BD10A0 ?FUN_10bd10a0@Class_10E93138@@UAEXAAVFArchive@@@Z
void Class_10E93138::FUN_10bd10a0(FArchive& Ar)
{
    FUN_10b232e0(&Ar, &Unknown04);
    Ar.Serialize(&Unknown08, 4);
    Ar.Serialize(&Unknown0C, 4);
}

// FUNCTION: 0x10BD1320 ?FUN_10bd1320@Class_10BD1320@@QAEHPBUItem_10BD1320@@@Z
int Class_10BD1320::FUN_10bd1320(const Item_10BD1320* Item)
{
    int Index = Unknown00;
    FUN_10bd0410(Index + 1);
    Item_10BD1320* Dest = &Unknown08[Index];
    Dest->Unknown04 = Item->Unknown04;
    Dest->Unknown08 = Item->Unknown08;
    Dest->Unknown0C = Item->Unknown0C;
    return Index;
}

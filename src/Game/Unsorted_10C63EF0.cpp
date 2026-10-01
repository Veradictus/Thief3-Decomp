// Game/Unsorted_10C63EF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C63EF0;

bool FUN_10c5d5b0(int p1, int p2);

void FUN_10c5d830(void* Item, Class_10C63EF0* Owner);

class Class_10C63EF0
{
public:
    void FUN_10c63ef0(void* NewItem);

    char Unknown00[0x18];
    void* Unknown18;
};

class Class_10C63F20
{
public:
    bool FUN_10c63f20(int p1);

    char Unknown00[0x18];
    int Unknown18;
};

// FUNCTION: 0x10C63EF0 ?FUN_10c63ef0@Class_10C63EF0@@QAEXPAX@Z
void Class_10C63EF0::FUN_10c63ef0(void* NewItem)
{
    if (Unknown18)
        FUN_10c5d5b0((int)this, (int)Unknown18);
    Unknown18 = NewItem;
    FUN_10c5d830(NewItem, this);
}

// FUNCTION: 0x10C63F20 ?FUN_10c63f20@Class_10C63F20@@QAE_NH@Z
bool Class_10C63F20::FUN_10c63f20(int p1)
{
    bool Result = false;
    if (Unknown18)
    {
        Result = true;
        Unknown18 = 0;
    }
    return Result;
}

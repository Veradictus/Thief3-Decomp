// Game/Unsorted_10C32B40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C32C30
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Entry_10C32C30
{
    Struct_10C32C30* Unknown00;
};

class Class_10C49740
{
public:
    bool FUN_10c49740(int* Key, Entry_10C32C30** Out);
};

class Class_10C32C30
{
public:
    int FUN_10c32c30(int A);

    char Unknown00[0xC];
    Class_10C49740 Unknown0C;
};

// FUNCTION: 0x10C32C30 ?FUN_10c32c30@Class_10C32C30@@QAEHH@Z
int Class_10C32C30::FUN_10c32c30(int A)
{
    int Key = A;
    Entry_10C32C30* Value;
    Entry_10C32C30* Entry = Unknown0C.FUN_10c49740(&Key, &Value) ? Value : 0;
    Struct_10C32C30* Obj = Entry->Unknown00;
    if (Obj)
        return Obj->Unknown08;
    return 0;
}

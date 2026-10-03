// Game/Unsorted_10A68C10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A680C0
{
public:
    void FUN_10a680c0();
};

class Class_10E6B5B8
{
public:
    void FUN_10a68cb0();

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Class_10A680C0** Unknown0C;
};

// FUNCTION: 0x10A68CB0 ?FUN_10a68cb0@Class_10E6B5B8@@QAEXXZ
void Class_10E6B5B8::FUN_10a68cb0()
{
    for (int i = 0; i < Unknown04; i++)
    {
        Class_10A680C0* Item = Unknown0C[i];
        if (Item)
        {
            Item->FUN_10a680c0();
            ::operator delete(Item);
        }
    }
    Unknown04 = 0;
}

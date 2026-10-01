// Game/Unsorted_10C3E9F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9BB80 {
public:
    virtual void FUN_10c3e9f0(int p1, int* p2, int* p3);
};


class Class_10C3EA90
{
public:
    void FUN_10c3ea10(int A);
    void FUN_10c3ea90();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

// FUNCTION: 0x10C3E9F0 ?FUN_10c3e9f0@Class_10E9BB80@@UAEXHPAH0@Z
void Class_10E9BB80::FUN_10c3e9f0(int p1, int* p2, int* p3)
{
    *p2 = p1;
    *p3 = 4;
}

// FUNCTION: 0x10C3EA90 ?FUN_10c3ea90@Class_10C3EA90@@QAEXXZ
void Class_10C3EA90::FUN_10c3ea90()
{
    FUN_10c3ea10(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}

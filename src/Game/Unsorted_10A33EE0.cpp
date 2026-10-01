// Game/Unsorted_10A33EE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6649C
{
public:
    virtual void FUN_10a34760(int p1, int* p2, int* p3);
};


class Class_10A34B90
{
public:
    void FUN_10a34b90(int A);
    void FUN_10a35140();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Class_10A34CD0
{
public:
    void FUN_10a34cd0(int A);
    void FUN_10a35170();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

// FUNCTION: 0x10A34760 ?FUN_10a34760@Class_10E6649C@@UAEXHPAH0@Z
void Class_10E6649C::FUN_10a34760(int p1, int* p2, int* p3)
{
    *p2 = p1;
    *p3 = 0x10;
}

// FUNCTION: 0x10A35140 ?FUN_10a35140@Class_10A34B90@@QAEXXZ
void Class_10A34B90::FUN_10a35140()
{
    FUN_10a34b90(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}

// FUNCTION: 0x10A35170 ?FUN_10a35170@Class_10A34CD0@@QAEXXZ
void Class_10A34CD0::FUN_10a35170()
{
    FUN_10a34cd0(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}

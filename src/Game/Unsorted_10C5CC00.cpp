// Game/Unsorted_10C5CC00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C5CE70
{
};

class Class_10C5CE70
{
public:
    void FUN_10c5ce70();
    void FUN_10c5ccd0();

    char Unknown00[0x18];
    Struct_10C5CE70* Unknown18;
};

class Class_10C5CBF0
{
public:
    void FUN_10c5cbf0();

    Class_10C5CBF0* Unknown00;
    Class_10C5CBF0* Unknown04;
};

class Class_10C5CCD0
{
public:
    void FUN_10c5ccd0();

    char Unknown00[0x18];
    Class_10C5CBF0* Unknown18;
    int Unknown1C;
};

// FUNCTION: 0x10C5CCD0 ?FUN_10c5ccd0@Class_10C5CCD0@@QAEXXZ
void Class_10C5CCD0::FUN_10c5ccd0()
{
    Class_10C5CBF0* Node = Unknown18->Unknown00;
    Unknown18->Unknown00 = Unknown18;
    Unknown18->Unknown04 = Unknown18;
    Unknown1C = 0;
    while (Node != Unknown18)
    {
        Class_10C5CBF0* Next = Node->Unknown00;
        Node->FUN_10c5cbf0();
        ::operator delete(Node);
        Node = Next;
    }
}

// FUNCTION: 0x10C5CE70 ?FUN_10c5ce70@Class_10C5CE70@@QAEXXZ
void Class_10C5CE70::FUN_10c5ce70()
{
    FUN_10c5ccd0();
    delete Unknown18;
    Unknown18 = 0;
}

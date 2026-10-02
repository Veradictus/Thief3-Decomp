// Game/Unsorted_10C549A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C55090
{
public:
    void FUN_10c55090();

    Class_10C55090* Unknown00;
    Class_10C55090* Unknown04;
};

class Class_10C55800
{
public:
    void FUN_10c553a0();

    char Unknown00[0x18];
    Class_10C55090* Unknown18;
    int Unknown1C;
};

// FUNCTION: 0x10C553A0 ?FUN_10c553a0@Class_10C55800@@QAEXXZ
void Class_10C55800::FUN_10c553a0()
{
    Class_10C55090* Node = Unknown18->Unknown00;
    Unknown18->Unknown00 = Unknown18;
    Unknown18->Unknown04 = Unknown18;
    Unknown1C = 0;
    while (Node != Unknown18)
    {
        Class_10C55090* Next = Node->Unknown00;
        Node->FUN_10c55090();
        ::operator delete(Node);
        Node = Next;
    }
}

// Game/Unsorted_10A10570.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A10C20
{
public:
    void FUN_10a10c20();

    Class_10A10C20* Unknown00;
    Class_10A10C20* Unknown04;
};

class Class_10A111B0
{
public:
    void FUN_10a111b0();

    char Unknown00[0x18];
    Class_10A10C20* Unknown18;
    int Unknown1C;
};

// FUNCTION: 0x10A111B0 ?FUN_10a111b0@Class_10A111B0@@QAEXXZ
void Class_10A111B0::FUN_10a111b0()
{
    Class_10A10C20* Node = Unknown18->Unknown00;
    Unknown18->Unknown00 = Unknown18;
    Unknown18->Unknown04 = Unknown18;
    Unknown1C = 0;
    while (Node != Unknown18)
    {
        Class_10A10C20* Next = Node->Unknown00;
        Node->FUN_10a10c20();
        ::operator delete(Node);
        Node = Next;
    }
}

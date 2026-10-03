// Game/Unsorted_10AA35D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C1A690
{
public:
    void FUN_10c1a690();

    char Unknown00[4];
};

// A chained hash table's entry: 12 bytes, allocated per insert.
class Class_10AA44B0_Node
{
public:
    Class_10C1A690 Key;
    int Value;
    Class_10AA44B0_Node* Next;
};

class Class_10AA44B0
{
public:
    void FUN_10aa3830(int Size);
    void FUN_10aa36b0(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10AA44B0_Node** Unknown14;
};

// FUNCTION: 0x10AA3830 ?FUN_10aa3830@Class_10AA44B0@@QAEXH@Z
void Class_10AA44B0::FUN_10aa3830(int Size)
{
    for (int i = 0; i < Unknown0C; i++)
    {
        Class_10AA44B0_Node* Node = Unknown14[i];
        while (Node)
        {
            Class_10AA44B0_Node* Next = Node->Next;
            Node->Key.FUN_10c1a690();
            ::operator delete(Node);
            Node = Next;
        }
    }
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown00 = 0;
    ::operator delete(Unknown14);
    Unknown14 = 0;
    if (!Unknown10)
        FUN_10aa36b0(Size);
}

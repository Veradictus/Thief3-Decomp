// Game/Unsorted_10C2F970_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// A chained hash table's entry, allocated per insert.
class Class_10C30D10_Node
{
public:
    int Unknown00;
    int Unknown04;
    Class_10C30D10_Node* Next;
};

class Class_10C30D10
{
public:
    void FUN_10c30e90(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10C30D10_Node** Unknown14;
};

class Class_10C32C70 : public Class_10C30D10
{
public:
    void FUN_10c325e0(int Size);
};

// FUNCTION: 0x10C325E0 ?FUN_10c325e0@Class_10C32C70@@QAEXH@Z
void Class_10C32C70::FUN_10c325e0(int Size)
{
    for (int i = 0; i < Unknown0C; i++)
    {
        Class_10C30D10_Node* Node = Unknown14[i];
        while (Node)
        {
            Class_10C30D10_Node* Next = Node->Next;
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
        FUN_10c30e90(Size);
}

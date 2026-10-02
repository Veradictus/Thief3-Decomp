// Game/Unsorted_10A858C0_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// A chained hash table's entry, allocated per insert.
class Class_10A85940_Node
{
public:
    int Unknown00;
    int Unknown04;
    Class_10A85940_Node* Next;
};

class Class_10A85940
{
public:
    void FUN_10a85a00(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10A85940_Node** Unknown14;
};

class Class_10A873D0 : public Class_10A85940
{
public:
    void FUN_10a86490(int Size);
};

// FUNCTION: 0x10A86490 ?FUN_10a86490@Class_10A873D0@@QAEXH@Z
void Class_10A873D0::FUN_10a86490(int Size)
{
    for (int i = 0; i < Unknown0C; i++)
    {
        Class_10A85940_Node* Node = Unknown14[i];
        while (Node)
        {
            Class_10A85940_Node* Next = Node->Next;
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
        FUN_10a85a00(Size);
}

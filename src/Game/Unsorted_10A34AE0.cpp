// Game/Unsorted_10A34AE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// A chained hash table's entry, allocated per insert.
class Class_10A34B90_Node
{
public:
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    Class_10A34B90_Node* Next;
};

class Class_10A34B90
{
public:
    void FUN_10a34810(int Size);
    void FUN_10a34b90(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10A34B90_Node** Unknown14;
};

// FUNCTION: 0x10A34B90 ?FUN_10a34b90@Class_10A34B90@@QAEXH@Z
void Class_10A34B90::FUN_10a34b90(int Size)
{
    for (int i = 0; i < Unknown0C; i++)
    {
        Class_10A34B90_Node* Node = Unknown14[i];
        while (Node)
        {
            Class_10A34B90_Node* Next = Node->Next;
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
        FUN_10a34810(Size);
}

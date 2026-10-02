// Game/Unsorted_109E6D80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's string (0x109081E0): a char pointer, null when default constructed.
class Class_109081E0
{
public:
    ~Class_109081E0();

    char* Unknown00;
};

// A chained hash table's entry: 12 bytes, allocated per insert.
class Class_109E6520_Node
{
public:
    Class_109081E0 Key;
    int Value;
    Class_109E6520_Node* Next;
};

class Class_109E6520
{
public:
    void FUN_109e6600(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_109E6520_Node** Unknown14;
};

class Class_109E7C30 : public Class_109E6520
{
public:
    void FUN_109e7c30(int Size);
};

// FUNCTION: 0x109E7C30 ?FUN_109e7c30@Class_109E7C30@@QAEXH@Z
void Class_109E7C30::FUN_109e7c30(int Size)
{
    for (int i = 0; i < Unknown0C; i++)
    {
        Class_109E6520_Node* Node = Unknown14[i];
        while (Node)
        {
            Class_109E6520_Node* Next = Node->Next;
            Node->Key.~Class_109081E0();
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
        FUN_109e6600(Size);
}

// Game/Unsorted_10919CB0_6.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's string (0x109081E0): a char pointer, null when default constructed.
class Class_109081E0
{
public:
    ~Class_109081E0();

    char* Unknown00;
};

// A chained hash table's entry: 12 bytes, allocated per insert.
class Class_1091AD50_Node
{
public:
    Class_109081E0 Key;
    int Value;
    Class_1091AD50_Node* Next;
};

class Class_1091AD50
{
public:
    void FUN_1091ae30(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_1091AD50_Node** Unknown14;
};

class Class_1091C820 : public Class_1091AD50
{
public:
    void FUN_1091b370(int Size);
};

// FUNCTION: 0x1091B370 ?FUN_1091b370@Class_1091C820@@QAEXH@Z
void Class_1091C820::FUN_1091b370(int Size)
{
    for (int i = 0; i < Unknown0C; i++)
    {
        Class_1091AD50_Node* Node = Unknown14[i];
        while (Node)
        {
            Class_1091AD50_Node* Next = Node->Next;
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
        FUN_1091ae30(Size);
}

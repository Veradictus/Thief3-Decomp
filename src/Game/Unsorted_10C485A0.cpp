// Game/Unsorted_10C485A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// A chained hash table's entry: 12 bytes, allocated per insert.
class Class_10C48260_Node
{
public:
    int Key;
    int Value;
    Class_10C48260_Node* Next;
};

// The hash table of 0x1090F080 (Class_1090F080) over another key type.
class Class_10C48260
{
public:
    void FUN_10c48400(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10C48260_Node** Unknown14;
};

class Class_10C49200 : public Class_10C48260
{
public:
    void FUN_10c48b80(int Size);
};

// FUNCTION: 0x10C48B80 ?FUN_10c48b80@Class_10C49200@@QAEXH@Z
void Class_10C49200::FUN_10c48b80(int Size)
{
    for (int i = 0; i < Unknown0C; i++)
    {
        Class_10C48260_Node* Node = Unknown14[i];
        while (Node)
        {
            Class_10C48260_Node* Next = Node->Next;
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
        FUN_10c48400(Size);
}

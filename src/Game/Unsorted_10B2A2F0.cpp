// Game/Unsorted_10B2A2F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

// The table's key hasher: slot 0 gives the bytes FUN_1090e9b0 hashes,
// slot 1 compares a key with an entry's key (0 when they are equal).
class Class_10B2A160_Field18
{
public:
    virtual void Virtual0(const int& Key, const void** Data, int* Length);
    virtual int Virtual1(const int& Key, const int& Other);
};

// The hash table of 0x10B2A160.
class Class_10B2A160
{
public:
    unsigned int FUN_10b2a160(const int& Key, const int& Value);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    void* Unknown14;
    Class_10B2A160_Field18 Unknown18;
};

// A doubly linked list entry: 12 bytes, linked at the tail.
class Class_10B2A2F0_Node
{
public:
    Class_10B2A2F0_Node() : Next((Class_10B2A2F0_Node*)-1), Prev((Class_10B2A2F0_Node*)-1) {}

    Class_10B2A2F0_Node* Next;
    Class_10B2A2F0_Node* Prev;
    void* Value;
};

// A linked list whose values are also indexed by a hash table.
class Class_10B2A2F0
{
public:
    void FUN_10b2a2f0(void* Value);

    int Count;
    Class_10B2A2F0_Node* Head;
    Class_10B2A2F0_Node* Tail;
    Class_10B2A160 Index;
};

// FUNCTION: 0x10B2A2F0 ?FUN_10b2a2f0@Class_10B2A2F0@@QAEXPAX@Z
void Class_10B2A2F0::FUN_10b2a2f0(void* Value)
{
    int Link = 0;
    Class_10B2A2F0_Node* Node = new(Link, 0, 0, 0, 0) Class_10B2A2F0_Node();
    Node->Value = Value;
    Node->Prev = Tail;
    Node->Next = 0;
    Link = (int)Node;
    if (Tail)
        Tail->Next = Node;
    Tail = Node;
    if (!Head)
        Head = Node;
    Count++;
    Index.FUN_10b2a160((int)Value, Link);
}

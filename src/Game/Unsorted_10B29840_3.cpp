// Game/Unsorted_10B29840_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

unsigned int FUN_1090e9b0(const void* Data, int Length);

// A chained hash table's entry: 12 bytes, allocated per insert.
class Class_10B2A160_Node
{
public:
    int Key;
    int Value;
    Class_10B2A160_Node* Next;
};

// The table's key hasher: slot 0 gives the bytes FUN_1090e9b0 hashes.
class Class_10B2A160_Field18
{
public:
    virtual void Virtual0(const int& Key, const void** Data, int* Length);
};

// The hash table of 0x1090F080 (Class_1090F080) over another key type.
class Class_10B2A160
{
public:
    unsigned int FUN_10b2a160(const int& Key, const int& Value);
    void FUN_10b2a220(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10B2A160_Node** Unknown14;
    Class_10B2A160_Field18 Unknown18;
};

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B, int C, int D, int E);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10B2AB30
{
public:
    void FUN_10b2a8a0(int Count);
    void FUN_10b2ab30();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x10B2A160 ?FUN_10b2a160@Class_10B2A160@@QAEIABH0@Z
unsigned int Class_10B2A160::FUN_10b2a160(const int& Key, const int& Value)
{
    if (!Unknown10 && Unknown00 > Unknown0C * 0.2)
        FUN_10b2a220(Unknown0C * 2);
    Class_10B2A160_Node* Node = new(0, 0, 0, 0, 0) Class_10B2A160_Node;
    Node->Key = Key;
    Node->Value = Value;
    unsigned int Index;
    {
        const void* Data;
        int Length;
        Unknown18.Virtual0(Key, &Data, &Length);
        Index = FUN_1090e9b0(Data, Length) & ((1 << Unknown08) - 1);
    }
    if (Unknown14[Index])
        Unknown00++;
    Node->Next = Unknown14[Index];
    Unknown14[Index] = Node;
    Unknown04++;
    return Index;
}

// FUNCTION: 0x10B2A220 ?FUN_10b2a220@Class_10B2A160@@QAEXH@Z
void Class_10B2A160::FUN_10b2a220(int Size)
{
    int OldSize = Unknown0C;
    Class_10B2A160_Node** OldBuckets = Unknown14;
    Unknown14 = new(0, 0, 0, 0, 0) Class_10B2A160_Node*[Size];
    Unknown0C = Size;
    Unknown08 = 0;
    while (Size >>= 1)
        Unknown08++;
    Unknown04 = 0;
    Unknown00 = 0;
    for (int i = 0; i < Unknown0C; i++)
        Unknown14[i] = 0;
    for (int j = 0; j < OldSize; j++)
    {
        Class_10B2A160_Node* Node = OldBuckets[j];
        while (Node)
        {
            FUN_10b2a160(Node->Key, Node->Value);
            Class_10B2A160_Node* Next = Node->Next;
            delete Node;
            Node = Next;
        }
    }
    delete OldBuckets;
}

// FUNCTION: 0x10B2AB30 ?FUN_10b2ab30@Class_10B2AB30@@QAEXXZ
void Class_10B2AB30::FUN_10b2ab30()
{
    FUN_10b2a8a0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// Game/Unsorted_10C013C0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

unsigned int FUN_1090e9b0(const void* Data, int Length);

// A chained hash table's entry: 12 bytes, allocated per insert.
class Class_10C01140_Node
{
public:
    int Key;
    int Value;
    Class_10C01140_Node* Next;
};

// The table's key hasher: slot 0 gives the bytes FUN_1090e9b0 hashes,
// slot 1 compares a key with an entry's key (0 when they are equal).
class Class_10C01140_Field18
{
public:
    virtual void Virtual0(const int& Key, const void** Data, int* Length);
    virtual int Virtual1(const int& Key, const int& Other);
};

// The hash table of 0x1090F080 (Class_1090F080) over another key type.
class Class_10C01140
{
public:
    unsigned int FUN_10c01140(const int& Key, const int& Value);
    void FUN_10c012d0(int Size);
    bool FUN_10c015b0(const int& Key);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10C01140_Node** Unknown14;
    Class_10C01140_Field18 Unknown18;
};

// A chained hash table's entry, allocated per insert.
class Class_10C00F60_Node
{
public:
    int Unknown00;
    int Unknown04;
    Class_10C00F60_Node* Next;
};

class Class_10C00F60
{
public:
    void FUN_10c01200(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10C00F60_Node** Unknown14;
};

class Class_10C01F50 : public Class_10C00F60
{
public:
    void FUN_10c01730(int Size);
};

// FUNCTION: 0x10C015B0 ?FUN_10c015b0@Class_10C01140@@QAE_NABH@Z
bool Class_10C01140::FUN_10c015b0(const int& Key)
{
    if (!Unknown10 && Unknown04 < Unknown0C * 0.05 && Unknown0C > 64)
        FUN_10c012d0(Unknown0C / 2);
    unsigned int Index;
    {
        const void* Data;
        int Length;
        Unknown18.Virtual0(Key, &Data, &Length);
        Index = FUN_1090e9b0(Data, Length) & ((1 << Unknown08) - 1);
    }
    for (Class_10C01140_Node* Node = Unknown14[Index], *Prev = 0; Node; Prev = Node, Node = Node->Next)
    {
        if (Unknown18.Virtual1(Key, Node->Key) == 0)
        {
            if (Prev || Node->Next)
                Unknown00--;
            if (!Prev)
                Unknown14[Index] = Node->Next;
            else
                Prev->Next = Node->Next;
            Unknown04--;
            delete Node;
            return true;
        }
    }
    return false;
}

// FUNCTION: 0x10C01730 ?FUN_10c01730@Class_10C01F50@@QAEXH@Z
void Class_10C01F50::FUN_10c01730(int Size)
{
    for (int i = 0; i < Unknown0C; i++)
    {
        Class_10C00F60_Node* Node = Unknown14[i];
        while (Node)
        {
            Class_10C00F60_Node* Next = Node->Next;
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
        FUN_10c01200(Size);
}

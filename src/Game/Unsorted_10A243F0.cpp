// Game/Unsorted_10A243F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10A243F0
{
public:
    void FUN_10a243f0(int A);
    void FUN_10a24580();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// Ion Storm's string (0x109081E0): a char pointer, null when default constructed.
class Class_109081E0
{
public:
    Class_109081E0() : Unknown00(0) {}
    ~Class_109081E0();
    Class_109081E0& operator=(const Class_109081E0& Other);

    char* Unknown00;
};

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

// A chained hash table's entry from a string to a string: 12 bytes, allocated
// per insert; its implicit destructor (0x10A24660) frees both strings.
class Class_10A250D0_Node
{
public:
    Class_109081E0 Key;
    Class_109081E0 Value;
    Class_10A250D0_Node* Next;
};

// The table's key hasher: slot 0 gives the bytes FUN_1090e9b0 hashes.
class Class_10A250D0_Field18
{
public:
    virtual void Virtual0(const Class_109081E0& Key, const void** Data, int* Length);
};

// The hash table of 0x1090F080 (Class_1090F080) with string values.
class Class_10A250D0
{
public:
    unsigned int FUN_10a250d0(const Class_109081E0& Key, const Class_109081E0& Value);
    void FUN_10a251b0(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10A250D0_Node** Unknown14;
    Class_10A250D0_Field18 Unknown18;
};

class Class_10A24540
{
public:
    void FUN_10a24540(char Old, char New);

    char* Unknown00;
};

// FUNCTION: 0x10A24540 ?FUN_10a24540@Class_10A24540@@QAEXDD@Z
void Class_10A24540::FUN_10a24540(char Old, char New)
{
    for (int i = 0; i < (Unknown00 == 0 ? 0 : ((int*)Unknown00)[-1]); i++)
    {
        if (Unknown00[i] == Old)
            Unknown00[i] = New;
    }
}

// FUNCTION: 0x10A24580 ?FUN_10a24580@Class_10A243F0@@QAEXXZ
void Class_10A243F0::FUN_10a24580()
{
    FUN_10a243f0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10A251B0 ?FUN_10a251b0@Class_10A250D0@@QAEXH@Z
void Class_10A250D0::FUN_10a251b0(int Size)
{
    int OldSize = Unknown0C;
    Class_10A250D0_Node** OldBuckets = Unknown14;
    Unknown14 = new(0, 0, 0, 0, 0) Class_10A250D0_Node*[Size];
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
        Class_10A250D0_Node* Node = OldBuckets[j];
        while (Node)
        {
            FUN_10a250d0(Node->Key, Node->Value);
            Class_10A250D0_Node* Next = Node->Next;
            delete Node;
            Node = Next;
        }
    }
    delete OldBuckets;
}

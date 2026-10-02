// Game/Unsorted_10C49260.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10D3F830
{
public:
    bool FUN_10d3f830(int* p1);
};

struct Struct_10C49860
{
    int Unknown00;
    int Unknown04;
};

class Class_10E9BBC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void FUN_10c49860(Struct_10C49860* A);

    Class_10D3F830 Unknown04;
};

int FUN_10c48c80(int A);

class Class_10E9BB8C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void FUN_10c49f50(int A);

    void FUN_10c49340(int A);
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

unsigned int FUN_1090e9b0(const void* Data, int Length);

// A chained hash table's entry: 12 bytes, allocated per insert.
class Class_10C49100_Node
{
public:
    Class_109081E0 Key;
    int Value;
    Class_10C49100_Node* Next;
};

// The table's key hasher: slot 0 gives the bytes FUN_1090e9b0 hashes.
class Class_10C49100_Field18
{
public:
    virtual void Virtual0(const Class_109081E0& Key, const void** Data, int* Length);
};

class Class_10C49100
{
public:
    unsigned int FUN_10c49100(const Class_109081E0& Key, const int& Value);
    void FUN_10c49260(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10C49100_Node** Unknown14;
    Class_10C49100_Field18 Unknown18;
};

// FUNCTION: 0x10C49260 ?FUN_10c49260@Class_10C49100@@QAEXH@Z
void Class_10C49100::FUN_10c49260(int Size)
{
    int OldSize = Unknown0C;
    Class_10C49100_Node** OldBuckets = Unknown14;
    Unknown14 = new(0, 0, 0, 0, 0) Class_10C49100_Node*[Size];
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
        Class_10C49100_Node* Node = OldBuckets[j];
        while (Node)
        {
            FUN_10c49100(Node->Key, Node->Value);
            Class_10C49100_Node* Next = Node->Next;
            Node->Key.~Class_109081E0();
            ::operator delete(Node);
            Node = Next;
        }
    }
    delete OldBuckets;
}

// FUNCTION: 0x10C49860 ?FUN_10c49860@Class_10E9BBC0@@UAEXPAUStruct_10C49860@@@Z
void Class_10E9BBC0::FUN_10c49860(Struct_10C49860* A)
{
    int Key = A->Unknown04;
    Unknown04.FUN_10d3f830(&Key);
}

// FUNCTION: 0x10C49F50 ?FUN_10c49f50@Class_10E9BB8C@@UAEXH@Z
void Class_10E9BB8C::FUN_10c49f50(int A)
{
    FUN_10c49340(FUN_10c48c80(A));
}

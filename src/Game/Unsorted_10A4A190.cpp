// Game/Unsorted_10A4A190.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

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
class Class_10A492B0_Node
{
public:
    Class_109081E0 Key;
    int Value;
    Class_10A492B0_Node* Next;
};

// The table's key hasher: slot 0 gives the bytes FUN_1090e9b0 hashes.
class Class_10A492B0_Field18
{
public:
    virtual void Virtual0(const Class_109081E0& Key, const void** Data, int* Length);
};

class Class_10A492B0
{
public:
    unsigned int FUN_10a492b0(const Class_109081E0& Key, const int& Value);
    void FUN_10a4ab10(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10A492B0_Node** Unknown14;
    Class_10A492B0_Field18 Unknown18;
};

// FUNCTION: 0x10A4AB10 ?FUN_10a4ab10@Class_10A492B0@@QAEXH@Z
void Class_10A492B0::FUN_10a4ab10(int Size)
{
    int OldSize = Unknown0C;
    Class_10A492B0_Node** OldBuckets = Unknown14;
    Unknown14 = new(0, 0, 0, 0, 0) Class_10A492B0_Node*[Size];
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
        Class_10A492B0_Node* Node = OldBuckets[j];
        while (Node)
        {
            FUN_10a492b0(Node->Key, Node->Value);
            Class_10A492B0_Node* Next = Node->Next;
            Node->Key.~Class_109081E0();
            ::operator delete(Node);
            Node = Next;
        }
    }
    delete OldBuckets;
}

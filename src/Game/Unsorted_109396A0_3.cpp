// Game/Unsorted_109396A0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

// Ion Storm's string: a char buffer it frees on destruction.
class Class_109081E0
{
public:
    ~Class_109081E0();

    char* Unknown00;
};

// A chained hash table's entry keyed by a string: 12 bytes, allocated per insert.
class Class_1093AF30_Node
{
public:
    Class_109081E0 Key;
    int Value;
    Class_1093AF30_Node* Next;
};

// The hash table of 0x10A85940 (Class_10A85940) over a string key.
class Class_1093AF30
{
public:
    unsigned int FUN_1093af30(const Class_109081E0& Key, const int& Value);
    void FUN_1093b040(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_1093AF30_Node** Unknown14;
};

// FUNCTION: 0x1093B040 ?FUN_1093b040@Class_1093AF30@@QAEXH@Z
void Class_1093AF30::FUN_1093b040(int Size)
{
    int OldSize = Unknown0C;
    Class_1093AF30_Node** OldBuckets = Unknown14;
    Unknown14 = new(0, 0, 0, 0, 0) Class_1093AF30_Node*[Size];
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
        Class_1093AF30_Node* Node = OldBuckets[j];
        while (Node)
        {
            FUN_1093af30(Node->Key, Node->Value);
            Class_1093AF30_Node* Next = Node->Next;
            delete Node;
            Node = Next;
        }
    }
    delete OldBuckets;
}

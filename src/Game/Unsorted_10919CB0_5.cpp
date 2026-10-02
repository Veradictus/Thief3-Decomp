// Game/Unsorted_10919CB0_5.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// A string-keyed hash table: buckets of singly linked nodes.

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

// A bucket entry (12 bytes; FUN_1091ad50 allocates it).
struct Class_1091AD50_Node
{
    Class_109081E0 Key;
    int Value;
    Class_1091AD50_Node* Next;
};

class Class_1091AD50
{
public:
    unsigned int FUN_1091ad50(const Class_109081E0& Key, const int& Value);
    void FUN_1091ae30(int NewSize);

    int Collisions;
    int Count;
    int Bits;
    int Size;
    bool Unknown10;
    Class_1091AD50_Node** Table;
};

// FUNCTION: 0x1091AE30 ?FUN_1091ae30@Class_1091AD50@@QAEXH@Z
void Class_1091AD50::FUN_1091ae30(int NewSize)
{
    int OldSize = Size;
    Class_1091AD50_Node** OldTable = Table;
    Table = (Class_1091AD50_Node**)operator new(NewSize * sizeof(Class_1091AD50_Node*), 0, 0, 0, 0, 0);
    Size = NewSize;
    Bits = 0;
    while (NewSize >>= 1)
        Bits++;
    Count = 0;
    Collisions = 0;
    for (int i = 0; i < Size; i++)
        Table[i] = 0;
    for (int j = 0; j < OldSize; j++)
    {
        Class_1091AD50_Node* Node = OldTable[j];
        while (Node)
        {
            FUN_1091ad50(Node->Key, Node->Value);
            Class_1091AD50_Node* Next = Node->Next;
            delete Node;
            Node = Next;
        }
    }
    ::operator delete(OldTable);
}

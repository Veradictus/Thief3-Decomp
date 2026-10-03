// Game/Unsorted_109E6240.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <list>

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
class Class_109E6520_Node
{
public:
    Class_109081E0 Key;
    int Value;
    Class_109E6520_Node* Next;
};

// The table's key hasher: slot 0 gives the bytes FUN_1090e9b0 hashes.
class Class_109E6520_Field18
{
public:
    virtual void Virtual0(const Class_109081E0& Key, const void** Data, int* Length);
};

class Class_109E6520
{
public:
    unsigned int FUN_109e6520(const Class_109081E0& Key, const int& Value);
    void FUN_109e6600(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_109E6520_Node** Unknown14;
    Class_109E6520_Field18 Unknown18;
};

class Class_10E5B7C8_Unknown88
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
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16(int A);
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual void Virtual44();
    virtual void Virtual45();
    virtual void Virtual46();
    virtual void Virtual47();
    virtual void Virtual48();
    virtual void Virtual49();
    virtual void Virtual50();
    virtual void Virtual51();
    virtual void Virtual52();
    virtual void Virtual53();
    virtual bool Virtual54();
};

class Class_10E5B7C8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_109e64e0();

    char Unknown04[0x84];
    std::list<Class_10E5B7C8_Unknown88*> Unknown88;
};

// FUNCTION: 0x109E64E0 ?FUN_109e64e0@Class_10E5B7C8@@UAEXXZ
void Class_10E5B7C8::FUN_109e64e0()
{
    for (std::list<Class_10E5B7C8_Unknown88*>::iterator It = Unknown88.begin(); It != Unknown88.end(); ++It)
    {
        Class_10E5B7C8_Unknown88* Item = *It;
        if (Item->Virtual54())
            Item->Virtual16(1);
    }
}

// FUNCTION: 0x109E6520 ?FUN_109e6520@Class_109E6520@@QAEIABVClass_109081E0@@ABH@Z
unsigned int Class_109E6520::FUN_109e6520(const Class_109081E0& Key, const int& Value)
{
    if (!Unknown10 && Unknown00 > Unknown0C * 0.2)
        FUN_109e6600(Unknown0C * 2);
    Class_109E6520_Node* Node = new(0, 0, 0, 0, 0) Class_109E6520_Node;
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

// FUNCTION: 0x109E6600 ?FUN_109e6600@Class_109E6520@@QAEXH@Z
void Class_109E6520::FUN_109e6600(int Size)
{
    int OldSize = Unknown0C;
    Class_109E6520_Node** OldBuckets = Unknown14;
    Unknown14 = new(0, 0, 0, 0, 0) Class_109E6520_Node*[Size];
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
        Class_109E6520_Node* Node = OldBuckets[j];
        while (Node)
        {
            FUN_109e6520(Node->Key, Node->Value);
            Class_109E6520_Node* Next = Node->Next;
            delete Node;
            Node = Next;
        }
    }
    delete OldBuckets;
}

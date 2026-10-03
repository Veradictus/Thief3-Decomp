// Game/Unsorted_10C31030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

// The table's key hasher: slot 0 gives the bytes FUN_1090e9b0 hashes,
// slot 1 compares a key with an entry's key (0 when they are equal).
class Class_10C30D10_Field18
{
public:
    virtual void Virtual0(const int& Key, const void** Data, int* Length);
    virtual int Virtual1(const int& Key, const int& Other);
};

// The hash table of 0x10B2A160.
class Class_10C30D10
{
public:
    unsigned int FUN_10c30d10(const int& Key, const int& Value);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    void* Unknown14;
    Class_10C30D10_Field18 Unknown18;
};

// A doubly linked list entry: 12 bytes, linked at the tail.
class Class_10C323A0_Node
{
public:
    Class_10C323A0_Node() : Next((Class_10C323A0_Node*)-1), Prev((Class_10C323A0_Node*)-1) {}

    Class_10C323A0_Node* Next;
    Class_10C323A0_Node* Prev;
    void* Value;
};

// A linked list whose values are also indexed by a hash table.
class Class_10C323A0
{
public:
    void FUN_10c323a0(void* Value);

    int Count;
    Class_10C323A0_Node* Head;
    Class_10C323A0_Node* Tail;
    Class_10C30D10 Index;
};

extern float DAT_10eafbdc;

class Class_109BC840
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
    virtual void Virtual16();
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
    virtual void Virtual54();
    virtual void Virtual55();
    virtual void Virtual56();
    virtual void Virtual57();
    virtual void Virtual58();
    virtual void Virtual59();
    virtual void Virtual60();
    virtual void Virtual61();
    virtual void Virtual62();
    virtual void Virtual63();
    virtual void Virtual64();
    virtual void Virtual65();
    virtual void Virtual66();
    virtual float Virtual67(int A);
};

class Class_10BAA580
{
public:
    Class_109BC840* FUN_10baa580();
};

class Class_10C311D0
{
public:
    void FUN_10c311d0();
    void FUN_10c30240(int A, int B);

    char Unknown00[8];
    Class_10BAA580* Unknown08;
    char Unknown0C[0x108];
    char Unknown114;
};

// FUNCTION: 0x10C311D0 ?FUN_10c311d0@Class_10C311D0@@QAEXXZ
void Class_10C311D0::FUN_10c311d0()
{
    Class_109BC840* P = Unknown08->FUN_10baa580();
    if (P)
    {
        if (P->Virtual67(7) < DAT_10eafbdc)
        {
            Unknown114 = 1;
            FUN_10c30240(7, 0);
        }
    }
}

// FUNCTION: 0x10C323A0 ?FUN_10c323a0@Class_10C323A0@@QAEXPAX@Z
void Class_10C323A0::FUN_10c323a0(void* Value)
{
    int Link = 0;
    Class_10C323A0_Node* Node = new(Link, 0, 0, 0, 0) Class_10C323A0_Node();
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
    Index.FUN_10c30d10((int)Value, Link);
}

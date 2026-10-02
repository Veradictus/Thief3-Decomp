// Game/Unsorted_10A87400_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// A list of nodes (Count, Head, Tail) and a Class_10A873D0 at +0xC.

class Class_10A873D0
{
public:
    ~Class_10A873D0()
    {
        FUN_10a86490(0x40);
        ::operator delete(Unknown14);
        Unknown04 = 0;
        Unknown0C = 0;
        Unknown14 = 0;
        Unknown00 = 0;
    }

    void FUN_10a86490(int A);

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

struct Class_10A87C00_Node
{
    Class_10A87C00_Node* Next;
    Class_10A87C00_Node* Prev;
};

class Class_10A87C00
{
public:
    ~Class_10A87C00();

    int Count;
    Class_10A87C00_Node* Head;
    Class_10A87C00_Node* Tail;
    Class_10A873D0 Unknown0C;
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

class Class_10A87F40
{
public:
    void FUN_10a87cd0(int Count);
    void FUN_10a87f40();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x10A87C00 ??1Class_10A87C00@@QAE@XZ
Class_10A87C00::~Class_10A87C00()
{
    while (Head)
    {
        Class_10A87C00_Node* Node = Head;
        Head = Node->Next;
        if (Tail == Node)
            Tail = Node->Prev;
        if (Node->Next)
            Node->Next->Prev = Node->Prev;
        if (Node->Prev)
            Node->Prev->Next = Node->Next;
        Node->Next = (Class_10A87C00_Node*)-1;
        Node->Prev = (Class_10A87C00_Node*)-1;
        Count--;
        delete Node;
    }
    Unknown0C.FUN_10a86490(0x40);
}

// FUNCTION: 0x10A87F40 ?FUN_10a87f40@Class_10A87F40@@QAEXXZ
void Class_10A87F40::FUN_10a87f40()
{
    FUN_10a87cd0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

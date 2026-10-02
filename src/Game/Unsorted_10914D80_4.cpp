// Game/Unsorted_10914D80_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780;

class Class_109169E0
{
public:
    void FUN_109172f0(int B);
};

class Class_10915210
{
public:
    Class_109169E0* FUN_10915210(const Class_1090A780& Name);
    void FUN_109152a0(const Class_1090A780& Name, int B);
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

unsigned int FUN_1090e9b0(const void* Data, int Length);

// A chained hash table's entry: 12 bytes, allocated per insert.
class Class_10914D80_Node
{
public:
    Class_109081E0 Key;
    int Value;
    Class_10914D80_Node* Next;
};

// The table's key hasher: slot 0 gives the bytes FUN_1090e9b0 hashes,
// slot 1 compares a key with an entry's key (0 when they are equal).
class Class_10914D80_Field18
{
public:
    virtual void Virtual0(const Class_109081E0& Key, const void** Data, int* Length);
    virtual int Virtual1(const Class_109081E0& Key, const Class_109081E0& Other);
};

class Class_10914D80
{
public:
    unsigned int FUN_10914d80(const Class_109081E0& Key, const int& Value);
    void FUN_10914e60(int Size);
    bool FUN_109153e0(const Class_109081E0& Key);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10914D80_Node** Unknown14;
    Class_10914D80_Field18 Unknown18;
};

// FUNCTION: 0x109152A0 ?FUN_109152a0@Class_10915210@@QAEXABVClass_1090A780@@H@Z
void Class_10915210::FUN_109152a0(const Class_1090A780& Name, int B)
{
    Class_109169E0* Obj = FUN_10915210(Name);
    if (Obj)
        Obj->FUN_109172f0(B);
}

// FUNCTION: 0x109153E0 ?FUN_109153e0@Class_10914D80@@QAE_NABVClass_109081E0@@@Z
bool Class_10914D80::FUN_109153e0(const Class_109081E0& Key)
{
    if (!Unknown10 && Unknown04 < Unknown0C * 0.05 && Unknown0C > 64)
        FUN_10914e60(Unknown0C / 2);
    unsigned int Index;
    {
        const void* Data;
        int Length;
        Unknown18.Virtual0(Key, &Data, &Length);
        Index = FUN_1090e9b0(Data, Length) & ((1 << Unknown08) - 1);
    }
    for (Class_10914D80_Node* Node = Unknown14[Index], *Prev = 0; Node; Prev = Node, Node = Node->Next)
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
            Node->Key.~Class_109081E0();
            ::operator delete(Node);
            return true;
        }
    }
    return false;
}

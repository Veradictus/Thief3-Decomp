// Game/Unsorted_10B40620.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual ~Class_10E67FD0();

    char Unknown04[0x114];
};

class Class_10E7FD18 : public Class_10E67FD0
{
public:
    Class_10E7FD18();

    virtual ~Class_10E7FD18();

    int Unknown118;
    int Unknown11C;
    int Unknown120;
    int Unknown124;
    FArray Unknown128;
    int Unknown134;
};

struct Struct_10B406A0
{
    Struct_10B406A0() : Unknown00(0) {}

    int Unknown00;
};

class Class_10E696A8
{
public:
    Class_10E696A8();

    virtual ~Class_10E696A8();

    char Unknown04[0x1C8];
};

class Class_10E7FB08 : public Class_10E696A8
{
public:
    Class_10E7FB08();

    virtual ~Class_10E7FB08();

    int Unknown1CC;
    int Unknown1D0;
    int Unknown1D4;
    int Unknown1D8;
    Struct_10B406A0 Unknown1DC;
    int Unknown1E0;
    int Unknown1E4;
    int Unknown1E8;
    int Unknown1EC;
    int Unknown1F0;
    int Unknown1F4;
    int Unknown1F8;
    int Unknown1FC;
    int Unknown200;
    bool Unknown204;
};

// A chained hash table's entry, allocated per insert.
class Class_10B2A160_Node
{
public:
    int Unknown00;
    int Unknown04;
    Class_10B2A160_Node* Next;
};

class Class_10B2A160
{
public:
    void FUN_10b2a220(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_10B2A160_Node** Unknown14;
};

class Class_10B408D0 : public Class_10B2A160
{
public:
    void FUN_10b40620(int Size);
};

// FUNCTION: 0x10B40620 ?FUN_10b40620@Class_10B408D0@@QAEXH@Z
void Class_10B408D0::FUN_10b40620(int Size)
{
    for (int i = 0; i < Unknown0C; i++)
    {
        Class_10B2A160_Node* Node = Unknown14[i];
        while (Node)
        {
            Class_10B2A160_Node* Next = Node->Next;
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
        FUN_10b2a220(Size);
}

// FUNCTION: 0x10B406A0 ??0Class_10E7FB08@@QAE@XZ
Class_10E7FB08::Class_10E7FB08()
    : Unknown1CC(0), Unknown1D0(0), Unknown1D4(0), Unknown1D8(0), Unknown1E0(0), Unknown1E4(0), Unknown1E8(0),
      Unknown1EC(0), Unknown1F0(0), Unknown1F4(0), Unknown1F8(0), Unknown1FC(0), Unknown200(0), Unknown204(false)
{
}

// FUNCTION: 0x10B40710 ??0Class_10E7FD18@@QAE@XZ
Class_10E7FD18::Class_10E7FD18() : Unknown118(0), Unknown11C(0), Unknown124(-1), Unknown134(0)
{
}

// FUNCTION: 0x10B40760 ??_GClass_10E7FD18@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B40710's definition in this unit.

// FUNCTION: 0x10B40900 ??_GClass_10E7FB08@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B406A0's definition in this unit.

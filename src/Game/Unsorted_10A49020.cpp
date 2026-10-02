// Game/Unsorted_10A49020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

int FUN_10a48b30(int A, int B);

void FUN_10a4a100(int A, int B, int C, int D);

struct Struct_10A4C4A0_Pair
{
    int Unknown00;
    int Unknown04;
};

struct Struct_10A4C4A0
{
    int Unknown00;
    int Unknown04;
    Struct_10A4C4A0_Pair Unknown08;
};

class Class_10A4C4A0
{
public:
    Struct_10A4C4A0* FUN_10a4c0d0(int A, int B);
    void FUN_10a4c4a0(int A, int B, Struct_10A4C4A0_Pair* C);
};

class FCoords
{
public:
    FCoords() {}

    FRotator OrthoRotation() const;

    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
};

void FUN_10a48f20(int A, int B, FCoords* Out);

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

// FUNCTION: 0x10A492B0 ?FUN_10a492b0@Class_10A492B0@@QAEIABVClass_109081E0@@ABH@Z
unsigned int Class_10A492B0::FUN_10a492b0(const Class_109081E0& Key, const int& Value)
{
    if (!Unknown10 && Unknown00 > Unknown0C * 0.2)
        FUN_10a4ab10(Unknown0C * 2);
    Class_10A492B0_Node* Node = new(0, 0, 0, 0, 0) Class_10A492B0_Node;
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

// FUNCTION: 0x10A4A100 ?FUN_10a4a100@@YAXHHPAVFVector@@PAVFRotator@@@Z
void FUN_10a4a100(int A, int B, FVector* OutLocation, FRotator* OutRotation)
{
    FCoords Coords;
    FUN_10a48f20(A, B, &Coords);
    *OutRotation = Coords.OrthoRotation();
    *OutLocation = Coords.Origin;
}

// FUNCTION: 0x10A4A160 ?FUN_10a4a160@@YAXHHHH@Z
void FUN_10a4a160(int A, int B, int C, int D)
{
    int Value = FUN_10a48b30(A, B);
    FUN_10a4a100(A, Value, C, D);
}

// FUNCTION: 0x10A4C4A0 ?FUN_10a4c4a0@Class_10A4C4A0@@QAEXHHPAUStruct_10A4C4A0_Pair@@@Z
void Class_10A4C4A0::FUN_10a4c4a0(int A, int B, Struct_10A4C4A0_Pair* C)
{
    Struct_10A4C4A0* Node = FUN_10a4c0d0(1, 0);
    if (Node)
    {
        Node->Unknown00 = A;
        Node->Unknown04 = B;
        Node->Unknown08 = *C;
    }
}

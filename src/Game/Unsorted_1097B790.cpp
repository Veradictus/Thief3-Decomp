// Game/Unsorted_1097B790.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_1096BD50
{
public:
    Class_1096BD50* FUN_1096bd50(UClass* InClass);
};

class Class_1097CAA0 : public Class_1096BD50
{
public:
    Class_1097CAA0* FUN_1097caa0();
};

class Class_1097CAE0 : public Class_1096BD50
{
public:
    Class_1097CAE0* FUN_1097cae0();
};

class AActor;

class APawn
{
    DECLARE_CLASS(APawn, AActor, 0x800, Engine)
};

class Class_1097CB20 : public Class_1096BD50
{
public:
    Class_1097CB20* FUN_1097cb20();
};

class ULodMesh;

class USkeletalMesh
{
    DECLARE_CLASS(USkeletalMesh, ULodMesh, 0x40, Engine)
};

class Class_1097CB60 : public Class_1096BD50
{
public:
    Class_1097CB60* FUN_1097cb60();
};

class UMeshAnimation
{
    DECLARE_CLASS(UMeshAnimation, UObject, 0x40, Engine)
};

class Class_1097CBA0 : public Class_1096BD50
{
public:
    Class_1097CBA0* FUN_1097cba0();
};

// Ion Storm's string (0x109081E0): a char pointer, null when default constructed.
class Class_109081E0
{
public:
    ~Class_109081E0();

    char* Unknown00;
};

// A chained hash table's entry: 24 bytes, allocated per insert.
class Class_1097B240_Node
{
public:
    Class_109081E0 Key;
    char Unknown04[0x10];
    Class_1097B240_Node* Next;
};

class Class_1097B240
{
public:
    void FUN_1097b240(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    Class_1097B240_Node** Unknown14;
};

class Class_1097CBE0 : public Class_1097B240
{
public:
    void FUN_1097c880(int Size);
};

// FUNCTION: 0x1097C880 ?FUN_1097c880@Class_1097CBE0@@QAEXH@Z
void Class_1097CBE0::FUN_1097c880(int Size)
{
    for (int i = 0; i < Unknown0C; i++)
    {
        Class_1097B240_Node* Node = Unknown14[i];
        while (Node)
        {
            Class_1097B240_Node* Next = Node->Next;
            Node->Key.~Class_109081E0();
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
        FUN_1097b240(Size);
}

// FUNCTION: 0x1097CAA0 ?FUN_1097caa0@Class_1097CAA0@@QAEPAV1@XZ
Class_1097CAA0* Class_1097CAA0::FUN_1097caa0()
{
    FUN_1096bd50(UClass::StaticClass());
    return this;
}

// FUNCTION: 0x1097CAE0 ?FUN_1097cae0@Class_1097CAE0@@QAEPAV1@XZ
Class_1097CAE0* Class_1097CAE0::FUN_1097cae0()
{
    FUN_1096bd50(UObject::StaticClass());
    return this;
}

// FUNCTION: 0x1097CB20 ?FUN_1097cb20@Class_1097CB20@@QAEPAV1@XZ
Class_1097CB20* Class_1097CB20::FUN_1097cb20()
{
    FUN_1096bd50(APawn::StaticClass());
    return this;
}

// FUNCTION: 0x1097CB60 ?FUN_1097cb60@Class_1097CB60@@QAEPAV1@XZ
Class_1097CB60* Class_1097CB60::FUN_1097cb60()
{
    FUN_1096bd50(USkeletalMesh::StaticClass());
    return this;
}

// FUNCTION: 0x1097CBA0 ?FUN_1097cba0@Class_1097CBA0@@QAEPAV1@XZ
Class_1097CBA0* Class_1097CBA0::FUN_1097cba0()
{
    FUN_1096bd50(UMeshAnimation::StaticClass());
    return this;
}

// Game/Unsorted_10B7C020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Allocator_10FFA700
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* p1, int p2, int p3);
};

extern Allocator_10FFA700* DAT_10ffa700;

struct Struct_10B7C150
{
    char Unknown00[4];
    unsigned short Unknown04;
};

struct Struct_10B7C3D0
{
    char Unknown00[4];
    unsigned short Unknown04;
};

extern void* DAT_10e47850[];

class Class_10AF4B90
{
public:
    Class_10AF4B90* FUN_10af4b90(int p1, void* p2);
};

class Class_10B7ECC0
{
public:
    Class_10B7ECC0* FUN_10b7ecc0();

    char Unknown00[0xC];
    Class_10AF4B90 Unknown0C;
};

// FUNCTION: 0x10B7C150 ?FUN_10b7c150@@YAXPAUStruct_10B7C150@@@Z
void FUN_10b7c150(Struct_10B7C150* p)
{
    DAT_10ffa700->Virtual5(p, p->Unknown04, 0xf);
}

// FUNCTION: 0x10B7C3D0 ?FUN_10b7c3d0@@YAXPAUStruct_10B7C3D0@@@Z
void FUN_10b7c3d0(Struct_10B7C3D0* p)
{
    DAT_10ffa700->Virtual5(p, p->Unknown04, 0x23);
}

// FUNCTION: 0x10B7ECC0 ?FUN_10b7ecc0@Class_10B7ECC0@@QAEPAV1@XZ
Class_10B7ECC0* Class_10B7ECC0::FUN_10b7ecc0()
{
    Unknown0C.FUN_10af4b90(0x27, DAT_10e47850);
    return this;
}

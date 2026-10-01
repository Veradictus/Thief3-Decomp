// Game/Unsorted_10B81D20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Allocator_10FFA700
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void* Alloc(int Size, int Tag);
    virtual void Free(void* Ptr, int Size, int Tag);
};

extern Allocator_10FFA700* DAT_10ffa700;

struct Struct_10B81D20
{
    char Unknown00[4];
    unsigned short Unknown04;
};

// FUNCTION: 0x10B81D20 ?FUN_10b81d20@@YAXPAUStruct_10B81D20@@@Z
void FUN_10b81d20(Struct_10B81D20* P)
{
    DAT_10ffa700->Free(P, P->Unknown04, 0x2b);
}

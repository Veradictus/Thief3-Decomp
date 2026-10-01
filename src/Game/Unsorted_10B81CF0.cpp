// Game/Unsorted_10B81CF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

struct Struct_10B81CF0
{
    char Unknown00[4];
    unsigned short Unknown04;
};

// FUNCTION: 0x10B81CF0 ?FUN_10b81cf0@@YAXPAUStruct_10B81CF0@@@Z
void FUN_10b81cf0(Struct_10B81CF0* p)
{
    DAT_10ffa700->Virtual5(p, p->Unknown04, 0x1f);
}

// Game/Unsorted_10C27410.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C27460_Param
{
public:
    virtual void Virtual0();
    virtual void Virtual1(void* p1, int p2);
};

class Class_10E99350
{
public:
    virtual void FUN_10c27460(Class_10C27460_Param* p1);

    int Unknown04;
};

// FUNCTION: 0x10C27460 ?FUN_10c27460@Class_10E99350@@UAEXPAVClass_10C27460_Param@@@Z
void Class_10E99350::FUN_10c27460(Class_10C27460_Param* p1)
{
    p1->Virtual1(&Unknown04, 4);
}

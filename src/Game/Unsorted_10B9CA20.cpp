// Game/Unsorted_10B9CA20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B9CA20_Item
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual ~Class_10B9CA20_Item();
};

struct Struct_10B9CA20
{
    int Unknown00;
    int Unknown04;
    Class_10B9CA20_Item** Unknown08;
};

// FUNCTION: 0x10B9CA20 ?FUN_10b9ca20@@YAXPAUStruct_10B9CA20@@@Z
void FUN_10b9ca20(Struct_10B9CA20* List)
{
    for (int i = 0; i < List->Unknown00; i++)
        delete List->Unknown08[i];
    List->Unknown00 = 0;
}

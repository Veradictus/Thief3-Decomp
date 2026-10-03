// Game/Unsorted_10BFBD30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

double FUN_10c00480();

class Class_10BFBE30
{
public:
    bool FUN_10bfbe30();

    char Unknown00[4];
    float Unknown04;
    float Unknown08;
};

class Object_10BFBD30
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual ~Object_10BFBD30();
};

struct Struct_10BFBD30
{
    int Unknown00;
    int Unknown04;
    Object_10BFBD30** Unknown08;
};

// FUNCTION: 0x10BFBD30 ?FUN_10bfbd30@@YAXPAUStruct_10BFBD30@@@Z
void FUN_10bfbd30(Struct_10BFBD30* List)
{
    for (int i = 0; i < List->Unknown00; i++)
        delete List->Unknown08[i];
    List->Unknown00 = 0;
}

// FUNCTION: 0x10BFBE30 ?FUN_10bfbe30@Class_10BFBE30@@QAE_NXZ
bool Class_10BFBE30::FUN_10bfbe30()
{
    float Limit = Unknown08;
    if (FUN_10c00480() - Unknown04 > Limit)
        return true;
    return false;
}

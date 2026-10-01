// Game/Unsorted_10B8AB90_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B8AC20
{
    char Unknown00[4];
    int Unknown04;
};

class Class_10E894C8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual Struct_10B8AC20* FUN_10b8ac20();

    char Unknown04[0x28];
    Struct_10B8AC20* Unknown2C;
};

// FUNCTION: 0x10B8AC20 ?FUN_10b8ac20@Class_10E894C8@@UAEPAUStruct_10B8AC20@@XZ
Struct_10B8AC20* Class_10E894C8::FUN_10b8ac20()
{
    if (Unknown2C && Unknown2C->Unknown04 == 2)
        return Unknown2C;
    return 0;
}

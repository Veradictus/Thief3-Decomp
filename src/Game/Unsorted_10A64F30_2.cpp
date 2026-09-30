// Game/Unsorted_10A64F30_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6B490
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual bool FUN_10a66dd0(Class_10E6B490* p1);

    int Unknown04;
    int Unknown08;
};

extern void* DAT_10e6b4ac[];

class Class_10EB7660
{
public:
    Class_10EB7660();

    void** VTable;
    int Unknown04;
};

struct Struct_10A66E20
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E6B4AC : public Class_10EB7660
{
public:
    Class_10E6B4AC* FUN_10a66e20(const Struct_10A66E20& Value);

    Struct_10A66E20 Unknown08;
};

// FUNCTION: 0x10A66DD0 ?FUN_10a66dd0@Class_10E6B490@@UAE_NPAV1@@Z
bool Class_10E6B490::FUN_10a66dd0(Class_10E6B490* p1)
{
    return p1->Unknown08 == Unknown08;
}

// FUNCTION: 0x10A66E20 ?FUN_10a66e20@Class_10E6B4AC@@QAEPAV1@ABUStruct_10A66E20@@@Z
Class_10E6B4AC* Class_10E6B4AC::FUN_10a66e20(const Struct_10A66E20& Value)
{
    this->Class_10EB7660::Class_10EB7660();
    VTable = DAT_10e6b4ac;
    Unknown08 = Value;
    return this;
}

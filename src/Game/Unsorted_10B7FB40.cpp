// Game/Unsorted_10B7FB40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

class Class_10B7FEE0
{
public:
    void FUN_10b7fee0();

    int Unknown00;
    void* Unknown04;
    int Unknown08;
    int Unknown0C;
};

struct Struct_10B7FC20_Item
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10B7FC20
{
public:
    int FUN_10b7fc20();

    std::vector<Struct_10B7FC20_Item> Unknown00;
};

// FUNCTION: 0x10B7FC20 ?FUN_10b7fc20@Class_10B7FC20@@QAEHXZ
int Class_10B7FC20::FUN_10b7fc20()
{
    return Unknown00.size();
}

// FUNCTION: 0x10B7FEE0 ?FUN_10b7fee0@Class_10B7FEE0@@QAEXXZ
void Class_10B7FEE0::FUN_10b7fee0()
{
    if (Unknown04)
        ::operator delete(Unknown04);
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
}

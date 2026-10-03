// Game/Unsorted_10AB0800.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

struct Struct_10AB0400
{
};

class Class_10AB0400
{
public:
    void FUN_10a6e990();
    void FUN_10ab0400()
    {
        FUN_10a6e990();
        delete Unknown04;
        Unknown04 = 0;
    }

    char Unknown00[4];
    Struct_10AB0400* Unknown04;
};

class Class_10AB0C40
{
public:
    void FUN_10ab0c40();

    char Unknown00[4];
    Class_10AB0400 Unknown04;
    char Unknown0C[4];
    std::vector<void*> Unknown10;
};

// FUNCTION: 0x10AB0C40 ?FUN_10ab0c40@Class_10AB0C40@@QAEXXZ
void Class_10AB0C40::FUN_10ab0c40()
{
    Unknown10.~vector();
    Unknown04.FUN_10ab0400();
}

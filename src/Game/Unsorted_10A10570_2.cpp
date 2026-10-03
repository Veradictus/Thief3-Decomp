// Game/Unsorted_10A10570_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10A10C20
{
public:
    void FUN_10a10c20();

    char Unknown00[0x10];
    Class_10AB0400 Unknown10;
    char Unknown18[4];
    std::vector<void*> Unknown1C;
};

// FUNCTION: 0x10A10C20 ?FUN_10a10c20@Class_10A10C20@@QAEXXZ
void Class_10A10C20::FUN_10a10c20()
{
    Unknown1C.~vector();
    Unknown10.FUN_10ab0400();
}

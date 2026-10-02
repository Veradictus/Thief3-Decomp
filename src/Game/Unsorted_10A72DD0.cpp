// Game/Unsorted_10A72DD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

struct Struct_10A72F10
{
};

class Class_10A111B0
{
public:
    ~Class_10A111B0()
    {
        FUN_10a111b0();
        delete Unknown18;
        Unknown18 = 0;
    }

    void FUN_10a111b0();

    char Unknown00[0x18];
    Struct_10A72F10* Unknown18;
};

class Class_10A72F10
{
public:
    ~Class_10A72F10();

    char Unknown00[4];
    Class_10A111B0 Unknown04;
    char Unknown20[8];
    std::vector<int> Unknown28;
};

// FUNCTION: 0x10A72F10 ??1Class_10A72F10@@QAE@XZ
Class_10A72F10::~Class_10A72F10()
{
}

// Game/Unsorted_10C49AB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <list>

class Class_10C49E20
{
public:
    int FUN_10c49e20();

    std::list<int> Unknown00;
    int Unknown0C;
};

// FUNCTION: 0x10C49E20 ?FUN_10c49e20@Class_10C49E20@@QAEHXZ
int Class_10C49E20::FUN_10c49e20()
{
    if (!Unknown00.empty())
    {
        int Value = Unknown00.front();
        Unknown00.pop_front();
        return Value;
    }
    return ++Unknown0C - 1;
}

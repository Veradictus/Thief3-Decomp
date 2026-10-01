// Game/Unsorted_10AB0360.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <string>

class Class_10E6D4F0
{
public:
    virtual ~Class_10E6D4F0() = 0;
};

inline Class_10E6D4F0::~Class_10E6D4F0() {}

class Class_10E77978 : public Class_10E6D4F0
{
public:
    virtual ~Class_10E77978();

    std::string Unknown04;
};

struct Struct_10AB0400
{
};

class Class_10AB0400
{
public:
    void FUN_10ab0400();
    void FUN_10a6e990();

    char Unknown00[4];
    Struct_10AB0400* Unknown04;
};

// FUNCTION: 0x10AB0400 ?FUN_10ab0400@Class_10AB0400@@QAEXXZ
void Class_10AB0400::FUN_10ab0400()
{
    FUN_10a6e990();
    delete Unknown04;
    Unknown04 = 0;
}

// FUNCTION: 0x10AB0520 ??1Class_10E77978@@UAE@XZ
Class_10E77978::~Class_10E77978()
{
}

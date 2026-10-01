// Game/Unsorted_10BB8CE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C01CE0
{
public:
    void FUN_10c01ce0();
};

class Class_10BA9EC0
{
public:
    void* FUN_10ba9ec0();
};

class Class_10BB8CE0
{
public:
    void FUN_10bb8ce0();

    char Unknown00[8];
    Class_10BA9EC0* Unknown08;
    char Unknown0C[0x328];
    bool Unknown334;
    bool Unknown335;
};

// FUNCTION: 0x10BB8CE0 ?FUN_10bb8ce0@Class_10BB8CE0@@QAEXXZ
void Class_10BB8CE0::FUN_10bb8ce0()
{
    Unknown334 = false;
    Unknown335 = false;
    static_cast<Class_10C01CE0*>(Unknown08->FUN_10ba9ec0())->FUN_10c01ce0();
}

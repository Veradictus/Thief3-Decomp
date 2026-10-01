// Game/Unsorted_10947530.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_109481D0
{
    int Unknown00;
    int Unknown04;
};

class Class_109481D0
{
public:
    bool FUN_109481d0(int Mask);

    char Unknown00[0xB0];
    Struct_109481D0* UnknownB0;
};

// FUNCTION: 0x109481D0 ?FUN_109481d0@Class_109481D0@@QAE_NH@Z
bool Class_109481D0::FUN_109481d0(int Mask)
{
    if (UnknownB0)
    {
        if (UnknownB0->Unknown04 & Mask)
            return true;
    }
    return false;
}

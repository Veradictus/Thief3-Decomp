// Game/Unsorted_1094D700.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// A COM object (Direct3D): slot 2 is Release.
class Class_1094D700_Element
{
public:
    virtual int __stdcall Virtual0();
    virtual int __stdcall Virtual1();
    virtual int __stdcall Virtual2();
};

class Class_1094D700
{
public:
    void FUN_1094d700();

    char Unknown00[4];
    Class_1094D700_Element* Unknown04;
    Class_1094D700_Element* Unknown08[4];
};

// FUNCTION: 0x1094D700 ?FUN_1094d700@Class_1094D700@@QAEXXZ
void Class_1094D700::FUN_1094d700()
{
    if (Unknown04)
    {
        Unknown04->Virtual2();
        Unknown04 = 0;
    }
    for (int i = 0; i < 4; i++)
    {
        if (Unknown08[i])
        {
            Unknown08[i]->Virtual2();
            Unknown08[i] = 0;
        }
    }
}

// Game/Unsorted_10B54790.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B542D0
{
public:
    ~Class_10B542D0();
};

extern Class_10B542D0* DAT_10ff6580;

// FUNCTION: 0x10B54790 ?FUN_10b54790@@YAXXZ
void FUN_10b54790()
{
    if (DAT_10ff6580)
    {
        delete DAT_10ff6580;
        DAT_10ff6580 = 0;
    }
}

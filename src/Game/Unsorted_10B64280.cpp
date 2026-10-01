// Game/Unsorted_10B64280.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void* FUN_10b154c0();

class Class_10B15960
{
public:
    bool FUN_10b15960(int A);
};

class Class_10B64280
{
public:
    void FUN_10b744b0();
    void FUN_10b64280();

    char Unknown00[0x17C];
    bool Unknown17C;
};

// FUNCTION: 0x10B64280 ?FUN_10b64280@Class_10B64280@@QAEXXZ
void Class_10B64280::FUN_10b64280()
{
    bool Hidden = !Unknown17C;
    FUN_10b744b0();
    if (Hidden)
        static_cast<Class_10B15960*>(FUN_10b154c0())->FUN_10b15960(0);
}

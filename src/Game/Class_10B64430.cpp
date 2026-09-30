// Game/Class_10B64430.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Parameter setter at field offset 0x2fc

class Class_10B64430 {
public:
    char Unknown00[0x2fc];
    int Field2fc;
    void FUN_10b64430(int param);
};

// FUNCTION: 0x10B64430 ?FUN_10b64430@Class_10B64430@@QAEXH@Z
void Class_10B64430::FUN_10b64430(int param)
{
    Field2fc = param;
}

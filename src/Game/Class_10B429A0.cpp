// Game/Class_10B429A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Parameter setter at field offset 0x120

class Class_10B429A0 {
public:
    char Unknown00[0x120];
    int Field120;
    void FUN_10b429a0(int param);
};

// FUNCTION: 0x10B429A0 ?FUN_10b429a0@Class_10B429A0@@QAEXH@Z
void Class_10B429A0::FUN_10b429a0(int param)
{
    Field120 = param;
}

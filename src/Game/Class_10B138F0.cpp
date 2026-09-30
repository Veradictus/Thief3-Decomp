// Game/Class_10B138F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Parameter setter - stores parameter to field at offset 0x30

class Class_10B138F0 {
public:
    char Unknown00[0x30];
    int Field30;
    void FUN_10b138f0(int param);
};

// FUNCTION: 0x10B138F0 ?FUN_10b138f0@Class_10B138F0@@QAEXH@Z
void Class_10B138F0::FUN_10b138f0(int param)
{
    Field30 = param;
}

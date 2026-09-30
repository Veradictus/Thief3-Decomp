// Game/Class_10B61020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Parameter setter at field offset 0x1ec

class Class_10B61020 {
public:
    char Unknown00[0x1ec];
    int Field1ec;
    void FUN_10b61020(int param);
};

// FUNCTION: 0x10B61020 ?FUN_10b61020@Class_10B61020@@QAEXH@Z
void Class_10B61020::FUN_10b61020(int param)
{
    Field1ec = param;
}

// Game/Class_10B9C9F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class InnerClass_10B9C9F0 {
public:
    char Unknown00[0x8];
    void* Field8;
};

class Class_10B9C9F0 {
public:
    char Unknown00[0xc];
    InnerClass_10B9C9F0* Fieldc;
    void* FUN_10b9c9f0();
};

// FUNCTION: 0x10B9C9F0 ?FUN_10b9c9f0@Class_10B9C9F0@@QAEPAXXZ
void* Class_10B9C9F0::FUN_10b9c9f0()
{
    return Fieldc->Field8;
}

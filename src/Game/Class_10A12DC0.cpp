// Game/Class_10A12DC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class InnerObject {
public:
    int Field00;
    int Field04;
};

class Class_10A12DC0 {
public:
    int FUN_10a12dc0();
    char Unknown00[0x40];
    InnerObject* Field40;
};

// FUNCTION: 0x10A12DC0 ?FUN_10a12dc0@Class_10A12DC0@@QAEHXZ
int Class_10A12DC0::FUN_10a12dc0()
{
    return Field40->Field04;
}

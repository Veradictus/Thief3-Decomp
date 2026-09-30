// Game/Class_1096A500.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class InnerObject {
public:
    char Unknown00[0xac];
    int Field0AC;
};

class Class_1096A500 {
public:
    int FUN_1096a500();
    char Unknown00[4];
    InnerObject* Field04;
};

// FUNCTION: 0x1096A500 ?FUN_1096a500@Class_1096A500@@QAEHXZ
int Class_1096A500::FUN_1096a500()
{
    return Field04->Field0AC;
}

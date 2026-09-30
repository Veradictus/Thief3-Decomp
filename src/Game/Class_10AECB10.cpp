// Game/Class_10AECB10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AECB10_Member {
public:
    char Unknown00[0x20];
    unsigned char Field20;
};

class Class_10AECB10 {
public:
    char Unknown00[0x24];
    Class_10AECB10_Member* Field24;

    unsigned char FUN_10aecb10();
};

// FUNCTION: 0x10AECB10 ?FUN_10aecb10@Class_10AECB10@@QAEEXZ
unsigned char Class_10AECB10::FUN_10aecb10()
{
    return Field24->Field20;
}

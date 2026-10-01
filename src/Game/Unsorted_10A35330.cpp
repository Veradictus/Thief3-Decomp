// Game/Unsorted_10A35330.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A35330 {
public:
    void FUN_10a35330(int p1, int p2, int p3);
};

struct Struct_10AA3520 {
    char Unknown00[0x54];
    Class_10A35330* Unknown54;
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x10A35550 ?FUN_10a35550@@YAXHHH@Z
void FUN_10a35550(int p1, int p2, int p3)
{
    DAT_10f35dec->Unknown54->FUN_10a35330(p1, p2, p3);
}

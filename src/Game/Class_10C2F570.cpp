// Game/Class_10C2F570.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C2F570
{
public:
    bool FUN_10c2f570(int Key, int* Out);

    char Unknown00[0x150];
    int Unknown150;
    int Unknown154;
};

// FUNCTION: 0x10C2F570 ?FUN_10c2f570@Class_10C2F570@@QAE_NHPAH@Z
bool Class_10C2F570::FUN_10c2f570(int Key, int* Out)
{
    if (Key == Unknown150) {
        *Out = Unknown154;
        return true;
    }
    return false;
}

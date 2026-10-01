// Game/Unsorted_1098E550.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E70A50
{
public:
    Class_10E70A50();

    void** Unknown00;
    char Unknown04[0x28];
};

class AMetaData : public Class_10E70A50
{
public:
    AMetaData* FUN_1098dbf0();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

class AElevatorFloors : public Class_10E70A50
{
public:
    AElevatorFloors* FUN_1098dc20();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

// FUNCTION: 0x1098E550 ?FUN_1098e550@@YAXPAVAMetaData@@@Z
void FUN_1098e550(AMetaData* Object)
{
    if (Object)
        Object->FUN_1098dbf0();
}

// FUNCTION: 0x1098E560 ?FUN_1098e560@@YAXPAVAElevatorFloors@@@Z
void FUN_1098e560(AElevatorFloors* Object)
{
    if (Object)
        Object->FUN_1098dc20();
}

// Game/Class_10B06220.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B06220 {
public:
    char Unknown00[0x1c];
    int Field1c;

    int FUN_10b06220();
};

// FUNCTION: 0x10B06220 ?FUN_10b06220@Class_10B06220@@QAEHXZ
int Class_10B06220::FUN_10b06220()
{
    return Field1c & 0x800;
}

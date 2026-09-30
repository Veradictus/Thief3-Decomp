// Game/Class_10A3D840.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A3D840_Target {
public:
    char Unknown00[0x218];
    int Field218;
};

class Class_10A3D840 {
public:
    char Unknown00[0x94];
    Class_10A3D840_Target* Field94;
    void FUN_10a3d840();
};

// FUNCTION: 0x10A3D840 ?FUN_10a3d840@Class_10A3D840@@QAEXXZ
void Class_10A3D840::FUN_10a3d840()
{
    Field94->Field218 &= 0xffffff7f;
}

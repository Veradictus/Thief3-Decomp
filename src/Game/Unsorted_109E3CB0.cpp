// Game/Unsorted_109E3CB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109E3D60_Member {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

struct Struct_10AA3520 {
    char Unknown00[0x28];
    Class_109E3D60_Member* Unknown28;
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x109E3D60 ?FUN_109e3d60@@YAXXZ
void FUN_109e3d60()
{
    DAT_10f35dec->Unknown28->Virtual2();
}

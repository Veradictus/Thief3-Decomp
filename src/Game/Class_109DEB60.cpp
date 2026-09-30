// Game/Class_109DEB60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10f344ec;

class Class_10E70A50
{
public:
    virtual void FUN_10adb3a0();

    char Unknown04[0x28];
};

class Class_109DEB60 : public Class_10E70A50
{
public:
    void FUN_109deb60();
};

// FUNCTION: 0x109DEB60 ?FUN_109deb60@Class_109DEB60@@QAEXXZ
void Class_109DEB60::FUN_109deb60()
{
    DAT_10f344ec = 0;
    Class_10E70A50::FUN_10adb3a0();
}

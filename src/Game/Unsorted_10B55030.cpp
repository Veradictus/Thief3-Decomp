// Game/Unsorted_10B55030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10953590;

class Class_10939570
{
public:
    void FUN_1093bce0(Class_10953590* Param);
};

extern Class_10939570* DAT_10f323fc;

class Class_10E67FD0
{
public:
    virtual ~Class_10E67FD0();

    char Unknown04[0x114];
};

class Class_10E7FD18 : public Class_10E67FD0
{
public:
    virtual ~Class_10E7FD18();

    void FUN_10b550c0();

    char Unknown118[0x14];
    int Unknown12C;
    char Unknown130[4];
    Class_10953590** Unknown134;
};

// FUNCTION: 0x10B550C0 ?FUN_10b550c0@Class_10E7FD18@@QAEXXZ
void Class_10E7FD18::FUN_10b550c0()
{
    for (int i = 0; i < Unknown12C; i++)
    {
        DAT_10f323fc->FUN_1093bce0(Unknown134[i]);
        Unknown134[i] = 0;
    }
    Unknown12C = 0;
}

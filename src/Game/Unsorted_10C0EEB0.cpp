// Game/Unsorted_10C0EEB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

int FUN_10af36e0(const char* A, const char* B);

struct Struct_10FF66B0
{
    const char* Unknown00;
    char Unknown04[0x10];
};

extern Struct_10FF66B0 DAT_10ff66b0[];

extern const char DAT_10e47660[];

// FUNCTION: 0x10C0EF40 ?FUN_10c0ef40@@YAHPBD@Z
int FUN_10c0ef40(const char* Name)
{
    for (int i = 0; i < 124; i++)
    {
        const char* Text = DAT_10ff66b0[i].Unknown00 ? DAT_10ff66b0[i].Unknown00 : DAT_10e47660;
        if (!FUN_10af36e0(Name, Text))
            return i;
    }
    return -1;
}

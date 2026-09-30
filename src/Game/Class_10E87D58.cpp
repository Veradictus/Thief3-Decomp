// Game/Class_10E87D58.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e87d58[];

extern void* DAT_10e7edb8[];

class Class_10E68D80
{
public:
    Class_10E68D80();

    void** Unknown00;
    char Unknown04[0x114];
    void** Unknown118;
    char Unknown11C[0xDC];
};

class Class_10E87D58 : public Class_10E68D80
{
public:
    Class_10E87D58* FUN_10b75b10();

    int Unknown1F8;
    int Unknown1FC;
};

// FUNCTION: 0x10B75B10 ?FUN_10b75b10@Class_10E87D58@@QAEPAV1@XZ
Class_10E87D58* Class_10E87D58::FUN_10b75b10()
{
    this->Class_10E68D80::Class_10E68D80();
    Unknown1F8 = 0;
    Unknown1FC = 0;
    Unknown00 = DAT_10e87d58;
    Unknown118 = DAT_10e7edb8;
    return this;
}

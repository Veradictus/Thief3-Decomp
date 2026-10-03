// Game/Unsorted_10951F10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4ad48[];

void* FUN_1092fdd0();

class Class_1091E2E0
{
public:
    void FUN_1091e2e0();

    void** Unknown00;
    char Unknown04[0x40];
};

class Class_10E4A9C8 : public Class_1091E2E0
{
public:
    Class_10E4A9C8();
    ~Class_10E4A9C8();

    int Unknown44;
    bool Unknown48;
    int Unknown4C;
    char Unknown50[8];
    int Unknown58;
    int Unknown5C;
    char Unknown60[0x80];
    bool UnknownE0;
};

class Class_10E4AD48 : public Class_10E4A9C8
{
public:
    Class_10E4AD48();

    char UnknownE4[0x54];
    int Unknown138;
    int Unknown13C;
    void* Unknown140;
};

// FUNCTION: 0x10951F10 ??0Class_10E4AD48@@QAE@XZ
Class_10E4AD48::Class_10E4AD48()
{
    Unknown00 = DAT_10e4ad48;
    Unknown138 = 0;
    Unknown140 = FUN_1092fdd0();
    Unknown58 |= 1;
    Unknown44 = 3;
    Unknown5C = -1;
    Unknown13C = 0;
}

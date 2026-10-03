// Game/Unsorted_10B75670.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e876d0;

extern void* DAT_10e7edb8[];

class Class_10E69080
{
public:
    Class_10E69080();
    ~Class_10E69080();

    void** Unknown00;
    char Unknown04[0x114];
    void** Unknown118;
    char Unknown11C[0xB4];
};

class Class_10B7B910
{
public:
    Class_10B7B910* FUN_10b7b910();

    int Field00;
};

class Class_10E876D0 : public Class_10E69080
{
public:
    Class_10E876D0();

    Class_10B7B910 Unknown1D0;
};

// FUNCTION: 0x10B75670 ??0Class_10E876D0@@QAE@XZ
Class_10E876D0::Class_10E876D0()
{
    Unknown00 = &DAT_10e876d0;
    Unknown118 = DAT_10e7edb8;
    Unknown1D0.FUN_10b7b910();
}

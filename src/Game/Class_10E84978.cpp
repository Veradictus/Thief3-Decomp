// Game/Class_10E84978.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e84978[];

extern void* DAT_10e7edb8[];

class Class_10E87D58
{
public:
    Class_10E87D58* FUN_10b75b10();

    void* Unknown00;
    char Unknown04[0x114];
    void* Unknown118;
    char Unknown11C[0xE4];
};

class Class_10E84978 : public Class_10E87D58
{
public:
    Class_10E84978* FUN_10b65e00();

    int Unknown200;
};

// FUNCTION: 0x10B65E00 ?FUN_10b65e00@Class_10E84978@@QAEPAV1@XZ
Class_10E84978* Class_10E84978::FUN_10b65e00()
{
    FUN_10b75b10();
    Unknown00 = DAT_10e84978;
    Unknown118 = (void*)DAT_10e7edb8;
    Unknown200 = 0;
    return this;
}

// Game/Unsorted_10B69640.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual ~Class_10E67FD0();

    char Unknown04[0xC0];
    int UnknownC4;
    char UnknownC8[0x20];
    int Unknown0E8;
    char Unknown0EC[0x2C];
};

class Class_10BFBD70
{
public:
    Class_10BFBD70() : Unknown00(0), Unknown04(0), Unknown08(0) {}

    void FUN_10bfbd70(int NewCount);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E85AD8 : public Class_10E67FD0
{
public:
    Class_10E85AD8();

    virtual ~Class_10E85AD8();

    int FUN_10b69640();

    int Unknown118;
    int Unknown11C;
    int Unknown120;
    int Unknown124;
    int Unknown128;
    int Unknown12C;
    int Unknown130;
    int Unknown134;
    int Unknown138;
    int Unknown13C;
    int Unknown140;
    int Unknown144;
    int Unknown148;
    Class_10BFBD70 Unknown14C;
    int Unknown158;
    int Unknown15C;
    int Unknown160;
    int Unknown164;
    int Unknown168;
    int Unknown16C;
    char Unknown170[0xC];
    int Unknown17C;
    int Unknown180;
};

// FUNCTION: 0x10B69640 ?FUN_10b69640@Class_10E85AD8@@QAEHXZ
int Class_10E85AD8::FUN_10b69640()
{
    int i;
    for (i = 0; i < Unknown14C.Unknown00; i++)
    {
        if (Unknown14C.Unknown08[i] == UnknownC4)
        {
            Unknown158 = i;
            break;
        }
    }
    return i;
}

// Game/Unsorted_10B761A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual void Virtual0();

    char Unknown04[0x114];
};

class Class_10E87F90 : public Class_10E67FD0
{
public:
    Class_10E87F90();

    virtual void Virtual0();

    int Unknown118;
    char Unknown11C[0xC];
    FArray Unknown128;
    int Unknown134;
    int Unknown138;
    bool Unknown13C;
    bool Unknown13D;
};

// FUNCTION: 0x10B76200 ??0Class_10E87F90@@QAE@XZ
Class_10E87F90::Class_10E87F90() : Unknown118(0), Unknown134(0), Unknown138(0), Unknown13C(true), Unknown13D(true)
{
}

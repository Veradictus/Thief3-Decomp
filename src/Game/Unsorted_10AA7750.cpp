// Game/Unsorted_10AA7750.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E6C104
{
public:
    Class_10E6C104();

    virtual void Virtual0();

    char Unknown04[4];
};

class Class_10E6D940 : public Class_10E6C104
{
public:
    Class_10E6D940();

    virtual void Virtual0();

    int Unknown08;
    int Unknown0C;
    FArray Unknown10;
};

// FUNCTION: 0x10AA79F0 ??0Class_10E6D940@@QAE@XZ
Class_10E6D940::Class_10E6D940() : Unknown08(0), Unknown0C(0)
{
}

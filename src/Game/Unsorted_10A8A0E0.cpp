// Game/Unsorted_10A8A0E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C5D0_Unknown04
{
public:
    virtual ~Class_10E6C5D0_Unknown04();
};

class Class_10E6BF84
{
public:
    virtual ~Class_10E6BF84() {}
};

class Class_10E6C5D0 : public Class_10E6BF84
{
public:
    virtual ~Class_10E6C5D0();

    Class_10E6C5D0_Unknown04* Unknown04;
};

// FUNCTION: 0x10A8A4C0 ??1Class_10E6C5D0@@UAE@XZ
Class_10E6C5D0::~Class_10E6C5D0()
{
    delete Unknown04;
}

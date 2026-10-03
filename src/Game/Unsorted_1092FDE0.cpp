// Game/Unsorted_1092FDE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int Count);

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

extern Class_10BFBD70 DAT_10f31ba8;

class Class_10928760
{
public:
    Class_10928760();

    virtual ~Class_10928760();
};

class Class_10E49C6C : public Class_10928760
{
public:
    virtual ~Class_10E49C6C();
    Class_10E49C6C();
};

// FUNCTION: 0x109302A0 ??1Class_10E49C6C@@UAE@XZ
Class_10E49C6C::~Class_10E49C6C()
{
    DAT_10f31ba8.FUN_10bfbd70(0);
}

// Game/Unsorted_10A923B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10EB766C
{
public:
    Class_10EB766C();
    virtual ~Class_10EB766C();

    int Unknown04;
    int Unknown08;
};

class Class_10E6C874 : public Class_10EB766C
{
public:
    Class_10E6C874() {}
};

class Class_10E67938
{
public:
    Class_10E67938();
    ~Class_10E67938();

    virtual void FUN_10a4c470(int Type, int A, int B, int C);
};

class Class_10E6CB20 : public Class_10E6C874, public Class_10E67938
{
public:
    Class_10E6CB20();

    int Unknown10;
};

// FUNCTION: 0x10A92400 ??0Class_10E6CB20@@QAE@XZ
Class_10E6CB20::Class_10E6CB20()
{
    Unknown10 = 0x37;
}

// Game/Unsorted_10A4FD20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AF4BB0
{
public:
    void FUN_10af3bd0(int A, int B, int C);

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10A4FC00 : public Class_10AF4BB0
{
public:
    ~Class_10A4FC00();

    void FUN_10a4fc00(int Slack);
    void FUN_10a4fc50(int Index, int Count);
};

class Class_10A4FD00
{
public:
    ~Class_10A4FD00();

    char Unknown00[4];
    Class_10A4FC00 Unknown04;
};

// FUNCTION: 0x10A4FD20 ??1Class_10A4FD00@@QAE@XZ
Class_10A4FD00::~Class_10A4FD00()
{
    Unknown04.FUN_10a4fc00(0);
}

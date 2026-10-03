// Game/Unsorted_10C282D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E98C8C
{
public:
    Class_10E98C8C(int p1);
    ~Class_10E98C8C();

    virtual void FUN_10c162e0(int p1);

    int Unknown04;
};

class Class_10C28B70
{
public:
    ~Class_10C28B70();

    Class_10E98C8C Unknown00;
    Class_10E98C8C Unknown08;
};

extern float DAT_10eafbdc;

double FUN_10c00480();

class Class_10C28570
{
public:
    void FUN_10c28570();
    void FUN_10c283f0();

    char Unknown00[8];
    float Unknown08;
    char Unknown0C[4];
    float Unknown10;
};

// FUNCTION: 0x10C28570 ?FUN_10c28570@Class_10C28570@@QAEXXZ
void Class_10C28570::FUN_10c28570()
{
    if (Unknown08 != DAT_10eafbdc)
    {
        double EndTime = Unknown08 + Unknown10;
        if (FUN_10c00480() > EndTime)
        {
            FUN_10c283f0();
            Unknown08 = 0;
        }
    }
}

// FUNCTION: 0x10C28B70 ??1Class_10C28B70@@QAE@XZ
Class_10C28B70::~Class_10C28B70()
{
}

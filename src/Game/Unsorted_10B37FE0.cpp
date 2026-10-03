// Game/Unsorted_10B37FE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7C584;

class Class_109A62E0
{
public:
    void FUN_109a62e0(Class_10E7C584* A);
};

class Class_10B48300
{
public:
    virtual ~Class_10B48300();

    void FUN_10b48300(int A);
};

class Class_10E7C584
{
public:
    ~Class_10E7C584();

    virtual void FUN_10b39500(int A);

    int Unknown04;
    Class_109A62E0* Unknown08;
    Class_10B48300* Unknown0C[8];
};

// FUNCTION: 0x10B394C0 ??1Class_10E7C584@@QAE@XZ
Class_10E7C584::~Class_10E7C584()
{
    for (int i = 0; i < 8; i++)
    {
        if (Unknown0C[i])
        {
            delete Unknown0C[i];
            Unknown0C[i] = 0;
        }
    }
    Unknown08->FUN_109a62e0(this);
}

// Game/Unsorted_1092D440.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1092D420;

extern Class_1092D420* DAT_10f31b88;

class Class_1092D410
{
public:
    ~Class_1092D410() { DAT_10f31b88 = 0; }
};

class Class_1092D420 : public Class_1092D410
{
public:
    ~Class_1092D420();

    bool FUN_1092d4b0();

    int Unknown00;
    int Unknown04;
    int Unknown08;
    bool Unknown0C;
};

// FUNCTION: 0x1092D510 ??1Class_1092D420@@QAE@XZ
Class_1092D420::~Class_1092D420()
{
    try
    {
        FUN_1092d4b0();
    }
    catch (...)
    {
    }
}

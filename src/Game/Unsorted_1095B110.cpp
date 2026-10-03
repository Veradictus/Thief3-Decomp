// Game/Unsorted_1095B110.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1095BC20
{
public:
    Class_1095BC20* FUN_1095bc20();

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

extern "C" long _time32(long* Time);

class Class_1095B0A0
{
public:
    float FUN_1095b0a0(int A, float B);

    int Unknown00;
};

class Class_1095B110
{
public:
    void FUN_1095b110();

    float Unknown00;
    char Unknown04[8];
    int Unknown0C;
    float Unknown10;
};

// FUNCTION: 0x1095B110 ?FUN_1095b110@Class_1095B110@@QAEXXZ
void Class_1095B110::FUN_1095b110()
{
    float Ratio;
    if (Unknown0C)
        Ratio = (float)Unknown0C / Unknown10;
    else
        Ratio = 0.0f;
    Class_1095B0A0 Stamp;
    Stamp.Unknown00 = _time32(0);
    Unknown00 = Stamp.FUN_1095b0a0(0, Ratio);
}

// FUNCTION: 0x1095BC20 ?FUN_1095bc20@Class_1095BC20@@QAEPAV1@XZ
Class_1095BC20* Class_1095BC20::FUN_1095bc20()
{
    Unknown00 = 1;
    Unknown04 = 0;
    Unknown08 = 0;
    return this;
}

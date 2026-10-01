// Game/Unsorted_10B7AD50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10B7AFA0
{
public:
    Class_10B7AFA0(int A, int B, bool C);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    float Unknown10;
    int Unknown14;
    bool Unknown18;
    float Unknown1C;
    bool Unknown20;
    float Unknown24;
    FArray Unknown28;
    FArray Unknown34;
    bool Unknown40;
};

// FUNCTION: 0x10B7AFA0 ??0Class_10B7AFA0@@QAE@HH_N@Z
Class_10B7AFA0::Class_10B7AFA0(int A, int B, bool C)
    : Unknown00(A), Unknown04(0), Unknown08(0x101), Unknown10(-1.0f), Unknown14(B), Unknown18(false),
      Unknown1C(-1.0f), Unknown20(C), Unknown24(1.0f), Unknown40(false)
{
}

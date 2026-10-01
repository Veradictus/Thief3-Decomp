// Game/Unsorted_10BDBA70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e94100[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E94100 : public Class_10E90D70
{
public:
    Class_10E94100* FUN_10bdbd10(int A, int B);

    int Unknown40;
    int Unknown44;
    int Unknown48[3];
};

// FUNCTION: 0x10BDBD10 ?FUN_10bdbd10@Class_10E94100@@QAEPAV1@HH@Z
Class_10E94100* Class_10E94100::FUN_10bdbd10(int A, int B)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = 0;
    Unknown44 = 0;
    Unknown00 = DAT_10e94100;
    for (int i = 0; i < 3; i++)
        Unknown48[i] = 0;
    return this;
}

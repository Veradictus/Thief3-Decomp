// Game/Unsorted_10BD01B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e93020[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E93020 : public Class_10E90D70
{
public:
    Class_10E93020* FUN_10bd01b0(int A, int B, bool C, bool D);

    int Unknown40;
    int Unknown44[4];
    bool Unknown54;
    bool Unknown55;
    bool Unknown56;
};

// FUNCTION: 0x10BD01B0 ?FUN_10bd01b0@Class_10E93020@@QAEPAV1@HH_N0@Z
Class_10E93020* Class_10E93020::FUN_10bd01b0(int A, int B, bool C, bool D)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = 0;
    Unknown54 = false;
    Unknown00 = DAT_10e93020;
    Unknown55 = D;
    Unknown56 = C;
    for (int i = 0; i < 4; i++)
        Unknown44[i] = 0;
    return this;
}

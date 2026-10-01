// Game/Unsorted_10BCE970.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e92b20[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

struct Struct_10BCE9F0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E92B20 : public Class_10E90D70
{
public:
    Class_10E92B20* FUN_10bce9f0(int A, int B, const Struct_10BCE9F0& C);

    Struct_10BCE9F0 Unknown40;
    bool Unknown4C;
};

// FUNCTION: 0x10BCE9F0 ?FUN_10bce9f0@Class_10E92B20@@QAEPAV1@HHABUStruct_10BCE9F0@@@Z
Class_10E92B20* Class_10E92B20::FUN_10bce9f0(int A, int B, const Struct_10BCE9F0& C)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown00 = DAT_10e92b20;
    Unknown40 = C;
    Unknown4C = false;
    return this;
}

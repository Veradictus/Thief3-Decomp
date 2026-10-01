// Game/Unsorted_10C0BDE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C0C8E0
{
    char Unknown00[0x2C];
    int Unknown2C;
    int Unknown30;
};

class Class_10C0C8E0
{
public:
    void FUN_10c0c8e0(const Struct_10C0C8E0* In);
    void FUN_10c0c200(int A, int B);
};

// FUNCTION: 0x10C0C8E0 ?FUN_10c0c8e0@Class_10C0C8E0@@QAEXPBUStruct_10C0C8E0@@@Z
void Class_10C0C8E0::FUN_10c0c8e0(const Struct_10C0C8E0* In)
{
    FUN_10c0c200(In->Unknown30, In->Unknown2C);
}

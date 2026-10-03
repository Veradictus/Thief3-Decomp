// Game/Unsorted_10BAFC40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10BB06A0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

float FUN_10bb0610(void* Stream, int Delimiter);

// FUNCTION: 0x10BB06A0 ?FUN_10bb06a0@@YA?AUStruct_10BB06A0@@PAX@Z
Struct_10BB06A0 FUN_10bb06a0(void* Stream)
{
    Struct_10BB06A0 Result;
    Result.Unknown00 = FUN_10bb0610(Stream, 0x2c);
    Result.Unknown04 = FUN_10bb0610(Stream, 0x2c);
    Result.Unknown08 = FUN_10bb0610(Stream, 0x2c);
    return Result;
}

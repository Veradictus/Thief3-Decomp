// Game/Unsorted_1093EFF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_1093FFE0
{
    Struct_1093FFE0() {}
    Struct_1093FFE0(float F11, float F12, float F13, float F14,
                    float F21, float F22, float F23, float F24,
                    float F31, float F32, float F33, float F34,
                    float F41, float F42, float F43, float F44)
    {
        M11 = F11; M12 = F12; M13 = F13; M14 = F14;
        M21 = F21; M22 = F22; M23 = F23; M24 = F24;
        M31 = F31; M32 = F32; M33 = F33; M34 = F34;
        M41 = F41; M42 = F42; M43 = F43; M44 = F44;
    }

    float M11, M12, M13, M14;
    float M21, M22, M23, M24;
    float M31, M32, M33, M34;
    float M41, M42, M43, M44;
};

class Class_10940970
{
public:
    void FUN_1093ffe0(int Width, int Height, Struct_1093FFE0* Out);
};

// FUNCTION: 0x1093FFE0 ?FUN_1093ffe0@Class_10940970@@QAEXHHPAUStruct_1093FFE0@@@Z
void Class_10940970::FUN_1093ffe0(int Width, int Height, Struct_1093FFE0* Out)
{
    float OffsetX = 0.5f + 0.5f / Width;
    float OffsetY = 0.5f + 0.5f / Height;
    Struct_1093FFE0 Adjust(0.5f, 0.0f, 0.0f, 0.0f,
                           0.0f, -0.5f, 0.0f, 0.0f,
                           0.0f, 0.0f, 0.5f, 0.0f,
                           OffsetX, OffsetY, 0.5f, 1.0f);
    *Out = Adjust;
}

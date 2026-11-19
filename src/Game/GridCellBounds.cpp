// Game/GridCellBounds.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C27CB0
{
    float X, Y, Z;
};

static inline void ClampCell(int& Value, int Minimum, int Maximum)
{
    if (Value < Minimum)
        Value = Minimum;
    else if (Value > Maximum)
        Value = Maximum;
}

class Class_10C27CB0
{
public:
    void FUN_10c27a20(Struct_10C27CB0 A, Struct_10C27CB0 B, int C, int D, int E, int F, int G, int H);
    int Unknown00;
    int CellCount;
    char Unknown08[0x10];
    Struct_10C27CB0 Origin;
    char Unknown24[0xC];
    Struct_10C27CB0 CellSize;
};

// FUNCTION: 0x10C27A20 ?FUN_10c27a20@Class_10C27CB0@@QAEXUStruct_10C27CB0@@0HHHHHH@Z
void Class_10C27CB0::FUN_10c27a20(Struct_10C27CB0 A, Struct_10C27CB0 B,
    int C, int D, int E, int F, int G, int H)
{
    float InverseX = 1.0f / CellSize.X;
    A.X = (A.X - Origin.X) * InverseX;
    B.X = (B.X - Origin.X) * InverseX;
    float InverseY = 1.0f / CellSize.Y;
    A.Y = (A.Y - Origin.Y) * InverseY;
    B.Y = (B.Y - Origin.Y) * InverseY;
    float InverseZ = 1.0f / CellSize.Z;
    A.Z = (A.Z - Origin.Z) * InverseZ;
    B.Z = (B.Z - Origin.Z) * InverseZ;

    int* MinX = (int*)C;
    int* MaxX = (int*)D;
    int* MinY = (int*)E;
    int* MaxY = (int*)F;
    int* MinZ = (int*)G;
    int* MaxZ = (int*)H;
    *MinX = (int)A.X;
    *MaxX = (int)B.X;
    *MinY = (int)A.Y;
    *MaxY = (int)B.Y;
    *MinZ = (int)A.Z - 1;
    *MaxZ = (int)B.Z + 1;

    ClampCell(*MinX, 0, CellCount - 1);
    ClampCell(*MaxX, 0, CellCount - 1);
    ClampCell(*MinY, 0, CellCount - 1);
    ClampCell(*MaxY, 0, CellCount - 1);
    ClampCell(*MinZ, 0, 0);
    ClampCell(*MaxZ, 0, 0);
}

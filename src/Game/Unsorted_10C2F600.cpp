// Game/Unsorted_10C2F600.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FVector
{
public:
    FVector() {}
    FVector(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}

    FVector operator+=(const FVector& V)
    {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        return *this;
    }

    float X, Y, Z;
};

class Class_10C2F650
{
public:
    void FUN_10c2f650(const FVector* V);

    char Unknown00[0x28];
    FVector Unknown28;
};

// FUNCTION: 0x10C2F650 ?FUN_10c2f650@Class_10C2F650@@QAEXPBVFVector@@@Z
void Class_10C2F650::FUN_10c2f650(const FVector* V)
{
    Unknown28 += *V;
    Unknown28.Z = V->Z;
}

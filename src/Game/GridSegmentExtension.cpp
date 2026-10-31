// Game/GridSegmentExtension.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FVector
{
public:
    FVector() {}
    FVector(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector& V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector& V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(float Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator*=(float Scale)
    {
        X = Scale * X;
        Y = Scale * Y;
        Z = Scale * Z;
        return *this;
    }
    FVector FUN_10967580() const;
    float X, Y, Z;
};

struct cGridEdgeRecord
{
    FVector Start;
    FVector End;
    char Unknown18[0xC];
};

// FUNCTION: 0x10C219E0 ?FUN_10c219e0@@YAXPAVFVector@@0PBUcGridEdgeRecord@@PBM@Z
void FUN_10c219e0(FVector* OutStart, FVector* OutEnd, const cGridEdgeRecord* Edge, const float* Radius)
{
    FVector Delta = Edge->Start - Edge->End;
    FVector Direction = Delta.FUN_10967580();
    *OutStart = Delta + Edge->End + Direction * *Radius;
    Delta *= -1.0f;
    Direction *= -1.0f;
    *OutEnd = Delta + Edge->Start + Direction * *Radius;
}

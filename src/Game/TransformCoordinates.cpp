// Game/TransformCoordinates.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/FCoords.h"

struct __declspec(align(16)) TransformVector
{
    float X;
    float Y;
    float Z;

    TransformVector(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}

    operator FVector() const { return FVector(X, Y, Z); }
};

struct AlignedTransform
{
    TransformVector XAxis;
    TransformVector YAxis;
    TransformVector ZAxis;
    TransformVector Translation;
};

// The rotation is a contiguous group of three aligned basis vectors.
struct TransformBasis
{
    TransformVector XAxis;
    TransformVector YAxis;
    TransformVector ZAxis;

    TransformBasis(const AlignedTransform& Transform)
        : XAxis(Transform.XAxis.X, Transform.XAxis.Y, Transform.XAxis.Z),
          YAxis(Transform.YAxis.X, Transform.YAxis.Y, Transform.YAxis.Z),
          ZAxis(Transform.ZAxis.X, Transform.ZAxis.Y, Transform.ZAxis.Z) {}
};

extern float DAT_11006e34;

// FUNCTION: 0x10B91370 ?FUN_10b91370@@YA?AVFCoords@@ABUAlignedTransform@@@Z
FCoords FUN_10b91370(const AlignedTransform& Transform)
{
    TransformBasis Basis(Transform);
    return FCoords(FVector(Transform.Translation.X, Transform.Translation.Y, Transform.Translation.Z) * DAT_11006e34,
        Basis.XAxis, Basis.YAxis, Basis.ZAxis);
}

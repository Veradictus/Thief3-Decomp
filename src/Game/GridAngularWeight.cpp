// Game/GridAngularWeight.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

float InterpolateLinear(float A, float B, float C, float D, float E);

extern float DAT_10e49684;

extern float DAT_10e66518;

// FUNCTION: 0x10C21DD0 ?FUN_10c21dd0@@YAMPBEHHH@Z
float FUN_10c21dd0(const unsigned char* Samples, int Index, int Distance, int Origin)
{
    float Scale = Samples[Index] * 0.03125f + DAT_10e49684;
    Scale = DAT_10e49684 / (Scale * Scale);
    float Weight;
    if (Distance >= 0 && Distance < 22)
        Weight = InterpolateLinear((float)Distance, 0.0f, 1.0f, 22.0f, 0.8f);
    else
        Weight = InterpolateLinear((float)Distance, 22.0f, 0.8f, 45.0f, 0.4f);

    int Difference = Index - Origin;
    int Delta = Difference >= 0 ? Difference : -Difference;
    if (Delta > 45)
        Delta = 90 - Delta;

    if (Delta > 0 && Delta < 22)
        return InterpolateLinear((float)Delta, 0.0f, 1.0f, 22.0f, 0.75f) * Weight * Scale;
    if (Delta > 33)
        return InterpolateLinear((float)Delta, 33.0f, 0.75f, 45.0f, 0.01f) * Weight * Scale;
    return DAT_10e66518 * Weight * Scale;
}

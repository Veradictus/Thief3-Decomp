// Game/Unsorted_10919310.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <xmmintrin.h>

class Class_10939570
{
public:
    char FUN_10939570();
};

class Class_10940970
{
public:
    char FUN_10940970();
};

extern Class_10939570* DAT_10f323fc;

extern Class_10940970* DAT_10f2c8e4;

// FUNCTION: 0x10919310 ?FUN_10919310@@YAXPBMPAE@Z
void FUN_10919310(const float* Normal, unsigned char* Color)
{
    __m128 V = _mm_loadu_ps(Normal);
    __declspec(align(16)) int Result[4];
    _mm_store_ps((float*)Result, _mm_add_ps(_mm_mul_ps(_mm_add_ps(V, _mm_set_ps1(1.0f)), _mm_set_ps1(127.5f)), _mm_set_ps1(8388608.0f)));
    Color[2] = (unsigned char)Result[0];
    Color[3] = 0xff;
    Color[1] = (unsigned char)Result[1];
    Color[0] = (unsigned char)Result[2];
}

// FUNCTION: 0x10919460 ?FUN_10919460@@YA_NXZ
bool FUN_10919460()
{
    if (!DAT_10f323fc->FUN_10939570())
        return false;
    return DAT_10f2c8e4->FUN_10940970();
}

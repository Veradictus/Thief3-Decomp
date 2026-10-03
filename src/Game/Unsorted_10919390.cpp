// Game/Unsorted_10919390.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// FUNCTION: 0x10919390 ?FUN_10919390@@YAXPBMPAE@Z
void FUN_10919390(const float* Normal, unsigned char* Color)
{
    float Biased[3];
    Color[3] = 0xff;
    Biased[0] = (Normal[2] + 1.0f) * 127.5f + 8388608.0f;
    Color[0] = *(unsigned char*)&Biased[0];
    Biased[1] = (Normal[1] + 1.0f) * 127.5f + 8388608.0f;
    Color[1] = *(unsigned char*)&Biased[1];
    Biased[2] = (Normal[0] + 1.0f) * 127.5f + 8388608.0f;
    Color[2] = *(unsigned char*)&Biased[2];
}

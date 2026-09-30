// Game/Unsorted_10C9E2C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10c970f0();

void* __aligned_malloc(unsigned int, unsigned int);

void FUN_10d23c73();

extern "C" int __vsnprintf(const char *, int, const char *, char *);

extern "C" char * _strncpy(char *, const char *, int);

extern "C" char * _strrchr(const char *, int);

// FUNCTION: 0x10CA3700 ?FUN_10ca3700@@YAXXZ
void FUN_10ca3700()
{
    FUN_10c970f0();
}

// FUNCTION: 0x10CA6E70 ?FUN_10ca6e70@@YAPAXII@Z
void* FUN_10ca6e70(unsigned int a, unsigned int b)
{
    return __aligned_malloc(a, b);
}

// FUNCTION: 0x10CA6E80 ?FUN_10ca6e80@@YAXXZ
void FUN_10ca6e80()
{
    FUN_10d23c73();
}

// FUNCTION: 0x10CA79D0 _FUN_10ca79d0
extern "C" int FUN_10ca79d0(const char * a, int b, const char * c, char * d)
{
    return __vsnprintf(a, b, c, d);
}

// FUNCTION: 0x10CA7AA0 _FUN_10ca7aa0
extern "C" char * FUN_10ca7aa0(char * a, const char * b, int c)
{
    return _strncpy(a, b, c);
}

// FUNCTION: 0x10CA7AD0 _FUN_10ca7ad0
extern "C" char * FUN_10ca7ad0(const char * a, int b)
{
    return _strrchr(a, b);
}

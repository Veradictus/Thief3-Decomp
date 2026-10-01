// Game/ADifficultyInfo.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class ADifficultyInfo
{
public:
    ADifficultyInfo();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10AB4D30 ?InternalConstructor@ADifficultyInfo@@SAXPAX@Z
void ADifficultyInfo::InternalConstructor(void* X)
{
    new ((EInternal*)X) ADifficultyInfo();
}

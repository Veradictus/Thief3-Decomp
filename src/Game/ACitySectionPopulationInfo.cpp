// Game/ACitySectionPopulationInfo.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class ACitySectionPopulationInfo
{
public:
    ACitySectionPopulationInfo();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10B95270 ?InternalConstructor@ACitySectionPopulationInfo@@SAXPAX@Z
void ACitySectionPopulationInfo::InternalConstructor(void* X)
{
    new ((EInternal*)X) ACitySectionPopulationInfo();
}

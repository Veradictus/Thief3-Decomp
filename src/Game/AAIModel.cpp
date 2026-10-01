// Game/AAIModel.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AAIModel
{
public:
    AAIModel();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10B95280 ?InternalConstructor@AAIModel@@SAXPAX@Z
void AAIModel::InternalConstructor(void* X)
{
    new ((EInternal*)X) AAIModel();
}

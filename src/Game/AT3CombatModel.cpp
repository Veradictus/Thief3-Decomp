// Game/AT3CombatModel.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AT3CombatModel
{
public:
    AT3CombatModel();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10964500 ?InternalConstructor@AT3CombatModel@@SAXPAX@Z
void AT3CombatModel::InternalConstructor(void* X)
{
    new ((EInternal*)X) AT3CombatModel();
}

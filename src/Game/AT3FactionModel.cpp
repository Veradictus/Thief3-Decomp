// Game/AT3FactionModel.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AT3FactionModel
{
public:
    AT3FactionModel();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10964510 ?InternalConstructor@AT3FactionModel@@SAXPAX@Z
void AT3FactionModel::InternalConstructor(void* X)
{
    new ((EInternal*)X) AT3FactionModel();
}

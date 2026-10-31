// Game/AISpeechTimedDanger.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/cString.h"
#include "Game/Class_10E97B00.h"
#include "Game/Class_10BB84A0.h"
#include "Game/Class_10BB84D0.h"
#include "Game/Class_10BEFAB0.h"

class cAISpeech : public Class_10BEFAB0
{
public:
    void FUN_10bc7d70(Class_10E97B00* Name, int Flags, int Count, cString* Out, bool Flag);
    void FUN_10bc9f40();
};

inline Class_10E97B00* AddressOf(const Class_10E97B00& Object)
{
    return (Class_10E97B00*)&Object;
}

// FUNCTION: 0x10BC9F40 ?FUN_10bc9f40@cAISpeech@@QAEXXZ
void cAISpeech::FUN_10bc9f40()
{
    if ((unsigned char)((Class_10BB84A0*)Unknown04)->IsExpired())
    {
        {
            cString Text(DAT_10e47660);
            FUN_10bc7d70(AddressOf(Class_10E97B00("+busy:danger")), 10, 0, &Text, true);
        }
        ((Class_10BB84D0*)Unknown04)->StartTimeout();
    }
}

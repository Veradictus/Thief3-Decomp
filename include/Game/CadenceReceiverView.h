// Observational declarations for one cadence call site; not a global class map.
#ifndef GAME_CADENCERECEIVERVIEW_H
#define GAME_CADENCERECEIVERVIEW_H

#include "Game/cRefPtr.h"

// Method-facing pool view. Other translation units retain their existing views.
class Class_10C41420
{
public:
    int GetItemCount();
    cRefPtr GetItem(int Index);
};

// Known field offsets only. Full original size and inheritance are unproved.
// This view must not be combined with Game/Class_10C80360.h in one unit.
class Class_10C80360
{
public:
    void FUN_10c5dc60(float A);

    char m_Opaque00[0x0D];
    bool m_Guard0D;
    char m_Opaque0E[0x2A];
    unsigned char m_Flags38[4];
    int m_SelectedIndex3C;
};

#endif // GAME_CADENCERECEIVERVIEW_H

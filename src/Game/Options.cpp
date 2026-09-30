// Game/Options.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// The game's options (options.ini); docs/engine.md, "Options".
class Options
{
public:
    int Get(int Index);
    void GetResolution(int* Width, int* Height);

    int Unknown00;
    int Values[21];          // +0x04, indexed by the names table; [11] is the resolution

    static int ResolutionWidths[];
    static int ResolutionHeights[];
};

// FUNCTION: 0x10AB5AB0 ?Get@Options@@QAEHH@Z
int Options::Get(int Index)
{
    return Values[Index];
}

// FUNCTION: 0x10AB5AC0 ?GetResolution@Options@@QAEXPAH0@Z
void Options::GetResolution(int* Width, int* Height)
{
    int Index = Values[11];
    *Width = ResolutionWidths[Index];
    *Height = ResolutionHeights[Index];
}

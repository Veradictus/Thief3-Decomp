// Game/Config.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Config
{
public:
    Config();
    ~Config();

    static Config* Instance();
};

// FUNCTION: 0x10911950 ?Instance@Config@@SAPAV1@XZ
Config* Config::Instance()
{
    static Config GSingleton;
    return &GSingleton;
}

// Game/Unsorted_10914530.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Simple MAPI error codes (mapi.h).
enum
{
    MAPI_USER_ABORT = 1,
    MAPI_E_FAILURE = 2,
    MAPI_E_LOGIN_FAILURE = 3,
    MAPI_E_DISK_FULL = 4,
    MAPI_E_INSUFFICIENT_MEMORY = 5,
    MAPI_E_ACCESS_DENIED = 6,
    MAPI_E_TOO_MANY_SESSIONS = 8,
    MAPI_E_TOO_MANY_FILES = 9,
    MAPI_E_TOO_MANY_RECIPIENTS = 10,
    MAPI_E_ATTACHMENT_NOT_FOUND = 11,
    MAPI_E_ATTACHMENT_OPEN_FAILURE = 12,
    MAPI_E_ATTACHMENT_WRITE_FAILURE = 13,
    MAPI_E_UNKNOWN_RECIPIENT = 14,
    MAPI_E_BAD_RECIPTYPE = 15,
    MAPI_E_NO_MESSAGES = 16,
    MAPI_E_INVALID_MESSAGE = 17,
    MAPI_E_TEXT_TOO_LARGE = 18,
    MAPI_E_INVALID_SESSION = 19,
    MAPI_E_TYPE_NOT_SUPPORTED = 20,
    MAPI_E_AMBIGUOUS_RECIPIENT = 21,
    MAPI_E_MESSAGE_IN_USE = 22,
    MAPI_E_NETWORK_FAILURE = 23,
    MAPI_E_INVALID_EDITFIELDS = 24,
    MAPI_E_INVALID_RECIPS = 25,
    MAPI_E_NOT_SUPPORTED = 26
};

// FUNCTION: 0x109149C0 ?FUN_109149c0@@YAPBDH@Z
const char* FUN_109149c0(int Error)
{
    switch (Error)
    {
    case MAPI_USER_ABORT:
        return "User aborted";
    case MAPI_E_FAILURE:
        return "Unknown Failure";
    case MAPI_E_LOGIN_FAILURE:
        return "Login Failure";
    case MAPI_E_DISK_FULL:
        return "Disk Full";
    case MAPI_E_INSUFFICIENT_MEMORY:
        return "Insufficient memory";
    case MAPI_E_ACCESS_DENIED:
        return "Access denied";
    case MAPI_E_TOO_MANY_SESSIONS:
        return "Too many sessions";
    case MAPI_E_TOO_MANY_FILES:
        return "Too many files";
    case MAPI_E_TOO_MANY_RECIPIENTS:
        return "Too many recipients";
    case MAPI_E_ATTACHMENT_NOT_FOUND:
        return "Attachment not found";
    case MAPI_E_ATTACHMENT_OPEN_FAILURE:
        return "Attachment open failure";
    case MAPI_E_ATTACHMENT_WRITE_FAILURE:
        return "Attachment write failure";
    case MAPI_E_UNKNOWN_RECIPIENT:
        return "Unknown recipient";
    case MAPI_E_BAD_RECIPTYPE:
        return "Bad reciptype";
    case MAPI_E_NO_MESSAGES:
        return "No messages";
    case MAPI_E_INVALID_MESSAGE:
        return "Invalid message";
    case MAPI_E_TEXT_TOO_LARGE:
        return "Text too large";
    case MAPI_E_INVALID_SESSION:
        return "Invalid session";
    case MAPI_E_TYPE_NOT_SUPPORTED:
        return "Type not supported";
    case MAPI_E_AMBIGUOUS_RECIPIENT:
        return "Ambiguous recipient";
    case MAPI_E_MESSAGE_IN_USE:
        return "Message in use";
    case MAPI_E_NETWORK_FAILURE:
        return "Network failure";
    case MAPI_E_INVALID_EDITFIELDS:
        return "Invalid editfields";
    case MAPI_E_INVALID_RECIPS:
        return "Invalid recips";
    case MAPI_E_NOT_SUPPORTED:
        return "Not supported";
    }
    return 0;
}

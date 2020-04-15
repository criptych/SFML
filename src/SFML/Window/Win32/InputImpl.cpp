////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#ifdef _WIN32_WINDOWS
    #undef _WIN32_WINDOWS
#endif
#ifdef _WIN32_WINNT
    #undef _WIN32_WINNT
#endif
#define _WIN32_WINDOWS 0x0501
#define _WIN32_WINNT   0x0501
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Win32/InputImpl.hpp>
#include <windows.h>

#include <iostream>

namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
Keyboard::Scancode InputImpl::m_keyToScancodeMapping[Keyboard::KeyCount];      ///< Mapping from Key to Scancode
Keyboard::Key      InputImpl::m_scancodeToKeyMapping[Keyboard::ScancodeCount]; ///< Mapping from Scancode to Key

////////////////////////////////////////////////////////////
Keyboard::Key virtualKeyToSfKey(int virtualKey)
{
    Keyboard::Key key;
    switch (virtualKey)
    {
        default:            key = Keyboard::Unknown;    break;
        case 'A':           key = Keyboard::A;          break;
        case 'B':           key = Keyboard::B;          break;
        case 'C':           key = Keyboard::C;          break;
        case 'D':           key = Keyboard::D;          break;
        case 'E':           key = Keyboard::E;          break;
        case 'F':           key = Keyboard::F;          break;
        case 'G':           key = Keyboard::G;          break;
        case 'H':           key = Keyboard::H;          break;
        case 'I':           key = Keyboard::I;          break;
        case 'J':           key = Keyboard::J;          break;
        case 'K':           key = Keyboard::K;          break;
        case 'L':           key = Keyboard::L;          break;
        case 'M':           key = Keyboard::M;          break;
        case 'N':           key = Keyboard::N;          break;
        case 'O':           key = Keyboard::O;          break;
        case 'P':           key = Keyboard::P;          break;
        case 'Q':           key = Keyboard::Q;          break;
        case 'R':           key = Keyboard::R;          break;
        case 'S':           key = Keyboard::S;          break;
        case 'T':           key = Keyboard::T;          break;
        case 'U':           key = Keyboard::U;          break;
        case 'V':           key = Keyboard::V;          break;
        case 'W':           key = Keyboard::W;          break;
        case 'X':           key = Keyboard::X;          break;
        case 'Y':           key = Keyboard::Y;          break;
        case 'Z':           key = Keyboard::Z;          break;
        case '0':           key = Keyboard::Num0;       break;
        case '1':           key = Keyboard::Num1;       break;
        case '2':           key = Keyboard::Num2;       break;
        case '3':           key = Keyboard::Num3;       break;
        case '4':           key = Keyboard::Num4;       break;
        case '5':           key = Keyboard::Num5;       break;
        case '6':           key = Keyboard::Num6;       break;
        case '7':           key = Keyboard::Num7;       break;
        case '8':           key = Keyboard::Num8;       break;
        case '9':           key = Keyboard::Num9;       break;
        case VK_ESCAPE:     key = Keyboard::Escape;     break;
        case VK_LCONTROL:   key = Keyboard::LControl;   break;
        case VK_LSHIFT:     key = Keyboard::LShift;     break;
        case VK_LMENU:      key = Keyboard::LAlt;       break;
        case VK_LWIN:       key = Keyboard::LSystem;    break;
        case VK_RCONTROL:   key = Keyboard::RControl;   break;
        case VK_RSHIFT:     key = Keyboard::RShift;     break;
        case VK_RMENU:      key = Keyboard::RAlt;       break;
        case VK_RWIN:       key = Keyboard::RSystem;    break;
        case VK_APPS:       key = Keyboard::Menu;       break;
        case VK_OEM_4:      key = Keyboard::LBracket;   break;
        case VK_OEM_6:      key = Keyboard::RBracket;   break;
        case VK_OEM_1:      key = Keyboard::Semicolon;  break;
        case VK_OEM_COMMA:  key = Keyboard::Comma;      break;
        case VK_OEM_PERIOD: key = Keyboard::Period;     break;
        case VK_OEM_7:      key = Keyboard::Apostrophe; break;
        case VK_OEM_2:      key = Keyboard::Slash;      break;
        case VK_OEM_5:      key = Keyboard::Backslash;  break;
        case VK_OEM_3:      key = Keyboard::Tilde;      break;
        case VK_OEM_PLUS:   key = Keyboard::Equal;      break;
        case VK_OEM_MINUS:  key = Keyboard::Hyphen;     break;
        case VK_SPACE:      key = Keyboard::Space;      break;
        case VK_RETURN:     key = Keyboard::Enter;      break;
        case VK_BACK:       key = Keyboard::Backspace;  break;
        case VK_TAB:        key = Keyboard::Tab;        break;
        case VK_PRIOR:      key = Keyboard::PageUp;     break;
        case VK_NEXT:       key = Keyboard::PageDown;   break;
        case VK_END:        key = Keyboard::End;        break;
        case VK_HOME:       key = Keyboard::Home;       break;
        case VK_INSERT:     key = Keyboard::Insert;     break;
        case VK_DELETE:     key = Keyboard::Delete;     break;
        case VK_ADD:        key = Keyboard::Add;        break;
        case VK_SUBTRACT:   key = Keyboard::Subtract;   break;
        case VK_MULTIPLY:   key = Keyboard::Multiply;   break;
        case VK_DIVIDE:     key = Keyboard::Divide;     break;
        case VK_LEFT:       key = Keyboard::Left;       break;
        case VK_RIGHT:      key = Keyboard::Right;      break;
        case VK_UP:         key = Keyboard::Up;         break;
        case VK_DOWN:       key = Keyboard::Down;       break;
        case VK_NUMPAD0:    key = Keyboard::Numpad0;    break;
        case VK_NUMPAD1:    key = Keyboard::Numpad1;    break;
        case VK_NUMPAD2:    key = Keyboard::Numpad2;    break;
        case VK_NUMPAD3:    key = Keyboard::Numpad3;    break;
        case VK_NUMPAD4:    key = Keyboard::Numpad4;    break;
        case VK_NUMPAD5:    key = Keyboard::Numpad5;    break;
        case VK_NUMPAD6:    key = Keyboard::Numpad6;    break;
        case VK_NUMPAD7:    key = Keyboard::Numpad7;    break;
        case VK_NUMPAD8:    key = Keyboard::Numpad8;    break;
        case VK_NUMPAD9:    key = Keyboard::Numpad9;    break;
        case VK_F1:         key = Keyboard::F1;         break;
        case VK_F2:         key = Keyboard::F2;         break;
        case VK_F3:         key = Keyboard::F3;         break;
        case VK_F4:         key = Keyboard::F4;         break;
        case VK_F5:         key = Keyboard::F5;         break;
        case VK_F6:         key = Keyboard::F6;         break;
        case VK_F7:         key = Keyboard::F7;         break;
        case VK_F8:         key = Keyboard::F8;         break;
        case VK_F9:         key = Keyboard::F9;         break;
        case VK_F10:        key = Keyboard::F10;        break;
        case VK_F11:        key = Keyboard::F11;        break;
        case VK_F12:        key = Keyboard::F12;        break;
        case VK_F13:        key = Keyboard::F13;        break;
        case VK_F14:        key = Keyboard::F14;        break;
        case VK_F15:        key = Keyboard::F15;        break;
        case VK_PAUSE:      key = Keyboard::Pause;      break;
    }
    return key;
}

////////////////////////////////////////////////////////////
int sfKeyToVirtualKey(Keyboard::Key key)
{
    int virtualKey = 0;
    switch (key)
    {
        default:                   virtualKey = 0;             break;
        case Keyboard::A:          virtualKey = 'A';           break;
        case Keyboard::B:          virtualKey = 'B';           break;
        case Keyboard::C:          virtualKey = 'C';           break;
        case Keyboard::D:          virtualKey = 'D';           break;
        case Keyboard::E:          virtualKey = 'E';           break;
        case Keyboard::F:          virtualKey = 'F';           break;
        case Keyboard::G:          virtualKey = 'G';           break;
        case Keyboard::H:          virtualKey = 'H';           break;
        case Keyboard::I:          virtualKey = 'I';           break;
        case Keyboard::J:          virtualKey = 'J';           break;
        case Keyboard::K:          virtualKey = 'K';           break;
        case Keyboard::L:          virtualKey = 'L';           break;
        case Keyboard::M:          virtualKey = 'M';           break;
        case Keyboard::N:          virtualKey = 'N';           break;
        case Keyboard::O:          virtualKey = 'O';           break;
        case Keyboard::P:          virtualKey = 'P';           break;
        case Keyboard::Q:          virtualKey = 'Q';           break;
        case Keyboard::R:          virtualKey = 'R';           break;
        case Keyboard::S:          virtualKey = 'S';           break;
        case Keyboard::T:          virtualKey = 'T';           break;
        case Keyboard::U:          virtualKey = 'U';           break;
        case Keyboard::V:          virtualKey = 'V';           break;
        case Keyboard::W:          virtualKey = 'W';           break;
        case Keyboard::X:          virtualKey = 'X';           break;
        case Keyboard::Y:          virtualKey = 'Y';           break;
        case Keyboard::Z:          virtualKey = 'Z';           break;
        case Keyboard::Num0:       virtualKey = '0';           break;
        case Keyboard::Num1:       virtualKey = '1';           break;
        case Keyboard::Num2:       virtualKey = '2';           break;
        case Keyboard::Num3:       virtualKey = '3';           break;
        case Keyboard::Num4:       virtualKey = '4';           break;
        case Keyboard::Num5:       virtualKey = '5';           break;
        case Keyboard::Num6:       virtualKey = '6';           break;
        case Keyboard::Num7:       virtualKey = '7';           break;
        case Keyboard::Num8:       virtualKey = '8';           break;
        case Keyboard::Num9:       virtualKey = '9';           break;
        case Keyboard::Escape:     virtualKey = VK_ESCAPE;     break;
        case Keyboard::LControl:   virtualKey = VK_LCONTROL;   break;
        case Keyboard::LShift:     virtualKey = VK_LSHIFT;     break;
        case Keyboard::LAlt:       virtualKey = VK_LMENU;      break;
        case Keyboard::LSystem:    virtualKey = VK_LWIN;       break;
        case Keyboard::RControl:   virtualKey = VK_RCONTROL;   break;
        case Keyboard::RShift:     virtualKey = VK_RSHIFT;     break;
        case Keyboard::RAlt:       virtualKey = VK_RMENU;      break;
        case Keyboard::RSystem:    virtualKey = VK_RWIN;       break;
        case Keyboard::Menu:       virtualKey = VK_APPS;       break;
        case Keyboard::LBracket:   virtualKey = VK_OEM_4;      break;
        case Keyboard::RBracket:   virtualKey = VK_OEM_6;      break;
        case Keyboard::Semicolon:  virtualKey = VK_OEM_1;      break;
        case Keyboard::Comma:      virtualKey = VK_OEM_COMMA;  break;
        case Keyboard::Period:     virtualKey = VK_OEM_PERIOD; break;
        case Keyboard::Apostrophe: virtualKey = VK_OEM_7;      break;
        case Keyboard::Slash:      virtualKey = VK_OEM_2;      break;
        case Keyboard::Backslash:  virtualKey = VK_OEM_5;      break;
        case Keyboard::Tilde:      virtualKey = VK_OEM_3;      break;
        case Keyboard::Equal:      virtualKey = VK_OEM_PLUS;   break;
        case Keyboard::Hyphen:     virtualKey = VK_OEM_MINUS;  break;
        case Keyboard::Space:      virtualKey = VK_SPACE;      break;
        case Keyboard::Enter:      virtualKey = VK_RETURN;     break;
        case Keyboard::Backspace:  virtualKey = VK_BACK;       break;
        case Keyboard::Tab:        virtualKey = VK_TAB;        break;
        case Keyboard::PageUp:     virtualKey = VK_PRIOR;      break;
        case Keyboard::PageDown:   virtualKey = VK_NEXT;       break;
        case Keyboard::End:        virtualKey = VK_END;        break;
        case Keyboard::Home:       virtualKey = VK_HOME;       break;
        case Keyboard::Insert:     virtualKey = VK_INSERT;     break;
        case Keyboard::Delete:     virtualKey = VK_DELETE;     break;
        case Keyboard::Add:        virtualKey = VK_ADD;        break;
        case Keyboard::Subtract:   virtualKey = VK_SUBTRACT;   break;
        case Keyboard::Multiply:   virtualKey = VK_MULTIPLY;   break;
        case Keyboard::Divide:     virtualKey = VK_DIVIDE;     break;
        case Keyboard::Left:       virtualKey = VK_LEFT;       break;
        case Keyboard::Right:      virtualKey = VK_RIGHT;      break;
        case Keyboard::Up:         virtualKey = VK_UP;         break;
        case Keyboard::Down:       virtualKey = VK_DOWN;       break;
        case Keyboard::Numpad0:    virtualKey = VK_NUMPAD0;    break;
        case Keyboard::Numpad1:    virtualKey = VK_NUMPAD1;    break;
        case Keyboard::Numpad2:    virtualKey = VK_NUMPAD2;    break;
        case Keyboard::Numpad3:    virtualKey = VK_NUMPAD3;    break;
        case Keyboard::Numpad4:    virtualKey = VK_NUMPAD4;    break;
        case Keyboard::Numpad5:    virtualKey = VK_NUMPAD5;    break;
        case Keyboard::Numpad6:    virtualKey = VK_NUMPAD6;    break;
        case Keyboard::Numpad7:    virtualKey = VK_NUMPAD7;    break;
        case Keyboard::Numpad8:    virtualKey = VK_NUMPAD8;    break;
        case Keyboard::Numpad9:    virtualKey = VK_NUMPAD9;    break;
        case Keyboard::F1:         virtualKey = VK_F1;         break;
        case Keyboard::F2:         virtualKey = VK_F2;         break;
        case Keyboard::F3:         virtualKey = VK_F3;         break;
        case Keyboard::F4:         virtualKey = VK_F4;         break;
        case Keyboard::F5:         virtualKey = VK_F5;         break;
        case Keyboard::F6:         virtualKey = VK_F6;         break;
        case Keyboard::F7:         virtualKey = VK_F7;         break;
        case Keyboard::F8:         virtualKey = VK_F8;         break;
        case Keyboard::F9:         virtualKey = VK_F9;         break;
        case Keyboard::F10:        virtualKey = VK_F10;        break;
        case Keyboard::F11:        virtualKey = VK_F11;        break;
        case Keyboard::F12:        virtualKey = VK_F12;        break;
        case Keyboard::F13:        virtualKey = VK_F13;        break;
        case Keyboard::F14:        virtualKey = VK_F14;        break;
        case Keyboard::F15:        virtualKey = VK_F15;        break;
        case Keyboard::Pause:      virtualKey = VK_PAUSE;      break;
    }
    return virtualKey;
}

////////////////////////////////////////////////////////////
WORD sfScanToWinScan(Keyboard::Scancode code)
{
    // Convert an SFML scancode to a Windows scancode
    // Reference: https://msdn.microsoft.com/en-us/library/aa299374(v=vs.60).aspx
    switch (code)
    {
        case Keyboard::ScanA: return 30;
        case Keyboard::ScanB: return 48;
        case Keyboard::ScanC: return 46;
        case Keyboard::ScanD: return 32;
        case Keyboard::ScanE: return 18;
        case Keyboard::ScanF: return 33;
        case Keyboard::ScanG: return 34;
        case Keyboard::ScanH: return 35;
        case Keyboard::ScanI: return 23;
        case Keyboard::ScanJ: return 36;
        case Keyboard::ScanK: return 37;
        case Keyboard::ScanL: return 38;
        case Keyboard::ScanM: return 50;
        case Keyboard::ScanN: return 49;
        case Keyboard::ScanO: return 24;
        case Keyboard::ScanP: return 25;
        case Keyboard::ScanQ: return 16;
        case Keyboard::ScanR: return 19;
        case Keyboard::ScanS: return 31;
        case Keyboard::ScanT: return 20;
        case Keyboard::ScanU: return 22;
        case Keyboard::ScanV: return 47;
        case Keyboard::ScanW: return 17;
        case Keyboard::ScanX: return 45;
        case Keyboard::ScanY: return 21;
        case Keyboard::ScanZ: return 44;
    
        case Keyboard::ScanNum1: return 2;
        case Keyboard::ScanNum2: return 3;
        case Keyboard::ScanNum3: return 4;
        case Keyboard::ScanNum4: return 5;
        case Keyboard::ScanNum5: return 6;
        case Keyboard::ScanNum6: return 7;
        case Keyboard::ScanNum7: return 8;
        case Keyboard::ScanNum8: return 9;
        case Keyboard::ScanNum9: return 10;
        case Keyboard::ScanNum0: return 11;
    
        case Keyboard::ScanEnter:      return 28;
        case Keyboard::ScanEscape:     return 1;
        case Keyboard::ScanBackspace:  return 14;
        case Keyboard::ScanTab:        return 15;
        case Keyboard::ScanSpace:      return 57;
        case Keyboard::ScanHyphen:     return 12;
        case Keyboard::ScanEqual:      return 13;
        case Keyboard::ScanLBracket:   return 26;
        case Keyboard::ScanRBracket:   return 27;
        case Keyboard::ScanBackslash:  return 43;
        case Keyboard::ScanGrave:      return 41;
        case Keyboard::ScanSemicolon:  return 39;
        case Keyboard::ScanApostrophe: return 40;
        case Keyboard::ScanComma:      return 51;
        case Keyboard::ScanPeriod:     return 52;
        case Keyboard::ScanSlash:      return 53;
    
        case Keyboard::ScanF1:  return 59;
        case Keyboard::ScanF2:  return 60;
        case Keyboard::ScanF3:  return 61;
        case Keyboard::ScanF4:  return 62;
        case Keyboard::ScanF5:  return 63;
        case Keyboard::ScanF6:  return 64;
        case Keyboard::ScanF7:  return 65;
        case Keyboard::ScanF8:  return 66;
        case Keyboard::ScanF9:  return 67;
        case Keyboard::ScanF10: return 68;
        case Keyboard::ScanF11: return 87;
        case Keyboard::ScanF12: return 88;
        case Keyboard::ScanF13: return 100;
        case Keyboard::ScanF14: return 101;
        case Keyboard::ScanF15: return 102;
        case Keyboard::ScanF16: return 103;
        case Keyboard::ScanF17: return 104;
        case Keyboard::ScanF18: return 105;
        case Keyboard::ScanF19: return 106;
        case Keyboard::ScanF20: return 107;
        case Keyboard::ScanF21: return 108;
        case Keyboard::ScanF22: return 109;
        case Keyboard::ScanF23: return 110;
        case Keyboard::ScanF24: return 118;
    
        case Keyboard::ScanCapsLock:    return 58;
        case Keyboard::ScanPrintScreen: return 55;
        case Keyboard::ScanScrollLock:  return 70;
        case Keyboard::ScanPause:       return 69;
        case Keyboard::ScanInsert:      return 82;
        case Keyboard::ScanHome:        return 71;
        case Keyboard::ScanPageUp:      return 73;
        case Keyboard::ScanDelete:      return 83;
        case Keyboard::ScanEnd:         return 79;
        case Keyboard::ScanPageDown:    return 81;
        case Keyboard::ScanRight:       return 77;
        case Keyboard::ScanLeft:        return 75;
        case Keyboard::ScanDown:        return 80;
        case Keyboard::ScanUp:          return 72;
        case Keyboard::ScanNumLock:     return 69;

        case Keyboard::ScanNumpadDivide:   return 53;
        case Keyboard::ScanNumpadMultiply: return 55;
        case Keyboard::ScanNumpadMinus:    return 74;
        case Keyboard::ScanNumpadPlus:     return 78;
        case Keyboard::ScanNumpadEqual:    return 126;
        case Keyboard::ScanNumpadEnter:    return 28;
        case Keyboard::ScanNumpadDecimal:  return 83;
        
        case Keyboard::ScanNumpad1:        return 79;
        case Keyboard::ScanNumpad2:        return 80;
        case Keyboard::ScanNumpad3:        return 81;
        case Keyboard::ScanNumpad4:        return 75;
        case Keyboard::ScanNumpad5:        return 76;
        case Keyboard::ScanNumpad6:        return 77;
        case Keyboard::ScanNumpad7:        return 71;
        case Keyboard::ScanNumpad8:        return 72;
        case Keyboard::ScanNumpad9:        return 73;
        case Keyboard::ScanNumpad0:        return 82;
    
        case Keyboard::ScanNonUsBackslash: return 86;
        // No known scancode for Keyboard::ScanApplication
        // No known scancode for Keyboard::ScanExecute
        // No known scancode for Keyboard::ScanModeChange
        case Keyboard::ScanHelp:           return 97;
        case Keyboard::ScanMenu:           return 93;
        case Keyboard::ScanSelect:         return 30;
        // No known scancode for Keyboard::ScanRedo
        // No known scancode for Keyboard::ScanUndo
        // No known scancode for Keyboard::ScanCut
        // No known scancode for Keyboard::ScanCopy
        // No known scancode for Keyboard::ScanPaste

        case Keyboard::ScanVolumeMute:         return 32;
        case Keyboard::ScanVolumeUp:           return 46;
        case Keyboard::ScanVolumeDown:         return 44;
        case Keyboard::ScanMediaPlayPause:     return 34;
        case Keyboard::ScanMediaStop:          return 36;
        case Keyboard::ScanMediaNextTrack:     return 25;
        case Keyboard::ScanMediaPreviousTrack: return 16;

        case Keyboard::ScanLControl: return 29;
        case Keyboard::ScanLShift:   return 42;
        case Keyboard::ScanLAlt:     return 56;
        case Keyboard::ScanLSystem:  return 91;
        case Keyboard::ScanRControl: return 29;
        case Keyboard::ScanRShift:   return 54;
        case Keyboard::ScanRAlt:     return 56;
        case Keyboard::ScanRSystem:  return 92;

        case Keyboard::ScanBack:      return 106;
        case Keyboard::ScanForward:   return 105;
        case Keyboard::ScanRefresh:   return 103;
        case Keyboard::ScanStop:      return 104;
        case Keyboard::ScanSearch:    return 101;
        case Keyboard::ScanFavorites: return 102;
        case Keyboard::ScanHomePage:  return 48;

        case Keyboard::ScanLaunchApplication1: return 107;
        case Keyboard::ScanLaunchApplication2: return 33;
        case Keyboard::ScanLaunchMail:         return 108;
        case Keyboard::ScanLaunchMediaSelect:  return 109;

        // Unable to map to a scancode
        default: return 0;
    }
}

////////////////////////////////////////////////////////////
WORD sfScanToWinScanExtended(Keyboard::Scancode code)
{
    // Convert an SFML scancode to a Windows scancode
    // Reference: https://msdn.microsoft.com/en-us/library/aa299374(v=vs.60).aspx
    switch (code)
    {
        case Keyboard::ScanPrintScreen:        return 55  | 0xE100;
        case Keyboard::ScanInsert:             return 82  | 0xE100;
        case Keyboard::ScanHome:               return 71  | 0xE100;
        case Keyboard::ScanPageUp:             return 73  | 0xE100;
        case Keyboard::ScanDelete:             return 83  | 0xE100;
        case Keyboard::ScanEnd:                return 79  | 0xE100;
        case Keyboard::ScanPageDown:           return 81  | 0xE100;
        case Keyboard::ScanRight:              return 77  | 0xE100;
        case Keyboard::ScanLeft:               return 75  | 0xE100;
        case Keyboard::ScanDown:               return 80  | 0xE100;
        case Keyboard::ScanUp:                 return 72  | 0xE100;
        case Keyboard::ScanNumLock:            return 69  | 0xE100;
        case Keyboard::ScanNumpadEnter:        return 28  | 0xE100;
        case Keyboard::ScanHelp:               return 97  | 0xE100;
        case Keyboard::ScanMenu:               return 93  | 0xE100;
        case Keyboard::ScanSelect:             return 30  | 0xE100;
        case Keyboard::ScanVolumeMute:         return 32  | 0xE100;
        case Keyboard::ScanVolumeUp:           return 46  | 0xE100;
        case Keyboard::ScanVolumeDown:         return 44  | 0xE100;
        case Keyboard::ScanMediaPlayPause:     return 34  | 0xE100;
        case Keyboard::ScanMediaStop:          return 36  | 0xE100;
        case Keyboard::ScanMediaNextTrack:     return 25  | 0xE100;
        case Keyboard::ScanMediaPreviousTrack: return 16  | 0xE100;
        case Keyboard::ScanLSystem:            return 91  | 0xE100;
        case Keyboard::ScanRControl:           return 29  | 0xE100;
        case Keyboard::ScanRAlt:               return 56  | 0xE100;
        case Keyboard::ScanRSystem:            return 92  | 0xE100;
        case Keyboard::ScanBack:               return 106 | 0xE100;
        case Keyboard::ScanForward:            return 105 | 0xE100;
        case Keyboard::ScanRefresh:            return 103 | 0xE100;
        case Keyboard::ScanStop:               return 104 | 0xE100;
        case Keyboard::ScanSearch:             return 101 | 0xE100;
        case Keyboard::ScanFavorites:          return 102 | 0xE100;
        case Keyboard::ScanHomePage:           return 48  | 0xE100;
        case Keyboard::ScanLaunchApplication1: return 107 | 0xE100;
        case Keyboard::ScanLaunchApplication2: return 33  | 0xE100;
        case Keyboard::ScanLaunchMail:         return 108 | 0xE100;
        case Keyboard::ScanLaunchMediaSelect:  return 109 | 0xE100;

        // Use non-extended mapping
        default: return sfScanToWinScan(code);
    }
}

UINT sfScanToVirtualKey(Keyboard::Scancode code)
{
    WORD winScancode = sfScanToWinScan(code);
    UINT virtualKey = MapVirtualKey(winScancode, MAPVK_VSC_TO_VK_EX);

    // Manually map non-extended key codes
    switch (code)
    {
        case Keyboard::ScanNumpad0:
            virtualKey = VK_NUMPAD0;
            break;
        case Keyboard::ScanNumpad1:
            virtualKey = VK_NUMPAD1;
            break;
        case Keyboard::ScanNumpad2:
            virtualKey = VK_NUMPAD2;
            break;
        case Keyboard::ScanNumpad3:
            virtualKey = VK_NUMPAD3;
            break;
        case Keyboard::ScanNumpad4:
            virtualKey = VK_NUMPAD4;
            break;
        case Keyboard::ScanNumpad5:
            virtualKey = VK_NUMPAD5;
            break;
        case Keyboard::ScanNumpad6:
            virtualKey = VK_NUMPAD6;
            break;
        case Keyboard::ScanNumpad7:
            virtualKey = VK_NUMPAD7;
            break;
        case Keyboard::ScanNumpad8:
            virtualKey = VK_NUMPAD8;
            break;
        case Keyboard::ScanNumpad9:
            virtualKey = VK_NUMPAD9;
            break;
        case Keyboard::ScanNumpadMinus:
            virtualKey = VK_SUBTRACT;
            break;
        case Keyboard::ScanNumpadDecimal:
            virtualKey = VK_DECIMAL;
            break;
        case Keyboard::ScanNumpadDivide:
            virtualKey = VK_DIVIDE;
            break;
        case Keyboard::ScanPause:
            virtualKey = VK_PAUSE;
            break;
        case Keyboard::ScanRControl:
            virtualKey = VK_RCONTROL;
            break;
        case Keyboard::ScanRAlt:
            virtualKey = VK_RMENU;
            break;
    }

    return virtualKey;
}

bool isValidScancode(Keyboard::Scancode code)
{
    return code > Keyboard::ScanUnknown && code < Keyboard::ScancodeCount;
}

bool isValidKey(Keyboard::Key key)
{
    return key > Keyboard::Unknown && key < Keyboard::KeyCount;
}

////////////////////////////////////////////////////////////
void InputImpl::ensureMappings()
{
    static bool isMappingInitialized = false;

    if (isMappingInitialized)
        return;

    // Phase 1: Initialize mappings with default values
    for (int i = 0; i < Keyboard::KeyCount; ++i)
        m_keyToScancodeMapping[i] = Keyboard::ScanUnknown;

    for (int i = 0; i < Keyboard::ScancodeCount; ++i)
        m_scancodeToKeyMapping[i] = Keyboard::Unknown;

    // Phase 2: Translate scancode to virtual code to key names
    for (int i = 0; i < Keyboard::ScancodeCount; ++i)
    {
        Keyboard::Scancode scan = static_cast<Keyboard::Scancode>(i);
        UINT virtualKey = sfScanToVirtualKey(scan);
        Keyboard::Key key = virtualKeyToSfKey(virtualKey);
        m_keyToScancodeMapping[key] = scan;
        m_scancodeToKeyMapping[scan] = key;
    }

    isMappingInitialized = true;
}

////////////////////////////////////////////////////////////
bool InputImpl::isKeyPressed(Keyboard::Key key)
{
    int virtualKey = sfKeyToVirtualKey(key);
    return (GetAsyncKeyState(virtualKey) & 0x8000) != 0;
}

////////////////////////////////////////////////////////////
bool InputImpl::isKeyPressed(Keyboard::Scancode code)
{
    UINT virtualKey = sfScanToVirtualKey(code);
    return (GetAsyncKeyState(virtualKey) & KF_UP) != 0;
}

////////////////////////////////////////////////////////////
Keyboard::Key InputImpl::localize(Keyboard::Scancode code)
{
    if (!isValidScancode(code))
        return Keyboard::Unknown;

    ensureMappings();

    return m_scancodeToKeyMapping[code];
}

////////////////////////////////////////////////////////////
Keyboard::Scancode InputImpl::delocalize(Keyboard::Key key)
{
    if (!isValidKey(key))
        return Keyboard::ScanUnknown;

    ensureMappings();

    return m_keyToScancodeMapping[key];
}

////////////////////////////////////////////////////////////
String InputImpl::getDescription(Keyboard::Scancode code)
{
    WORD winCode = sfScanToWinScanExtended(code);
    const int bufSize(1024);
    WCHAR name[bufSize];
    int result = GetKeyNameText(winCode << 16, name, bufSize);
    if (result > 0)
    {
        return name;
    }
    return "Unknown";
}

////////////////////////////////////////////////////////////
void InputImpl::setVirtualKeyboardVisible(bool visible)
{
    // Not applicable
}


////////////////////////////////////////////////////////////
bool InputImpl::isMouseButtonPressed(Mouse::Button button)
{
    int virtualKey = 0;
    switch (button)
    {
        case Mouse::Left:     virtualKey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON; break;
        case Mouse::Right:    virtualKey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_LBUTTON : VK_RBUTTON; break;
        case Mouse::Middle:   virtualKey = VK_MBUTTON;  break;
        case Mouse::XButton1: virtualKey = VK_XBUTTON1; break;
        case Mouse::XButton2: virtualKey = VK_XBUTTON2; break;
        default:              virtualKey = 0;           break;
    }

    return (GetAsyncKeyState(virtualKey) & 0x8000) != 0;
}


////////////////////////////////////////////////////////////
Vector2i InputImpl::getMousePosition()
{
    POINT point;
    GetCursorPos(&point);
    return Vector2i(point.x, point.y);
}


////////////////////////////////////////////////////////////
Vector2i InputImpl::getMousePosition(const WindowBase& relativeTo)
{
    WindowHandle handle = relativeTo.getSystemHandle();
    if (handle)
    {
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(handle, &point);
        return Vector2i(point.x, point.y);
    }
    else
    {
        return Vector2i();
    }
}


////////////////////////////////////////////////////////////
void InputImpl::setMousePosition(const Vector2i& position)
{
    SetCursorPos(position.x, position.y);
}


////////////////////////////////////////////////////////////
void InputImpl::setMousePosition(const Vector2i& position, const WindowBase& relativeTo)
{
    WindowHandle handle = relativeTo.getSystemHandle();
    if (handle)
    {
        POINT point = {position.x, position.y};
        ClientToScreen(handle, &point);
        SetCursorPos(point.x, point.y);
    }
}


////////////////////////////////////////////////////////////
bool InputImpl::isTouchDown(unsigned int /*finger*/)
{
    // Not applicable
    return false;
}


////////////////////////////////////////////////////////////
Vector2i InputImpl::getTouchPosition(unsigned int /*finger*/)
{
    // Not applicable
    return Vector2i();
}


////////////////////////////////////////////////////////////
Vector2i InputImpl::getTouchPosition(unsigned int /*finger*/, const WindowBase& /*relativeTo*/)
{
    // Not applicable
    return Vector2i();
}

} // namespace priv

} // namespace sf

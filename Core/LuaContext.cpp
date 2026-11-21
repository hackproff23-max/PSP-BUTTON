// PSP BUTTON: Lua removido (a biblioteca Lua/Sol nao e mais usada).
// Para voltar ao original: git revert <commit do corte 3>

#include <string>

#include "Core/LuaContext.h"

LuaContext g_lua;

void LuaContext::Init() {}

void LuaContext::Shutdown() {}

void LuaContext::Print(LogLineType type, std::string_view text) {
	lines_.push_back(LuaLogLine{ type, std::string(text), 0 });
}

void LuaContext::ExecuteConsoleCommand(std::string_view cmd) {
	Print(LogLineType::Error, "Lua foi removido desta versao.");
}

// PSP BUTTON: Lua removido.
// A interface continua a mesma (para o resto do codigo compilar), mas nao ha mais interpretador Lua.
#pragma once

#include <string_view>
#include <string>
#include <vector>

enum class LogLineType {
	Cmd,
	String,
	Integer,
	Error,
	External,
	Url,
};

// A bit richer than regular log lines, so we can display them in color, and allow various UI tricks.
// All have a string, but some may also have a number or other value.
struct LuaLogLine {
	LogLineType type;
	std::string line;
	int number;
};

class LuaContext {
public:
	void Init();
	void Shutdown();

	const std::vector<LuaLogLine> GetLines() const {
		return lines_;
	}
	void Clear() { lines_.clear(); }

	void Print(LogLineType type, std::string_view text);
	void Print(std::string_view text) {
		Print(LogLineType::External, text);
	}

	// For the console.
	void ExecuteConsoleCommand(std::string_view cmd);

private:
	std::vector<LuaLogLine> lines_;
};

extern LuaContext g_lua;

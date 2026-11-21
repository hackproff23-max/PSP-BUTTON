// PSP BUTTON: depurador por WebSocket removido.
// As 5 funcoes que o resto do codigo chama continuam existindo, mas nao fazem nada.
// Como este arquivo nao referencia mais os "subscribers" (Core/Debugger/WebSocket/*.cpp),
// o linker deixa de incluir a maior parte deles no APK.
// Para voltar ao original: git revert <commit do corte 4>

#include "Core/Debugger/WebSocket.h"

void HandleDebuggerRequest(const http::ServerRequest &request) {}

void StopAllDebuggers() {}

void WebSocketDebuggerTick() {}

bool WebSocketDebuggerHasClients() { return false; }

void WebSocketNotifyBreakpointHit(const BreakpointHit &hit) {}

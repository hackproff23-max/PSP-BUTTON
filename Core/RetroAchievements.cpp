// PSP BUTTON: RetroAchievements removido.
// Todas as funcoes do namespace Achievements continuam existindo (para o resto do codigo compilar),
// mas nao fazem nada: ninguem fica logado, nenhum jogo ativa conquistas, nada e baixado.
// Para voltar ao original: git checkout <commit-anterior> -- Core/RetroAchievements.cpp

#include <string>
#include <set>
#include <string_view>

#include "Core/RetroAchievements.h"

namespace Achievements {

bool IsLoggedIn() { return false; }
bool IsActive() { return false; }
bool UnofficialEnabled() { return false; }
bool EncoreModeActive() { return false; }
bool IsBlockingExecution() { return false; }
bool HardcoreModeActive() { return false; }
bool WarnUserIfHardcoreModeActive(bool isSaveStateAction, std::string_view message) { return false; }
size_t GetRichPresenceMessage(char *buffer, size_t bufSize) { return (size_t)-1; }
bool RAIntegrationDirty() { return false; }
rc_client_t *GetClient() { return nullptr; }

void Initialize() {}
void InitializeRAIntegration(void *windowHandle) {}
void UpdateSettings() {}

bool LoginProblems(std::string *errorString) { return false; }
bool HasToken() { return false; }

bool Shutdown(bool waitForRequests) { return true; }

void DownloadImageIfMissing(std::string_view url, double maxAge) {}

void FrameUpdate() {}
void Idle() {}
void DoState(PointerWrap &p) {}

bool HasAchievementsOrLeaderboards() { return false; }

bool LoginAsync(const char *username, const char *password) { return false; }
void Logout() {}

void SetGame(const Path &path, IdentifiedFileType fileType, FileLoader *fileLoader) {}
void ChangeUMD(const Path &path, FileLoader *fileLoader) {}
void UnloadGame() {}

Statistics GetStatistics() { return Statistics(); }

std::string GetGameAchievementSummary(uint32_t subsetId) { return std::string(); }

std::set<uint32_t> GetActiveChallengeIDs() { return std::set<uint32_t>(); }

} // namespace Achievements

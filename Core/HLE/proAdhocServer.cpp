// PSP BUTTON: servidor adhoc embutido removido.
// Mantem todas as funcoes e variaveis que o resto do codigo espera, mas nenhuma faz nada:
// o servidor nunca inicia e o banco de usuarios/jogos fica vazio.
// Para voltar ao original: git revert <commit do corte 6>

#include <atomic>
#include <thread>

#include "Core/HLE/proAdhocServer.h"

uint32_t _db_user_count = 0;
SceNetAdhocctlUserNode *_db_user = nullptr;
SceNetAdhocctlGameNode *_db_game = nullptr;

std::atomic<bool> adhocServerRunning(false);
std::thread adhocServerThread;

void __AdhocServerInit() {}

void login_user_stream(int fd, uint32_t ip) {}

void login_user_data(SceNetAdhocctlUserNode *user, SceNetAdhocctlLoginPacketC2S *data) {}

void logout_user(SceNetAdhocctlUserNode *user) {}

void free_database() {}

void connect_user(SceNetAdhocctlUserNode *user, SceNetAdhocctlGroupName *group) {}

void disconnect_user(SceNetAdhocctlUserNode *user) {}

void send_scan_results(SceNetAdhocctlUserNode *user) {}

void spread_message(SceNetAdhocctlUserNode *user, const char *message) {}

int get_user_state(SceNetAdhocctlUserNode *user) { return USER_STATE_WAITING; }

void clear_user_rxbuf(SceNetAdhocctlUserNode *user, int clear) {}

void game_product_relink(SceNetAdhocctlProductCode *product, char *from, char *to) {}

void game_product_override(SceNetAdhocctlProductCode *product) {}

void update_status() {}

int proAdhocServerThread(int port) { return 0; }

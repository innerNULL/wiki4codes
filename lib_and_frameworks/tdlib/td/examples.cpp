/**
 * file: example.cpp
 * date: 2022-05-20
 */


#include <map>
#include <td/telegram/Client.h>
#include <td/telegram/td_api.h>
#include <td/telegram/td_api.hpp>

namespace td_api = td::td_api;
using Object = td_api::object_ptr<td_api::Object>;


typedef struct TelegramContext {
  std::unique_ptr<td::ClientManager> client_manager = NULL;
  int32_t client_id = -1;
  std::map<uint64_t, std::function<void(Object)>> handlers;
  uint64_t current_query_id = 0;
  bool need_restart = false;
  bool is_authorized = false;
} TelegramContext;


void init_client_manager(TelegramContext* ctx) {
  td::ClientManager::execute(
    td_api::make_object<td_api::setLogVerbosityLevel>(1));
  ctx->client_manager = std::make_unique<td::ClientManager>();
  printf("finished initialized client manager\n");
}


void init_client_id(TelegramContext* ctx) {
  ctx->client_id = ctx->client_manager->create_client_id();
  printf("the client_id is: %i\n", ctx->client_id);
}


uint64_t get_next_query_id(TelegramContext* ctx) {
  return ++(ctx->current_query_id);
}


void send_query(
    TelegramContext* ctx, 
    td_api::object_ptr<td_api::Function> f, 
    std::function<void(Object)> handler) {
  auto query_id = get_next_query_id(ctx);
  if (handler) {
    ctx->handlers.emplace(query_id, std::move(handler));
  }
  ctx->client_manager->send(ctx->client_id, query_id, std::move(f));
}


/*
void process_response(TelegramContext* ctx) {
  if (!response.object) { return; }
  if (response.request_id == 0) {
  }
}
*/


void running_loop(TelegramContext* ctx) {
  while (true) {
    if (ctx->need_restart) {
    } else if (!ctx->is_authorized) {

    }
  }
}


int main(int argc, char** argv) {
  TelegramContext ctx;
  init_client_manager(&ctx);
  init_client_id(&ctx);
  send_query(&ctx, td_api::make_object<td_api::getOption>("version"), {});
  running_loop(&ctx);
  return 0;
}

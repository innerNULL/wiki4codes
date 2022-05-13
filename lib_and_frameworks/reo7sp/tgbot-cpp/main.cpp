/**
 * file: main.cpp
 * date: 2022-05-13
 */


#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>

#include <tgbot/tgbot.h>


int main(int argc, char** argv) {
  std::string token = "";

  if (argc != 2) {
    printf("sth error with args\n");
  } else {
    token = std::string(argv[1]);
    printf("the token is '%s\n'", token.c_str());
  }

  TgBot::Bot bot(token);

  bot.getEvents().onCommand(
    "start", [&bot](TgBot::Message::Ptr message) {
      bot.getApi().sendMessage(message->chat->id, "Hello world!");
    }
  );

  return 0;
}

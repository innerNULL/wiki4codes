/// file: ws_example.cpp
/// date: 2022-06-05


#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;

using tcp = boost::asio::ip::tcp;


int main(int argc, char** argv) {
  const std::string sub_path = std::string(argv[1]);
  printf("The ws subpath is: %s\n", sub_path.c_str());

  //const std::string host = "websocketstest.com";
  const std::string host = "demo.piesocket.com";
  const std::string port = "80";
  const std::string msg = "hello world";

  net::io_context io_context;
  tcp::resolver resolver{io_context};
  websocket::stream<tcp::socket> ws{io_context};

  auto const results = resolver.resolve(host, port);
  auto ep = net::connect(ws.next_layer(), results);
  std::string host_port = host + ":" + std::to_string(ep.port());
  std::cout << host_port << std::endl;

  /*
  ws.set_option(websocket::stream_base::decorator(
      [](websocket::request_type& req) {
        req.set(
          http::field::user_agent,  
          std::string(BOOST_BEAST_VERSION_STRING) + " websocket-client-coro");
      }
  ));
  */

  ws.handshake(host, sub_path);
  ws.write(net::buffer(std::string(msg)));
  printf("Sent msg: %s\n", msg.c_str());

  beast::flat_buffer buffer;
  ws.read(buffer);

  ws.close(websocket::close_code::normal);
  std::cout << "Get msg: " << beast::make_printable(buffer.data()) << std::endl;
  return 0;
}

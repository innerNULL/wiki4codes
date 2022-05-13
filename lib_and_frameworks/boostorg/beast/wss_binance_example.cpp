/// file: wss_binance_example.cpp
/// date: 2022-06-25
///
/// Some references:
/// * https://gitmotion.com/beast/327154393/the-demo-websocket-client-async-ssl-to-get-data-from-wss
/// * https://www.boost.org/doc/libs/1_70_0/libs/beast/doc/html/beast/using_websocket.html
/// * https://github.com/boostorg/beast/blob/boost-1.78.0/example/websocket/client/sync-ssl/websocket_client_sync_ssl.cpp 
/// * https://github.com/boostorg/beast/issues/1152
/// * https://binance-docs.github.io/apidocs/spot/en/#websocket-market-streams
/// * https://github.com/boostorg/beast/issues/1656


#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace ssl = boost::asio::ssl;

using tcp = boost::asio::ip::tcp;


int main(int argc, char** argv) {
  const std::string host = "stream.binance.com";
  const std::string port = "9443";
  //std::string endpoint = 
  //    "wss://" + host + ":" + std::to_string(port);
  std::string endpoint = host + ":" + port;
  std::string target = "/ws/bnbeth@depth";
  //std::string target = "/ws";
  std::string msg = "{\"method\": \"SUBSCRIBE\", \"params\": [\"btcusdt@@kline_1m\"], \"id\": 312}";

  net::io_context ioc;
  ssl::context ctx{ssl::context::tlsv12_client};
  ///load_root_certificates(ctx);

  tcp::resolver resolver{ioc};
  websocket::stream<beast::ssl_stream<tcp::socket>> ws{ioc, ctx};
  auto const results = resolver.resolve(host, port);

  auto ep = net::connect(get_lowest_layer(ws), results);
  
  ws.next_layer().handshake(ssl::stream_base::client);
  
  ws.set_option(websocket::stream_base::decorator(
    [](websocket::request_type& req) {
      req.set(
        http::field::user_agent, 
        std::string(BOOST_BEAST_VERSION_STRING) + " websocket-client-coro"
      );
    }
  ));

  /// This will cause coredump:
  /// ws.handshake(host, "/");
  ws.handshake(host, target);

  // Send  msg
  //ws.write(net::buffer(msg));
  
  // Define response buffer, both are work
  beast::flat_buffer buffer;
  //boost::beast::multi_buffer buffer;
  
  // Read response and put result into buffer
  std::string response = "";
  for (int16_t i = 0; i < 1000; ++i) {
    printf("%i times reading websocket buffer\n", i);
    ws.read(buffer);
    if (buffer.size() > 0) {
      response = beast::buffers_to_string(buffer.data());
      buffer.clear();
      /// TODO: buffer.consume(0);
      
      //std::cout << beast::make_printable(buffer.data()) << std::endl;
      printf("%s\n", response.c_str());
    }
  }
  
  // Close connection
  ws.close(websocket::close_code::normal);

  return 0;
}

/// file: subscriber_demo_v0.cpp 
/// date: 2022-09-30


#include <ccapi_cpp/ccapi_session.h>


class CustomizedEventHandler : public ccapi::EventHandler {
 public:
  bool processEvent(
      const ccapi::Event& event, ccapi::Session* session
  ) override {
    if (event.getType() == ccapi::Event::Type::SUBSCRIPTION_DATA) {
      for (const auto& message : event.getMessageList()) {
        std::cout << std::string("Best bid and ask at ") 
          << ccapi::UtilTime::getISOTimestamp(message.getTime()) 
          << " are:" << std::endl;

        for (const auto& element : message.getElementList()) {
          const std::map<std::string, std::string>& 
          elementNameValueMap = element.getNameValueMap();
          std::cout << "  " + ccapi::toString(elementNameValueMap) << std::endl;
        }
      }
    }
    return true;
  }
};


int main(int argc, char** argv) {
  std::cout << "Starting" << std::endl;

  ccapi::SessionOptions sessionOptions;
  ccapi::SessionConfigs sessionConfigs;
  CustomizedEventHandler eventHandler;
  ccapi::Session session(sessionOptions, sessionConfigs, &eventHandler);
  ccapi::Subscription subscription("coinbase", "BTC-USD", "MARKET_DEPTH");
  session.subscribe(subscription);
  std::this_thread::sleep_for(std::chrono::seconds(100));
  
  session.stop();
  std::cout << "End" << std::endl;
  return 0;
}

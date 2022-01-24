/// file: helloworld_client.cpp
/// date: 2022-02-15


#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>

#include "helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;


class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel) 
      : stub_(Greeter::NewStub(channel)) {}

  std::string SayHello(const std::string& user) {
    HelloRequest request;
    HelloReply reply;
    ClientContext context;

    request.set_name(user);
    Status status = stub_->SayHello(&context, request, &reply);

    if (status.ok()) {
      return reply.message();
    } else {
      printf(
        "Sth wrong with grpc call, status: %s\n", 
        status.error_message().c_str());
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};


int main(int argc, char** argv) {
  std::string server_info = "localhost:50051";
  std::string name = "world";
  if (argc >= 2) {
    name = argv[1];
    printf("Your name is: %s\n", name.c_str());
  }

  auto channel = grpc::CreateChannel(
    server_info, grpc::InsecureChannelCredentials());
  GreeterClient greeter(channel);

  std::string reply = greeter.SayHello(name);
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}

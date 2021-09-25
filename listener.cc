#include "cyber/cyber.h"
#include "test.pb.h"

void MessageCallback(const std::shared_ptr<test::Test>& msg) {
  std::cout << "a: " << msg->a() <<  "; b: " << msg->b() << std::endl;
}

int main(int argc, char* argv[]) {
  // init cyber framework
  apollo::cyber::Init(argv[0]);
  // create listener node
  auto listener_node = apollo::cyber::CreateNode("listener");
  // create listener
  auto listener = listener_node->CreateReader<test::Test>("test", MessageCallback);
  apollo::cyber::WaitForShutdown();
  return 0;
}

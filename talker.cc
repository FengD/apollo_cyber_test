#include "cyber/cyber.h"
#include "test.pb.h"

using apollo::cyber::Rate;
using apollo::cyber::Time;

int main(int argc, char *argv[]) {
  // init cyber framework
  apollo::cyber::Init(argv[0]);
  // create talker node
  auto talker_node = apollo::cyber::CreateNode("test");
  // create talker
  auto talker = talker_node->CreateWriter<test::Test>("test");
  Rate rate(100.0);
  uint64_t seq = 0;
  while (apollo::cyber::OK()) {
    auto msg = std::make_shared<test::Test>();
    msg->set_a(Time::Now().ToNanosecond());
    msg->set_b(seq);
    talker->Write(msg);
    AINFO << "talker sent a message! No. " << seq;
    seq++;
    rate.Sleep();
  }
  return 0;
}

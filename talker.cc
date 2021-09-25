#include "cyber/cyber.h"
#include "sensor_proto/lidar.pb.h"

using apollo::cyber::Rate;
using apollo::cyber::Time;

int main(int argc, char *argv[]) {
  // init cyber framework
  apollo::cyber::Init(argv[0]);
  // create talker node
  auto talker_node = apollo::cyber::CreateNode("talker");
  // create talker
  auto talker = talker_node->CreateWriter<crdc::airi::PointCloud>("channel/chatter");
  Rate rate(100.0);
  uint64_t seq = 0;
  while (apollo::cyber::OK()) {
    auto msg = std::make_shared<crdc::airi::PointCloud>();
    msg->mutable_header()->set_lidar_timestamp(Time::Now().ToNanosecond());
    msg->mutable_header()->set_sequence_num(seq);
    talker->Write(msg);
    AINFO << "talker sent a message! No. " << seq;
    seq++;
    rate.Sleep();
  }
  return 0;
}

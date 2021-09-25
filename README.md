# Description
This project is a demo which show you how to use [apollo cyber](https://github.com/FengD/apollo_cyber).

# Build
``` shell
mkdir build && cd build
cmake ..
make
```

# Steps
1. Create your own [proto](test.proto) file. You could also use the pre-defined [proto](https://github.com/FengD/apollo_cyber/tree/master/sensor_proto) in [cyber project](https://github.com/FengD/apollo_cyber);
2. Read the user guide of apollo cyber. Create the test code. [talker](talker.cc) [listener](listener)
``` c++
// talker
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

// listener
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

```
3. [develop tools](https://github.com/ApolloAuto/apollo/blob/master/docs/cyber/CyberRT_Developer_Tools.md)

* cyber_monitor
![1](images/1.png)
![2](images/2.png)
* cyber_recorder
![3](images/3.png)
![4](images/4.png)
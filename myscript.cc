

// HELO WORLD
// #include "ns3/core-module.h"

// using namespace ns3;

// NS_LOG_COMPONENT_DEFINE ("HELLO_WORLD");

// int main (int argc, char *argv[])
// {
//   NS_LOG_UNCOND ("Hello World! From NS3!");
//   return 0;
// }
// END HELO WORLD


// START LOGGING
#include "ns3/core-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("myscript");

int main(int argc, char const *argv[])
{
    // LogComponentEnable("myscript", LOG_LEVEL_INFO);
    NS_LOG_ERROR("An example of error log");
    return 0;
}
// END LOGGING


// start of first.cc
// #include "ns3/applications-module.h"
// #include "ns3/core-module.h"
// #include "ns3/internet-module.h"
// #include "ns3/network-module.h"
// #include "ns3/point-to-point-module.h"

// using namespace ns3;

// NS_LOG_COMPONENT_DEFINE("FirstScriptExample");

// int main(int argc, char* argv[]) {

//     NS_LOG_UNCOND ("Executing part 1...");
//     CommandLine cmd(__FILE__);
//     cmd.Parse(argc, argv);


//     NS_LOG_UNCOND ("Program Finished!");
// }
// END first.cc
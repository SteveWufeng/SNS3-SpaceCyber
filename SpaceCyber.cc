#include "ns3/core-module.h"
#include "ns3/satellite-module.h"
#include "ns3/satellite-helper.h"
#include "ns3/simulation-helper.h"
#include "ns3/applications-module.h"
#include "ns3/traffic-module.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SpaceCyber");


/**
 * \file SpaceCyber.cc
 * 
 * \brief This is a simple example of a satellite network simulation.
 *        where a satellite is communicating with a ground station in space.
*/
int main (int argc, char *argv[]) {
    NS_LOG_UNCOND("Setting up simulation...");
    
    SatHelper::PreDefinedScenario_t satScenario = SatHelper::SIMPLE;
    std::string scenario = "Simple";

    // Create simulation helper
    auto simulationHelper = CreateObject<SimulationHelper> ("example-tutorial");
    simulationHelper->SetSimulationTime (12.0);
    
    // Enable creation traces
    // creation trace are used to print out the creation of the different objects
    Config::SetDefault ("ns3::SatHelper::ScenarioCreationTraceEnabled", BooleanValue (true));

    // Enable packet traces (to file PacketTrace.log).
    // packet trace are used to print out the packets that are sent and received
    Config::SetDefault ("ns3::SatHelper::PacketTraceEnabled", BooleanValue (true));

    // Set simulation output details
    // simulation tag is used to name the output files
    // EnableSimulationOutputOverwrite is used to overwrite the output files
    Config::SetDefault ("ns3::SatEnvVariables::SimulationTag", StringValue (scenario));
    Config::SetDefault ("ns3::SatEnvVariables::EnableSimulationOutputOverwrite", BooleanValue (true));

    // enable info logs
    LogComponentEnable ("CbrApplication", LOG_LEVEL_INFO);
    LogComponentEnable ("PacketSink", LOG_LEVEL_INFO);
    LogComponentEnable ("SpaceCyber", LOG_LEVEL_INFO);

    // set simulation time to 12 seconds

    // create helper and simulation scenario
    Ptr<SatHelper> helper = simulationHelper->CreateSatScenario (satScenario);
    

    // getting UT users
    NodeContainer utUsers = helper->GetUtUsers ();

    // get GW users
    NodeContainer gwUsers = helper->GetGwUsers ();
    

    uint16_t port = 9; // well-known echo port number

    // create and install applications on GW user
    PacketSinkHelper sinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (helper->GetUserAddress(gwUsers.Get(0))));
    CbrHelper crbHelper ("ns3::UdpSocketFactory", InetSocketAddress (helper->GetUserAddress(utUsers.Get(0)), port));

    // install sink to receive packets from UT (this is setting up the GW to receive packets from UT)
    // in other word listen to packets from UT for 9 seconds
    ApplicationContainer gwSink = sinkHelper.Install (gwUsers.Get(0));
    gwSink.Start (Seconds (1.0)); // start at 1 second
    gwSink.Stop (Seconds (10.0)); // stop at 10 seconds

    // install CBR to send packets to UT (this is setting up the GW to send packets to UT)
    // in other word send packets from GW to UT for 1.1 seconds
    ApplicationContainer gwCbr = crbHelper.Install (gwUsers.Get(0));
    gwCbr.Start (Seconds (1.0)); // start at 1 second
    gwCbr.Stop (Seconds (2.1)); // stop at 2.1 seconds

    // create applications on UT user
    sinkHelper.SetAttribute("Local", AddressValue(Address(InetSocketAddress (helper->GetUserAddress(utUsers.Get(0)), port))));
    crbHelper.SetAttribute("Remote", AddressValue(Address(InetSocketAddress (helper->GetUserAddress(gwUsers.Get(0)), port))));

    // install sink to receive packets from GW
    ApplicationContainer utSink = sinkHelper.Install (utUsers.Get(0));
    utSink.Start (Seconds (1.0)); // start at 1 second
    utSink.Stop (Seconds (10.0)); // stop at 10 seconds

    // install CBR to send packets to GW
    ApplicationContainer utCbr = crbHelper.Install (utUsers.Get(0));
    utCbr.Start (Seconds (7.0)); // start at 7 second
    utCbr.Stop (Seconds (9.1)); // stop at 3.1 seconds

    NS_LOG_INFO ("---> Starting simulation...");
    NS_LOG_INFO ("  Scenario: " << scenario);
    NS_LOG_INFO ("  ");

    // run simulation
    simulationHelper->RunSimulation ();

    return 0;
}
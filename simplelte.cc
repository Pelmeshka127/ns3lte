#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/lte-module.h"
#include "ns3/mobility-module.h"

using namespace ns3;

int main()
{
    Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();

    NodeContainer enbNodes;
    NodeContainer ueNodes;
    enbNodes.Create(1);
    ueNodes.Create(2);

    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(enbNodes);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(ueNodes);

    NetDeviceContainer enbDevices;
    NetDeviceContainer ueDevices;

    lteHelper->SetSchedulerType("ns3::RrFfMacScheduler");

    enbDevices = lteHelper->InstallEnbDevice(enbNodes);
    ueDevices  = lteHelper->InstallUeDevice(ueNodes);

    lteHelper->Attach(ueDevices.Get(0), enbDevices.Get(0));
    lteHelper->Attach(ueDevices.Get(1), enbDevices.Get(0));

    EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
    EpsBearer bearer(q);
    lteHelper->ActivateDataRadioBearer(ueDevices, bearer);

    lteHelper->EnableMacTraces();
    lteHelper->EnableRlcTraces();

    Simulator::Stop(Seconds(10));
    Simulator::Run();
    Simulator::Destroy();
}
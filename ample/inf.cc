//-------------------------------------------------------------
// file: inf.cc
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------

#include "inf.h"

Define_Module( InfiniteServer );

void InfiniteServer::initialize()
{
}

void InfiniteServer::handleMessage(cMessage *msg)
{
  if (inService.count(msg)) // Departure
    {
      inService.erase(msg);
      endService( msg );
    }
  else // Arrival 
    {
      arrival( msg );
      inService.insert(msg);

      simtime_t serviceTime = serviceRequirement( msg );
      scheduleAt( simTime()+serviceTime, msg );
    }
}

void InfiniteServer::finish()
{
}


simtime_t InfiniteServer::serviceRequirement(cMessage *msg)
{
  ev << "Starting service of " << msg->name() << endl;
  return par("service_time");
}

void InfiniteServer::endService(cMessage *msg)
{
  ev << "Completed service of " << msg->name() << endl;
  send( msg, "out" );
}



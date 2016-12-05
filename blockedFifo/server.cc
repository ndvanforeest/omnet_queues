#include "server.h"

Define_Module( Server );

void Server::initialize()
{
   msgServiced = NULL;
   endServiceMsg = new cMessage("end-service");

   busy = false;
}

void Server::handleMessage(cMessage *msg)
{
   if (msg==endServiceMsg) // Departure
      {
         endService( msgServiced );
	 msgServiced = NULL;
      }
   else
     msgServiced = scheduleEndOfService( msg );
}

void Server::finish()
{
  ev << "*** Module: " << fullPath() << "***" << endl;
}



cMessage* Server::scheduleEndOfService(cMessage *msg)
{
  simtime_t serviceTime = serviceRequirement( msg );
  scheduleAt( simTime()+serviceTime, endServiceMsg );
  busy = true;
  informQueue();
  return( msg );
}

simtime_t Server::serviceRequirement(cMessage *msg)
{
   ev << "Starting service of " << msg->name() << endl;
   return par("service_time");
}

void Server::informQueue()
{
         char msgname[32];
	 if( !busy )
	   sprintf( msgname, "idle");
	 else
	   sprintf( msgname, "busy");

         cMessage *msg = new cMessage( msgname );
	 msg->setKind(busy);
         msg->setTimestamp();
         send( msg, "outUpstream" );
}

void Server::endService(cMessage *msg)
{
   ev << "Completed service of " << msg->name() << endl;
   busy = false;
   send( msg, "outDownstream" );
   informQueue();
   
}


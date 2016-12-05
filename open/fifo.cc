//-------------------------------------------------------------
// file: fifo.cc
//        (part of Queues - an OMNeT++ demo simulation)
//
// We print the  number of customers in the system upon arrival.
//-------------------------------------------------------------

#include "fifo.h"

Define_Module( Fifo );

void Fifo::initialize()
{
   msgServiced = NULL;
   endServiceMsg = new cMessage("end-service");
}

void Fifo::handleMessage(cMessage *msg)
{
   if (msg==endServiceMsg) // Departure
      {
         endService( msgServiced );
         if (queue.empty()) // There is no remaining customer
            {
               msgServiced = NULL;
            }
         else
            {
               msgServiced = (cMessage *) queue.pop();
               simtime_t serviceTime = serviceRequirement( msgServiced );
               scheduleAt( simTime()+serviceTime, endServiceMsg );
            }
      }
   else if (!msgServiced) // Arrival while server is idle
      {
         arrival( msg );

         msgServiced = msg;
         simtime_t serviceTime = serviceRequirement( msgServiced );
         scheduleAt( simTime()+serviceTime, endServiceMsg );
      }
   else // Arrival while server is busy
      {
         arrival( msg );

         queue.insert( msg );
      }
}

void Fifo::finish()
{
}

simtime_t Fifo::serviceRequirement(cMessage *msg)
{
   ev << "Starting service of " << msg->name() << endl;
   return par("service_time");
}

void Fifo::endService(cMessage *msg)
{
   ev << "Completed service of " << msg->name() << endl;
   send( msg, "out" );
}



//------------------------------------------------------------- file:
// file: sink.cc
//      (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------

#include "sink.h"


Define_Module( Sink );

void Sink::initialize()
{
   cycleTimeStats.setName("Cycle time statistics");
}

void Sink::activity()
{
   for(;;)
      {
         cMessage *msg = receive();
         double d = simTime()-msg->timestamp();

         cycleTimeStats.collect( d );

         delete msg;

      }
}

void Sink::finish()
{
   ev << "*** Module: " << fullPath() << "***" << endl;
   ev << "Total jobs processed: " << cycleTimeStats.samples() << endl;
   ev << "Avg cycle time:       " << cycleTimeStats.mean() << endl;
   ev << "Max cycle time:       " << cycleTimeStats.max() << endl;
   ev << "Standard deviation:   " << cycleTimeStats.stddev() << endl;
}




//-------------------------------------------------------------
// file: gen.cc
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------

#include "gen.h"

Define_Module( Generator );

void Generator::initialize()
{
   numJobs = 0;
   newJobMsg = new cMessage("end-service");
   scheduleAt( simTime(), newJobMsg );
   queueFull = false;
}

void Generator::handleMessage(cMessage *msg )
{
  if( msg->arrivedOn("inDownstream") )
    {
      queueFull = msg->kind(); // true if queue downstream is full
      delete( msg );
      if( queueFull )
	{
	  if( newJobMsg->isScheduled() )
	    cancelEvent( newJobMsg );
	}
      else
	if( !newJobMsg->isScheduled() )
	  {
	    simtime_t ia_time = par("ia_time");
	    scheduleAt( simTime()+ ia_time, newJobMsg );
	  }
    }
  else
    {
      simtime_t ia_time = par("ia_time");
      scheduleAt( simTime()+ ia_time, newJobMsg );

      char msgname[32];
      numJobs++;
      sprintf( msgname, "job-%d", numJobs);
      cMessage *msg = new cMessage( msgname );
      msg->setTimestamp();
      send( msg, "out" );
    }
}

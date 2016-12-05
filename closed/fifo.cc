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
  // Set up the initial number of jobs in the queue
  int index = this->index(); // get the index no of this fifo queue
  char msgname[32];

  for(int i=0; i< (int) par("num_init_jobs"); ++i)
    {
      sprintf( msgname, "job-%d_%d", index, i);

      cMessage *msg = new cMessage( msgname );
      //      msg->setTimestamp();
      scheduleAt(simTime(), msg);
    }

  // Arrange for the statistics gathering
  int numcells = 130;

  jobDist = new cDoubleHistogram("Job Distribution", numcells);
  //    jobDist->setRangeAutoUpper(0,1000,4);
  jobDist->setRange(0,numcells);
  waitDist = new cDoubleHistogram("Waiting Distribution", numcells);
  waitDist->setRange(0,400);

  jobsInSys.setName("Jobs in System");

  queue.setName("queue");
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
      queue.insert( msg );
      arrival( msg );
    }
}

void Fifo::arrival(cMessage *msg)
{
  if(this->index() == 0 )
    {
      waitDist->collect(simTime() - msg->timestamp() );
      msg->setTimestamp();
    }
  jobDist->collect(queue.length());
  jobsInSys.record(queue.length());
}


void Fifo::finish()
{
  if( this->index() == 0 )
    {    
      ev << "Th = " << (float)jobDist->samples()/simTime() << endl;
    }
}

simtime_t Fifo::serviceRequirement(cMessage *msg)
{
  ev << "Starting service of " << msg->name() << endl;
  return par("service_time");
}

void Fifo::endService(cMessage *msg)
{
  ev << "Completed service of " << msg->name() << endl;
  //  waitDist->collect(simTime() - msg->timestamp() );
  send( msg, "out" );
}



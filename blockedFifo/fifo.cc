#include "fifo.h"

Define_Module( Fifo );

void Fifo::initialize()
{
   size = par( "size" );

   queue.setName("queue");
   queueDist = new cDoubleHistogram( "Queue Distribution", 100 );
   queueDist->setRange( 0, 100 );
   serverBusy = false;
}

void Fifo::handleMessage(cMessage *msg)
{
  if( msg->arrivedOn("inUpstream") )
    {
      if( !serverBusy && queue.empty() )
	sendDownstream(msg);
      else
	{
	  if( queue.length() < size )
	    queue.insert( msg );
	}
    }
  else // message from server
    {
      serverBusy = msg->kind(); // true if server is busy
      delete( msg );
      if( !serverBusy && !queue.empty() )
	sendDownstream( (cMessage *) queue.pop() );
    }
  informSource();
}

void Fifo::arrival(cMessage* msg)
{
  queueDist->collect( queue.length() );
}

void Fifo::finish()
{
  ev << "*** Module: " << fullPath() << "***" << endl;
  queueDist->recordScalar("Queue Statistics");
}

void Fifo::sendDownstream( cMessage *msg )
{
  send(msg, "outDownstream");
}

void  Fifo::informSource()
{
  char msgname[32];
  if( queue.length() == size)
    sprintf( msgname, "full");
  else
    sprintf( msgname, "room");
 
  cMessage *msg = new cMessage( msgname );
  msg->setKind(queue.length() == size);
  msg->setTimestamp();
  send( msg, "outUpstream" );
}

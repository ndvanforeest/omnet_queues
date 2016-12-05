//-------------------------------------------------------------
// file: msfifo.cc
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------


//------------------------------------------------------------ 
// These //are the problems to tackle (as compared to the
// single-server fifo //queue): 
//
// - When an endServiceMsg arrives, figure out the server that
// finishes the service of what msg.
//
// - When a job arrives or leaves, figure out whether servers are
// free, and obtain an id of a free server that can start serving.
//
// The first problem is solved by creating arrays of endServiceMsgs
// and msgInService.
//
// The second is solved with a pool(deque) containing the Ids of free
// servers. When a served becomes free(busy) its Id is added(removed)
// from the freeServers pool.
//--------------------------------------

#include "msfifo.h"
#include <string>

Define_Module( msFifo );

void msFifo::initialize()
{
   // Set up the initial number of jobs in the queue
   char msgname[32];

   for(int i=0; i< (int) par("num_init_jobs"); ++i)
      {
         sprintf( msgname, "init_job_%d", i);

         cMessage *msg = new cMessage( msgname );
         msg->setTimestamp();
         scheduleAt(simTime(), msg);
      }

   for(int i=0; i<(int)par("num_servers"); ++i)
      {
         msgInService.push_back(NULL); // No msg in service now.

         freeServers.push_back(i);  // Add a server Id.

         cMessage *msg= new cMessage("_end");
         msg->setKind(i);              // Set the server id
         endServiceMsg.push_back(msg); 
      }
}


// I did not want to use the msg->kind to figure out the serverId, the
// reason being that non-end-of-service-messages may have their
// msg-kind set to some value. Hence I rely on the, hopefully, rather
// obscure word "_end" to denote an endServiceMsg. Can this be done in
// a better way?

// I kept in the ev statements for testing. They will be removed when
// everything has been reviewed.

void msFifo::activity()
{
   int serverId;

   for(;;){
      cMessage *msg = receive();
      if (strcmp(msg->name(),"_end")==0) //  end-of-service-msg
         {
            serverId=msg->kind();  
            endService( msgInService[serverId] );
            if (queue.empty()) // There is no remaining job in the queue
               {
                  ev << "serverId " << serverId << " becomes free\n";
                  msgInService[serverId] = NULL;
                  freeServers.push_front(serverId); 
               }
            else  // Give server a new job
               {
                  ev << "serverId " << serverId << " gets new job\n";
                  msgInService[serverId] = (cMessage *) queue.pop();
                  simtime_t serviceTime = serviceRequirement( msgInService[serverId]);
                  scheduleAt( simTime()+serviceTime, endServiceMsg[serverId] );
               }
         }
      else if (freeServers.size()>0) // Arrival while some server is idle
         {
            arrival( msg );
            
            serverId = freeServers.front(); // find id of free server
            freeServers.pop_front(); // the server is no longer free
            ev << "serverId " << serverId << " becomes busy\n";

            msgInService[serverId] = msg;
            simtime_t serviceTime = serviceRequirement( msg );
            scheduleAt( simTime()+serviceTime, endServiceMsg[serverId]);
         }
      else // Arrival while all servers are busy
         {
            arrival( msg );
            ev << "All servers busy\n";

            queue.insert( msg );
         }
   }
}

void msFifo::finish()
{
}

simtime_t msFifo::serviceRequirement(cMessage *msg)
{
   ev << "Starting service of " << msg->name() << endl;
   return par("service_time");
}

void msFifo::endService(cMessage *msg)
{
   ev << "Completed service of " << msg->name() << endl;
   send( msg, "out" );
}





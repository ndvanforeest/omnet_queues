//-------------------------------------------------------------
// file: prosh.cc
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------

#include "prosh.h"

Define_Module( proSh );

void proSh::initialize()
{
   endServiceMsg = new cMessage("end-service");
}

void proSh::activity()
{
   simtime_t service;
   simtime_t nextDep;

   list<jobtype>::iterator jobIt;
   jobtype initJob(endServiceMsg,0);

   for(;;){
      cMessage *msg = receive();

      if (msg==endServiceMsg){ // jobs.begin()->first is finished
         endService(jobs.begin()->first);

         service=jobs.begin()->second;  // All jobs are equal
         for(jobIt=jobs.begin();jobIt!=jobs.end(); ++jobIt){
            jobIt->second -= service;
         }
           
         jobs.erase(jobs.begin());

         if (!jobs.empty()){
            endServiceMsg->setTimestamp();
            nextDep=simTime()+(jobs.begin()->second * jobs.size());
            scheduleAt( nextDep, endServiceMsg);
         }
      } else { 
         arrival( msg );
         simtime_t serviceTime = serviceRequirement( msg );
         jobtype job(initJob);
         job=make_pair(msg,serviceTime);

         if(jobs.empty()){
            jobs.push_back(job);
         } else {
            cancelEvent(endServiceMsg);
            
            service = simTime() - endServiceMsg->timestamp();
            service /= (double) jobs.size();
            for(jobIt=jobs.begin();jobIt!=jobs.end(); ++jobIt){
               jobIt->second -= service;
            }

            for(jobIt=jobs.begin();jobIt!=jobs.end(); ++jobIt){
               if(serviceTime < jobIt->second){
                  break;
               }
            }
            jobs.insert(jobIt,job);
         }

         endServiceMsg->setTimestamp();
         nextDep=simTime()+(jobs.begin()->second * jobs.size());
         scheduleAt( nextDep, endServiceMsg);
      }
   }
}

void proSh::finish()
{
}

simtime_t proSh::serviceRequirement(cMessage *msg)
{  
   simtime_t serviceTime=par("service_time"); 
   ev << "Starting service of " << msg->name();
   ev << " " << serviceTime << endl;
   return serviceTime;
}

void proSh::endService(cMessage *msg)
{
   ev << "Completed service of " << msg->name() << endl;
   send( msg, "out" );
}





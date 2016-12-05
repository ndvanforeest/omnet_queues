//-------------------------------------------------------------
// file: prosh.h
//        (part of Queues - an OMNeT++ demo simulation)
// Author: Nicky van Foreest
//
// This is a processor sharing queue
//-------------------------------------------------------------

#ifndef __PROSH_H
#define __PROSH_H

#include <omnetpp.h>
#include <list>
#include <string>

using namespace std;

class proSh : public cSimpleModule
{
public:
   Module_Class_Members(proSh,cSimpleModule,16384);

   cMessage* endServiceMsg;

   typedef pair<cMessage *, simtime_t> jobtype;
   list<jobtype> jobs;

   virtual void initialize();
   virtual void activity();
   virtual void finish();

   void arrival(cMessage *msg) {}
   simtime_t serviceRequirement(cMessage *msg);
   void endService(cMessage *msg);
};

#endif


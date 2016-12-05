//-------------------------------------------------------------
// file: inf.h
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------

#ifndef __INF_H
#define __INF_H

#include <omnetpp.h>
#include <set>

using namespace std;

// InfiniteServer : abstract base class for single-server queues
class InfiniteServer : public cSimpleModule
{
  public:
    Module_Class_Members(InfiniteServer,cSimpleModule,0);

    set<cMessage*> inService;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

    void arrival(cMessage *msg) {}
    simtime_t serviceRequirement(cMessage *msg);
    void endService(cMessage *msg);
};

#endif


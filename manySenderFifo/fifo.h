//-------------------------------------------------------------
// file: fifo.h
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------

#ifndef __FIFO_H
#define __FIFO_H

#include <omnetpp.h>

// Fifo : abstract base class for single-server queues
class Fifo : public cSimpleModule
{
  public:
    Module_Class_Members(Fifo,cSimpleModule,0);

    cMessage *msgServiced;
    cMessage *endServiceMsg;
    cQueue queue;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

    void arrival(cMessage *msg) {}
    simtime_t serviceRequirement(cMessage *msg);
    void endService(cMessage *msg);
};

#endif


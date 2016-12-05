//-------------------------------------------------------------
// file: fifo.h
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------

#ifndef __FIFO_H
#define __FIFO_H

#include <omnetpp.h>

using namespace std;

class Fifo : public cSimpleModule
{
  public:
    Module_Class_Members(Fifo,cSimpleModule,0);

    cQueue queue;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

    void arrival(cMessage* msg);
    void sendDownstream( cMessage* msg);
    void informSource();

 protected:
    int size;
    bool serverBusy;

    cDoubleHistogram *queueDist; 
};

#endif


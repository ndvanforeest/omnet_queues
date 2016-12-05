#ifndef __SERVER_H
#define __SERVER_H

#include <omnetpp.h>

using namespace std;

class Server : public cSimpleModule
{
  public:
    Module_Class_Members(Server,cSimpleModule,0);

    cMessage *msgServiced;
    cMessage *endServiceMsg;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

    simtime_t serviceRequirement(cMessage *msg);
    cMessage* scheduleEndOfService(cMessage *msg);
    void endService(cMessage *msg);
    void informQueue();

 protected:
    int numDropped;
    bool busy;
};

#endif


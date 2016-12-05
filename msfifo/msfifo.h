//-------------------------------------------------------------
// file: msfifo.h
//        (part of Queues - an OMNeT++ demo simulation)
// Author: Nicky van Foreest
//
// This is a multiserver fifo queue
//-------------------------------------------------------------

#ifndef __MSFIFO_H
#define __MSFIFO_H

#include <omnetpp.h>
#include <deque>
#include <vector>

using namespace std;

class msFifo : public cSimpleModule
{
 public:
    Module_Class_Members(msFifo,cSimpleModule,16384);

    vector<cMessage*> msgInService;
    vector<cMessage*> endServiceMsg;

    deque<int> freeServers;

    cQueue queue;

    virtual void initialize();
    virtual void activity();
    virtual void finish();

    void arrival(cMessage *msg) {}
    simtime_t serviceRequirement(cMessage *msg);
    void endService(cMessage *msg);
};

#endif


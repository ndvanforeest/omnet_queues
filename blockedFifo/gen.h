#ifndef __GEN_H
#define __GEN_H

#include <omnetpp.h>

class Generator : public cSimpleModule
{
    Module_Class_Members(Generator,cSimpleModule,0)

    virtual void initialize();
    virtual void handleMessage( cMessage *msg );

    int numJobs;
    bool queueFull;

    cMessage *newJobMsg;
};

#endif

//-------------------------------------------------------------
// file: fifo.ned
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------


// FifoQueue
//
simple Fifo
    parameters:
        size : numeric;
    gates:
        in: inUpstream, inDownstream;
        out: outDownstream, outUpstream;
endsimple

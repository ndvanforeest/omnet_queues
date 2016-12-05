//-------------------------------------------------------------
// file: fifo.ned
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------


// Fifo --
//
// single-server queue, same service rate for each packet
//
simple Fifo
    parameters:
        service_time : numeric;
    gates:
        in: in[];
        out: out[];
endsimple

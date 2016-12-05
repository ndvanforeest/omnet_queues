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
        size : numeric,
        service_time : numeric;
    gates:
        in: in;
        out: out;
endsimple

//-------------------------------------------------------------
// file: inf.ned
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------


// Inf --
//
// infinite server queue, same service rate for each packet
//
simple InfiniteServer
    parameters:
        service_time : numeric;
    gates:
        in: in;
        out: out;
endsimple

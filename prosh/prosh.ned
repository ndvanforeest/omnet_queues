//-------------------------------------------------------------
// file: prosh.ned
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------


// proSh --
//
// Processor sharing queue
//
simple proSh
    parameters:
        service_time : numeric;
    gates:
        in: in;
        out: out;
endsimple

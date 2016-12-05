//-------------------------------------------------------------
// file: msfifo.ned
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------


// msFifo --
//
// multi-server queue, same service rate for each packet
//
simple msFifo
    parameters:
        service_time : numeric,
        num_servers: numeric,
        num_init_jobs: numeric;
    gates:
        in: in;
        out: out;
endsimple

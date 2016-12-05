// -------------------------------------------------------------
// file: fifonet.ned
//        (part of Queues - an OMNeT++ demo simulation)
// -------------------------------------------------------------


import
    "gen",
    "msfifo",
    "sink";

// FifoNet --
//
// generator + FIFO + sink
//
module FifoNet
    parameters:
        num_servers : numeric;
    submodules:
        gen: Generator;
            parameters:
                num_messages = input,
                ia_time = input;
            display: "p=35,152;i=gen";
        msfifo: msFifo;
            parameters:
                num_servers = num_servers,
                service_time = input,
                num_init_jobs = input;
            display: "p=125,152;i=queue";
        sink: Sink;
            display: "p=;i=sink";
    connections:
        gen.out --> msfifo.in;
        msfifo.out --> sink.in;
endmodule

network fifonet : FifoNet
    parameters:
        num_servers = input( 2, "Number of servers: ");
endnetwork


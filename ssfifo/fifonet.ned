// -------------------------------------------------------------
// file: fifonet.ned
//        (part of Queues - an OMNeT++ demo simulation)
// -------------------------------------------------------------


import
    "gen",
    "fifo",
    "sink";

// FifoNet --
//
// generator + FIFO + sink
//
module FifoNet
    submodules:
        gen: Generator;
            parameters:
                num_messages = input,
                ia_time = input;
            display: "p=35,152;i=gen";
        fifo: Fifo;
            parameters:
		size = input,
                service_time = input;
            display: "p=125,152;i=queue;q=queue";
        sink: Sink;
            display: "p=;i=sink";
    connections:
        gen.out --> fifo.in;
        fifo.out --> sink.in;
endmodule

network fifonet : FifoNet
endnetwork


// -------------------------------------------------------------
// file: closed.ned
//        (part of Queues - an OMNeT++ demo simulation)
// -------------------------------------------------------------


import
    "fifo";

// This is a closed ring network --
//
// generator + FIFO + sink
//
module GeneralRing
    parameters:
        num_buffers : numeric;
    submodules:
        fifo: Fifo[num_buffers];
            parameters:
                service_time = input,
                num_init_jobs = input;
            display: "i=queue;q=queue";
    connections:
        for i=0..num_buffers-2 do
            fifo[i].out --> fifo[i+1].in;
        endfor;
        fifo[num_buffers-1].out --> fifo[0].in;
endmodule

network generalring : GeneralRing
endnetwork


// -------------------------------------------------------------
// file: infnet.ned
//        (part of Queues - an OMNeT++ demo simulation)
// -------------------------------------------------------------


import
    "gen",
    "inf",
    "sink";

// InfNet --
//
// generator + Infinite server queue + sink
//
module InfNet
    submodules:
        gen: Generator;
            parameters:
                num_messages = input,
                ia_time = input;
            display: "p=35,152;i=gen";
        inf: InfiniteServer;
            parameters:
                service_time = input;
            display: "p=125,152;i=queue";
        sink: Sink;
            display: "p=;i=sink";
    connections:
        gen.out --> inf.in;
        inf.out --> sink.in;
endmodule

network infnet : InfNet
endnetwork


// -------------------------------------------------------------
// file: proshnet.ned
//        (part of Queues - an OMNeT++ demo simulation)
// -------------------------------------------------------------


import
    "gen",
    "prosh",
    "sink";

// FifoNet --
//
// generator + processor sharing + sink
//
module ProShNet
    submodules:
        gen: Generator;
            parameters:
                num_messages = input,
                ia_time = input;
            display: "p=35,152;i=gen";
        prosh: proSh;
            parameters:
                service_time = input;
            display: "p=125,152;i=queue";
        sink: Sink;
            display: "p=;i=sink";
    connections:
        gen.out --> prosh.in;
        prosh.out --> sink.in;
endmodule

network proshnet : ProShNet
endnetwork


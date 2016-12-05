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
    parameters: 
        numGen : numeric,
        numSink: numeric;
    submodules: 
        gen: Generator[numGen]; 
            parameters: 
                num_messages = input, 
                ia_time = input; 
            display: "i=block/source";
        fifo: Fifo; 
            parameters: 
                service_time = input; 
            gatesizes: 
                in[numGen],
                out[numSink];
            display: "p=168,156;i=block/queue;q=queue";
        sink: Sink[numSink]; 
            display: "i=block/sink";
    connections: 
        for i=0..numGen-1 do 
            gen[i].out --> fifo.in[i]; 
        endfor; 
        for i=0..numSink-1 do 
            fifo.out[i] --> sink[i].in; 
        endfor; 
endmodule 

network fifonet : FifoNet 
endnetwork 





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
module Closed 
    submodules: 
        fifo0: Fifo; 
            parameters: 
                service_time = input, 
                num_init_jobs = input; 
            display: "b=32,30;p=58,83;i=queue";
        fifo1: Fifo; 
            parameters: 
                service_time = input, 
                num_init_jobs = input; 
            display: "b=32,30;p=89,233;i=queue";
        fifo2: Fifo; 
            parameters: 
                service_time = input, 
                num_init_jobs = input; 
            display: "b=32,30;p=207,134;i=queue";
    connections: 
        fifo0.out --> fifo1.in; 
        fifo1.out --> fifo2.in; 
        fifo2.out --> fifo0.in; 
endmodule 

network closed : Closed 
endnetwork 


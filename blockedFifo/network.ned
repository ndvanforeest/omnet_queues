import
    "gen","fifo","server","sink";

module Network
    submodules:
        gen: Generator;
            parameters:
                num_messages = input,
                ia_time = input;
            display: "i=block/source";
        fifo: Fifo; 
	    parameters:
		size = input;
            display: "i=block/passiveq;q=queue";
	server: Server;	
            parameters:
                service_time = input;
            display: "i=block/server";
        sink: Sink;
            display: "p=;i=sink";
    connections:
        gen.out --> fifo.inUpstream;
	fifo.outUpstream --> gen.inDownstream;
	fifo.outDownstream -->server.inUpstream;
        server.outUpstream --> fifo.inDownstream;
        server.outDownstream --> sink.inUpstream;
	sink.outUpstream --> server.inDownstream;
endmodule

network blocked : Network
endnetwork


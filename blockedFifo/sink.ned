//-------------------------------------------------------------
// file: sink.ned
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------


// Sink --
//
// destroys the packets and creates statistics
//
simple Sink
    gates:
	in: inUpstream;	
	out: outUpstream;
endsimple


//-------------------------------------------------------------
// file: server.ned
//        (part of Queues - an OMNeT++ demo simulation)
//-------------------------------------------------------------


simple Server
    parameters:
        service_time : numeric;
    gates:
        in: inUpstream, inDownstream;
        out: outDownstream, outUpstream;
endsimple

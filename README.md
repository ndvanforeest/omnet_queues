Queues
======

Queues is a queueing network tutorial and basic queueing library for
OMNeT++.

I made this set of programs a long time ago, and I don't expect them
to need some updating before they will run in the current omnet
environment. 


Author: Nicky van Foreest. Part of the code is based on the two fifo
samples in ../samples/fifo1 and ../samples/fifo2

License: GPL

Queues: Queues contains a general tutorial to OMNeT++ and a number of
subdirectories. Each of these shows an implementation of one specific
type of queue such as a single server queue. The idea is to provide a
user a starting point from which he/she can build his/her own queueing
simulation/network in OMNeT++.

Features:
   - Tutorial to running queueing simulations
   - Start of a library with queueing functionality

Usage:
- Read the included tutorial file: tutorial.pdf
- First run opp_makemake -f before trying to compile the files

Tutorial: 
- tutorial.pdf: an explanation of basic OMNeT++ functionality aiming
to show how OMNeT++ can help simulate queueing networks.
- queuesTut/: the files mentioned in the tutorial document. These files
show how to collect, visualize and statistically process simulation
data, change interarrival/service time distributions of jobs, etc.

The queueing library consists of the following directories:
- ample/: an ample, or infinite, server queue
- closed/: a closed ring network consisting of 3 single server fifos
- doc_src/: The sources of the tutorial documentation.
- manySenderFifo/: a single server with multiple in- and outputs
- msfifo/: a multi server fifo
- open/: an open network of single server fifos
- prosh/: a processor sharing queue
- ssfifo/: a single server fifo
- tutorial/: the html pages of the tutorial doc.

Note: 
You are invited to contribute to this library. Please inform me
about any comment you may have.


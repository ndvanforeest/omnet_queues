//-------------------------------------------------------------
// file: distributions.cc
//        (part of Queues - an OMNeT++ demo simulation)
//
// Here we introduce some new distribution functions.
//-------------------------------------------------------------

#include <omnetpp.h>

double deterministic(double a)
{
  return (a);
}

double hyperExponential(double a)
{
  double p= uniform(0.,1.);

  if( p < 0.5 )
    return exponential(a);
  else
    return exponential(5.*a);
    
}

double perturbedExponential(double a, double b)
{
    return ( exponential(a) + uniform(0,b));
}


Define_Function( deterministic, 1);
Define_Function( hyperExponential, 1);
Define_Function( perturbedExponential, 2);

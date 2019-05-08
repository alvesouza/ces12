#ifndef TICKUTIL_H
#define TICKUTIL_H

#include <math.h>       /* round, floor, ceil, trunc */
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

namespace ces12 {

/**
 * \brief Utility class to compute fps of images, or periods of period events. 
 * \par any of methods tick* returns the time since the last call of any of the cycle* methods. There are various flavors, just to allow various different output formats.
 * \par it also counts how many times the tick* methods were called.  
 */
class Tick {
public:
  Tick( ) : valid_(false),cycleCount_(0) {};
  
  long tickNano();
  double tickSec();
  double tickMili();
  double tickHZ() ;
  long getCount() { return cycleCount_;}
  void reset() { cycleCount_=0; valid_=false;}
   
private:
  std::chrono::steady_clock::time_point tstamp_;
  bool valid_; /// valid only if we have already got the first timestamp
  long cycleCount_; /// how many times cycle was called.
  
};//class

}//namespace


#endif

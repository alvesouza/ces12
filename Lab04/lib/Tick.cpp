#include <Tick.h>

using namespace ces12;

/**
 * \par calculate the duration since the last call.
 * @return false at the first call, in this case period will not be written; true at the next calls.
 */
long Tick::tickNano(){
  
  auto current = std::chrono::steady_clock::now();
  cycleCount_++;
  if (!valid_) { // no data to calculate at the first call. 
    tstamp_ = current; // save for the next time
    valid_ = true; // next time we'll have data...
    return 0;;
  }
  long period = std::chrono::duration_cast<std::chrono::nanoseconds>(current - tstamp_).count(); // return the last period
  tstamp_ = current; // save for the next time
  return period;
}//cycle

double Tick::tickSec() {
    return tickNano() / 1e9;    
}

double Tick::tickMili() {
    return tickNano() / 1e6;    
}

double Tick::tickHZ() {
  double period = tickSec();
  if (period <= 0) return 0;
  return  1.0 / period;
};

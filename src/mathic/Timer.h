#ifndef MATHIC_TIMER_GUARD
#define MATHIC_TIMER_GUARD

#include "stdinc.h"
// the following has higher resolution than #include <ctime>
#include <chrono>
#include <cstdio>
#include <ostream>

namespace mathic {
  /** Measures spans of CPU time.

      The internal record of time can overflow quickly. If
      clock_t is 32 bits unsigned and CLOCKS_PER_TIC is one million
      then overflow will occur after 71 minutes. */
  class Timer {
  public:
  typedef std::chrono::steady_clock Clock;
  typedef Clock::time_point Time_point;
    Timer() {reset();}

    /** Resets the amount of elapsed CPU time to zero. */
    void reset() {_clocksAtReset = Clock::now();}

    /** Returns the number of CPU milliseconds since the last reset.
        See class description for time span overflow limitations. */
    unsigned long getMilliseconds() const;

    /** Prints the elapsed time in a human readable format. See
        class description for time span overflow limitations. */
    void print(FILE* out) const;

    /** Prints the elapsed time in a human readable format. See
        class description for time span overflow limitations. */
    void print(std::ostream& out) const;

  private:
  Time_point _clocksAtReset;
  };

  inline std::ostream& operator<<(std::ostream& out, const Timer& timer) {
    timer.print(out);
    return out;
  }
}

#endif

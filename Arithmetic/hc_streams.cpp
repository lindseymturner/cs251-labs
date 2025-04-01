#include "hc_streams.h"
#include <fstream>  /* needed for ofstream below */

namespace HaverfordCS {
    std::ostream &trace = (getenv("TRACE_OUTPUT") ? (*(new std::ofstream(getenv("TRACE_OUTPUT")))) : std::cout);
    std::ostream &debug = (getenv("DEBUG_OUTPUT") ? (*(new std::ofstream(getenv("DEBUG_OUTPUT")))) : std::cout);
}

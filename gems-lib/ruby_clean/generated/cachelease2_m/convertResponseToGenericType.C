/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"

GenericRequestType Chip::convertResponseToGenericType(CoherenceResponseType param_type)
{
  if ((param_type == CoherenceResponseType_DATA)) {
    return GenericRequestType_ST;
  } else {
    if ((param_type == CoherenceResponseType_DATA_ATOMIC)) {
      return GenericRequestType_ATOMIC;
    } else {
      DEBUG_SLICC(MedPrio, "../protocols/FUSION/cachelease2-msg.sm:168: ", param_type);
;
            cerr << "Runtime Error at ../protocols/FUSION/cachelease2-msg.sm:169, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("invalid CoherenceResponseType") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
    }
  }
}


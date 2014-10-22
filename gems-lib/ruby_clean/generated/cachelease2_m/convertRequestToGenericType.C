/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"

GenericRequestType Chip::convertRequestToGenericType(CoherenceRequestType param_type)
{
  if ((param_type == CoherenceRequestType_GETS)) {
    return GenericRequestType_LD;
  } else {
    if ((param_type == CoherenceRequestType_DATA_UPGRADE)) {
      return GenericRequestType_ST;
    } else {
      if ((param_type == CoherenceRequestType_DATA)) {
        return GenericRequestType_ST;
      } else {
        if ((param_type == CoherenceRequestType_DATA_ATOMIC)) {
          return GenericRequestType_ATOMIC;
        } else {
          DEBUG_SLICC(MedPrio, "../protocols/FUSION/cachelease2-msg.sm:157: ", param_type);
;
                    cerr << "Runtime Error at ../protocols/FUSION/cachelease2-msg.sm:158, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("invalid CoherenceRequestType") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
        }
      }
    }
  }
}


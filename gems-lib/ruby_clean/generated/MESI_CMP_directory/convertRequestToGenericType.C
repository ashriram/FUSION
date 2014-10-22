/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"

GenericRequestType Chip::convertRequestToGenericType(CoherenceRequestType param_type)
{
  if ((param_type == CoherenceRequestType_GETS)) {
    return GenericRequestType_LD;
  } else {
    if ((param_type == CoherenceRequestType_GET_INSTR)) {
      return GenericRequestType_IFETCH;
    } else {
      if ((param_type == CoherenceRequestType_GETX)) {
        return GenericRequestType_ST;
      } else {
        if ((param_type == CoherenceRequestType_UPGRADE)) {
          return GenericRequestType_ST;
        } else {
          DEBUG_SLICC(MedPrio, "../protocols/FUSION/MESI_CMP_directory-msg.sm:119: ", param_type);
;
                    cerr << "Runtime Error at ../protocols/FUSION/MESI_CMP_directory-msg.sm:120, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("invalid CoherenceRequestType") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
        }
      }
    }
  }
}


/** \file MessageSizeType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "MessageSizeType.h"

ostream& operator<<(ostream& out, const MessageSizeType& obj)
{
  out << MessageSizeType_to_string(obj);
  out << flush;
  return out;
}

string MessageSizeType_to_string(const MessageSizeType& obj)
{
  switch(obj) {
  case MessageSizeType_Undefined:
    return "Undefined";
  case MessageSizeType_Control:
    return "Control";
  case MessageSizeType_Data:
    return "Data";
  case MessageSizeType_Request_Control:
    return "Request_Control";
  case MessageSizeType_Reissue_Control:
    return "Reissue_Control";
  case MessageSizeType_Response_Data:
    return "Response_Data";
  case MessageSizeType_ResponseL2hit_Data:
    return "ResponseL2hit_Data";
  case MessageSizeType_ResponseLocal_Data:
    return "ResponseLocal_Data";
  case MessageSizeType_Response_Control:
    return "Response_Control";
  case MessageSizeType_Writeback_Data:
    return "Writeback_Data";
  case MessageSizeType_Writeback_Control:
    return "Writeback_Control";
  case MessageSizeType_Forwarded_Control:
    return "Forwarded_Control";
  case MessageSizeType_Invalidate_Control:
    return "Invalidate_Control";
  case MessageSizeType_Unblock_Control:
    return "Unblock_Control";
  case MessageSizeType_Persistent_Control:
    return "Persistent_Control";
  case MessageSizeType_Completion_Control:
    return "Completion_Control";
  case MessageSizeType_Custom_8:
    return "Custom_8";
  case MessageSizeType_Custom_16:
    return "Custom_16";
  case MessageSizeType_Custom_24:
    return "Custom_24";
  case MessageSizeType_Custom_32:
    return "Custom_32";
  case MessageSizeType_Custom_40:
    return "Custom_40";
  case MessageSizeType_Custom_48:
    return "Custom_48";
  case MessageSizeType_Custom_56:
    return "Custom_56";
  case MessageSizeType_Custom_64:
    return "Custom_64";
  case MessageSizeType_Custom_72:
    return "Custom_72";
  case MessageSizeType_Custom_80:
    return "Custom_80";
  case MessageSizeType_Custom_88:
    return "Custom_88";
  case MessageSizeType_Custom_96:
    return "Custom_96";
  case MessageSizeType_Custom_104:
    return "Custom_104";
  case MessageSizeType_Custom_112:
    return "Custom_112";
  case MessageSizeType_Custom_120:
    return "Custom_120";
  case MessageSizeType_Custom_128:
    return "Custom_128";
  case MessageSizeType_Custom_136:
    return "Custom_136";
  case MessageSizeType_Custom_144:
    return "Custom_144";
  case MessageSizeType_Custom_152:
    return "Custom_152";
  case MessageSizeType_Custom_160:
    return "Custom_160";
  case MessageSizeType_Custom_168:
    return "Custom_168";
  case MessageSizeType_Custom_176:
    return "Custom_176";
  case MessageSizeType_Custom_184:
    return "Custom_184";
  case MessageSizeType_Custom_192:
    return "Custom_192";
  case MessageSizeType_Custom_200:
    return "Custom_200";
  case MessageSizeType_Custom_208:
    return "Custom_208";
  case MessageSizeType_Custom_216:
    return "Custom_216";
  case MessageSizeType_Custom_224:
    return "Custom_224";
  case MessageSizeType_Custom_232:
    return "Custom_232";
  case MessageSizeType_Custom_240:
    return "Custom_240";
  case MessageSizeType_Custom_248:
    return "Custom_248";
  case MessageSizeType_Custom_256:
    return "Custom_256";
  default:
    ERROR_MSG("Invalid range for type MessageSizeType");
    return "";
  }
}

MessageSizeType string_to_MessageSizeType(const string& str)
{
  if (false) {
  } else if (str == "Undefined") {
    return MessageSizeType_Undefined;
  } else if (str == "Control") {
    return MessageSizeType_Control;
  } else if (str == "Data") {
    return MessageSizeType_Data;
  } else if (str == "Request_Control") {
    return MessageSizeType_Request_Control;
  } else if (str == "Reissue_Control") {
    return MessageSizeType_Reissue_Control;
  } else if (str == "Response_Data") {
    return MessageSizeType_Response_Data;
  } else if (str == "ResponseL2hit_Data") {
    return MessageSizeType_ResponseL2hit_Data;
  } else if (str == "ResponseLocal_Data") {
    return MessageSizeType_ResponseLocal_Data;
  } else if (str == "Response_Control") {
    return MessageSizeType_Response_Control;
  } else if (str == "Writeback_Data") {
    return MessageSizeType_Writeback_Data;
  } else if (str == "Writeback_Control") {
    return MessageSizeType_Writeback_Control;
  } else if (str == "Forwarded_Control") {
    return MessageSizeType_Forwarded_Control;
  } else if (str == "Invalidate_Control") {
    return MessageSizeType_Invalidate_Control;
  } else if (str == "Unblock_Control") {
    return MessageSizeType_Unblock_Control;
  } else if (str == "Persistent_Control") {
    return MessageSizeType_Persistent_Control;
  } else if (str == "Completion_Control") {
    return MessageSizeType_Completion_Control;
  } else if (str == "Custom_8") {
    return MessageSizeType_Custom_8;
  } else if (str == "Custom_16") {
    return MessageSizeType_Custom_16;
  } else if (str == "Custom_24") {
    return MessageSizeType_Custom_24;
  } else if (str == "Custom_32") {
    return MessageSizeType_Custom_32;
  } else if (str == "Custom_40") {
    return MessageSizeType_Custom_40;
  } else if (str == "Custom_48") {
    return MessageSizeType_Custom_48;
  } else if (str == "Custom_56") {
    return MessageSizeType_Custom_56;
  } else if (str == "Custom_64") {
    return MessageSizeType_Custom_64;
  } else if (str == "Custom_72") {
    return MessageSizeType_Custom_72;
  } else if (str == "Custom_80") {
    return MessageSizeType_Custom_80;
  } else if (str == "Custom_88") {
    return MessageSizeType_Custom_88;
  } else if (str == "Custom_96") {
    return MessageSizeType_Custom_96;
  } else if (str == "Custom_104") {
    return MessageSizeType_Custom_104;
  } else if (str == "Custom_112") {
    return MessageSizeType_Custom_112;
  } else if (str == "Custom_120") {
    return MessageSizeType_Custom_120;
  } else if (str == "Custom_128") {
    return MessageSizeType_Custom_128;
  } else if (str == "Custom_136") {
    return MessageSizeType_Custom_136;
  } else if (str == "Custom_144") {
    return MessageSizeType_Custom_144;
  } else if (str == "Custom_152") {
    return MessageSizeType_Custom_152;
  } else if (str == "Custom_160") {
    return MessageSizeType_Custom_160;
  } else if (str == "Custom_168") {
    return MessageSizeType_Custom_168;
  } else if (str == "Custom_176") {
    return MessageSizeType_Custom_176;
  } else if (str == "Custom_184") {
    return MessageSizeType_Custom_184;
  } else if (str == "Custom_192") {
    return MessageSizeType_Custom_192;
  } else if (str == "Custom_200") {
    return MessageSizeType_Custom_200;
  } else if (str == "Custom_208") {
    return MessageSizeType_Custom_208;
  } else if (str == "Custom_216") {
    return MessageSizeType_Custom_216;
  } else if (str == "Custom_224") {
    return MessageSizeType_Custom_224;
  } else if (str == "Custom_232") {
    return MessageSizeType_Custom_232;
  } else if (str == "Custom_240") {
    return MessageSizeType_Custom_240;
  } else if (str == "Custom_248") {
    return MessageSizeType_Custom_248;
  } else if (str == "Custom_256") {
    return MessageSizeType_Custom_256;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type MessageSizeType");
  }
}

MessageSizeType& operator++( MessageSizeType& e) {
  assert(e < MessageSizeType_NUM);
  return e = MessageSizeType(e+1);
}

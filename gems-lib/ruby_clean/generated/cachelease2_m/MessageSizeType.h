/** \file MessageSizeType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef MessageSizeType_H
#define MessageSizeType_H

#include "Global.h"

/** \enum MessageSizeType
  * \brief ...
  */
enum MessageSizeType {
  MessageSizeType_FIRST,
  MessageSizeType_Undefined = MessageSizeType_FIRST,  /**< Undefined */
  MessageSizeType_Control,  /**< Control Message */
  MessageSizeType_Data,  /**< Data Message */
  MessageSizeType_Request_Control,  /**< Request */
  MessageSizeType_Reissue_Control,  /**< Reissued request */
  MessageSizeType_Response_Data,  /**< data response */
  MessageSizeType_ResponseL2hit_Data,  /**< data response */
  MessageSizeType_ResponseLocal_Data,  /**< data response */
  MessageSizeType_Response_Control,  /**< non-data response */
  MessageSizeType_Writeback_Data,  /**< Writeback data */
  MessageSizeType_Writeback_Control,  /**< Writeback control */
  MessageSizeType_Forwarded_Control,  /**< Forwarded control */
  MessageSizeType_Invalidate_Control,  /**< Invalidate control */
  MessageSizeType_Unblock_Control,  /**< Unblock control */
  MessageSizeType_Persistent_Control,  /**< Persistent request activation messages */
  MessageSizeType_Completion_Control,  /**< Completion messages */
  MessageSizeType_Custom_8,  /**< Custom message size */
  MessageSizeType_Custom_16,  /**< Custom message size */
  MessageSizeType_Custom_24,  /**< Custom message size */
  MessageSizeType_Custom_32,  /**< Custom message size */
  MessageSizeType_Custom_40,  /**< Custom message size */
  MessageSizeType_Custom_48,  /**< Custom message size */
  MessageSizeType_Custom_56,  /**< Custom message size */
  MessageSizeType_Custom_64,  /**< Custom message size */
  MessageSizeType_Custom_72,  /**< Custom message size */
  MessageSizeType_Custom_80,  /**< Custom message size */
  MessageSizeType_Custom_88,  /**< Custom message size */
  MessageSizeType_Custom_96,  /**< Custom message size */
  MessageSizeType_Custom_104,  /**< Custom message size */
  MessageSizeType_Custom_112,  /**< Custom message size */
  MessageSizeType_Custom_120,  /**< Custom message size */
  MessageSizeType_Custom_128,  /**< Custom message size */
  MessageSizeType_Custom_136,  /**< Custom message size */
  MessageSizeType_Custom_144,  /**< Custom message size */
  MessageSizeType_Custom_152,  /**< Custom message size */
  MessageSizeType_Custom_160,  /**< Custom message size */
  MessageSizeType_Custom_168,  /**< Custom message size */
  MessageSizeType_Custom_176,  /**< Custom message size */
  MessageSizeType_Custom_184,  /**< Custom message size */
  MessageSizeType_Custom_192,  /**< Custom message size */
  MessageSizeType_Custom_200,  /**< Custom message size */
  MessageSizeType_Custom_208,  /**< Custom message size */
  MessageSizeType_Custom_216,  /**< Custom message size */
  MessageSizeType_Custom_224,  /**< Custom message size */
  MessageSizeType_Custom_232,  /**< Custom message size */
  MessageSizeType_Custom_240,  /**< Custom message size */
  MessageSizeType_Custom_248,  /**< Custom message size */
  MessageSizeType_Custom_256,  /**< Custom message size */
  MessageSizeType_NUM
};
MessageSizeType string_to_MessageSizeType(const string& str);
string MessageSizeType_to_string(const MessageSizeType& obj);
MessageSizeType &operator++( MessageSizeType &e);
ostream& operator<<(ostream& out, const MessageSizeType& obj);

#endif // MessageSizeType_H

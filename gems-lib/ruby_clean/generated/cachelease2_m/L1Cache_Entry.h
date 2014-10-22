/** \file L1Cache_Entry.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef L1Cache_Entry_H
#define L1Cache_Entry_H

#include "Global.h"
#include "Allocator.h"
#include "L1Cache_State.h"
#include "DataBlock.h"
#include "AbstractCacheEntry.h"
class L1Cache_Entry :  public AbstractCacheEntry {
public:
  L1Cache_Entry() 
  : AbstractCacheEntry()
  {
    m_CacheState = L1Cache_State_I; // default value of L1Cache_State
    // m_DataBlk has no default
    m_liveUntilTime = 0; // default value of Time
  }
  ~L1Cache_Entry() { };
  L1Cache_Entry(const L1Cache_State& local_CacheState, const DataBlock& local_DataBlk, const Time& local_liveUntilTime)
  : AbstractCacheEntry()
  {
    m_CacheState = local_CacheState;
    m_DataBlk = local_DataBlk;
    m_liveUntilTime = local_liveUntilTime;
  }
  // Const accessors methods for each field
/** \brief Const accessor method for CacheState field.
  * \return CacheState field
  */
  const L1Cache_State& getCacheState() const { return m_CacheState; }
/** \brief Const accessor method for DataBlk field.
  * \return DataBlk field
  */
  const DataBlock& getDataBlk() const { return m_DataBlk; }
/** \brief Const accessor method for liveUntilTime field.
  * \return liveUntilTime field
  */
  const Time& getliveUntilTime() const { return m_liveUntilTime; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for CacheState field.
  * \return CacheState field
  */
  L1Cache_State& getCacheState() { return m_CacheState; }
/** \brief Non-const accessor method for DataBlk field.
  * \return DataBlk field
  */
  DataBlock& getDataBlk() { return m_DataBlk; }
/** \brief Non-const accessor method for liveUntilTime field.
  * \return liveUntilTime field
  */
  Time& getliveUntilTime() { return m_liveUntilTime; }

  // Mutator methods for each field
/** \brief Mutator method for CacheState field */
  void setCacheState(const L1Cache_State& local_CacheState) { m_CacheState = local_CacheState; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for liveUntilTime field */
  void setliveUntilTime(const Time& local_liveUntilTime) { m_liveUntilTime = local_liveUntilTime; }

  void print(ostream& out) const;
//private:
  L1Cache_State m_CacheState; /**< cache state*/
  DataBlock m_DataBlk; /**< data for the block*/
  Time m_liveUntilTime; /**< lifetime of the cache block*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const L1Cache_Entry& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const L1Cache_Entry& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // L1Cache_Entry_H

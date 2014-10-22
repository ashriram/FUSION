// Auto generated C++ code started by symbols/SymbolTable.C:370

#include "Chip.h"
#include "Network.h"
#include "CacheRecorder.h"

// Includes for controllers
#include "L2Cache_Controller.h"
#include "L1Cache_Controller.h"
#include "Directory_Controller.h"

Chip::Chip(NodeID id, Network* net_ptr):AbstractChip(id, net_ptr)
{
  m_chip_ptr = this;
  // L2Cache_DirRequestFromL2Cache
  m_L2Cache_DirRequestFromL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_DirRequestFromL2Cache_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), false, 2);
    assert(m_L2Cache_DirRequestFromL2Cache_vec[i] != NULL);
    m_L2Cache_DirRequestFromL2Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L2Cache_DirRequestFromL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_L2Cache_DirRequestFromL2Cache_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L2Cache, DirRequestFromL2Cache]");

  }
  // L2Cache_L1RequestFromL2Cache
  m_L2Cache_L1RequestFromL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L1RequestFromL2Cache_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), false, 1);
    assert(m_L2Cache_L1RequestFromL2Cache_vec[i] != NULL);
    m_L2Cache_L1RequestFromL2Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L2Cache_L1RequestFromL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_L2Cache_L1RequestFromL2Cache_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L2Cache, L1RequestFromL2Cache]");

  }
  // L2Cache_responseFromL2Cache
  m_L2Cache_responseFromL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_responseFromL2Cache_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), false, 3);
    assert(m_L2Cache_responseFromL2Cache_vec[i] != NULL);
    m_L2Cache_responseFromL2Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L2Cache_responseFromL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_L2Cache_responseFromL2Cache_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L2Cache, responseFromL2Cache]");

  }
  // L2Cache_unblockToL2Cache
  m_L2Cache_unblockToL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_unblockToL2Cache_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), false, 4);
    assert(m_L2Cache_unblockToL2Cache_vec[i] != NULL);
    m_L2Cache_unblockToL2Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L2Cache_unblockToL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_L2Cache_unblockToL2Cache_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L2Cache, unblockToL2Cache]");

  }
  // L2Cache_L1RequestToL2Cache
  m_L2Cache_L1RequestToL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L1RequestToL2Cache_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), false, 0);
    assert(m_L2Cache_L1RequestToL2Cache_vec[i] != NULL);
    m_L2Cache_L1RequestToL2Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L2Cache_L1RequestToL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_L2Cache_L1RequestToL2Cache_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L2Cache, L1RequestToL2Cache]");

  }
  // L2Cache_responseToL2Cache
  m_L2Cache_responseToL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_responseToL2Cache_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), false, 3);
    assert(m_L2Cache_responseToL2Cache_vec[i] != NULL);
    m_L2Cache_responseToL2Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L2Cache_responseToL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_L2Cache_responseToL2Cache_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L2Cache, responseToL2Cache]");

  }
  // L2Cache_L2_TBEs
  m_L2Cache_L2_TBEs_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L2_TBEs_vec[i] = new TBETable<L2Cache_TBE>(this);

    assert(m_L2Cache_L2_TBEs_vec[i] != NULL);
  }

  // L2Cache_L2cacheMemory
  m_L2Cache_L2cacheMemory_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L2cacheMemory_vec[i] = new CacheMemory<L2Cache_Entry>(this, L2_CACHE_NUM_SETS_BITS,L2_CACHE_ASSOC,MachineType_L2Cache,int_to_string(i));

    assert(m_L2Cache_L2cacheMemory_vec[i] != NULL);
  }

  // L1Cache_requestFromL1Cache
  m_L1Cache_requestFromL1Cache_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_requestFromL1Cache_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfL1CachePerChip()+MachineType_base_number(string_to_MachineType("L1Cache")), false, 0);
    assert(m_L1Cache_requestFromL1Cache_vec[i] != NULL);
    m_L1Cache_requestFromL1Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L1Cache_requestFromL1Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_L1Cache_requestFromL1Cache_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L1Cache, requestFromL1Cache]");

  }
  // L1Cache_responseFromL1Cache
  m_L1Cache_responseFromL1Cache_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_responseFromL1Cache_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfL1CachePerChip()+MachineType_base_number(string_to_MachineType("L1Cache")), false, 3);
    assert(m_L1Cache_responseFromL1Cache_vec[i] != NULL);
    m_L1Cache_responseFromL1Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L1Cache_responseFromL1Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_L1Cache_responseFromL1Cache_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L1Cache, responseFromL1Cache]");

  }
  // L1Cache_unblockFromL1Cache
  m_L1Cache_unblockFromL1Cache_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_unblockFromL1Cache_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfL1CachePerChip()+MachineType_base_number(string_to_MachineType("L1Cache")), false, 4);
    assert(m_L1Cache_unblockFromL1Cache_vec[i] != NULL);
    m_L1Cache_unblockFromL1Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L1Cache_unblockFromL1Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_L1Cache_unblockFromL1Cache_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L1Cache, unblockFromL1Cache]");

  }
  // L1Cache_requestToL1Cache
  m_L1Cache_requestToL1Cache_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_requestToL1Cache_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfL1CachePerChip()+MachineType_base_number(string_to_MachineType("L1Cache")), false, 1);
    assert(m_L1Cache_requestToL1Cache_vec[i] != NULL);
    m_L1Cache_requestToL1Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L1Cache_requestToL1Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_L1Cache_requestToL1Cache_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L1Cache, requestToL1Cache]");

  }
  // L1Cache_responseToL1Cache
  m_L1Cache_responseToL1Cache_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_responseToL1Cache_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfL1CachePerChip()+MachineType_base_number(string_to_MachineType("L1Cache")), false, 3);
    assert(m_L1Cache_responseToL1Cache_vec[i] != NULL);
    m_L1Cache_responseToL1Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L1Cache_responseToL1Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_L1Cache_responseToL1Cache_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L1Cache, responseToL1Cache]");

  }
  // L1Cache_L1_TBEs
  m_L1Cache_L1_TBEs_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1_TBEs_vec[i] = new TBETable<L1Cache_TBE>(this);

    assert(m_L1Cache_L1_TBEs_vec[i] != NULL);
  }

  // L1Cache_L1IcacheMemory
  m_L1Cache_L1IcacheMemory_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1IcacheMemory_vec[i] = new CacheMemory<L1Cache_Entry>(this, L1_CACHE_NUM_SETS_BITS,L1_CACHE_ASSOC,MachineType_L1Cache,int_to_string(i)+"_L1I");

    assert(m_L1Cache_L1IcacheMemory_vec[i] != NULL);
  }

  // L1Cache_L1DcacheMemory
  m_L1Cache_L1DcacheMemory_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1DcacheMemory_vec[i] = new CacheMemory<L1Cache_Entry>(this, L1_CACHE_NUM_SETS_BITS,L1_CACHE_ASSOC,MachineType_L1Cache,int_to_string(i)+"_L1D");

    assert(m_L1Cache_L1DcacheMemory_vec[i] != NULL);
  }

  // L1Cache_mandatoryQueue
  m_L1Cache_mandatoryQueue_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_mandatoryQueue_vec[i] = new MessageBuffer(this);

    assert(m_L1Cache_mandatoryQueue_vec[i] != NULL);
    m_L1Cache_mandatoryQueue_vec[i]->setOrdering(false);
    m_L1Cache_mandatoryQueue_vec[i]->setPriority(100);
    if (FINITE_BUFFERING) {
      m_L1Cache_mandatoryQueue_vec[i]->setSize(PROCESSOR_BUFFER_SIZE);
    }
  m_L1Cache_mandatoryQueue_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", L1Cache, mandatoryQueue]");

  }

  // L1Cache_sequencer
  m_L1Cache_sequencer_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_sequencer_vec[i] = new Sequencer(this, i);

    assert(m_L1Cache_sequencer_vec[i] != NULL);
  }

  // Directory_requestToDir
  m_Directory_requestToDir_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_requestToDir_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfDirectoryPerChip()+MachineType_base_number(string_to_MachineType("Directory")), false, 2);
    assert(m_Directory_requestToDir_vec[i] != NULL);
    m_Directory_requestToDir_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_Directory_requestToDir_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_Directory_requestToDir_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", Directory, requestToDir]");

  }
  // Directory_responseToDir
  m_Directory_responseToDir_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_responseToDir_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfDirectoryPerChip()+MachineType_base_number(string_to_MachineType("Directory")), false, 3);
    assert(m_Directory_responseToDir_vec[i] != NULL);
    m_Directory_responseToDir_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_Directory_responseToDir_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_Directory_responseToDir_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", Directory, responseToDir]");

  }
  // Directory_responseFromDir
  m_Directory_responseFromDir_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_responseFromDir_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfDirectoryPerChip()+MachineType_base_number(string_to_MachineType("Directory")), false, 3);
    assert(m_Directory_responseFromDir_vec[i] != NULL);
    m_Directory_responseFromDir_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_Directory_responseFromDir_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  m_Directory_responseFromDir_vec[i]->setDescription("[Chip " + int_to_string(getID()) + " " + int_to_string(i) + ", Directory, responseFromDir]");

  }
  // Directory_directory
  m_Directory_directory_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_directory_vec[i] = new DirectoryMemory(this, i);

    assert(m_Directory_directory_vec[i] != NULL);
  }

  m_L2Cache_Controller_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_Controller_vec[i] = new L2Cache_Controller(this, i);
    assert(m_L2Cache_Controller_vec[i] != NULL);
  }

  m_L1Cache_Controller_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_Controller_vec[i] = new L1Cache_Controller(this, i);
    assert(m_L1Cache_Controller_vec[i] != NULL);
  }

  m_Directory_Controller_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_Controller_vec[i] = new Directory_Controller(this, i);
    assert(m_Directory_Controller_vec[i] != NULL);
  }

}

Chip::~Chip()
{
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_L2_TBEs_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_L2cacheMemory_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_L1_TBEs_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_L1IcacheMemory_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_L1DcacheMemory_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_mandatoryQueue_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_sequencer_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    delete m_Directory_directory_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_Controller_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_Controller_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    delete m_Directory_Controller_vec[i];
  }
}

void Chip::clearStats()
{
  L2Cache_Controller::clearStats();
  L1Cache_Controller::clearStats();
  Directory_Controller::clearStats();
}

void Chip::printStats(ostream& out)
{
  out << endl;
  out << "Chip Stats" << endl;
  out << "----------" << endl << endl;
  L2Cache_Controller::dumpStats(out);
  L1Cache_Controller::dumpStats(out);
  Directory_Controller::dumpStats(out);
}

void Chip::printBufferStats(ostream& out)
{
  out << endl;
  out << "Chip Buffer Stats" << endl;
  out << "----------" << endl << endl;
  // L2Cache_DirRequestFromL2Cache
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_DirRequestFromL2Cache_vec[i]->printStats(out);
  }
  // L2Cache_L1RequestFromL2Cache
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L1RequestFromL2Cache_vec[i]->printStats(out);
  }
  // L2Cache_responseFromL2Cache
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_responseFromL2Cache_vec[i]->printStats(out);
  }
  // L2Cache_unblockToL2Cache
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_unblockToL2Cache_vec[i]->printStats(out);
  }
  // L2Cache_L1RequestToL2Cache
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L1RequestToL2Cache_vec[i]->printStats(out);
  }
  // L2Cache_responseToL2Cache
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_responseToL2Cache_vec[i]->printStats(out);
  }
  // L2Cache_L2_TBEs
  // L2Cache_L2cacheMemory
  // L1Cache_requestFromL1Cache
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_requestFromL1Cache_vec[i]->printStats(out);
  }
  // L1Cache_responseFromL1Cache
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_responseFromL1Cache_vec[i]->printStats(out);
  }
  // L1Cache_unblockFromL1Cache
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_unblockFromL1Cache_vec[i]->printStats(out);
  }
  // L1Cache_requestToL1Cache
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_requestToL1Cache_vec[i]->printStats(out);
  }
  // L1Cache_responseToL1Cache
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_responseToL1Cache_vec[i]->printStats(out);
  }
  // L1Cache_L1_TBEs
  // L1Cache_L1IcacheMemory
  // L1Cache_L1DcacheMemory
  // L1Cache_mandatoryQueue
  // L1Cache_sequencer
  // Directory_requestToDir
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_requestToDir_vec[i]->printStats(out);
  }
  // Directory_responseToDir
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_responseToDir_vec[i]->printStats(out);
  }
  // Directory_responseFromDir
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_responseFromDir_vec[i]->printStats(out);
  }
  // Directory_directory
}

void Chip::printConfig(ostream& out)
{
  out << "Chip Config" << endl;
  out << "-----------" << endl;
  out << "Total_Chips: " << RubyConfig::numberOfChips() << endl;
  out << "\nL2Cache_L2_TBEs numberPerChip: " << RubyConfig::numberOfL2CachePerChip() << endl;
  if(m_L2Cache_L2_TBEs_vec.size()>0)
    m_L2Cache_L2_TBEs_vec[0]->printConfig(out);
  out << "\nL2Cache_L2cacheMemory numberPerChip: " << RubyConfig::numberOfL2CachePerChip() << endl;
  if(m_L2Cache_L2cacheMemory_vec.size()>0)
    m_L2Cache_L2cacheMemory_vec[0]->printConfig(out);
  out << "\nL1Cache_L1_TBEs numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  if(m_L1Cache_L1_TBEs_vec.size()>0)
    m_L1Cache_L1_TBEs_vec[0]->printConfig(out);
  out << "\nL1Cache_L1IcacheMemory numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  if(m_L1Cache_L1IcacheMemory_vec.size()>0)
    m_L1Cache_L1IcacheMemory_vec[0]->printConfig(out);
  out << "\nL1Cache_L1DcacheMemory numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  if(m_L1Cache_L1DcacheMemory_vec.size()>0)
    m_L1Cache_L1DcacheMemory_vec[0]->printConfig(out);
  out << "\nL1Cache_mandatoryQueue numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  if(m_L1Cache_mandatoryQueue_vec.size()>0)
    m_L1Cache_mandatoryQueue_vec[0]->printConfig(out);
  out << "\nL1Cache_sequencer numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  if(m_L1Cache_sequencer_vec.size()>0)
    m_L1Cache_sequencer_vec[0]->printConfig(out);
  out << "\nDirectory_directory numberPerChip: " << RubyConfig::numberOfDirectoryPerChip() << endl;
  if(m_Directory_directory_vec.size()>0)
    m_Directory_directory_vec[0]->printConfig(out);
  out << endl;
}

void Chip::print(ostream& out) const
{
  out << "Ruby Chip" << endl;
}
#ifdef CHECK_COHERENCE

bool Chip::isBlockShared(const Address& addr) const
{
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    if (m_L2Cache_Controller_vec[i]->L2Cache_isBlockShared(addr)) {
      return true; 
    }
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    if (m_L1Cache_Controller_vec[i]->L1Cache_isBlockShared(addr)) {
      return true; 
    }
  }
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    if (m_Directory_Controller_vec[i]->Directory_isBlockShared(addr)) {
      return true; 
    }
  }
  return false;
}


bool Chip::isBlockExclusive(const Address& addr) const
{
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    if (m_L2Cache_Controller_vec[i]->L2Cache_isBlockExclusive(addr)) {
      return true; 
    }
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    if (m_L1Cache_Controller_vec[i]->L1Cache_isBlockExclusive(addr)) {
      return true; 
    }
  }
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    if (m_Directory_Controller_vec[i]->Directory_isBlockExclusive(addr)) {
      return true; 
    }
  }
  return false;
}

#endif /* CHECK_COHERENCE */ 

void Chip::dumpCaches(ostream& out) const
{
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L2cacheMemory_vec[i]->print(out);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1IcacheMemory_vec[i]->print(out);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1DcacheMemory_vec[i]->print(out);
  }
}

void Chip::dumpCacheData(ostream& out) const
{
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L2cacheMemory_vec[i]->printData(out);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1IcacheMemory_vec[i]->printData(out);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1DcacheMemory_vec[i]->printData(out);
  }
}

void Chip::recordCacheContents(CacheRecorder& tr) const
{
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L2cacheMemory_vec[i]->recordCacheContents(tr);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1IcacheMemory_vec[i]->recordCacheContents(tr);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1DcacheMemory_vec[i]->recordCacheContents(tr);
  }
}

void Chip::flushAllL1DCaches(ostream& out)
{
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    assert(m_L1Cache_L1DcacheMemory_vec.size() > i);
    m_L1Cache_L1DcacheMemory_vec[i]->flushCache(out);
  }
}

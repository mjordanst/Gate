/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/
//GND:ClassToRemove

#include "GatePileupOld.hh"

#include "G4UnitsTable.hh"

#include "GateOutputVolumeID.hh"
#include "GatePileupOldMessenger.hh"
#include "GateTools.hh"


GatePileupOld::GatePileupOld(GatePulseProcessorChain* itsChain,
      	      	      	 const G4String& itsName)
  : GateVPulseProcessor(itsChain,itsName),
    m_depth(1),
    m_PileupOld(0),
    m_waiting("")
{
  m_messenger = new GatePileupOldMessenger(this);
}




GatePileupOld::~GatePileupOld()
{
  delete m_messenger;
}


GatePulseList* GatePileupOld::ProcessPulseList(const GatePulseList* inputPulseList)
{
  G4double minTime = inputPulseList->ComputeStartTime();
  GatePulseList* ans = new GatePulseList(GetObjectName());
  std::vector<GatePulseIterator> toDel;
  GatePulseIterator iter;
  for (iter = m_waiting.begin() ; iter != m_waiting.end() ; ++iter ){
    if ( (*iter)->GetTime()+m_PileupOld<minTime) {
    	ans->push_back( (*iter) );
	toDel.push_back(iter);
    }
  }
  for (int i= (int)toDel.size()-1;i>=0;i--){
    m_waiting.erase( toDel[i] );
  }

  GatePulseConstIterator itr;
  for (itr = inputPulseList->begin() ; itr != inputPulseList->end() ; ++itr)
      	ProcessOnePulse( *itr, m_waiting);
  return ans;
}


void GatePileupOld::ProcessOnePulse(const GatePulse* inputPulse,GatePulseList& outputPulseList)
{
  const GateOutputVolumeID& blockID  = inputPulse->GetOutputVolumeID().Top(m_depth);

  if (blockID.IsInvalid()) {
    if (nVerboseLevel>1)
      	G4cout << "[GatePileupOld::ProcessOnePulse]: out-of-block hit for \n"
	      <<  *inputPulse << Gateendl
	      << " -> pulse ignored\n\n";
    return;
  }

  GatePulseIterator iter;
  for (iter = outputPulseList.begin() ; iter != outputPulseList.end() ; ++iter )
    if ( ((*iter)->GetOutputVolumeID().Top(m_depth) == blockID )
         &&  (std::abs((*iter)->GetTime()-inputPulse->GetTime())<m_PileupOld) )
      break;

  if ( iter != outputPulseList.end() ){
     G4double energySum = (*iter)->GetEnergy() + inputPulse->GetEnergy();
     if ( inputPulse->GetEnergy() > (*iter)->GetEnergy() ){
     	G4double time = std::max( (*iter)->GetTime() ,inputPulse->GetTime());
      	**iter = *inputPulse;
	(*iter)->SetTime(time);
     }
     (*iter)->SetEnergy(energySum);
     if (nVerboseLevel>1)
      	  G4cout  << "Overwritten previous pulse for block " << blockID << " with new pulse with higer energy.\n"
      	          << "Resulting pulse is: \n"
		  << **iter << Gateendl << Gateendl ;
  } else {
    GatePulse* outputPulse = new GatePulse(*inputPulse);
    if (nVerboseLevel>1)
      	G4cout << "Created new pulse for block " << blockID << ".\n"
      	       << "Resulting pulse is: \n"
	       << *outputPulse << Gateendl << Gateendl ;
    outputPulseList.push_back(outputPulse);
  }
}





void GatePileupOld::DescribeMyself(size_t indent)
{
  G4cout << GateTools::Indent(indent) << "PileupOld at depth:      " << m_depth << Gateendl;
}

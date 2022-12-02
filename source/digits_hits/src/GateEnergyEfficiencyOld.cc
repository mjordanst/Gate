/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

//GND:ClassToRemove

#include "../include/GateEnergyEfficiencyOld.hh"

#include "GateTools.hh"
#include "GateVSystem.hh"
#include "GateVDistribution.hh"
#include "GateSystemListManager.hh"

#include "Randomize.hh"

#include "G4UnitsTable.hh"
#include <fstream>
#include "../include/GateEnergyEfficiencyOldMessenger.hh"



GateEnergyEfficiencyOld::GateEnergyEfficiencyOld(GatePulseProcessorChain* itsChain,
      	      	      	      	 const G4String& itsName)
  : GateVPulseProcessor(itsChain,itsName),
    m_efficiency(0)
{
  m_messenger = new GateEnergyEfficiencyOldMessenger(this);
}




GateEnergyEfficiencyOld::~GateEnergyEfficiencyOld()
{
  delete m_messenger;
}

void GateEnergyEfficiencyOld::ProcessOnePulse(const GatePulse* inputPulse,GatePulseList& outputPulseList)
{
   if (!m_efficiency){ // default efficiency is 1
      outputPulseList.push_back(new GatePulse(*inputPulse));
      return;
   }
   GateVSystem* system = GateSystemListManager::GetInstance()->GetSystem(0);
   if (!system){
      G4cerr<<"[GateEnergyEfficiencyOld::ProcessOnePulse] Problem : no system defined\n";
      return ;
   }
   G4double eff = m_efficiency->Value(inputPulse->GetEnergy());
//   G4cout<<inputPulse->GetEnergy()<<"   "<<eff<< Gateendl;
   if (G4UniformRand() < eff)
      outputPulseList.push_back(new GatePulse(*inputPulse));

}

void GateEnergyEfficiencyOld::DescribeMyself(size_t indent)
{
  G4cout << GateTools::Indent(indent) << "Tabular Efficiency "<< Gateendl;
}

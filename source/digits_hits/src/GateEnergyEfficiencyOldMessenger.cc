/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

//GND:ClassToRemove
#include "../include/GateEnergyEfficiencyOldMessenger.hh"

#include "../include/GateEnergyEfficiencyOld.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "GateVDistribution.hh"
#include "GateDistributionListManager.hh"

GateEnergyEfficiencyOldMessenger::GateEnergyEfficiencyOldMessenger(GateEnergyEfficiencyOld* itsPulseProcessor)
    : GatePulseProcessorMessenger(itsPulseProcessor)
{
  G4String guidance;
  G4String cmdName;

  cmdName = GetDirectoryName() + "setDistribution";
  distNameCmd = new G4UIcmdWithAString(cmdName,this);
  distNameCmd->SetGuidance("Set the efficiency distribution");

}


GateEnergyEfficiencyOldMessenger::~GateEnergyEfficiencyOldMessenger()
{
  delete distNameCmd;
}


void GateEnergyEfficiencyOldMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  GateEnergyEfficiencyOld* localEff = (GateEnergyEfficiencyOld*)GetNamedObject();
  if (!localEff) return;
  if ( command==distNameCmd ){
    GateVDistribution* distrib = (GateVDistribution*)GateDistributionListManager::GetInstance()->FindElementByBaseName(newValue);
    if (distrib) localEff->SetEfficiency(distrib);}
  else
    GatePulseProcessorMessenger::SetNewValue(command,newValue);
}

/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/
//GND:ClassToRemove

#include "GatePileupOldMessenger.hh"

#include "GatePileupOld.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

GatePileupOldMessenger::GatePileupOldMessenger(GatePileupOld* itsPileupOld)
    : GatePulseProcessorMessenger(itsPileupOld)
{
    G4String cmdName;

    cmdName = GetDirectoryName()+"setDepth";
    SetDepthCmd = new G4UIcmdWithAnInteger(cmdName,this);
    SetDepthCmd->SetGuidance("Defines the 'depth' of the PileupOld");

    cmdName = GetDirectoryName()+"setPileupOld";
    SetPileupOldCmd = new G4UIcmdWithADoubleAndUnit(cmdName,this);
    SetPileupOldCmd->SetGuidance("Defines the 'time' of the PileupOld");
    SetPileupOldCmd->SetUnitCategory("Time");

}


GatePileupOldMessenger::~GatePileupOldMessenger()
{
  delete SetDepthCmd;
  delete SetPileupOldCmd;
}

void GatePileupOldMessenger::SetNewValue(G4UIcommand* aCommand, G4String aString)
{
  if( aCommand==SetDepthCmd )
    { GetPileupOld()->SetDepth(SetDepthCmd->GetNewIntValue(aString));}
  else if (aCommand==SetPileupOldCmd )
    { GetPileupOld()->SetPileupOld(SetPileupOldCmd->GetNewDoubleValue(aString));}
  else
    GatePulseProcessorMessenger::SetNewValue(aCommand,aString);
}

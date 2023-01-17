/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/


#include "GateDeadTimeOldMessenger.hh"
#include "GateDeadTimeOld.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"

GateDeadTimeOldMessenger::GateDeadTimeOldMessenger(GateDeadTimeOld* itsDeadTimeOld)
  : GatePulseProcessorMessenger(itsDeadTimeOld)
{
  G4String guidance;
  G4String cmdName;

  cmdName = GetDirectoryName() + "setDeadTimeOld";
  DeadTimeOldCmd= new G4UIcmdWithADoubleAndUnit(cmdName,this);
  DeadTimeOldCmd->SetGuidance("Set Dead time (in ps) for pulse-discrimination");
  DeadTimeOldCmd->SetUnitCategory("Time");

  cmdName = GetDirectoryName() + "chooseDTVolume";
  newVolCmd = new G4UIcmdWithAString(cmdName,this);
  newVolCmd->SetGuidance("Choose a volume (depth) for dead time(e.g. crystal)");

  cmdName = GetDirectoryName() + "setMode";
  modeCmd = new G4UIcmdWithAString(cmdName,this);
  modeCmd->SetGuidance("set a mode for dead time");
  modeCmd->SetGuidance("paralysable nonparalysable");

  cmdName = GetDirectoryName() + "setBufferMode";
  bufferModeCmd = new G4UIcmdWithAnInteger(cmdName,this);
  bufferModeCmd->SetGuidance("set a mode for buffer management");
  bufferModeCmd->SetGuidance("0 : DT during writing, 1 : DT if writing AND buffer full");

  cmdName = GetDirectoryName() + "setBufferSize";
  bufferSizeCmd = new G4UIcmdWithADoubleAndUnit(cmdName,this);
  bufferSizeCmd->SetGuidance("set the buffer size");
  bufferSizeCmd->SetUnitCategory("Memory size");

}


GateDeadTimeOldMessenger::~GateDeadTimeOldMessenger()
{
  delete DeadTimeOldCmd;
  delete newVolCmd;
  delete modeCmd;
  delete bufferSizeCmd;
  delete bufferModeCmd;
}


void GateDeadTimeOldMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command== DeadTimeOldCmd)
    { GetDeadTimeOld()->SetDeadTimeOld(DeadTimeOldCmd->GetNewDoubleValue(newValue)); }
  else if (command==newVolCmd )
    GetDeadTimeOld()->CheckVolumeName(newValue);
  else if (command == modeCmd)
    GetDeadTimeOld()->SetDeadTimeOldMode(newValue);
  else if (command == bufferModeCmd)
    GetDeadTimeOld()->SetBufferMode(bufferModeCmd->GetNewIntValue(newValue));
  else if (command == bufferSizeCmd)
    GetDeadTimeOld()->SetBufferSize(bufferSizeCmd->GetNewDoubleValue(newValue));
  else
    GatePulseProcessorMessenger::SetNewValue(command,newValue);
}

/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

// OK GND 2022
/*This class is not used by GATE !
  The purpose of this class is to help to create new users digitizer module(DM).
  Please, check GateEnergyResolution.cc for more detals
  */

#include "GateEnergyResolutionMessenger.hh"
#include "GateEnergyResolution.hh"
#include "GateDigitizerMgr.hh"

#include "G4SystemOfUnits.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"



GateEnergyResolutionMessenger::GateEnergyResolutionMessenger (GateEnergyResolution* EnergyResolution)
:GateClockDependentMessenger(EnergyResolution),
 	 m_EnergyResolution(EnergyResolution)
{
	G4String guidance;
	G4String cmdName;

    cmdName = GetDirectoryName() + "fwhm";
    resoCmd = new G4UIcmdWithADouble(cmdName,this);
    resoCmd->SetGuidance("Set the energy resolution");


    cmdName = GetDirectoryName() + "fwhmMin";
    resoMinCmd = new G4UIcmdWithADouble(cmdName,this);
    resoMinCmd->SetGuidance("Set the minimum energy resolution");

    cmdName = GetDirectoryName() + "fwhmMax";
    resoMaxCmd = new G4UIcmdWithADouble(cmdName,this);
    resoMaxCmd->SetGuidance("Set the maximum energy resolution");

	cmdName = GetDirectoryName() + "energyOfReference";
	erefCmd = new G4UIcmdWithADoubleAndUnit(cmdName,this);
	erefCmd->SetGuidance("Set the energy of reference (in keV) for the selected resolution");
	erefCmd->SetUnitCategory("Energy");


	cmdName = GetDirectoryName() + "slope";
	slopeCmd = new G4UIcmdWithADoubleAndUnit(cmdName,this);
	slopeCmd->SetGuidance("Set the slope of the linear law (with unit) for gaussian blurring");
}


GateEnergyResolutionMessenger::~GateEnergyResolutionMessenger()
{
	delete  resoCmd;
	delete  resoMinCmd;
	delete  resoMaxCmd;
	delete  erefCmd;
	delete  slopeCmd;
}


void GateEnergyResolutionMessenger::SetNewValue(G4UIcommand * aCommand,G4String newValue)
{

	if (aCommand == resoCmd)
	  {
		m_EnergyResolution->SetResolution(resoCmd->GetNewDoubleValue(newValue));
	  }
	else if (aCommand == resoMinCmd)
	  {
		m_EnergyResolution->SetResolutionMin(resoMinCmd->GetNewDoubleValue(newValue));
	  }
	else if (aCommand == resoMaxCmd)
	  {
		m_EnergyResolution->SetResolutionMax(resoMaxCmd->GetNewDoubleValue(newValue));
	  }
	else if (aCommand == erefCmd)
	  {
		m_EnergyResolution->SetEnergyRef(erefCmd->GetNewDoubleValue(newValue));
	  }
	else if (aCommand == slopeCmd)
	  {
		m_EnergyResolution->SetSlope(slopeCmd->GetNewDoubleValue(newValue));
	  }
	else
	  {
		GateClockDependentMessenger::SetNewValue(aCommand,newValue);
	  }
}













/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

// OK GND 2022
/*This class is not used by GATE !
  The purpose of this class is to help to create new users digitizer module(DM).
  Please, check GateTimeResolution.cc for more detals
  */

#include "GateTimeResolutionMessenger.hh"
#include "GateTimeResolution.hh"
#include "GateDigitizerMng.hh"

#include "G4SystemOfUnits.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"



GateTimeResolutionMessenger::GateTimeResolutionMessenger (GateTimeResolution* TimeResolution)
:GateClockDependentMessenger(TimeResolution),
 	 m_TimeResolution(TimeResolution)
{
	G4String guidance;
	G4String cmdName;

//G4cout<<	GetDirectoryName()<<G4endl;
	cmdName = GetDirectoryName() + "fwhm";
	fwhmCmd = new G4UIcmdWithADoubleAndUnit(cmdName,this);
	fwhmCmd->SetGuidance("Set the temporal resolution with time unity (for expemple: 1 ns) for pulse-discrimination");
	fwhmCmd->SetUnitCategory("Time");

}


GateTimeResolutionMessenger::~GateTimeResolutionMessenger()
{
	  delete fwhmCmd;
}


void GateTimeResolutionMessenger::SetNewValue(G4UIcommand * aCommand,G4String newValue)
{

	 if ( aCommand==fwhmCmd )
	    {
		 m_TimeResolution->SetFWHM(fwhmCmd->GetNewDoubleValue(newValue));
	    }
	  else
		  GateClockDependentMessenger::SetNewValue(aCommand,newValue);
}














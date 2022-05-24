/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#include "GateDigitizerMessenger.hh"
#include "GateDigitizer.hh"
#include "GateAdder.hh"
//#include "GateReadout.hh"

#include "G4SystemOfUnits.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include "G4DigiManager.hh"

GateDigitizerMessenger::GateDigitizerMessenger (GateDigitizer* digitizer): m_digitizer(digitizer)
{

	//G4cout<<"GateDigitizerMessenger::constructor"<<G4endl;
	Dir = new G4UIdirectory("/gate/digitizer/Singles/");
	Dir->SetGuidance("Digitizer directory");

	G4String cmdName;

	cmdName = Dir->GetCommandPath () + "insert";
	SetModuleNameCmd = new G4UIcmdWithAString(cmdName,this);



}


GateDigitizerMessenger::~GateDigitizerMessenger()
{
	delete Dir;
	delete SetModuleNameCmd;
}


void GateDigitizerMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
	//G4cout<<"GateDigitizerMessenger::SetNewValue"<<G4endl;
	//G4VDigitizerModule* myDM=0;
	G4DigiManager * fDM = G4DigiManager::GetDMpointer();

	if( command == SetModuleNameCmd )
	    {
		if(newValue=="adder")
			{
			GateAdder * myAdder = new GateAdder( "GateAdder" );
			G4DigiManager::GetDMpointer()->AddNewModule(myAdder);
			}
		//
/*		else if (newValue=="readout")
			{
			GateReadout * myReadout = new GateReadout( "GateReadout" );
			G4DigiManager::GetDMpointer()->AddNewModule(myReadout);

			}
*/
	    }
	fDM->List();

}


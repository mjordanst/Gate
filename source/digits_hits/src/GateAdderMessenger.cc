/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

// OK GND 2022
#include "GateAdderMessenger.hh"
#include "GateAdder.hh"


#include "G4SystemOfUnits.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"



GateAdderMessenger::GateAdderMessenger (GateAdder* adder): m_Adder(adder)
{

	//G4cout<<"GateAdderMessenger::constructor"<<G4endl;
	Dir = new G4UIdirectory("/digitizer/adder/");
	Dir->SetGuidance("Digitizer directory");

	/*SetModuleNameCmd = new G4UIcmdWithAString("/digitizer/insert",this);
	SetModuleNameCmd->SetGuidance("Module to insert");
	SetModuleNameCmd->SetParameterName("choice",false);
	SetModuleNameCmd->AvailableForStates(G4State_PreInit);
	G4cout<<"GateAdderMessenger::GateAdderMessenger"<<G4endl;
	*/
	G4String cmdName;

	cmdName = Dir->GetCommandPath () + "politics";
	SetPoliticsCmd = new G4UIcmdWithAString(cmdName,this);



}


GateAdderMessenger::~GateAdderMessenger()
{
	delete Dir;
	delete SetPoliticsCmd;
}


void GateAdderMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
	G4cout<<"GateAdderMessenger::SetNewValue"<<G4endl;


	if( command == SetPoliticsCmd )
	    {
		m_Adder->SetPolitics(newValue);
	    }

}














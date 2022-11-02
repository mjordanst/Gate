/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

#include "GateDigitizerMngMessenger.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"

#include "GateCoincidenceSorter.hh"

// Constructor
GateDigitizerMngMessenger::GateDigitizerMngMessenger(GateDigitizerMng* itsDigitizerMng)
: GateClockDependentMessenger(itsDigitizerMng)
{
  //G4cout << " DEBUT Constructor GateDigitizerMngMessenger \n";

  const G4String& elementTypeName = itsDigitizerMng->GetElementTypeName();

  G4String guidance = G4String("Manages a list of ") + elementTypeName + "s.";
  GetDirectory()->SetGuidance(guidance.c_str());

  G4String cmdName;

 // G4cout<<GetDirectoryName()<<G4endl;

  cmdName = GetDirectoryName()+"name";
  guidance = "Sets the name given to the next " + elementTypeName + " to insert.";
  DefineNameCmd = new G4UIcmdWithAString(cmdName,this);
  DefineNameCmd->SetGuidance(guidance);
  DefineNameCmd->SetParameterName("Name",false);

  cmdName = GetDirectoryName()+"insert"; // /gate/digitizer/insert
  guidance = "Inserts a new " + elementTypeName + ".";
  pInsertCmd = new G4UIcmdWithAString(cmdName,this);
  pInsertCmd->SetGuidance(guidance);
  pInsertCmd->SetParameterName("choice",false);


  cmdName = GetDirectoryName()+"chooseSD";
  SetChooseSDCmd = new G4UIcmdWithAString(cmdName,this);
  SetChooseSDCmd->SetGuidance("Set the name of the input pulse channel");
  SetChooseSDCmd->SetParameterName("Name",false);


  cmdName = GetDirectoryName()+"info";
  guidance = "List the " + elementTypeName + " choices available.";
  ListChoicesCmd = new G4UIcmdWithoutParameter(cmdName,this);
  ListChoicesCmd->SetGuidance(guidance);

  cmdName = GetDirectoryName()+"list";
  guidance = "List the " + elementTypeName + "'s within '" + GetDigitizerMng()->GetObjectName() + "'";
  ListCmd = new G4UIcmdWithoutParameter(cmdName,this);
  ListCmd->SetGuidance(guidance);

  pInsertCmd->SetCandidates(DumpMap());

//  G4cout << " FIN Constructor GateDigitizerMngMessenger \n";
}



// Destructor
GateDigitizerMngMessenger::~GateDigitizerMngMessenger()
{
  delete ListCmd;
  delete ListChoicesCmd;
  delete pInsertCmd;
  delete SetChooseSDCmd;
  delete DefineNameCmd;
}



// UI command interpreter method
void GateDigitizerMngMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if( command==DefineNameCmd )
    { m_newCollectionName = newValue; }
  else if (command == SetChooseSDCmd)
        {  m_SDname=newValue; }
  else if( command==pInsertCmd )
    	{ DoInsertion(newValue); }
  else if( command==ListChoicesCmd )
    { ListChoices(); }
  else if( command==ListCmd )
    { GetDigitizerMng()->ShowSummary(); }
  else
    GateClockDependentMessenger::SetNewValue(command,newValue);
}




const G4String& GateDigitizerMngMessenger::DumpMap()
{
  static G4String theList = "SinglesDigitizer CoincidenceSorter coincidenceChain";
  return theList;
}




void GateDigitizerMngMessenger::DoInsertion(const G4String& childTypeName)
{
	//G4cout<<"GateDigitizerMngMessenger::DoInsertion "<<childTypeName<<G4endl;

	if (GetNewCollectionName().empty())
    SetNewCollectionName(childTypeName);

  AvoidNameConflicts();

  if(m_SDname.empty())
	  GateError("***ERROR*** Please, choose the sensitive detector name for which you want to insert new digitizer. "
			  "Command: /gate/digitizerMng/chooseSD"
			   "ATTENTION: this command can be called only before /insert command");

  if (childTypeName=="SinglesDigitizer") {
	  G4SDManager* SDman = G4SDManager::GetSDMpointer();
	  GateCrystalSD* SD = (GateCrystalSD*) SDman->FindSensitiveDetector(m_SDname, true);
	  GetDigitizerMng()->AddNewSinglesDigitizer( new GateDigitizer(GetDigitizerMng(),GetNewCollectionName(),SD) );

  } else if (childTypeName=="CoincidenceSorter") {
	  // One CoinSorter per System! Defined in the constructor of the system ! Only its parameters should be defiend with CS messenger
	 GetDigitizerMng()->AddNewCoincidenceSorter( new GateCoincidenceSorter(GetDigitizerMng(),GetNewCollectionName()) );
  }/* else if (childTypeName=="coincidenceChain") {
    GetDigitizerMng()->StoreNewCoincidenceProcessorChain( new GateCoincidencePulseProcessorChain(GetDigitizer(),GetNewInsertionBaseName()) );
  *///}
   else {
    G4cout << "Digitizer module type name '" << childTypeName << "' was not recognised --> insertion request must be ignored!\n";
    return;
  }

  SetNewCollectionName("");
}




//  Check whether there may be a name conflict between a new
//  attachment and an already existing one
G4bool GateDigitizerMngMessenger::CheckNameConflict(const G4String& newName)
{
  // Check whether an object with the same name already exists in the list
  return (GetDigitizerMng()->FindElement(newName) != 0 ) ;
}



/*  Check for a potential name conflict between a new attachment and an already existing one.
    If such a conflict is found, a new, conflict-free, name is generated
*/
void GateDigitizerMngMessenger::AvoidNameConflicts()
{
	//	G4cout<<" AvoidNameConflicts "<<G4endl;
  // Look for a potential name-conflict
  if (!CheckNameConflict( GetNewCollectionName() )) {
    // No name conflict, it's OK
    return;
  }


  G4int copyNumber = 2;
  char buffer[256];

  // Try with 'name2', 'name-3',... until the conflict is solved
  do {
    sprintf(buffer, "%s%i", GetNewCollectionName().c_str(), copyNumber);
    copyNumber++;
  } while (CheckNameConflict(buffer));

  G4cout << "Warning: the selected insertion name ('" << GetNewCollectionName() << "') was already in use.\n"
      	    "Name '" << buffer << "' will be used instead.\n";

  // A conflict-free name was found: store it into the insertion-name variable
  SetNewCollectionName(buffer);
}

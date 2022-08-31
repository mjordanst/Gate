
/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateVDigitizerModule
	- This class is virtual class to construct DigitizerModules from

	- Use GateDummyDigitizerModule and GateDummyDigitizerModuleMessenger class
	to create your DigitizerModule and its messenger

*/
#include "GateVDigitizerModule.hh"
#include "GateDigi.hh"

#include "GateDigitizerMng.hh"

#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"


GateVDigitizerModule::GateVDigitizerModule(G4String name, GateDigitizer *digitizer)
  :G4VDigitizerModule(name),
   GateClockDependent(name),
   m_digitizer(digitizer)//,
  // m_digitizerModuleName(name)
 {
	G4cout<<"GateVDigitizerModule::GateVDigitizerModule"<<G4endl;
  //G4String colName =  m_digitizer->m_digitizerName;
  //collectionName.push_back(colName);
  //fMessenger = new GateVDigitizerModuleMessenger(this);

}

GateVDigitizerModule::~GateVDigitizerModule()
{
 // delete fMessenger;
}



void GateVDigitizerModule::Describe(size_t indent)
{
  GateClockDependent::Describe(indent);
  G4cout << GateTools::Indent(indent) << "Attached to:        '" << m_digitizer->GetObjectName() << "'\n";
  G4cout << GateTools::Indent(indent) << "Output:             '" << GetObjectName() << "'\n";
  DescribeMyself(indent);
}

//////////////////
G4int GateVDigitizerModule::InputCollectionID()
{
	//G4cout<<"GateVDigitizerModule::InputCollectionID"<<G4endl;
	G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();

	G4String outputCollNameTMP = GetName() +"/"+(m_digitizer->m_digitizerName);

	G4int DCID = -1;

	if(DCID<0)
	{
		DCID = DigiMan->GetDigiCollectionID(outputCollNameTMP);
	}

	//check if this module is the first in this digitizer
	if ( m_digitizer->m_DMlist[0] == this)
	{
		//check if the module is called first time in a run /i.e. first after InitializationModule
		if((DCID-1)==0)
		{
		 DCID=DCID-1;
		}
		else
		{
		G4String inputCollectionName = m_digitizer->GetInputName();
		GateDigitizerMng* digitizerMng = GateDigitizerMng::GetInstance();
		GateDigitizer* inputDigitizer = digitizerMng->FindDigitizer(inputCollectionName);

		DCID=inputDigitizer->m_outputDigiCollectionID;

		}

	}
	//if not the first get the previous collection ID -> sequential processing
	else
	{
		DCID=DCID-1;
	}

	if(DCID<0)
	{
      G4Exception( "GateVDigitizerModule::InputCollectionID", "InputCollectionID", FatalException, "Something wrong with collection ID. Please, contact olga[dot]kochebina[at]cea.fr. Abort.\n");
	}


 return DCID;
}
















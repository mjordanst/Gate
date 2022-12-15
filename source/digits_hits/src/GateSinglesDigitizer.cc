/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateSinglesDigitizer
  GND (Gate New Digitizer) class
  2022 olga.kochebina@cea.fr

  The concept is slightly different for the old digitizer:
  Digitizer Modules (adder, readout, etc.) now are G4VDigitizerModule

*/

#include "GateSinglesDigitizer.hh"
#include "GateSinglesDigitizerMessenger.hh"
#include "G4UnitsTable.hh"

#include "GateDigitizerMgr.hh"
#include "G4VDigitizerModule.hh"
#include "GateTools.hh"
#include "GateHitConvertor.hh"
#include "GateSingleDigiMaker.hh"

#include "GateOutputMgr.hh"
#include "GateDigitizerInitializationModule.hh"

GateSinglesDigitizer::GateSinglesDigitizer( GateDigitizerMgr* itsDigitizerMgr,
										  const G4String& digitizerUsersName,
    			                          GateCrystalSD* SD)
  : GateModuleListManager(itsDigitizerMgr,itsDigitizerMgr->GetObjectName() + "/"+ SD->GetName() +"/SinglesDigitizer/" + digitizerUsersName ,"SinglesDigitizer"),
	m_outputName(digitizerUsersName+"_"+SD->GetName()),
    m_inputName(digitizerUsersName+"_"+SD->GetName()),
	m_recordFlag(false),
	m_SD(SD),
	m_digitizerName(digitizerUsersName)
{
	//G4cout<<"GateSinglesDigitizer::GateSinglesDigitizer "<<  itsDigitizerMgr->GetObjectName() + "/"+ SD->GetName() +"/SinglesDigitizer/" + digitizerUsersName <<G4endl;
	m_messenger = new GateSinglesDigitizerMessenger(this);

  //Prepare OutputMng for this digitizer
  	GateOutputMgr::GetInstance()->RegisterNewSingleDigiCollection(m_digitizerName+"_"+SD->GetName(),false);
  	if(!itsDigitizerMgr->m_isInitialized)
  	{

  		itsDigitizerMgr->AddNewSinglesDigitizer(this);

  	}
	//G4cout<<"end GateSinglesDigitizer::GateSinglesDigitizer "<<  itsDigitizerMgr->GetObjectName() + "/"+ SD->GetName() +"/SinglesDigitizer/" + "Singles" <<G4endl;


}




GateSinglesDigitizer::~GateSinglesDigitizer()
{
  for (auto processor = theListOfNamedObject.begin(); processor != theListOfNamedObject.end(); ++processor)
  {
    GateMessage("Core", 5, "~GateSinglesDigitizer -- delete module: " << (*processor)->GetObjectName() << Gateendl );
    delete (*processor);
  }
  delete m_messenger;
}


void GateSinglesDigitizer::AddNewModule(GateVDigitizerModule* DM)
{
	if (nVerboseLevel>1)
		G4cout << "[GateSinglesDigitizer::AddNewModule]: "<< DM->GetName() <<"\n";

	m_DMlist.push_back(DM);
	G4DigiManager::GetDMpointer()->AddNewModule(DM);

}


void GateSinglesDigitizer::DescribeMyself()
{
	G4cout<<"Digitizer Describe"<<G4endl;
	G4cout<<"Digitizer Name: "<< m_digitizerName<<G4endl;
	G4cout<<"Input Name: "<< m_inputName<<G4endl;
	G4cout<<"Output Name: "<< m_outputName<<G4endl;
	G4cout<<"Digitizer Modules: "<<G4endl;
	for (long unsigned int j = 0; j<m_DMlist.size(); j++)
			{
				G4cout<<"    " <<m_DMlist[j]->GetName()<<" "<<G4endl;
			}

}


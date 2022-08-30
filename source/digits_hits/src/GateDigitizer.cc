/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateDigitizer
  GND (Gate New Digitizer) class
  2022 olga.kochebina@cea.fr

  The concept is slightly different for the old digitizer:
  Digitizer Modules (adder, readout, etc.) now are G4VDigitizerModule

*/



#include "GateDigitizer.hh"
#include "GateDigitizerMessenger.hh"

#include "G4UnitsTable.hh"

#include "GateDigitizerMng.hh"
#include "G4VDigitizerModule.hh"
#include "GateTools.hh"
#include "GateHitConvertor.hh"
#include "GateSingleDigiMaker.hh"

#include "GateOutputMgr.hh"

GateDigitizer::GateDigitizer( GateDigitizerMng* itsDigitizerMng,
    			                          const G4String& digitizerName)
  : GateModuleListManager(itsDigitizerMng,itsDigitizerMng->GetObjectName() + "/digitizer/" + digitizerName,"pulse-processor"),
    m_collectionName(digitizerName)
	//m_digitizerName(digitizerName)//,
    //m_inputName(GateHitConvertor::GetOutputAlias())
{
	G4cout << " DEBUT Constructor GateDigitizer \n";
	m_digitizerName = m_collectionName;
	G4cout<<m_digitizerName<<G4endl;
  m_messenger = new GateDigitizerMessenger(this);

  //Prepare OutputMng for this digitizer
  	GateOutputMgr::GetInstance()->RegisterNewSingleDigiCollection(m_collectionName,true);

  	//G4cout<<"GateDigitizer::constr "<< itsDigitizerMng->m_isInitialized << " "<<m_collectionName<<G4endl;
  	//If it is not the first digitizer (i.e. the default one is "Singles") add it to DigitizerMng List
  	if(!itsDigitizerMng->m_isInitialized)
  	{
  		G4cout<<"GateDigitizer::constr "<< itsDigitizerMng->m_isInitialized << " "<<m_collectionName<<G4endl;

  		itsDigitizerMng->AddNewSinglesDigitizer(this);
  	}
}




GateDigitizer::~GateDigitizer()
{
  for (auto processor = theListOfNamedObject.begin(); processor != theListOfNamedObject.end(); ++processor)
  {
    GateMessage("Core", 5, "~GateDigitizer -- delete module: " << (*processor)->GetObjectName() << Gateendl );
    delete (*processor);
  }
  delete m_messenger;
}


void GateDigitizer::AddNewModule(G4VDigitizerModule* DM)
{
	m_DMlist.push_back(DM);

}



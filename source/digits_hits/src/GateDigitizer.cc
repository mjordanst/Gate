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
  : GateModuleListManager(itsDigitizerMng,itsDigitizerMng->GetObjectName() + "/SinglesDigitizer/" + digitizerName,"SinglesDigitizer"),
	m_outputName(digitizerName),
    m_inputName(digitizerName),
	m_digitizerName(digitizerName)
{
	m_messenger = new GateDigitizerMessenger(this);

  //Prepare OutputMng for this digitizer
  	GateOutputMgr::GetInstance()->RegisterNewSingleDigiCollection(m_digitizerName,true);

  	if(!itsDigitizerMng->m_isInitialized)
  	{
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
	if (nVerboseLevel>1)
		G4cout << "[GateSinglesDigitizer::AddNewModule]: "<< DM->GetName() <<"\n";
	m_DMlist.push_back(DM);

}


void GateDigitizer::DescribeMyself()
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


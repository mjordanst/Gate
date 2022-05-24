/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateDigitizer
*/



#include "GateDigitizer.hh"
//#include "GateDigi.hh"
#include "GateDigitizerMessenger.hh"

#include "GateHit.hh"
#include "GateOutputMgr.hh"


#include "G4SystemOfUnits.hh"
#include "G4DigiManager.hh"

#include "GateDigitizerInitializationModule.hh"
#include "GateAdder.hh"
//#include "GateReadout.hh"

GateDigitizer* GateDigitizer::theDigitizer=0;

//-----------------------------------------------------------------
GateDigitizer* GateDigitizer::GetInstance()
{
  if (!theDigitizer)
    theDigitizer = new GateDigitizer;
  return theDigitizer;
}


GateDigitizer::GateDigitizer()
{
	//G4cout<<"GateDigitizer:: constructor"<<G4endl;

	//create a messenger for this class
	fMessenger = new GateDigitizerMessenger(this);



}


GateDigitizer::~GateDigitizer()
{
 delete fMessenger;
}


void GateDigitizer::Initialize()
{

	G4cout<<"GateDigitizer::Initialize"<<G4endl;


	GateDigitizerInitializationModule * myDM = new GateDigitizerInitializationModule( "GateDigitizerInitializationModule" );
	G4DigiManager::GetDMpointer()->AddNewModule(myDM);

	//m_collectionName="Singles";

	//moved from GateSingleDigiMaker and GatePulseProcessorChain constructors
	GateOutputMgr::GetInstance()->RegisterNewSingleDigiCollection("Singles",true);


}


void GateDigitizer::RunDigitizer()
{


	G4cout<<"GateDigitizer::RunDigitizer"<<G4endl;

	G4DigiManager * fDM = G4DigiManager::GetDMpointer();

	for (G4int i=0; i<(fDM->GetModuleCapacity());i++)
	{
		fDM->Digitize(fDM->GetDCtable()->GetDMname(i));
	}



}











/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#include "GateSingleDigiMaker.hh"

#include "G4DigiManager.hh"

#include "GateSingleDigi.hh"
#include "GateTools.hh"
#include "GateDigitizerOld.hh"
#include "GateOutputMgr.hh"

// Constructor
GateSingleDigiMaker::GateSingleDigiMaker( GateDigitizerOld* itsDigitizer,
      	      	         	          const G4String& itsInputName,
					  G4bool itsOutputFlag)
  :GateVDigiMakerModule(itsDigitizer,itsInputName)
{
	G4cout<<"GateSingleDigiMaker constr"<<Gateendl;
  G4cout << " in GateSingleDigiMaker call RegisterNewSingleDigiCollection"  << Gateendl;
  G4cout<< 	itsInputName<<" "<< GetCollectionName() <<Gateendl;
  GateOutputMgr::GetInstance()->RegisterNewSingleDigiCollection( GetCollectionName(),itsOutputFlag );
}



// Destructor
GateSingleDigiMaker::~GateSingleDigiMaker()
{
}




// Convert a pulse list into a single Digi collection
void GateSingleDigiMaker::Digitize()
{
	G4cout<<"GateSingleDigiMaker::Digitize()"<<G4endl;
  if (nVerboseLevel>1)
    G4cout  << "[GateSingleDigiMaker::Digitize]: retrieving pulse-list '" << m_inputName << "'\n";

  GatePulseList* pulseList = GateDigitizerOld::GetInstance()->FindPulseList(m_inputName);

  if (!pulseList) {
    if (nVerboseLevel>1)
      G4cout  << "[GateSingleDigiMaker::Digitize]: pulse list null --> no digits created\n";
    return;
  }

  if (pulseList->empty()) {
    if (nVerboseLevel>1)
      G4cout  << "[GateSingleDigiMaker::Digitize]: pulse list empty --> no digits created\n";
    return;
  }

  // Get number of pulses from hit processing
  size_t n_pulses = pulseList->size();
  size_t i;

  // Create the digi collection
  GateSingleDigiCollection* singleDigiCollection = new GateSingleDigiCollection(m_digitizer->GetObjectName(),m_collectionName);

  G4cout<<"GateSingleDigiMaker::Digitize "<<m_digitizer->GetObjectName()<<" "<< m_collectionName<<Gateendl;


  // Transform each pulse into a single digi
  for (i=0;i<n_pulses;i++) {
	GateSingleDigi* Digi = new GateSingleDigi( (*pulseList)[i] );
	singleDigiCollection->insert(Digi);
      }

  if (nVerboseLevel>0) {
      	G4cout  << "[GateSingleDigiMaker::ConvertSinglePulseList]: "
	      	<< "created " << singleDigiCollection->entries() << " single digits:\n";
      	for (i=0; i<(size_t)(singleDigiCollection->entries()); i++)
	  (*singleDigiCollection)[i]->Print();
	G4cout << Gateendl;
  }

  // Store the digits into the digit collection of this event
  m_digitizer->StoreDigiCollection(singleDigiCollection);
}

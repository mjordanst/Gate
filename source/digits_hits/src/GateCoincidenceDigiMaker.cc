/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/
//GND:ClassToRemove

#include "GateCoincidenceDigiMaker.hh"

#include "G4DigiManager.hh"

#include "GateCoincidenceDigiOld.hh"
#include "GateDigitizerOld.hh"
#include "GateTools.hh"
#include "GateDigitizerOld.hh"
#include "GateOutputMgr.hh"

// Constructor
GateCoincidenceDigiMaker::GateCoincidenceDigiMaker( GateDigitizerOld* itsDigitizer,
      	      	         	        	    const G4String& itsInputName,
						    G4bool itsOutputFlag)
  :GateVDigiMakerModule(itsDigitizer,itsInputName)
{
	G4cout<<"GateCoincidenceDigiMaker constr"<<G4endl;
  GateOutputMgr::GetInstance()->RegisterNewCoincidenceDigiCollection( GetCollectionName(),itsOutputFlag );
}



// Destructor
GateCoincidenceDigiMaker::~GateCoincidenceDigiMaker()
{
}




// Convert a pulse list into a Coincidence Digi collection
void GateCoincidenceDigiMaker::Digitize()
{
  std::vector<GateCoincidencePulse*> coincidencePulse = GateDigitizerOld::GetInstance()->FindCoincidencePulse(m_inputName);
  if (coincidencePulse.empty()) {
    if (nVerboseLevel)
      G4cout  << "[GateCoincidenceDigiMaker::Digitize]: coincidence pulse null --> no digi created\n";
    return;
  }
  // Create the digi collection
  GateCoincidenceDigiOldCollection* CoincidenceDigiOldCollection = new GateCoincidenceDigiOldCollection(m_digitizer->GetObjectName(),m_collectionName);

  // Create and store the digi
  for (std::vector<GateCoincidencePulse*>::const_iterator it = coincidencePulse.begin();it != coincidencePulse.end() ; ++it){
      if ((*it)->size()>2){
      	if (nVerboseLevel)
      	    G4cout  << "[GateCoincidenceDigiMaker::Digitize]: ignoring multiple coincidence --> no digits created\n";
      } else {
      	GateCoincidenceDigiOld* Digi = new GateCoincidenceDigiOld( **it);
      	CoincidenceDigiOldCollection->insert(Digi);
      }
  }

  if (nVerboseLevel>0) {
      	  G4cout  << "[GateCoincidenceDigiMaker::Digitize]:  created 1 coincidence digi in this event:" <<	Gateendl;
	  (*CoincidenceDigiOldCollection)[0]->Print();
	  G4cout << Gateendl;
  }


  // Store the digits into the digit collection of this event
  m_digitizer->StoreDigiCollection(CoincidenceDigiOldCollection);
}

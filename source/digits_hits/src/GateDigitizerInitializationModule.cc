/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateDigitizerInitializationModule
  This class is a specific digitizer class that are called before running all users
  digitizers and digitizer modules.
  It creates Digi from Hits of this event and filles/copies all attributes for this Digi
*/


#include "GateDigitizerInitializationModule.hh"
#include "GateDigi.hh"
#include "GateCrystalSD.hh"

#include "GateHit.hh"

#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"


GateDigitizerInitializationModule::GateDigitizerInitializationModule(G4String name)
  :G4VDigitizerModule(name)
{
	G4cout<<" GateDigitizerInitializationModule constr "<<G4endl;
	//G4String insertionBaseName=GatePreDigitizer::GetInstance()->GetNewInsertionBaseName();

	//The name is Singles is hardcoded in this class, as it is just a transformation from Hits -> Digi and HitsColleciton to DigiColleciton.
	//This class is called only ones in the beginning of the simulation.
	//The output of this class is used by other DigiModules to create different DigiCollections
	G4String colName = "SinglesInit"; //
	collectionName.push_back(colName);
}


GateDigitizerInitializationModule::~GateDigitizerInitializationModule()
{
}


void GateDigitizerInitializationModule::Digitize()
{

	G4cout<<"DigitizerInitialization::Digitize()"<<G4endl;
	//G4String insertionBaseName=GatePreDigitizer::GetInstance()->GetNewInsertionBaseName();
	OutputDigiCollection = new GateDigiCollection ("GateDigitizerInitializationModule","SinglesInit"); // to create the Digi Collection


	G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
	static G4int HCID=-1;

	  if (HCID==-1)
	  	  HCID = DigiMan->GetHitsCollectionID(GateCrystalSD::GetCrystalCollectionName());

	 // G4cout<<HCID<<G4endl;
	GateHitsCollection* THC = (GateHitsCollection*) (DigiMan->GetHitsCollection(HCID));


	if (THC)
    {
      G4int n_hit = THC->entries();
      //G4cout<<"n_hit = "<<n_hit<<G4endl;
	// G4cout<<"THC "  << THC->GetSDname ()<<" " <<  THC-> GetName ()<<" "<<  THC->entries() <<G4endl;
	 //G4int j=0;
      //G4cout<< (*THC)[j]->GetEdep()  <<G4endl;
	 for (G4int i=0;i<n_hit;i++)
	{
    	 if((*THC)[i]->GetEdep() !=0 )
    	  {
    		//    		 G4cout<< (*THC)[i]->GetEdep()  <<G4endl;
    		  GateDigi* Digi = new GateDigi();
    		  Digi->SetRunID( (*THC)[i]->GetRunID() );
    		  Digi->SetEventID( (*THC)[i]->GetEventID() );
    		  Digi->SetTrackID( (*THC)[i]->GetTrackID() );
    		  Digi->SetSourceID( (*THC)[i]->GetSourceID() );
    		  Digi->SetSourcePosition( (*THC)[i]->GetSourcePosition() );
    		  Digi->SetTime( (*THC)[i]->GetTime() );
    		  Digi->SetEnergy( (*THC)[i]->GetEdep() );
    		  Digi->SetMaxEnergy( (*THC)[i]->GetEdep() );
    		  Digi->SetLocalPos( (*THC)[i]->GetLocalPos() );
    		  Digi->SetGlobalPos( (*THC)[i]->GetGlobalPos() );
    		  Digi->SetPDGEncoding( (*THC)[i]->GetPDGEncoding() );
    		  Digi->SetOutputVolumeID( (*THC)[i]->GetOutputVolumeID() );
    		  Digi->SetNPhantomCompton( (*THC)[i]->GetNPhantomCompton() );
    		  Digi->SetNCrystalCompton( (*THC)[i]->GetNCrystalCompton() );
    		  Digi->SetNPhantomRayleigh( (*THC)[i]->GetNPhantomRayleigh() );
    		  Digi->SetNCrystalRayleigh( (*THC)[i]->GetNCrystalRayleigh() );
    		  Digi->SetComptonVolumeName( (*THC)[i]->GetComptonVolumeName() );
    		  Digi->SetRayleighVolumeName( (*THC)[i]->GetRayleighVolumeName() );
    		  Digi->SetVolumeID( (*THC)[i]->GetVolumeID() );
    		  Digi->SetScannerPos( (*THC)[i]->GetScannerPos() );
    		  Digi->SetScannerRotAngle( (*THC)[i]->GetScannerRotAngle() );
    		  #ifdef GATE_USE_OPTICAL
    		    Digi->SetOptical( (*THC)[i]->GetPDGEncoding() == 0 );
    		  #endif
    		  Digi->SetNSeptal( (*THC)[i]->GetNSeptal() );  // HDS : septal penetration

    		  // AE : Added for IdealComptonPhot adder which take into account several Comptons in the same volume
    		  Digi->SetPostStepProcess((*THC)[i]->GetPostStepProcess());
    		  Digi->SetEnergyIniTrack((*THC)[i]->GetEnergyIniTrack());
    		  Digi->SetEnergyFin((*THC)[i]->GetEnergyFin());
    		  Digi->SetProcessCreator((*THC)[i]->GetProcess());
    		  Digi->SetTrackID((*THC)[i]->GetTrackID());
    		  Digi->SetParentID((*THC)[i]->GetParentID());
    		  Digi->SetSourceEnergy((*THC)[i]->GetSourceEnergy());
    		  Digi->SetSourcePDG((*THC)[i]->GetSourcePDG());
    		  Digi->SetNCrystalConv( (*THC)[i]->GetNCrystalConv() );

    		  //-------------------------------------------------

    		    if ((*THC)[i]->GetComptonVolumeName().empty()) {
    		      Digi->SetComptonVolumeName( "NULL" );
    		      Digi->SetSourceID( -1 );
    		    }

    		    if ((*THC)[i]->GetRayleighVolumeName().empty()) {
    		      Digi->SetRayleighVolumeName( "NULL" );
    		      Digi->SetSourceID( -1 );
    		    }

    		/* //  if (nVerboseLevel>1)
    		        	G4cout << "[GateDigitizerInitializationModule::Digitize]: \n"
    		  	       << "\tprocessed " << *(*THC)[i] << Gateendl
    		  	       << "\tcreated new Digi:\n"
    		  	       << *Digi << Gateendl;
*/
    		  OutputDigiCollection->insert(Digi);

    	  }



		}
   }
	//G4cout<<"n digi = "<<	OutputDigiCollection->GetSize () <<G4endl;
  StoreDigiCollection(OutputDigiCollection);
  G4cout<<"outputDigiColleciton = "<<	OutputDigiCollection->GetName () <<G4endl;

}










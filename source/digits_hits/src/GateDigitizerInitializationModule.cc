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


GateDigitizerInitializationModule::GateDigitizerInitializationModule(GateDigitizer *digitizer)
  :G4VDigitizerModule("GateDigitizerInitializationModule"),
   m_digitizer(digitizer)
{
	//G4cout<<" GateDigitizerInitializationModule constr "<<G4endl;
	//G4String insertionBaseName=GatePreDigitizer::GetInstance()->GetNewInsertionBaseName();

	//The name is Singles is hardcoded in this class, as it is just a transformation from Hits -> Digi and HitsColleciton to DigiColleciton.
	//This class is called only ones in the beginning of the simulation.
	//The output of this class is used by other DigiModules to create different DigiCollections
	G4String colName = digitizer->GetOutputName();//+ m_SD->GetName(); //
	collectionName.push_back(colName);
}


GateDigitizerInitializationModule::~GateDigitizerInitializationModule()
{
}


void GateDigitizerInitializationModule::Digitize()
{

	//G4cout<<"DigitizerInitialization::Digitize()" << m_digitizer->GetOutputName() <<G4endl;
	OutputDigiCollection = new GateDigiCollection ("GateDigitizerInitializationModule",  m_digitizer->GetOutputName() ); // to create the Digi Collection

	G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
	G4String HCname=m_digitizer->m_SD->GetName()+"Collection" ;


	static G4int HCID=-1;
	if(HCID<0)
	{
		HCID= DigiMan->GetHitsCollectionID(HCname);
	}
	GateHitsCollection* inHC = (GateHitsCollection*) (DigiMan->GetHitsCollection(HCID));// DigiMan->GetHitsCollectionID(HCname)));


	if (inHC)
    {
      G4int n_hit = inHC->entries();
      //G4cout<<"n_hit = "<<n_hit<<G4endl;
	// G4cout<<"inHC "  << inHC->GetSDname ()<<" " <<  inHC-> GetName ()<<" "<<  inHC->entries() <<G4endl;
	 //G4int j=0;
      //G4cout<< (*inHC)[j]->GetEdep()  <<G4endl;
	 for (G4int i=0;i<n_hit;i++)
	{
    	 if((*inHC)[i]->GetEdep() !=0 )
    	  {
    		//    		 G4cout<< (*inHC)[i]->GetEdep()  <<G4endl;
    		  GateDigi* Digi = new GateDigi();
    		  Digi->SetRunID( (*inHC)[i]->GetRunID() );
    		  Digi->SetEventID( (*inHC)[i]->GetEventID() );
    		  Digi->SetTrackID( (*inHC)[i]->GetTrackID() );
    		  Digi->SetSourceID( (*inHC)[i]->GetSourceID() );
    		  Digi->SetSourcePosition( (*inHC)[i]->GetSourcePosition() );
    		  Digi->SetTime( (*inHC)[i]->GetTime() );
    		  Digi->SetEnergy( (*inHC)[i]->GetEdep() );
    		  Digi->SetMaxEnergy( (*inHC)[i]->GetEdep() );
    		  Digi->SetLocalPos( (*inHC)[i]->GetLocalPos() );
    		  Digi->SetGlobalPos( (*inHC)[i]->GetGlobalPos() );
    		  Digi->SetPDGEncoding( (*inHC)[i]->GetPDGEncoding() );
    		  Digi->SetOutputVolumeID( (*inHC)[i]->GetOutputVolumeID() );
    		  Digi->SetNPhantomCompton( (*inHC)[i]->GetNPhantomCompton() );
    		  Digi->SetNCrystalCompton( (*inHC)[i]->GetNCrystalCompton() );
    		  Digi->SetNPhantomRayleigh( (*inHC)[i]->GetNPhantomRayleigh() );
    		  Digi->SetNCrystalRayleigh( (*inHC)[i]->GetNCrystalRayleigh() );
    		  Digi->SetComptonVolumeName( (*inHC)[i]->GetComptonVolumeName() );
    		  Digi->SetRayleighVolumeName( (*inHC)[i]->GetRayleighVolumeName() );
    		  Digi->SetVolumeID( (*inHC)[i]->GetVolumeID() );
    		  Digi->SetScannerPos( (*inHC)[i]->GetScannerPos() );
    		  Digi->SetScannerRotAngle( (*inHC)[i]->GetScannerRotAngle() );
    		  #ifdef GATE_USE_OPTICAL
    		    Digi->SetOptical( (*inHC)[i]->GetPDGEncoding() == 0 );
    		  #endif
    		  Digi->SetNSeptal( (*inHC)[i]->GetNSeptal() );  // HDS : septal penetration

    		  // AE : Added for IdealComptonPhot adder which take into account several Comptons in the same volume
    		  Digi->SetPostStepProcess((*inHC)[i]->GetPostStepProcess());
    		  Digi->SetEnergyIniTrack((*inHC)[i]->GetEnergyIniTrack());
    		  Digi->SetEnergyFin((*inHC)[i]->GetEnergyFin());
    		  Digi->SetProcessCreator((*inHC)[i]->GetProcess());
    		  Digi->SetTrackID((*inHC)[i]->GetTrackID());
    		  Digi->SetParentID((*inHC)[i]->GetParentID());
    		  Digi->SetSourceEnergy((*inHC)[i]->GetSourceEnergy());
    		  Digi->SetSourcePDG((*inHC)[i]->GetSourcePDG());
    		  Digi->SetNCrystalConv( (*inHC)[i]->GetNCrystalConv() );

    		  //-------------------------------------------------

    		    if ((*inHC)[i]->GetComptonVolumeName().empty()) {
    		      Digi->SetComptonVolumeName( "NULL" );
    		      Digi->SetSourceID( -1 );
    		    }

    		    if ((*inHC)[i]->GetRayleighVolumeName().empty()) {
    		      Digi->SetRayleighVolumeName( "NULL" );
    		      Digi->SetSourceID( -1 );
    		    }

    		/* //  if (nVerboseLevel>1)
    		        	G4cout << "[GateDigitizerInitializationModule::Digitize]: \n"
    		  	       << "\tprocessed " << *(*inHC)[i] << Gateendl
    		  	       << "\tcreated new Digi:\n"
    		  	       << *Digi << Gateendl;
*/
    		  OutputDigiCollection->insert(Digi);

    	  }



		}
   }
	//G4cout<<"n digi = "<<	OutputDigiCollection->GetSize () <<G4endl;
  StoreDigiCollection(OutputDigiCollection);
 // G4cout<<"outputDigiColleciton = "<<	OutputDigiCollection->GetName () <<G4endl;

}










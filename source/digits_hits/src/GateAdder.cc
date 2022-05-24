
/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateAdder
*/
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"


#include "GateAdder.hh"
#include "GateAdderMessenger.hh"
#include "GateDigi.hh"




GateAdder::GateAdder(G4String name)
  :G4VDigitizerModule(name)
{


  G4String colName = "Singles";
  collectionName.push_back(colName);

  fMessenger = new GateAdderMessenger(this);

}


GateAdder::~GateAdder()
{
  delete fMessenger;
}


void GateAdder::Digitize()
{

	G4cout<<"Adder::Digitize() "<< m_politics <<G4endl;
  
	DigitsCollection = new GateDigiCollection("GateAdder","Singles"); // to create the Digi Collection

  G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();

  //G4float Energy;
  //G4double min_time;

  G4int DCID;

  DCID = DigiMan->GetDigiCollectionID("GateAdder/Singles");
  GateDigiCollection* IDC = 0;
  IDC = (GateDigiCollection*) (DigiMan->GetDigiCollection(DCID-1)); //get previous collection for sequential digitizer

  m_outputDigi = new GateDigi();
  GateDigi* inputDigi = new GateDigi();

  if (IDC)
     {
	  G4int n_hit = IDC->entries();
	  //G4cout<<"n hits "<< n_hit<<G4endl;
	  //Energy=0;
	  //min_time = DBL_MAX;
	  //std::vector<GateVolumeID&> v_uniqueblockID;

	  for (G4int i=0;i<n_hit;i++)
	  {
		  inputDigi=(*IDC)[i];
		  G4cout<<"input "<<i<<" "<<inputDigi->GetVolumeID()<<" "<< inputDigi->GetEnergy()<< " "<< inputDigi->GetEventID()<<G4endl;


		  //if(std::find(v_uniqueblockID.begin(),  v_uniqueblockID.end(), inputDigi->GetVolumeID()) == v_uniqueblockID.end())
		//	  v_uniqueblockID.push_back(inputDigi->GetVolumeID());




		  if (i==0)
			  m_outputDigi->SetVolumeID(inputDigi->GetVolumeID());

		  if(m_outputDigi->GetVolumeID() == inputDigi->GetVolumeID() )
		  {
			  MergePositionEnergyWin(inputDigi);
			  G4cout<<"output"<<G4endl;
			  G4cout<<"volume "<< m_outputDigi->GetVolumeID()<<G4endl;
			  G4cout<<"energy "<< m_outputDigi->GetEnergy()<<G4endl;

			  DigitsCollection->insert(m_outputDigi);
		  }
		 /* else
		  {
			  m_outputDigi->SetVolumeID(inputDigi->GetVolumeID());
			  m_outputDigi = new GateDigi();
		  }
		   */

			  /*if (inputDigi->Time()<minTime)
				  minTime=inputDigi->Time();
			  Energy += inputDigi->GetEnergy();

			  //TODO adder
			  //G4cout<<"input "<< inputDigi->GetVolumeID()<<G4endl;
			  //if(inputDigi->GetVolumeID() == )


			  m_outputDigi->SetVolumeID(inputDigi->GetVolumeID());
			  G4cout<<"output "<< m_outputDigi->GetVolumeID()<<G4endl;

			  Energy += inputDigi->GetEnergy();
			  m_outputDigi->SetEnergy(Energy);

			/*  if (v_currentTime[j]<minTime[k])
			  {
			      minTime[k]=v_currentTime[j];
			  }

		  }
		  else
		  {
			  m_outputDigi->SetVolumeID(inputDigi->GetVolumeID());

		  }
*/
		  }
	//  m_outputDigi->SetEnergy(Energy);


     }

  
  StoreDigiCollection(DigitsCollection);

  G4cout<<"******Adder***** "<<DigitsCollection->GetSize ()<<Gateendl;
  G4cout<<DigitsCollection->GetName ()<<Gateendl;

}

void GateAdder::MergePositionEnergyWin(GateDigi *right)
{



	 m_outputDigi->SetRunID( right->GetRunID() );
			  m_outputDigi->SetEventID( right->GetEventID() );
			  m_outputDigi->SetSourceID( right->GetSourceID() );
			  m_outputDigi->SetSourcePosition( right->GetSourcePosition() );
			  //m_outputDigi->SetTime( right->GetTime() );
			  //m_outputDigi->SetEnergy( right->GetEdep() );
			  //m_outputDigi->SetMaxEnergy( right->GetEdep() );
			 //m_outputDigi->SetLocalPos( right->GetLocalPos() );
			  //m_outputDigi->SetGlobalPos( right->GetGlobalPos() );
			  m_outputDigi->SetPDGEncoding( right->GetPDGEncoding() );
			  m_outputDigi->SetOutputVolumeID( right->GetOutputVolumeID() );
			  m_outputDigi->SetNPhantomCompton( right->GetNPhantomCompton() );
			  m_outputDigi->SetNCrystalCompton( right->GetNCrystalCompton() );
			  m_outputDigi->SetNPhantomRayleigh( right->GetNPhantomRayleigh() );
			  m_outputDigi->SetNCrystalRayleigh( right->GetNCrystalRayleigh() );
			  m_outputDigi->SetComptonVolumeName( right->GetComptonVolumeName() );
			  m_outputDigi->SetRayleighVolumeName( right->GetRayleighVolumeName() );
			  m_outputDigi->SetVolumeID( right->GetVolumeID() );
			  m_outputDigi->SetScannerPos( right->GetScannerPos() );
			  m_outputDigi->SetScannerRotAngle( right->GetScannerRotAngle() );
			  #ifdef GATE_USE_OPTICAL
			   	   m_outputDigi->SetOptical( right->GetPDGEncoding() == 0 );
			  #endif
			  m_outputDigi->SetNSeptal( right->GetNSeptal() );  // HDS : septal penetration


			  m_outputDigi->SetSourceEnergy(right->GetSourceEnergy());
			  m_outputDigi->SetSourcePDG(right->GetSourcePDG());
			  m_outputDigi->SetNCrystalConv( right->GetNCrystalConv() );

			  //-------------------------------------------------

			  if (right->GetComptonVolumeName().empty()) {
				  m_outputDigi->SetComptonVolumeName( "NULL" );
				  m_outputDigi->SetSourceID( -1 );
			  }

			  if (right->GetRayleighVolumeName().empty()) {
				  m_outputDigi->SetRayleighVolumeName( "NULL" );
				  m_outputDigi->SetSourceID( -1 );
			  }

    // AE : Added in a real pulse no sense
    m_outputDigi->m_Postprocess="NULL";         // PostStep process
    m_outputDigi->m_energyIniTrack=0;         // Initial energy of the track
    m_outputDigi->m_energyFin=0;         // final energy of the particle
    m_outputDigi->m_processCreator="NULL";
    m_outputDigi->m_trackID=0;
    //-----------------

    // time: store the minimum time
    m_outputDigi->m_time = std::min ( m_outputDigi->m_time , right->m_time ) ;
    if (m_outputDigi->m_sourceEnergy != right->m_sourceEnergy) m_outputDigi->m_sourceEnergy=-1;
    if (m_outputDigi->m_sourcePDG != right->m_sourcePDG) m_outputDigi->m_sourcePDG=0;
    if ( right->m_nCrystalConv > m_outputDigi->m_nCrystalConv ){
    	m_outputDigi->m_nCrystalConv 	= right->m_nCrystalConv;
    }
    if ( right->m_nCrystalCompton > m_outputDigi->m_nCrystalCompton ){
    	m_outputDigi->m_nCrystalCompton 	= right->m_nCrystalCompton;
    }
    if ( right->m_nCrystalRayleigh > m_outputDigi->m_nCrystalRayleigh ){
    	m_outputDigi->m_nCrystalRayleigh 	= right->m_nCrystalRayleigh;
    }



    if( right->m_energy>m_outputDigi->m_max_energy){
    	m_outputDigi->m_max_energy=right->m_energy;
        // Local and global positions: store the controids
    	m_outputDigi->m_localPos  =   right->m_localPos;
    	m_outputDigi->m_globalPos =   right->m_globalPos;

    }

    m_outputDigi->m_energy = m_outputDigi->m_energy + right->m_energy;


    // # of compton process: store the max nb
    if ( right->m_nPhantomCompton > m_outputDigi->m_nPhantomCompton )
    {
    	m_outputDigi->m_nPhantomCompton 	= right->m_nPhantomCompton;
    	m_outputDigi->m_comptonVolumeName = right->m_comptonVolumeName;
    }

    // # of Rayleigh process: store the max nb
    if ( right->m_nPhantomRayleigh > m_outputDigi->m_nPhantomRayleigh )
    {
    	m_outputDigi->m_nPhantomRayleigh 	= right->m_nPhantomRayleigh;
    	m_outputDigi->m_RayleighVolumeName = right->m_RayleighVolumeName;
    }

    // HDS : # of septal hits: store the max nb
    if ( right->m_nSeptal > m_outputDigi->m_nSeptal )
    {
    	m_outputDigi->m_nSeptal 	= right->m_nSeptal;
    }

    // VolumeID: should be identical for both pulses, we do nothing
    // m_scannerPos: identical for both pulses, nothing to do
    // m_scannerRotAngle: identical for both pulses, nothing to do
    // m_outputVolumeID: should be identical for both pulses, we do nothing

    //return *this;

}
/*
void GateAdder::CentroidMerge(GateHit *aDigi)
{

}
*/



















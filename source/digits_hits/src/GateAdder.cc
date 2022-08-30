
/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/


#include "GateAdder.hh"
#include "GateAdderMessenger.hh"
#include "GateDigi.hh"

#include "GateDigitizerMng.hh"

#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"



GateAdder::GateAdder(G4String name, GateDigitizer *digitizer)
  :GateVDigitizerModule(name,digitizer),
   m_positionPolicy(kEnergyCentroid)
 {
	G4String colName = digitizer->m_digitizerName;
	collectionName.push_back(colName);
	fMessenger = new GateAdderMessenger(this);
	m_digitizer=digitizer;
}


GateAdder::~GateAdder()
{
  delete fMessenger;
}


void GateAdder::Digitize()
{
	//G4cout<<"Adder::Digitize() "<< m_positionPolicy <<G4endl;

	G4String digitizerName = m_digitizer->m_digitizerName;
	G4String inputCollName = m_digitizer->GetInputName();
	G4String outputCollName = digitizerName;

	OutputDigiCollection = new GateDigiCollection("GateAdder",outputCollName); // to create the Digi Collection

	G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();

	G4String outputCollNameTMP="GateAdder/"+outputCollName;


	GateDigiCollection* IDC = 0;
	IDC = (GateDigiCollection*) (DigiMan->GetDigiCollection( InputCollectionID() ));

	GateDigi* inputDigi = new GateDigi();


	std::vector< GateDigi* >* v_OutputDigiCollection = OutputDigiCollection->GetVector ();
	std::vector<GateDigi*>::iterator iter;


  if (IDC)
     {
	  G4int n_digi = IDC->entries();

	  //loop over input digits
	  for (G4int i=0;i<n_digi;i++)
	  {
		  inputDigi=(*IDC)[i];
		  //This part is from ProcessOnePulse
		     for (iter=v_OutputDigiCollection->begin(); iter!= v_OutputDigiCollection->end() ; ++iter)
		     {
		    	 if ( (*iter)->GetVolumeID()   == inputDigi->GetVolumeID() )
		    	 {
		    		 if(m_positionPolicy==kEnergyWinner){
		                 MergePositionEnergyWin(inputDigi);
		    		 }
		    		 else{
		    			 CentroidMerge( inputDigi );
		    		 }


		      if (nVerboseLevel>1)
		      {
		    	 G4cout << "Merged previous pulse for volume " << inputDigi->GetVolumeID()
		 		 << " with new pulse of energy " << G4BestUnit(inputDigi->GetEnergy(),"Energy") <<".\n"
		 		 << "Resulting pulse is: \n"
		 		 << **iter << Gateendl << Gateendl ;
		      }
		 	  break;
		       }
		     }
		     if ( iter == v_OutputDigiCollection->end() )
		     {
		       m_outputDigi = new GateDigi(*inputDigi);
		       m_outputDigi->SetEnergyIniTrack(-1);
		       m_outputDigi->SetEnergyFin(-1);
		       if (nVerboseLevel>1)
		 	  G4cout << "Created new pulse for volume " << inputDigi->GetVolumeID() << ".\n"
		 		 << "Resulting pulse is: \n"
		 		 << *m_outputDigi << Gateendl << Gateendl ;
		       OutputDigiCollection->insert(m_outputDigi);

		     }

   //This part is from ProcessPulseList
   if (nVerboseLevel==1) {
	 G4cout << "[GateAdder::ProcessPulseList]: returning output pulse-list with " << v_OutputDigiCollection->size() << " entries\n";
	  for (iter=v_OutputDigiCollection->begin(); iter!= v_OutputDigiCollection->end() ; ++iter)
	 G4cout << **iter << Gateendl;
	  G4cout << Gateendl;
	}

   }
  }
  
  StoreDigiCollection(OutputDigiCollection);

}


void GateAdder::SetPositionPolicy(const G4String &policy)
{
	G4cout<<"GateAdder::SetPositionPolicy "<< policy <<G4endl;
	G4cout<<m_positionPolicy<<G4endl;
	if (policy=="takeEnergyWinner")
    {
		m_positionPolicy=kEnergyWinner;
    }
    else {
        if (policy!="energyWeightedCentroid")
            G4cout<<"WARNING : policy not recognized, using default :energyWeightedCentroid\n";
       m_positionPolicy=kEnergyCentroid;
    }


}


///////////////////////////////////////////
////////////// Methods of DM //////////////
///////////////////////////////////////////

void GateAdder::MergePositionEnergyWin(GateDigi *right)
{
	//to copy all variables that are not changed
	m_outputDigi=right;

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

}

void GateAdder::CentroidMerge(GateDigi* right)
{
	m_outputDigi=right;

    // AE : Added in a real pulse no sense
    m_outputDigi->m_Postprocess="NULL";         // PostStep process
    m_outputDigi->m_energyIniTrack=-1;         // Initial energy of the track
    m_outputDigi->m_energyFin=-1;         // final energy of the particle
    m_outputDigi->m_processCreator="NULL";
    m_outputDigi->m_trackID=0;
    //-----------------

    // time: store the minimum time
    m_outputDigi->m_time = std::min ( m_outputDigi->m_time , right->m_time ) ;

    // energy: we compute the sum, but do not store it yet
    // (storing it now would mess up the centroid computations)
    G4double totalEnergy = m_outputDigi->m_energy + right->m_energy;

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

    // Local and global positions: store the controids
    if(totalEnergy>0){
        m_outputDigi->m_localPos  =  ( m_outputDigi->m_localPos  * m_outputDigi->m_energy  + right->m_localPos  * right->m_energy ) / totalEnergy ;
        m_outputDigi->m_globalPos =  ( m_outputDigi->m_globalPos * m_outputDigi->m_energy  + right->m_globalPos * right->m_energy ) / totalEnergy ;
    }
    else{
        m_outputDigi->m_localPos  =  ( m_outputDigi->m_localPos  + right->m_localPos)/2;
        m_outputDigi->m_globalPos =  ( m_outputDigi->m_globalPos + right->m_globalPos)/2 ;
    }

    // Now that the centroids are stored, we can store the energy
    m_outputDigi->m_energy   = totalEnergy;


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

}

void GateAdder::DescribeMyself(size_t )
{
  ;
}


/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateDummyDigitizerModule

  This class is not used by GATE !
  The purpose of this class is to help to create new users digitizer module(DM).

   - Create your DM by coping this class and GateDummyDigitizerMessenger class for your DM messenger
   - Places to change are marked with //****** comment and called with "dummy" names
   - Include your module to GateDigitizerMessenger in the method DoInsertion(..)

	If you adapting some already exiting class from Old Gate Digitizer here is some of the tips
	- Digitize () is a fusion of GateVPulseProcessor::ProcessPulseList and GateXXX::ProcessOnePulse
	- pulse --> Digi
	- outputPulseList --> v_OutputDigiCollection
	- inputPulse-->inputDigi
	- outputPulse --> m_outputDigi


  !!!! DO NOT FORGET TO WRITE A SHORT EXPLANATION ON WHAT DOES YOUR DM !!!!
	The example is also given in .hh
*/

#include "GateDummyDigitizerModule.hh"
#include "GateDummyDigitizerModuleMessenger.hh"
#include "GateDigi.hh"

#include "GateDigitizerMng.hh"

#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"



GateDummyDigitizerModule::GateDummyDigitizerModule(G4String name, GateDigitizer *digitizer)
  :GateVDigitizerModule(name,digitizer),
   m_parameter("dummy")
 {
	G4String colName = digitizer->m_digitizerName;
	collectionName.push_back(colName);
	fMessenger = new GateDummyDigitizerModuleMessenger(this);
	m_digitizer=digitizer;
}


GateDummyDigitizerModule::~GateDummyDigitizerModule()
{
  delete fMessenger;
}


void GateDummyDigitizerModule::Digitize()
{

	G4String digitizerName = m_digitizer->m_digitizerName;
	G4String inputCollName = m_digitizer->GetInputName();
	G4String outputCollName = digitizerName;

	OutputDigiCollection = new GateDigiCollection("GateDummyDigitizerModule",outputCollName); // to create the Digi Collection

	G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();

	G4String outputCollNameTMP="GateDummyDigitizerModule/"+outputCollName;


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
		  //****** the following part of the code to adapt
		  ///*** This part is from ProcessPulseList

		  //////** This part is from ProcessOnePulse
		     for (iter=v_OutputDigiCollection->begin(); iter!= v_OutputDigiCollection->end() ; ++iter)
		     {
		    	 if ( (*iter)->GetVolumeID()   == inputDigi->GetVolumeID() )
		    	 {
		    		 if(m_parameter=="dummy"){
		                 DummyMethod1(inputDigi);
		    		 }
		    		 else{
		    			 DummyMethod2( inputDigi );
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
		 //////** End of the part from ProcessOnePulse


		if (nVerboseLevel==1) {
			G4cout << "[GateDummyDigitizerModule::ProcessPulseList]: returning output pulse-list with " << v_OutputDigiCollection->size() << " entries\n";
			for (iter=v_OutputDigiCollection->begin(); iter!= v_OutputDigiCollection->end() ; ++iter)
				G4cout << **iter << Gateendl;
			G4cout << Gateendl;
		}
	///*** End of the part from ProcessPulseList
	  }
    }
  StoreDigiCollection(OutputDigiCollection);

}


void GateDummyDigitizerModule::SetDummyParameter(const G4String &param)
{
	m_parameter=param;
}


///////////////////////////////////////////
////////////// Methods of DM //////////////
///////////////////////////////////////////

void GateDummyDigitizerModule::DummyMethod1(GateDigi *right)
{
	//to copy all variables that are not changed
	m_outputDigi=right;

	// do your changes in output digi in the way shown below
   /* // AE : Added in a real pulse no sense
    m_outputDigi->m_Postprocess="NULL";         // PostStep process
    m_outputDigi->m_energyIniTrack=0;         // Initial energy of the track
    m_outputDigi->m_energyFin=0;         // final energy of the particle
    m_outputDigi->m_processCreator="NULL";
    m_outputDigi->m_trackID=0;
    //-----------------
    */

}

void GateDummyDigitizerModule::DummyMethod2(GateDigi *right)
{
	//to copy all variables that are not changed
	m_outputDigi=right;

	// do your changes in output digi in the way shown below
   /* // AE : Added in a real pulse no sense
    m_outputDigi->m_Postprocess="NULL";         // PostStep process
    m_outputDigi->m_energyIniTrack=0;         // Initial energy of the track
    m_outputDigi->m_energyFin=0;         // final energy of the particle
    m_outputDigi->m_processCreator="NULL";
    m_outputDigi->m_trackID=0;
    //-----------------
    */

}


void GateDummyDigitizerModule::DescribeMyself(size_t )
{
  ;
}

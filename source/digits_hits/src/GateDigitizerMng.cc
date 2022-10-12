/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateDigitizerMng
  GND (Gate New Digitizer) class
  2022 olga.kochebina@cea.fr

  The concept is slightly different for the old digitizer:
  Digitizer Modules (adder, readout, etc.) now are G4VDigitizerModule

*/

#include "GateDigitizerMng.hh"
#include "GateDigitizerMngMessenger.hh"
#include "GateDigitizerInitializationModule.hh"
#include "GateHit.hh"


#include "G4SystemOfUnits.hh"
#include "G4DigiManager.hh"
#include "G4RunManager.hh"



GateDigitizerMng* GateDigitizerMng::theDigitizerMng=0;

//-----------------------------------------------------------------
GateDigitizerMng* GateDigitizerMng::GetInstance()
{
  if (!theDigitizerMng)
    theDigitizerMng = new GateDigitizerMng;
  return theDigitizerMng;
}


GateDigitizerMng::GateDigitizerMng()
	: GateClockDependent("digitizerMng"),
	  m_elementTypeName("DigitizerMng module"),
	  m_systemList(0),
	  m_collectionID(0),
	  m_isInitialized(1)
{
	G4cout<<"GateDigitizerMng:: constructor "<<  nVerboseLevel<<G4endl;
	fMessenger = new GateDigitizerMngMessenger(this);
	G4cout<<"GateDigitizerMng:: constructor2 "<<  nVerboseLevel<<G4endl;
	//m_isInitialized=1;
	AddNewSinglesDigitizer( new GateDigitizer(this,"Singles"));

	//Prepare InitialisationModule to Hits->Digi, HitsCollection->DigiCollection
	//Digitize() to be run at the end of each event and before the main digitizers
	GateDigitizerInitializationModule * myDM = new GateDigitizerInitializationModule( "GateDigitizerInitializationModule" );
	G4DigiManager::GetDMpointer()->AddNewModule(myDM);

}


GateDigitizerMng::~GateDigitizerMng()
{
 delete fMessenger;
}



//-----------------------------------------------------------------
// The next three methods were added for the multi-system approach
void GateDigitizerMng::AddSystem(GateVSystem* aSystem)
{
  if(!m_systemList)
    m_systemList = new GateSystemList;

  m_systemList->push_back(aSystem);

  // mhadi_Note: We have here only one digitizer, this is the default digitizer created at the detector construction stage and
  //             which has the "Singles" outputName. So this loop here is to set a system to this digitizer.
  size_t i;
  for (i=0; i<m_SingleDigitizersList.size() ; ++i)
    {
      if(!(m_SingleDigitizersList[i]->GetSystem()))
    	  m_SingleDigitizersList[i]->SetSystem((*m_systemList)[0]);
    }

  for (i=0; i<m_CoincidenceSortersList.size() ; ++i)
    {
      if(!((m_CoincidenceSortersList[i])->GetSystem()))
        m_CoincidenceSortersList[i]->SetSystem((*m_systemList)[0]);
    }

}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
GateVSystem* GateDigitizerMng::FindSystem(GateDigitizer* digitizer)
{
  GateVSystem* system = 0;
  if(digitizer->size() != 0)
    {
      G4String sysName = digitizer->GetDigitizerModule(0)->GetObjectName();
      system = FindSystem(sysName);
    }
  return system;
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
GateVSystem* GateDigitizerMng::FindSystem(G4String& systemName)
{
  G4int index = -1;
  for(size_t i=0; i<m_systemList->size(); i++)
    {
      if(systemName.compare(m_systemList->at(i)->GetOwnName()) == 0)
        index = i;
    }

  if(index != -1)
    return m_systemList->at(index);
  else return 0;

}
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Integrates a new pulse-processor chain
void GateDigitizerMng::AddNewSinglesDigitizer(GateDigitizer* digitizer)
{
  G4String outputName = digitizer->m_digitizerName ;
  if (nVerboseLevel>1)
    G4cout << "[GateDigitizerMng::AddNewSinglesDigitizer]: Storing new digitizer '" << digitizer->GetObjectName() << "'"
           << " with output pulse-list name '" << outputName << "'\n";

  //Add digitizer to the list
  m_SingleDigitizersList.push_back(digitizer);

  //! Next lines are for the multi-system approach
  if(m_systemList && m_systemList->size() == 1)
	  digitizer->SetSystem((*m_systemList)[0]);
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Integrates a new pulse-processor chain
void GateDigitizerMng::AddNewCoincidenceSorter(GateCoincidenceSorter* coincidenceSorter)
{
	G4String outputName = coincidenceSorter->GetOutputName() ;
	  if (nVerboseLevel>1)
	    G4cout << "[GateDigitizerMng::AddNewCoincidenceSorter]: Storing new coincidence sorter '" << coincidenceSorter->GetObjectName() << "'"
	           << " with output coincidence-pulse name '" << outputName << "'\n";

	 m_CoincidenceSortersList.push_back ( coincidenceSorter );

	  //mhadi_add[
	  //! Next lines are for the multi-system approach
	  for (size_t i=0; i<m_SingleDigitizersList.size() ; ++i)
	    {
	      G4String pPCOutputName = m_SingleDigitizersList[i]->GetOutputName();

	      if(pPCOutputName.compare("Singles") == 0)
	        {
	          coincidenceSorter->SetSystem(m_SingleDigitizersList[i]->GetSystem());
	          break;
	        }
	    }
	  //mhadi_add]


}
//-----------------------------------------------------------------



GateClockDependent* GateDigitizerMng::FindElement(G4String mName)
{

	GateClockDependent* element;
	element = (GateClockDependent*)FindDigitizer(mName);
	if (!element) element = (GateClockDependent*)FindCoincidenceSorter(mName);

	return element;
}


GateDigitizer* GateDigitizerMng::FindDigitizer(G4String mName)
{

	//G4cout<<"GateDigitizerMng::FindDigitizer"<<G4endl;

	for(G4int i=0;i<int(m_SingleDigitizersList.size());i++)
		{
		//G4cout<<m_SingleDigitizersList[i]->m_digitizerName<<" "<<(m_SingleDigitizersList[i]->GetSystem())<<G4endl;
		if(m_SingleDigitizersList[i]->m_digitizerName== mName)
			return m_SingleDigitizersList [i];
		}
	return NULL;
}

GateCoincidenceSorter* GateDigitizerMng::FindCoincidenceSorter(G4String mName)
{
	for(G4int i=0;i<int(m_CoincidenceSortersList.size());i++)
	{
		if(m_CoincidenceSortersList[i]->GetOutputName() == mName)
			return m_CoincidenceSortersList[i];
	}
return NULL;
}






/////////////////
void GateDigitizerMng::RunDigitizers()
{
	if ( !IsEnabled() )
		return;

	if (nVerboseLevel>1)
	    G4cout << "[GateDigitizerMng::RunDigitizers]: starting\n";

	G4DigiManager *fDM = G4DigiManager::GetDMpointer();

	//List();

	//Run Initialization Module to convert Hits to Digis
	if (nVerboseLevel>1)
			    G4cout << "[GateDigitizerMng::RunDigitizers]: launching GateDigitizerInitializationModule\n";

	fDM->Digitize("GateDigitizerInitializationModule");

	//loop over all digitizers/collections
	//collID is the same as for G4DigiManager
	//start from on in order to have the same ordering as in G4DigiManager
	//G4int collID;
	 //define the first collection ID if there are Coincidecnes in the system or not
	if(fDM->GetDigiCollectionID("Coincidences")==1)
		m_collectionID=1;
	else
		m_collectionID=0;


	if (nVerboseLevel>1)
		    G4cout << "[GateDigitizerMng::RunDigitizers]: launching SingleDigitizers. N = " << m_SingleDigitizersList.size() << "\n";

	for (long unsigned int i = 0; i<m_SingleDigitizersList.size(); i++)
	{
		if (nVerboseLevel>1)
			G4cout << "[GateDigitizerMng::RunDigitizers]: Running SingleDigitizer " << m_SingleDigitizersList[i]->m_digitizerName <<" with "<< m_SingleDigitizersList[i]->m_DMlist.size() << " Digitizer Modules\n";
		//loop over all DMs of the current digitizer
		for (long unsigned int j = 0; j<m_SingleDigitizersList[i]->m_DMlist.size(); j++)
		{
			if (nVerboseLevel>2)
				G4cout << "[GateDigitizerMng::RunDigitizers]: Running DigitizerModule " << m_SingleDigitizersList[i]->m_DMlist[j]->GetName()<<" "<<	m_SingleDigitizersList[i]->m_DMlist[j]->GetNumberOfCollections ()<<" "<<m_SingleDigitizersList[i]->m_DMlist[j]->GetCollectionName (0)<< "\n";

			m_SingleDigitizersList[i]->m_DMlist[j]->Digitize();
			m_collectionID++;
		}
		//Save the name of the last digitizer module for current digitizer
		m_SingleDigitizersList[i]->m_outputDigiCollectionID=m_collectionID;

	}

}

void GateDigitizerMng::RunCoincidenceSorters()
{
	if ( !IsEnabled() )
		return;

	if (nVerboseLevel>1)
	    G4cout << "[GateDigitizerMng::RunCoincidenceSorters]: starting\n";


	if (nVerboseLevel>1)
		G4cout << "[GateDigitizerMng::RunCoincidenceSorters]: launching CoincidenceSorters. N = " << m_CoincidenceSortersList.size() << "\n";


	for (long unsigned int i = 0; i<m_CoincidenceSortersList.size(); i++) //DigitizerList
		{
			if (nVerboseLevel>1)
				G4cout << "[GateDigitizerMng::RunCoincidenceSorters]: Running CoincidenceSorter "<< m_CoincidenceSortersList[i]->m_coincidenceSorterName << "\n";

			m_CoincidenceSortersList[i]->Digitize();

			m_collectionID++;
			m_CoincidenceSortersList[i]->m_outputDigiCollectionID=m_collectionID;
		}
			//Save the name of the last digitizer module for current digitizer

			// G4cout<<"coll ID"<< m_collectionID<<G4endl;
			//m_SingleDigitizersList[i]->SetLastDMname();
}


void GateDigitizerMng::RunCoincidenceDigitizers()
{


	//m_coincidenceSorter->ProcessSingles(); //Digitizer() ??


		//RunCoinDigitizers
}

void GateDigitizerMng::ShowSummary()
{
	G4cout<<"-----------------------"<<G4endl;
	G4cout<<"DigitizerMng summary"<<G4endl;
	G4DigiManager *fDM = G4DigiManager::GetDMpointer();
	G4DCtable* DCTable=fDM->GetDCtable ();

	G4cout<<"Table size " <<DCTable->entries ()<<G4endl;
	G4cout<< std::left << std::setw(7)<<"collID" <<"| "<< std::left << std::setw(35) <<"DigitizerModule"<<"| "<< std::left << std::setw(20) <<"DigiCollection"<< "| "<< "size "<<G4endl;
	G4cout<<"---------------------------------------------------------------------------------"<<G4endl;
	for (int i=0; i<DCTable->entries ();i++)
	{
		G4String name=DCTable->GetDMname(i)+"/"+DCTable->GetDCname(i);

		if(fDM->GetDigiCollection(DCTable->GetCollectionID(name))==0)
		{
		G4cout<<std::left << std::setw(7) <<DCTable->GetCollectionID(name) <<"| "<< std::left << std::setw(35)<< DCTable->GetDMname(i) <<"| "<< std::left << std::setw(20) <<DCTable->GetDCname(i)<< "| "<< 0 <<G4endl;//" "<<GetDigiCollection(i)->GetName() <<G4endl;
		}
		else
		{
			G4cout<<std::left << std::setw(7) <<DCTable->GetCollectionID(name) <<"| "<< std::left << std::setw(35)<< DCTable->GetDMname(i) <<"| "<< std::left << std::setw(20) <<DCTable->GetDCname(i)<< "| "<< fDM->GetDigiCollection(DCTable->GetCollectionID(name))->GetSize () <<G4endl;//
		}
	}




}





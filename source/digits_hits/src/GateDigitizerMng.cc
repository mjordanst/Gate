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
	  m_isInitialized(0)
{
	G4cout<<"GateDigitizerMng:: constructor"<<G4endl;
	fMessenger = new GateDigitizerMngMessenger(this);

	m_isInitialized=1;
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

 /* TODO
  * // mhadi_Note: We have here only one pulse processor chain, this is the default chain created at the detector construction stage and
  //             which has the "Singles" outputName. So this loop here is to set a system to this chain.
  size_t i;
  for (i=0; i<GetChainNumber() ; ++i)
    {
      if(!(GetChain(i)->GetSystem()))
        GetChain(i)->SetSystem((*m_systemList)[0]);
    }

  for (i=0; i<m_coincidenceSorterList.size() ; ++i)
    {
      if(!((m_coincidenceSorterList[i])->GetSystem()))
        m_coincidenceSorterList[i]->SetSystem((*m_systemList)[0]);
    }
*/
}
//------------------------------------------------------------------------------

/*
//------------------------------------------------------------------------------
GateVSystem* GateDigitizerMng::FindSystem(GatePulsedigitizer* digitizer)
{
  GateVSystem* system = 0;
  if(digitizer->size() != 0)
    {
      G4String sysName = digitizer->GetProcessor(0)->GetObjectName();
      system = FindSystem(sysName);
    }
  return system;
}
//------------------------------------------------------------------------------
*/

//------------------------------------------------------------------------------
GateVSystem* GateDigitizerMng::FindSystem(G4String& systemName)
{
  /*TODO
   * G4int index = -1;
  for(size_t i=0; i<m_systemList->size(); i++)
    {
      if(systemName.compare(m_systemList->at(i)->GetOwnName()) == 0)
        index = i;
    }

  if(index != -1)
    return m_systemList->at(index);
  else return 0;
  */
}
//-----------------------------------------------------------------

void GateDigitizerMng::ListElements(size_t indent)
{
	//TODO implement describers
  //DescribeChains(indent); --> DescribeCollections
  //DescribeSorters(indent); --> DescribeDMs
}


//-----------------------------------------------------------------
// Integrates a new pulse-processor chain
void GateDigitizerMng::AddNewSinglesDigitizer(GateDigitizer* digitizer)
{
  G4String outputName = digitizer->GetOutputName() ;
  //if (nVerboseLevel)
    G4cout << "[GateDigitizerMng::AddNewSinglesDigitizer]: Storing new digitizer '" << digitizer->GetObjectName() << "'"
           << " with output pulse-list name '" << outputName << "'\n";

  //Add digitizer to the list
  m_SingleDigitizersList.push_back(digitizer);

  //TODO: adapt multi system
  //! Next lines are for the multi-system approach
 // if(m_systemList && m_systemList->size() == 1)
 //   digitizer->SetSystem((*m_systemList)[0]);
}
//-----------------------------------------------------------------

GateDigitizer* GateDigitizerMng::FindDigitizer(G4String mName)
{
for(G4int i=0;i<int(m_SingleDigitizersList.size());i++)
	{
	//TODO possible bug here in getting digitizer Name
	if(m_SingleDigitizersList[i]->m_digitizerName == mName) return m_SingleDigitizersList [i];
	}
return NULL;
}


/////////////////
void GateDigitizerMng::RunDigitizers()
{
	G4cout<<"GateDigitizerMng::RunDigitizers"<<G4endl;
	G4DigiManager *fDM = G4DigiManager::GetDMpointer();

	//G4cout<<"DCtable entries " <<fDM->GetDCtable ()->entries()<<G4endl;
	//fDM->List();
	fDM->Digitize("GateDigitizerInitializationModule");

	//loop over all digitizers/collections
	//collection ID is the same as for G4DigiManager
	G4int collID=0; //start from on in order to have the same ordering as in G4DigiManager
	G4cout<<"m_SingleDigitizersList size " <<m_SingleDigitizersList.size()<<G4endl;
	for (long unsigned int i = 0; i<m_SingleDigitizersList.size(); i++) //DigitizerList
	{
		//G4cout<<"Digitizer: "<<m_SingleDigitizersList[i]->m_digitizerName <<" "<< m_SingleDigitizersList[i]->m_DMlist.size() <<G4endl;

		//loop over all DMs of the current digitizer
		for (long unsigned int j = 0; j<m_SingleDigitizersList[i]->m_DMlist.size(); j++)
		{
			//    G4cout<<"DM " <<m_SingleDigitizersList[i]->m_DMlist[j]->GetName()<<" "<<	m_SingleDigitizersList[i]->m_DMlist[j]->GetNumberOfCollections ()<<" "<<m_SingleDigitizersList[i]->m_DMlist[j]->GetCollectionName (0)<<G4endl;
			m_SingleDigitizersList[i]->m_DMlist[j]->Digitize();
			collID++;
		}
		//Save the name of the last digitizer module for current digitizer
		m_SingleDigitizersList[i]->m_outputDigiCollectionID=collID;
		// G4cout<<"coll ID"<< collID<<G4endl;
		//m_SingleDigitizersList[i]->SetLastDMname();

	}

}


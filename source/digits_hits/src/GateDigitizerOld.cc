/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
//GND:ClassToRemove

/*!
  \class  GateDigitizerOld
*/

#include "GateDigitizerOld.hh"
#include "GateTools.hh"
#include "GateDigitizerOldMessenger.hh"
#include "GateSingleDigiMaker.hh"
#include "GateHitConvertor.hh"
#include "GateOutputMgr.hh"
#include "GateVPulseProcessor.hh"
#include "GateVSystem.hh"

typedef std::pair<G4String,GatePulseList*> 	GatePulseListAlias;

GateDigitizerOld* GateDigitizerOld::theDigitizerOld=0;

//-----------------------------------------------------------------
GateDigitizerOld* GateDigitizerOld::GetInstance()
{

	G4cout<<"GateDigitizerOld GetInstance"<<G4endl;
  if (!theDigitizerOld)
    theDigitizerOld = new GateDigitizerOld;
  return theDigitizerOld;
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
GateDigitizerOld::GateDigitizerOld()
  : GateClockDependent("digitizerOld"),
    G4VDigitizerModule("digitizerOld"),
    m_elementTypeName("digitizerOld module"),
    m_system(0),
    m_systemList(0)
{
	G4cout<<"GateDigitizerOld constr"<<G4endl;

  m_messenger = new GateDigitizerOldMessenger(this);

  m_hitConvertor = GateHitConvertor::GetInstance();
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
GateDigitizerOld::~GateDigitizerOld()
{
  if(m_systemList) delete m_systemList;
  delete m_hitConvertor;
  while (m_singleChainList.size())
    {
      delete m_singleChainList.back();
      m_singleChainList.erase(m_singleChainList.end()-1);
    }
  while ( m_coincidenceSorterList.size() ) {
    delete m_coincidenceSorterList.back();
    m_coincidenceSorterList.erase(m_coincidenceSorterList.end()-1);
  }
  while ( m_digiMakerList.size() ) {
    delete m_digiMakerList.back();
    m_digiMakerList.erase(m_digiMakerList.end()-1);
  }
  delete m_messenger;
  theDigitizerOld = 0;
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
GateNamedObject* GateDigitizerOld::FindElement(const G4String& name)
{
  size_t i;
  for (i=0; i<m_singleChainList.size() ; i++)
    if (m_singleChainList[i]->GetObjectName() == name)
      return m_singleChainList[i];
  for (i=0; i<m_coincidenceSorterList.size() ; i++)
    if (m_coincidenceSorterList[i]->GetObjectName() == name)
      return m_coincidenceSorterList[i];
  return 0;
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
void GateDigitizerOld::ListElements(size_t indent)
{
  DescribeChains(indent);
  DescribeSorters(indent);
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
void GateDigitizerOld::InsertChain(GatePulseProcessorChain* newChain)
{
	G4cout<<"GateDigitizerOld::InsertChain"<<G4endl;
  m_singleChainList.push_back(newChain);
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
void GateDigitizerOld::InsertCoincidenceChain(GateCoincidencePulseProcessorChain* newChain)
{
  m_coincidenceChainList.push_back(newChain);
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
void GateDigitizerOld::DescribeChains(size_t indent)
{
  G4cout << GateTools::Indent(indent) << "Nb of chains:       " << m_singleChainList.size() << "\n";
  for (size_t i=0; i<m_singleChainList.size(); i++)
    G4cout << GateTools::Indent(indent+1) << GetChain(i)->GetObjectName() << Gateendl;
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
void GateDigitizerOld::DescribeSorters(size_t indent)
{
  G4cout << GateTools::Indent(indent) << "Nb of coinc. units: " << m_coincidenceSorterList.size() << "\n";
  for (std::vector<GateCoincidenceSorterOld*>::iterator itr=m_coincidenceSorterList.begin(); itr!=m_coincidenceSorterList.end(); itr++)
    G4cout << GateTools::Indent(indent+1) << (*itr)->GetObjectName() << Gateendl;
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Clear the array of pulse-lists
void GateDigitizerOld::ErasePulseListVector()
{
  while (m_pulseListVector.size()) {
    if (nVerboseLevel>1)
      G4cout << "[GateDigitizerOld::ErasePulseListVector]: Erasing pulse-list '" << m_pulseListVector.back()->GetListName() << "'\n";
    delete m_pulseListVector.back();
    m_pulseListVector.erase(m_pulseListVector.end()-1);
  }
  while (m_coincidencePulseVector.size()) {
    if (nVerboseLevel>1)
      G4cout << "[GateDigitizerOld::ErasePulseListVector]: Erasing coincidence pulse\n";
    delete m_coincidencePulseVector.back();
    m_coincidencePulseVector.erase(m_coincidencePulseVector.end()-1);
  }
  while (m_pulseListAliasVector.size()) {
    if (nVerboseLevel>1)
      G4cout << "[GateDigitizerOld::ErasePulseListVector]: Erasing alias '" << m_pulseListAliasVector.back().first << "'\n";
    m_pulseListAliasVector.erase(m_pulseListAliasVector.end()-1);
  }
  while (m_coincidencePulseListAliasVector.size()) {
    if (nVerboseLevel>1)
      G4cout << "[GateDigitizerOld::ErasePulseListVector]: Erasing alias '" << m_coincidencePulseListAliasVector.back().first << "'\n";
    m_coincidencePulseListAliasVector.erase(m_coincidencePulseListAliasVector.end()-1);
  }
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Store a new pulse-list into the array of pulse-list
void GateDigitizerOld::StorePulseList(GatePulseList* newPulseList)
{
  if (newPulseList) {
    if (nVerboseLevel>1)
      G4cout << "[GateDigitizerOld::StorePulseList]: Storing new pulse-list '" << newPulseList->GetListName() << "'\n";
    m_pulseListVector.push_back(newPulseList);
  }
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Store a new coincidence pulse into the array of coincidence pulses
void GateDigitizerOld::StoreCoincidencePulse(GateCoincidencePulse* newCoincidencePulse)
{
  if (newCoincidencePulse) {
    if (nVerboseLevel>1)
      G4cout << "[GateDigitizerOld::StoreCoincidencePulse]: Storing new coincidence pulse\n";
       // G4cout<<"first pulse evtID"<<newCoincidencePulse->at(0)->GetEventID()<<"first pulse time+"<<newCoincidencePulse->at(0)->GetTime()<<G4endl;
    m_coincidencePulseVector.push_back(newCoincidencePulse);
  }
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Store a new alias for a pulse-list
void GateDigitizerOld::StorePulseListAlias(const G4String& aliasName,GatePulseList* aPulseList)
{
  if (aPulseList) {
    if (nVerboseLevel>1)
      G4cout << "[GateDigitizerOld::StorePulseListAlias]: Storing new alias '" << aliasName
             << "' for list '" << aPulseList->GetListName() << "'"<< Gateendl;
    m_pulseListAliasVector.push_back(GatePulseListAlias(aliasName,aPulseList));
  }
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Store a new alias for a coincidence pulse
void GateDigitizerOld::StoreCoincidencePulseAlias(const G4String& aliasName,GateCoincidencePulse* aPulse)
{
  if (aPulse) {
    if (nVerboseLevel>1)
      G4cout << "[GateDigitizerOld::StoreCoincidencePulseListAlias]: Storing new alias '" << aliasName
             << "' for coincidence '" << aPulse->GetListName() << "'"<< Gateendl;
    m_coincidencePulseListAliasVector.push_back(GateCoincidencePulseListAlias(aliasName,aPulse));
  }
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Find a pulse-list from the array of pulse-list
GatePulseList* GateDigitizerOld::FindPulseList(const G4String& pulseListName)
{
  if (nVerboseLevel>1)
    G4cout << "[GateDigitizerOld::FindPulseList]: Looking for pulse-list '" << pulseListName << "'"<< Gateendl;

  size_t i;
  for (i=0; i<m_pulseListAliasVector.size(); ++i)
    if ( m_pulseListAliasVector[i].first == pulseListName) {
      if (nVerboseLevel>1)
        G4cout << "[GateDigitizerOld::FindPulseList]: Found pulse-list '" << pulseListName << "'"<< Gateendl;
      return m_pulseListAliasVector[i].second;
    }
  for (i=0; i<m_pulseListVector.size(); ++i)
    if ( m_pulseListVector[i]->GetListName() == pulseListName) {
      if (nVerboseLevel>1)
        G4cout << "[GateDigitizerOld::FindPulseList]: Found pulse-list alias '" << pulseListName << "'"<< Gateendl;
      return m_pulseListVector[i];
    }
  if (nVerboseLevel>1)
    G4cout << "[GateDigitizerOld::FindPulseList]: Could not find pulse-list '" << pulseListName << "'"<< Gateendl;
  return 0;
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Find a pulse-list from the array of pulse-list
std::vector<GateCoincidencePulse*> GateDigitizerOld::FindCoincidencePulse(const G4String& pulseName)
{


  std::vector<GateCoincidencePulse*> ans;
  if (nVerboseLevel>1)
    G4cout << "[GateDigitizerOld::FindCoincidencePulse]: Looking for coincidence pulse '" << pulseName << "'"<< Gateendl;

  size_t i;
  for (i=0; i<m_coincidencePulseListAliasVector.size(); ++i)
    if ( m_coincidencePulseListAliasVector[i].first == pulseName) {
      if (nVerboseLevel>1)
        G4cout << "[GateDigitizerOld::FindCoincidencePulse]: Found pulse-list '" << pulseName << "'"<< Gateendl;
      ans.push_back(m_coincidencePulseListAliasVector[i].second);
    }
  for (i=0; i<m_coincidencePulseVector.size(); ++i){
    if ( m_coincidencePulseVector[i]->GetListName() == pulseName) {
      if (nVerboseLevel>1)
        G4cout << "[GateDigitizerOld::FindCoincidencePulse]: Found coincidence pulse '" << pulseName << "'"<< Gateendl;
      ans.push_back(m_coincidencePulseVector[i]);
    }
  }
  if (nVerboseLevel>1)
    G4cout << "[GateDigitizerOld::FindCoincidencePulse]: Cound not find coincidence pulse '" << pulseName << "'"<< Gateendl;

  return ans;
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Integrates a new pulse-processor chain
void GateDigitizerOld::StoreNewPulseProcessorChain(GatePulseProcessorChain* processorChain)
{
  G4String outputName = processorChain->GetOutputName() ;
  //if (nVerboseLevel)
    G4cout << "[GateDigitizerOld::StoreNewPulseProcessorChain]: Storing new processor chain '" << processorChain->GetObjectName() << "'"
           << " with output pulse-list name '" << outputName << "'\n";

  InsertChain ( processorChain );

  //! Next lines are for the multi-system approach
  if(m_systemList && m_systemList->size() == 1)
    processorChain->SetSystem((*m_systemList)[0]);
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Integrates a new coincidence-processor chain
void GateDigitizerOld::StoreNewCoincidenceProcessorChain(GateCoincidencePulseProcessorChain* processorChain)
{
  G4String outputName = processorChain->GetOutputName() ;
 // if (nVerboseLevel)
    G4cout << "[GateDigitizerOld::StoreNewPulseProcessorChain]: Storing new processor chain '" << processorChain->GetObjectName() << "'"
           << " with output pulse-list name '" << outputName << "'\n";

  InsertCoincidenceChain ( processorChain );

  //! Next lines are for the multi-system approach
  if(processorChain->GetInputNames().size() == 0)
    {
      G4int index = -1;
      for(size_t i=0; i<GetCoinSorterList().size(); i++)
        {
          G4String coincSorterChainName = GetCoinSorterList()[i]->GetOutputName();
          if(coincSorterChainName.compare("Coincidences") == 0)
            {
              index = i;
              break;
            }
        }
      processorChain->SetSystem(m_coincidenceSorterList[index]->GetSystem());
    }
}
//-----------------------------------------------------------------

//unsigned int GateDigitizerOld::GetPulseSingleListVectorSize(){
//    std::vector<G4String> aliasVector;

//    for(int i=0;i<m_pulseListAliasVector.size(); i++){
//        aliasVector.push_back(m_pulseListAliasVector.at(i).first);
//    }



//    unsigned int numSingles = std::count (aliasVector.begin(), aliasVector.end(), "Singles");
//     std::cout << "Singles  num= " << numSingles  << " times.\n";
//return numSingles;
//}



//std::vector<GatePulseListAlias> GateDigitizerOld::searchSingles(){

//    std::vector<GatePulseListAlias> singlesPulse;

//    std::copy_if(begin(m_pulseListAliasVector), end(m_pulseListAliasVector),
//        std::inserter(singlesPulse, end(singlesPulse)),
//        [&](GatePulseListAlias const &s) { return s.first == "Singles"; });
//    return singlesPulse;

//}

//-----------------------------------------------------------------
// Integrates a new coincidence sorter
void GateDigitizerOld::StoreNewCoincidenceSorter(GateCoincidenceSorterOld* coincidenceSorter)
{
  G4String outputName = coincidenceSorter->GetOutputName() ;
  //if (nVerboseLevel>1)
    G4cout << "[GateDigitizerOld::StoreNewCoincidenceSorter]: Storing new coincidence sorter '" << coincidenceSorter->GetObjectName() << "'"
           << " with output coincidence-pulse name '" << outputName << "'\n";

  //mhadi_add[
  //! Next lines are for the multi-system approach
  for (size_t i=0; i<GetChainNumber() ; ++i)
    {
      G4String pPCOutputName = GetChain(i)->GetOutputName();

      if(pPCOutputName.compare("Singles") == 0)
        {
          coincidenceSorter->SetSystem(GetChain(i)->GetSystem());
          break;
        }
    }
  //mhadi_add]

  m_coincidenceSorterList.push_back ( coincidenceSorter );
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Print-out a description of the object
void GateDigitizerOld::Describe(size_t indent)
{
  GateClockDependent::Describe(indent);
  ListElements(indent);
  G4cout << GateTools::Indent(indent) << "Hit convertor:      '" << m_hitConvertor->GetObjectName() << "'\n";
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
//make void GateDigitizerOld::Digitize(GateHitsCollection * optional)
void GateDigitizerOld::Digitize()
{
G4cout<<"GateDigitizerOld::Digitize()"<<G4endl;

  if ( !IsEnabled() )
    return;

  GateHitsCollection* CHC;
  CHC = GateOutputMgr::GetInstance()->GetHitCollection();
  //G4cout<<"------------------- New event "<<((GateHit*)(CHC->GetHit(0)))->GetEventID()<<G4endl;

 if (nVerboseLevel>1)
    G4cout << "[GateDigitizerOld::Digitize]: starting\n";

  if (nVerboseLevel>1)
    G4cout << "[GateDigitizerOld::Digitize]: erasing pulse-lists\n";

  //If I do not erase pulse list I lossinfo of evtID, time,.. at singles level pulse
  ErasePulseListVector();

  m_hitConvertor->ProcessHits(CHC);


  if (CHC->entries()==0) return; //go to next event if no hits to process

  DigitizePulses();


 for (size_t i=0; i<m_digiMakerList.size() ; ++i) {
    if (nVerboseLevel>1)
      G4cout << "[GateDigitizerOld::Digitize]: launching DigitizerOld module '" << m_digiMakerList[i]->GetObjectName() << "'\n";
    m_digiMakerList[i]->Digitize();
  }

  if (nVerboseLevel>1)
    G4cout << "[GateDigitizerOld::Digitize]: completed\n";

}


void GateDigitizerOld::Digitize(std::vector<GateHit*> vHitsCollection)
{
  if ( !IsEnabled() )
    return;


 if (nVerboseLevel>1)
    G4cout << "GateDigitizerOld::Digitize]: starting\n";

  //if (nVerboseLevel>1)
    //G4cout << "[GateDigitizerOld::Digitize]: erasing pulse-lists\n";

  //If I do not erase pulse list I lossinfo of evtID, time,.. at singles level pulse
  ErasePulseListVector();

  m_hitConvertor->ProcessHits(vHitsCollection);

  //G4cout << "hitconvertor finished";
  DigitizePulses();

}

void GateDigitizerOld::DigitizePulses()  {

	G4cout << "[GateDigitizerOld::DigitizePulses]"<<"\n";
  size_t i;
 // G4cout << "[GateDigitizerOld::Digitize]:Gate chain number"<<GetChainNumber()<<"\n";
  for (i=0; i<GetChainNumber() ; ++i) {
    if (nVerboseLevel>1)
    G4cout << "[GateDigitizerOld::Digitize]: launching processor chain '" << GetChain(i)->GetObjectName() << "'\n";
    //GetChain(i)->Describe();
    GetChain(i)->GetOutputName();
    GetChain(i)->ProcessPulseList();
  }

   //G4cout << "coinc vector Size before procesSinglesList="<<m_coincidencePulseVector.size()<<G4endl;
  // Have the pulses processed by the coincidence sorters
  for (i=0; i<m_coincidenceSorterList.size() ; ++i) {
    if (nVerboseLevel>1)
      G4cout << "[GateDigitizerOld::Digitize]: launching coincidence sorter '" << m_coincidenceSorterList[i]->GetObjectName() << "'\n";
    m_coincidenceSorterList[i]->ProcessSinglePulseList();
  }
   //G4cout << "coinc vector Siz after procesSinglesList="<<m_coincidencePulseVector.size()<<G4endl;
 // G4cout << (m_coincidencePulseVector[0])->GetCoincID()<<G4endl;

		  // Have the coincidences processed by the coincidence-processor chains
  for (i=0; i<m_coincidenceChainList.size() ; ++i) {
	 G4cout<<"m_coincidenceChainList loop"<<Gateendl;
    if (nVerboseLevel>1)
      G4cout << "[GateDigitizerOld::Digitize]: launching coincidence-processor '" << m_coincidenceChainList[i]->GetObjectName() << "'\n";
    m_coincidenceChainList[i]->ProcessCoincidencePulses();
  }


}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
void GateDigitizerOld::InsertDigiMakerModule(GateVDigiMakerModule* newDigiMakerModule)
{
  //if (nVerboseLevel>1)
    G4cout << "[GateDigitizerOld::InsertDigiMakerModule]: storing new digi-maker module '" << newDigiMakerModule->GetObjectName() << "'"
           << " with collection name " << newDigiMakerModule->GetCollectionName() << "'\n";
  m_digiMakerList.push_back(newDigiMakerModule);
  StoreCollectionName(newDigiMakerModule->GetCollectionName());
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
//mhadi_obso Obsolete, because we use now the multi-system approach
void GateDigitizerOld::SetSystem(GateVSystem* aSystem)
{
  m_system = aSystem;
  size_t i;
  for (i=0; i<GetChainNumber() ; ++i)
    GetChain(i)->SetSystem(aSystem);
  for (i=0; i<m_coincidenceSorterList.size() ; ++i)
    m_coincidenceSorterList[i]->SetSystem(aSystem);
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// The next three methods were added for the multi-system approach
void GateDigitizerOld::AddSystem(GateVSystem* aSystem)
{
  if(!m_systemList)
    m_systemList = new GateSystemList;

  m_systemList->push_back(aSystem);

  // mhadi_Note: We have here only one pulse processor chain, this is the default chain created at the detector construction stage and
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
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
GateVSystem* GateDigitizerOld::FindSystem(GatePulseProcessorChain* processorChain)
{
  GateVSystem* system = 0;
  if(processorChain->size() != 0)
    {
      G4String sysName = processorChain->GetProcessor(0)->GetObjectName();
      system = FindSystem(sysName);
    }
  return system;
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
GateVSystem* GateDigitizerOld::FindSystem(G4String& systemName)
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

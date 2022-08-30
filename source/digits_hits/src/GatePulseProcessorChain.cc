/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#include "GatePulseProcessorChain.hh"
#include "GatePulseProcessorChainMessenger.hh"

#include "G4UnitsTable.hh"

#include "GateDigitizerOld.hh"
#include "GateVPulseProcessor.hh"
#include "GateTools.hh"
#include "GateHitConvertor.hh"
#include "GateSingleDigiMaker.hh"



GatePulseProcessorChain::GatePulseProcessorChain( GateDigitizerOld* itsDigitizer,
    			                          const G4String& itsOutputName)
  : GateModuleListManager(itsDigitizer,itsDigitizer->GetObjectName() + "/" + itsOutputName,"pulse-processor"),
    m_system( itsDigitizer->GetSystem() ),
    m_outputName(itsOutputName),
    m_inputName(GateHitConvertor::GetOutputAlias())
{
	G4cout << " DEBUT Constructor GatePulseProcessorChain \n";
	G4cout<<m_outputName<<G4endl;
  m_messenger = new GatePulseProcessorChainMessenger(this);

G4cout << " in GatePulseProcessorChain call GateSingleDigiMaker\n";
  itsDigitizer->InsertDigiMakerModule( new GateSingleDigiMaker(itsDigitizer, itsOutputName,true) );
  
  G4cout << " FIN Constructor GatePulseProcessorChain \n";
}




GatePulseProcessorChain::~GatePulseProcessorChain()
{
  for (auto processor = theListOfNamedObject.begin(); processor != theListOfNamedObject.end(); ++processor)
  {
    GateMessage("Core", 5, "~GatePulseProcessorChain -- delete module: " << (*processor)->GetObjectName() << Gateendl );
    delete (*processor);
  }
  delete m_messenger;
}




void GatePulseProcessorChain::InsertProcessor(GateVPulseProcessor* newChildProcessor)
{
	G4cout<<"GatePulseProcessorChain::InsertProcessor "<<G4endl;
  theListOfNamedObject.push_back(newChildProcessor);
}



void GatePulseProcessorChain::Describe(size_t indent)
{
  GateModuleListManager::Describe();
  G4cout << GateTools::Indent(indent) << "Input:              '" << m_inputName << "'\n";
  G4cout << GateTools::Indent(indent) << "Output:             '" << m_outputName << "'\n";
}

void GatePulseProcessorChain::DescribeProcessors(size_t indent)
{
  G4cout << GateTools::Indent(indent) << "Nb of modules:       " << theListOfNamedObject.size() << Gateendl;
  for (size_t i=0; i<theListOfNamedObject.size(); i++)
      GetProcessor(i)->Describe(indent+1);
}

void GatePulseProcessorChain::ListElements()
{
  DescribeProcessors(0);
}

GatePulseList* GatePulseProcessorChain::ProcessPulseList()
{
  GatePulseList* pulseList = GateDigitizerOld::GetInstance()->FindPulseList( m_inputName );

  if (!pulseList)
    return 0;

  // Empty pulse list: no need to process
  if (pulseList->empty())
    return 0;

  // Sequentially launch all pulse processors
  for (size_t processorID = 0 ; processorID < GetProcessorNumber(); processorID++) 
    if (GetProcessor(processorID)->IsEnabled()) {
      pulseList = GetProcessor(processorID)->ProcessPulseList(pulseList);
      if (pulseList) GateDigitizerOld::GetInstance()->StorePulseList(pulseList);
      else break;
    }

  if (pulseList)  GateDigitizerOld::GetInstance()->StorePulseListAlias(m_outputName,pulseList);
  return pulseList;
}



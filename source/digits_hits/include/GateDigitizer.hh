/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateDigitizer
  Last modification in 12/2011 by Abdul-Fattah.Mohamad-Hadi@subatech.in2p3.fr, for the multi-system approach.
*/

#ifndef GateDigitizer_h
#define GateDigitizer_h 1

#include "globals.hh"
#include <vector>

#include "GateModuleListManager.hh"
#include "GateDigi.hh"

class GateDigitizerMng;
class G4VDigitizerModule;
class GateDigitizerMessenger;
class GatePulseList;
class GateVSystem;

class GateDigitizer : public GateModuleListManager
{
  public:
    GateDigitizer(GateDigitizerMng* itsDigitizer,
    			    const G4String& itsOutputName);
    virtual ~GateDigitizer();

     /*virtual void InsertProcessor(G4VDigitizerModule* newChildProcessor);

     /*! \brief Virtual method to print-out a description of the object

	\param indent: the print-out indentation (cosmetic parameter)
     */
    /* virtual void Describe(size_t indent=0);

     virtual void DescribeProcessors(size_t indent=0);
     virtual void ListElements();
     virtual G4VDigitizerModule* FindProcessor(const G4String& name)
      	  { return (G4VDigitizerModule*) FindElement(name); }
     virtual G4VDigitizerModule* GetProcessor(size_t i)
      	  {return (G4VDigitizerModule*) GetElement(i);}
     GatePulseList* ProcessPulseList();
     virtual size_t GetProcessorNumber()
      	  { return size();}

     const G4String& GetInputName() const
       { return m_inputName; }
     void SetInputName(const G4String& anInputName)
       {  m_inputName = anInputName; }
     const G4String& GetOutputName() const
       { return m_outputName; }
*/
     virtual inline GateVSystem* GetSystem() const
       { return m_system;}

     //TODO: find where SetSystem is called for PulseProcessorChain and
     //call also for the digitizer

     virtual inline void SetSystem(GateVSystem* aSystem)
       { m_system = aSystem; }

    const G4String& GetInputName() const
    { return m_inputName; }
    void SetInputName(const G4String& anInputName)
    {  m_inputName = anInputName; }
    const G4String& GetOutputName() const
    { return m_outputName; }


    const G4String& GetLastDMname() const
    { return m_lastDMname; }
    void SetLastDMname(const G4String& anInputName)
      {  m_lastDMname = anInputName; }

    void AddNewModule(G4VDigitizerModule* DM);


 protected:
      GateDigitizerMessenger*    m_messenger;
      GateVSystem *m_system;            //!< System to which the chain is attached
      G4String				   m_outputName;
      G4String                 m_inputName;
      G4String                 m_collectionName;

      G4String                 m_lastDMname;


      GateDigiCollection*      m_inputDigiCollection;
public:
      std::vector<G4VDigitizerModule*>    	m_DMlist;	 //!< List of DigitizerModules for this digitizer
      G4String                 m_digitizerName;
      G4int      m_outputDigiCollectionID;
};

#endif

/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateDigitizerMng

	GateDigitizerOld highly inspired
	BaseName -> DigitizerName/CollectionName
	PulseProcessorChain -> Digitizer

	StoreNewPulseProcessorChain -> AddNewSinglesDigitizer
	GateSingleDigiMaker	-> GateDigitizer

	DigitizerName = CollectionName

	DigiMakerModule -> Digitizer
	Digitizer is a List/Chain of a DigiModules in order to get a specific uses SinglesDigiCollection
*/

#ifndef GateDigitizerMng_h
#define GateDigitizerMng_h 1

#include "globals.hh"
#include "GateClockDependent.hh"
#include "GateTools.hh"
#include "GateCrystalSD.hh"
#include "G4DigiManager.hh"
#include "GateDigitizer.hh"

class GateDigitizerMngMessenger;
class GateVSystem;



/*
 * DigitizerOld -> DigitizerMng
 * PulseProcessorChain -> Digitizer
 * PulseProcessor, Processor-> DigitizerModule
 * DigitizerName = CollectionName
 * ?? GateVPulseProcessor -> GateDigitizerModule: public G4VDigitizerModule ?? to put common methods ??
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

class GateDigitizerMng : public GateClockDependent, public G4DigiManager
{
public:
	static GateDigitizerMng* GetInstance();

protected:
	GateDigitizerMng();

public:
  ~GateDigitizerMng();

  //mhadi_add[
    // Next methods were added for the multi-system approach
  inline GateSystemList* GetSystemList() const { return m_systemList; }

   // Add a system to the DigitizerOld systems list
   virtual void AddSystem(GateVSystem* aSystem);
   // To find a system from the DigitizerOld systems list
   //GateVSystem* FindSystem(GatePulseProcessorChain* processorChain);
   GateVSystem* FindSystem(G4String& systemName);

   //Messenger commands
   /**/
   inline const G4String&  GetElementTypeName()
   { return m_elementTypeName;}

   void ListElements(size_t indent=0);

   //! Integrates a new digitizer/singlesCollection
   void AddNewSinglesDigitizer(GateDigitizer* digitizer);

   GateDigitizer* FindDigitizer(G4String mName);

   //! Integrates a new DM to a digitizer
 //  void InsertSinglesDigitizerModule(GateDigitizer* digitizer, G4VDigitizerModule* DM);

  // virtual inline GateNamedObject* FindElementByBaseName(const G4String& baseName)
  //   { return FindElement( MakeElementName(baseName) ) ; }
   /**/

  // void InsertDigitizerBlock(GateDigitizer* newDigitizer); //InsertChain

   void RunDigitizers(); //Digitize, DigitizePulses




  /* //! Get the current value of the insertion name
   inline const G4String& GetNewInsertionBaseName()
   { return m_newInsertionBaseName; }

   //! Set the value of the insertion name
   inline void SetNewInsertionBaseName(const G4String& val)
   { m_newInsertionBaseName = val; }
   //! Get the current value of the insertion name
   inline const G4String& GetNewInsertionBaseType()
   { return m_newInsertionBaseType; }

   //! Set the value of the insertion name
   inline void SetNewInsertionBaseType(const G4String& val)
   { m_newInsertionBaseType = val; }
*/
private:


  GateDigitizerMngMessenger *fMessenger;

  static GateDigitizerMng*  theDigitizerMng;

protected:
  G4String 					m_elementTypeName;	 //!< Type-name for DigitizerMng --> used only for cout and help messengers
  GateSystemList*                               m_systemList;            //! List of systems to which the DigitizerOld is attached

  //G4String 					m_newInsertionBaseType;	 //!< Type-name for all DigitizerOld modules
  //G4String 					m_newInsertionBaseName;	 //!< Type-name for all DigitizerOld modules


public:
  G4bool m_isInitialized;
  std::vector<GateDigitizer*>    	m_SingleDigitizersList;	 //!< Vector of pulse-processor chains

};
#endif

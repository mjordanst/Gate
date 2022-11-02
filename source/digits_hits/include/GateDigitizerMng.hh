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
#include "GateCoincidenceSorter.hh"

#include "GateDigitizerInitializationModule.hh"


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
 * TODO :
 *  - Adder -> done
 *  - Readout
 *  - Energy windowing 2j
 *  	- upholder
 *  	- thresholder
 *  	- local energy thresholder
 *  	- Energy thresoler
 *  	- sigmoidal thresholder
 *  - Blurring -> big block 3s
 *  	- Energy Blurring
 *  	- Time Blurring/TemporalResolution
 *  	- SP Blurring
 *  	- local bluring
 *  	- crystal bluring
 *  	- local time resolution
 *  	- intrinistic resolution blurring
 *  - Efficiencies -> big block 3s
 *  	- quantum
 *  	- light yield
 *  	- energy efficiency
 *  - Dead time 2j
 *  - Noise 2j
 *  - Pile up ??
 *  - system filter ??
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
  void Initialize();

  void GetDigiCollection();

  //mhadi_add[
    // Next methods were added for the multi-system approach
  inline GateSystemList* GetSystemList() const { return m_systemList; }

   // Add a system to the DigitizerOld systems list
   virtual void AddSystem(GateVSystem* aSystem);
   // To find a system from the DigitizerOld systems list
   GateVSystem* FindSystem(GateDigitizer* digitizer);
   GateVSystem* FindSystem(G4String& systemName);

   //Messenger commands
   inline const G4String&  GetElementTypeName()
   { return m_elementTypeName;}

    GateClockDependent* FindElement(G4String baseName);
   //	   { return FindElement( MakeElementName(baseName) ) ; }
   //	*/

    void AddNewSD(GateDigitizer*, GateCrystalSD*);

   void ShowSummary();
   /// Methods for Singles
   //! Run Singles Digitizers
   void RunDigitizers();
   //! Integrates a new digitizer/singlesCollection
   void AddNewSinglesDigitizer(GateDigitizer* digitizer);
   //! Find Digitizer by its name
  GateDigitizer* FindDigitizer(G4String mName);
   /// End of methods for Singles


   /// Methods for Coincidences

   //Sorters
   //Sorters -> Initialization of Coincidence Digitizers
   //void AddNewSinglesDigitizer(GateDigitizer* digitizer);

   void RunCoincidenceSorters();
   void AddNewCoincidenceSorter(GateCoincidenceSorter* coincidenceSorter);
   GateCoincidenceSorter* FindCoincidenceSorter(G4String mName);
   //Coincidence digitizers
   void RunCoincidenceDigitizers();
   //void AddNewCoincidenceDigitizer(GateCoincidenceSorter* coincidenceSorter);
   //GateCoincidenceDigitizer* FindCoincidenceDigitizer(G4String mName);
   /// End of methods for Coincidences



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

  G4int m_collectionID;

public:
  G4bool m_isInitialized;
  G4bool m_isTheFirstEvent;
  std::vector<GateCrystalSD*>    	m_SDlist;	 //!< Vector of Sensitive Detectors
  std::vector<GateDigitizerInitializationModule*>    	m_digitizerIMList;	 //!< Vector of initialisation modules for different SD
  std::vector<GateDigitizer*>    	m_SingleDigitizersList;	 //!< Vector of digitizers
  std::vector<GateCoincidenceSorter*>    	m_CoincidenceSortersList;	 //!< Vector of coincidence sorters


};
#endif

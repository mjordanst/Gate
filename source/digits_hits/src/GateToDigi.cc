/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#include "GateToDigi.hh"
#include "GateOutputModuleMessenger.hh"

#include "globals.hh"

#include "G4Run.hh"
#include "G4DigiManager.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4ios.hh"
#include <iomanip>

#include "GateDetectorConstruction.hh"
//#include "GateDigitizerOld.hh"
#include "GateOutputMgr.hh"
#include "GateDigitizer.hh"


//---------------------------------------------------------------------------
GateToDigi::GateToDigi(const G4String& name, GateOutputMgr* outputMgr,
      	      	       DigiMode digiMode)
  : GateVOutputModule(name,outputMgr,digiMode)
{
	 G4cout<<"GateToDigi: constr"<<Gateendl;

  m_isEnabled = true; // This module lead the digitizer, so let it enabled !!!
  nVerboseLevel = 0;
  m_digiMessenger = new GateOutputModuleMessenger(this);

  //m_digitizer =    GateDigitizerOld::GetInstance();

/*  //OK GND 2022. moved from Gate.cc
#ifdef G4ANALYSIS_USE_GENERAL
	GateDigitizer* digitizer = GateDigitizer::GetInstance();
	digitizer->Initialize();
#endif
*/
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
GateToDigi::~GateToDigi()
{
  delete m_digiMessenger;
  //delete m_digitizer;

  if (nVerboseLevel > 0) G4cout << "GateToDigi deleting...\n";
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
const G4String& GateToDigi::GiveNameOfFile()
{
  m_noFileName = "  "; // 2 spaces for output module with no fileName
  return m_noFileName;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void GateToDigi::RecordBeginOfAcquisition()
{
  //if (nVerboseLevel > 2)
    G4cout << "GateToDigi::RecordBeginOfAcquisition\n";
    G4cout << "GateToDigi::RecordBeginOfAcquisition: Here we AddNewModule digitizer\n";
    //OK GND 2022
    //if (G4DigiManager::GetDMpointer()->FindDigitizerModule(m_digitizer->GetObjectName())==0)
    //	 G4DigiManager::GetDMpointer()->AddNewModule(m_digitizer);



}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void GateToDigi::RecordEndOfAcquisition()
{
  if (nVerboseLevel > 2)
    G4cout << "GateToDigi::RecordEndOfAcquisition\n";
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void GateToDigi::RecordBeginOfRun(const G4Run* )
{
  if (nVerboseLevel > 2)
    G4cout << "GateToDigi::RecordBeginOfRun\n";
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void GateToDigi::RecordEndOfRun(const G4Run* )
{
  if (nVerboseLevel > 2)
    G4cout << "GateToDigi::RecordEndOfRun\n";
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void GateToDigi::RecordBeginOfEvent(const G4Event* )
{
  //if (nVerboseLevel > 2)
    G4cout << "GateToDigi::RecordBeginOfEvent\n";
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void GateToDigi::RecordEndOfEvent(const G4Event* )
{
  //if (nVerboseLevel > 2)
    G4cout << "GateToDigi::RecordEndOfEvent\n";
  //m_digitizer->Digitize();



}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void GateToDigi::RecordStepWithVolume(const GateVVolume *, const G4Step* )
{
  if (nVerboseLevel > 2)
    G4cout << "GateToDigi::RecordStep\n";
}
//---------------------------------------------------------------------------

/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
//GND:ClassToRemove

#include "GateDeadTimeOld.hh"
#include "G4UnitsTable.hh"
#include "GateDeadTimeOldMessenger.hh"
#include "GateTools.hh"
#include "GateVolumeID.hh"
#include "GateOutputVolumeID.hh"
#include "GateDetectorConstruction.hh"
#include "GateCrystalSD.hh"
#include "GateVSystem.hh"
#include "GateObjectChildList.hh"
#include "GateVVolume.hh"
#include "GateMaps.hh"


GateDeadTimeOld::GateDeadTimeOld(GatePulseProcessorChain* itsChain, const G4String& itsName)
  : GateVPulseProcessor(itsChain,itsName)
  , m_bufferSize(0)
  , m_bufferMode(0)
{
  m_isParalysable = false;
  m_DeadTimeOld = 0;
  m_messenger = new GateDeadTimeOldMessenger(this);
  m_init_done_run_id = -1;
}




GateDeadTimeOld::~GateDeadTimeOld()
{
  delete m_messenger;
}




void GateDeadTimeOld::ProcessOnePulse(const GatePulse* inputPulse, GatePulseList& outputPulseList)
{


  if (!inputPulse) return;

  if (inputPulse->GetRunID() != m_init_done_run_id) {
    // initialise the DeadTimeOld buffer and table
    CheckVolumeName(m_volumeName);
   /* if (!m_testVolume) {
      G4cerr << Gateendl << "[GateDeadTimeOld::ProcessOnePulse]:\n"
             << "Sorry, but you don't have chosen any volume !\n";
    }
    */
    if (nVerboseLevel>1) {
      G4cout << "first pass in dead time pulse process\n" ;
      G4cout << "DeadTimeOld set at  " << m_DeadTimeOld << " ps"<< Gateendl ;
      G4cout << "mode = " << (m_isParalysable ? "paralysable":"non-paralysable") << Gateendl ;
    }
    m_init_done_run_id = inputPulse->GetRunID();
  }

  if (inputPulse->GetEnergy()==0) {
    if (nVerboseLevel>1)
      G4cout << "[GateDeadTimeOld::ProcessOneHit]: energy is null for " << inputPulse << " -> pulse ignored\n\n";
    return;
  }

  // FIND THE ELEMENT ID OF PULSE
  const GateVolumeID* aVolumeID = &inputPulse->GetVolumeID();
  G4int m_generalDetId = 0; // a unique number for each detector part
                            // that depends of the depth of application
                            // of the dead time
  size_t m_depth = (size_t)(aVolumeID->GetCreatorDepth(m_volumeName));

  m_generalDetId = aVolumeID->GetCopyNo(m_depth);

  /////// Bug Report - 8/6/2006 - Spencer Bowen - S.Jan ////////
  /*
    for (G4int i = 1 ; i < numberOfHigherLevels + 1; i++)
    {
    m_generalDetId += aVolumeID->GetCopyNo(m_depth-i) * numberOfComponentForLevel[i-1];
    }
  */

  G4int multFactor = 1;
  for (G4int i = 1 ; i < numberOfHigherLevels + 1; i++) {
    multFactor *= numberOfComponentForLevel[i-1];
    m_generalDetId += aVolumeID->GetCopyNo(m_depth-i)*multFactor;
  }
  //////////////////////////////////////////////////////////////

  // FIND TIME OF PULSE
  unsigned long long int currentTime = (unsigned long long int)((inputPulse->GetTime())/picosecond);
  if (nVerboseLevel>5) {
    G4cout << "A new pulse is processed by dead time time : " << (inputPulse->GetTime())/picosecond
           << " =  "<< currentTime  << Gateendl  ;
    G4cout << "ID elt = " <<  m_generalDetId << Gateendl ;
    G4cout << "Rebirth time for elt " << m_generalDetId << " = " << m_DeadTimeOldTable[m_generalDetId]<< Gateendl ;
  }

  // IS DETECTOR DEAD ?
  if (currentTime >= m_DeadTimeOldTable[m_generalDetId]) {
    // NO, DETECTOR IS NOT DEAD : COPY THIS PULSE TO OUTPUT PULSE LIST
    GatePulse* outputPulse = new GatePulse(*inputPulse);
    outputPulseList.push_back(outputPulse);

    //  m_DeadTimeOldTable[m_generalDetId] = currentTime + m_DeadTimeOld;
    if (m_bufferSize>1){
      m_bufferCurrentSize[m_generalDetId]++;
      if (m_bufferCurrentSize[m_generalDetId]==m_bufferSize){
        m_DeadTimeOldTable[m_generalDetId] = currentTime + m_DeadTimeOld;
        m_bufferCurrentSize[m_generalDetId]=0;
      }
    } else {
      m_DeadTimeOldTable[m_generalDetId] = currentTime + m_DeadTimeOld;
    }
    if (nVerboseLevel>5){
      G4cout << "We have accept " << currentTime << " a pulse in element " << m_generalDetId <<
        "\trebirth time\t" << m_DeadTimeOldTable[m_generalDetId] << Gateendl;
      G4cout << "Copied pulse to output:\n"
             << *outputPulse << Gateendl << Gateendl ;
    }
  }
  else
    {
      // YES DETECTOR IS DEAD : REMOVE PULSE
      if (nVerboseLevel>5)
        G4cout << "Removed pulse, due to dead time:\n";
      // AND IF "PARALYSABLE" DEAD TIME, MAKE THE DEATH OF DETECTOR LONGER
      if ((m_bufferSize>1) && (m_bufferMode==1)){
        if (m_bufferCurrentSize[m_generalDetId]<m_bufferSize-1) {
          m_bufferCurrentSize[m_generalDetId]++;
          outputPulseList.push_back(new GatePulse(*inputPulse));
        }
      } else {
      	if (m_isParalysable && (m_bufferSize<2)){
          m_DeadTimeOldTable[m_generalDetId]  = currentTime + m_DeadTimeOld;
        }
      }
    }
  if (nVerboseLevel>99)
    getchar();
}



void GateDeadTimeOld::SetDeadTimeOldMode(G4String val)
{
  if ((val!="paralysable")&&(val!="nonparalysable"))
    G4cout << "*** GateDeadTimeOld.cc : Wrong dead time mode : candidates are : paralysable nonparalysable\n";
  else
    m_isParalysable = (val=="paralysable");
}


void GateDeadTimeOld::CheckVolumeName(G4String val)
{
  GateObjectStore* anInserterStore = GateObjectStore::GetInstance();

  if (anInserterStore->FindCreator(val)) {
    m_volumeName = val;

    FindLevelsParams(anInserterStore);
    m_testVolume = 1;
  }
  else {
	  GateError("***ERROR*** Wrong Volume Name. Abort.");

  }
}



void GateDeadTimeOld::FindLevelsParams(GateObjectStore*  anInserterStore)
{
  G4int numberTotalOfComponentInSystem = 0;
  GateVVolume* anInserter = anInserterStore->FindCreator(m_volumeName);
  GateVVolume* anotherInserter = anInserter; // just to buffer anInserter

  if (nVerboseLevel>1)
    G4cout << "DEAD TIME IS APPLIED ON " <<  m_volumeName << Gateendl;

  // How many levels higher than volumeName level ?
  numberOfHigherLevels = 0;
  while(anotherInserter->GetMotherList()) {
    anotherInserter =  anotherInserter->GetMotherList()->GetCreator();
    numberOfHigherLevels ++;
  }
  //  numberOfHigherLevels--;
  anotherInserter = anInserter;

  // How many components for each levels ?
  numberOfComponentForLevel.resize(numberOfHigherLevels);
  if (numberOfHigherLevels < 1) {
    G4cout << "[GateDeadTimeOld::FindLevelsParams]: ERROR numberOfHigherLevels is zero.\n\n";
    return;
  }

  numberOfComponentForLevel[0] = anotherInserter->GetVolumeNumber();

  for (G4int i = 1 ; i < numberOfHigherLevels ; i++) {
    anotherInserter = anotherInserter->GetMotherList()->GetCreator();
    numberOfComponentForLevel[i] = anotherInserter->GetVolumeNumber();
  }

  numberTotalOfComponentInSystem = 1;
  for (G4int i2 = 0 ; i2 < numberOfHigherLevels ; i2++) {
    numberTotalOfComponentInSystem = numberTotalOfComponentInSystem * numberOfComponentForLevel[i2];
    if (nVerboseLevel>5)
      G4cout << "Level : " << i2 << " has "
             << numberOfComponentForLevel[i2] << " elements\n";
  }

  if (nVerboseLevel>5)
    G4cout << "total number of elements = " <<numberTotalOfComponentInSystem << Gateendl;

  // create the table of "rebirth time" (detector is dead than it rebirth)
  m_DeadTimeOldTable.resize(numberTotalOfComponentInSystem);
  m_bufferCurrentSize.resize(numberTotalOfComponentInSystem);

  for (G4int i=0;i<numberTotalOfComponentInSystem;i++) {
    m_DeadTimeOldTable[i] = 0;
    m_bufferCurrentSize[i] = 0.;
  }
}




void GateDeadTimeOld::DescribeMyself(size_t indent)
{
  G4cout << GateTools::Indent(indent) << "DeadTimeOld: " << G4BestUnit(m_DeadTimeOld,"Time") << Gateendl;
}

/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
//GND:ClassToRemove

#ifndef GateDeadTimeOld_h
#define GateDeadTimeOld_h 1

#include "globals.hh"
#include <iostream>
#include <vector>
#include "G4ThreeVector.hh"

#include "GateVPulseProcessor.hh"
#include "GateObjectStore.hh"

class GateDeadTimeOldMessenger;


/*! \class  GateDeadTimeOld
  \brief  Pulse-processor modeling a simple dead time discriminator.

  - GateDeadTimeOld - by Luc.Simon@iphe.unil.ch

  - The method ProcessOnePulse of this class models a simple
  DeadTimeOld discriminator. User chooses value of dead time, mode
  (paralysable or not) and geometric level of application (crystal, module,...)

  \sa GateVPulseProcessor
  \sa GateVolumeID
  \sa GatePulseProcessorChainMessenger
*/

class GateDeadTimeOld : public GateVPulseProcessor
{
public:

  //! Destructor
  virtual ~GateDeadTimeOld() ;

  //! Check the validity of the volume name where the dead time will be applied
  void CheckVolumeName(G4String val);

  //! Constructs a new dead time attached to a GateDigitizerOld
  GateDeadTimeOld(GatePulseProcessorChain* itsChain, const G4String& itsName);

public:

  //! Returns the DeadTimeOld
  unsigned long long int GetDeadTimeOld() { return m_DeadTimeOld; }

  //! Set the DeadTimeOld
  void SetDeadTimeOld(G4double val) { m_DeadTimeOld = (unsigned long long int)(val/picosecond); }

  //! Set the DeadTimeOld mode ; candidates : paralysable nonparalysable
  void SetDeadTimeOldMode(G4String val);
  //! Set the buffer mode ;
  void SetBufferMode(G4int val) { m_bufferMode=val; }
  //! Set the buffer mode ;
  void SetBufferSize(G4double val) { m_bufferSize=val; }
  //! Set the buffer mode ;

  //! Implementation of the pure virtual method declared by the base class GateClockDependent
  //! print-out the attributes specific of the DeadTimeOld
  virtual void DescribeMyself(size_t indent);

protected:

  /*! Implementation of the pure virtual method declared by the base class GateVPulseProcessor
    This methods processes one input-pulse
    It is is called by ProcessPulseList() for each of the input pulses
    The result of the pulse-processing is incorporated into the output pulse-list
    This method manages the updating of the "rebirth time table", the table of times when
    the detector volume will be alive again.
  */
  void ProcessOnePulse(const GatePulse* inputPulse, GatePulseList&  outputPulseList);

  //! To summarize it finds the number of elements of the different scanner levels
  void FindLevelsParams(GateObjectStore* anInserterStore);

private:
  G4String m_volumeName;  //!< Name of the volume where Dead time is applied
  G4int m_testVolume;     //!< equal to 1 if the volume name is valid, 0 else
  std::vector<int> numberOfComponentForLevel; //!< Table of number of element for each geometric level
  G4int numberOfHigherLevels ;  //!< number of geometric level higher than the one chosen by the user
  unsigned long long int m_DeadTimeOld; //!< DeadTimeOld value
  // was :  G4String m_DeadTimeOldMode;   //!< dead time mode : paralysable nonparalysable
  G4bool m_isParalysable;   //!< dead time mode : paralysable (true) nonparalysable (false) (modif. by D. Guez on 03/03/04)
  std::vector<unsigned long long int>  m_DeadTimeOldTable;  //!< contains the "rebirth times". Alocated once at the first call.
  G4double m_bufferSize;  //!< contains the rebirth time.
  std::vector<double> m_bufferCurrentSize;  //!< contains the buffers sizes
  G4int m_bufferMode; //! 0 : DT during writing, 1 : DT if writing AND buffer full
  G4int m_init_done_run_id;
  GateDeadTimeOldMessenger *m_messenger;    //!< Messenger
};


#endif

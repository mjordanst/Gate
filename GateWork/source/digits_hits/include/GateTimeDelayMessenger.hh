/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

// OK GND 2022
/*
  The purpose of this class is to help to create new users digitizer module(DM).
  Please, check GateTimeDelay.cc for more detals
*/


/*! \class  GateTimeDelayMessenger
    \brief  Messenger for the GateTimeDelay

    \sa GateTimeDelay, GateTimeDelayMessenger
*/


#ifndef GateTimeDelayMessenger_h
#define GateTimeDelayMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

#include "GateClockDependentMessenger.hh"
class GateTimeDelay;
class G4UIcmdWithAString;

class GateTimeDelayMessenger : public GateClockDependentMessenger
{
public:
  
  GateTimeDelayMessenger(GateTimeDelay*);
  ~GateTimeDelayMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);

  
private:
  GateTimeDelay* m_TimeDelay;
  G4UIcmdWithADoubleAndUnit*          TimeDCmd;


};

#endif







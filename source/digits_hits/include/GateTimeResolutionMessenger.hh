/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

// OK GND 2022
/*This class is not used by GATE !
  The purpose of this class is to help to create new users digitizer module(DM).
  Please, check GateTimeResolution.cc for more detals
  */


/*! \class  GateTimeResolutionMessenger
    \brief  Messenger for the GateTimeResolution

    - GateTimeResolution - by name.surname@email.com

    \sa GateTimeResolution, GateTimeResolutionMessenger
*/


#ifndef GateTimeResolutionMessenger_h
#define GateTimeResolutionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

#include "GateClockDependentMessenger.hh"
class GateTimeResolution;
class G4UIcmdWithAString;

class GateTimeResolutionMessenger : public GateClockDependentMessenger
{
public:
  
  GateTimeResolutionMessenger(GateTimeResolution*);
  ~GateTimeResolutionMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);

  
private:
  GateTimeResolution* m_TimeResolution;
  G4UIcmdWithADoubleAndUnit   *fwhmCmd;


};

#endif









/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

// OK GND 2022
/*This class is not used by GATE !
  The purpose of this class is to help to create new users digitizer module(DM).
  Please, check GateEnergyResolution.cc for more detals
  */


/*! \class  GateEnergyResolutionMessenger
    \brief  Messenger for the GateEnergyResolution

    - GateEnergyResolution - by name.surname@email.com

    \sa GateEnergyResolution, GateEnergyResolutionMessenger
*/


#ifndef GateEnergyResolutionMessenger_h
#define GateEnergyResolutionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

#include "GateClockDependentMessenger.hh"
class GateEnergyResolution;
class G4UIcmdWithAString;

class GateEnergyResolutionMessenger : public GateClockDependentMessenger
{
public:
  
  GateEnergyResolutionMessenger(GateEnergyResolution*);
  ~GateEnergyResolutionMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);

  
private:
  GateEnergyResolution* m_EnergyResolution;
  G4UIcmdWithADouble   *resoCmd;
  G4UIcmdWithADouble   *resoMinCmd;
  G4UIcmdWithADouble   *resoMaxCmd;
  G4UIcmdWithADoubleAndUnit *erefCmd;
  G4UIcmdWithADoubleAndUnit *slopeCmd;


};

#endif









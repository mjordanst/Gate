/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/
//GND:ClassToRemove

#ifndef GateEnergyEfficiencyOldMessenger_h
#define GateEnergyEfficiencyOldMessenger_h 1

#include "GatePulseProcessorMessenger.hh"

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

class GateEnergyEfficiencyOld;

class GateEnergyEfficiencyOldMessenger: public GatePulseProcessorMessenger
{
  public:
    GateEnergyEfficiencyOldMessenger(GateEnergyEfficiencyOld* itsPulseProcessor);
    virtual ~GateEnergyEfficiencyOldMessenger();

    inline void SetNewValue(G4UIcommand* aCommand, G4String aString);

  private:
    G4UIcmdWithAString   *distNameCmd;
};

#endif

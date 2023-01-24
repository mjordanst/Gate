/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/
//GND:ClassToRemovex

#ifndef GatePileupOldMessenger_h
#define GatePileupOldMessenger_h 1

#include "GatePulseProcessorMessenger.hh"

class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;

class GatePileupOld;

class GatePileupOldMessenger: public GatePulseProcessorMessenger
{
  public:
    GatePileupOldMessenger(GatePileupOld* itsPileupOld);
    virtual~GatePileupOldMessenger();

    void SetNewValue(G4UIcommand* aCommand, G4String aString);

    inline GatePileupOld* GetPileupOld()
      { return (GatePileupOld*) GetPulseProcessor(); }

  private:
    G4UIcmdWithAnInteger*      SetDepthCmd;
    G4UIcmdWithADoubleAndUnit* SetPileupOldCmd;
};

#endif

/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#ifndef GateReadoutOldMessenger_h
#define GateReadoutOldMessenger_h 1

#include "GatePulseProcessorMessenger.hh"

class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;

class GateReadoutOld;

/*! \class  GateReadoutOldMessenger
    \brief  Messenger for the GateReadoutOld

    - GateReadoutOldMessenger - by Daniel.Strul@iphe.unil.ch

    \sa GateReadoutOld, GatePulseProcessorMessenger
*/
class GateReadoutOldMessenger: public GatePulseProcessorMessenger
{
  public:
    GateReadoutOldMessenger(GateReadoutOld* itsReadoutOld);
    ~GateReadoutOldMessenger();

    inline void SetNewValue(G4UIcommand* aCommand, G4String aString);

    inline GateReadoutOld* GetReadoutOld()
      { return (GateReadoutOld*) GetPulseProcessor(); }

  private:
    G4UIcmdWithAnInteger*      SetDepthCmd;
    G4UIcmdWithAString*        SetPolicyCmd;
    G4UIcmdWithAString*        SetVolNameCmd;
    G4UIcmdWithABool*          ForceDepthCentroidCmd;
    //G4UIcmdWithAString*		   SetResultingXYCmd;
    //G4UIcmdWithAString*        SetResultingZCmd;


};

#endif

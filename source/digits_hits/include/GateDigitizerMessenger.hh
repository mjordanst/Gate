/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#ifndef GateDigitizerMessenger_h
#define GateDigitizerMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"


class GateDigitizer;
class G4UIdirectory;
class G4UIcmdWithAString;

class GateDigitizerMessenger: public G4UImessenger
{
public:
  GateDigitizerMessenger(GateDigitizer*);
  ~GateDigitizerMessenger();

  void SetNewValue(G4UIcommand*, G4String);


private:
  GateDigitizer* m_digitizer;

  G4UIdirectory           *Dir;

  G4UIcmdWithAString*         SetModuleNameCmd;


};

#endif

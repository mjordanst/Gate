/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

// OK GND 2022

#ifndef GateAdderMessenger_h
#define GateAdderMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class GateAdder;
class G4UIcmdWithAString;

class GateAdderMessenger : public G4UImessenger
{
public:
  
  GateAdderMessenger(GateAdder*);
  ~GateAdderMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);

  
private:
  GateAdder* m_Adder;
  G4UIdirectory           *Dir;
  G4UIcmdWithAString*         SetPoliticsCmd;


};

#endif









/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

// OK GND 2022

#ifndef GateAdder_h
#define GateAdder_h 1

#include "G4VDigitizerModule.hh"
#include "GateDigi.hh"
#include "globals.hh"

#include "GateAdderMessenger.hh"

class GateAdder : public G4VDigitizerModule
{
public:
  
  GateAdder(G4String name);
  ~GateAdder();
  
  void Digitize();

  void SetPolitics(G4String name){m_politics=name;}
  
  void MergePositionEnergyWin(GateDigi *);

private:
  G4String m_politics;
  GateDigi* m_outputDigi;

  GateAdderMessenger *fMessenger;


  GateDigiCollection*  DigitsCollection;


};

#endif









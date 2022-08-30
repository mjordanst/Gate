/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

// OK GND 2022
/*!
  \class  GateAdder (prev. GatePulseAdder)
  \brief   for adding/grouping pulses per volume.

    - For each volume where there was one or more input pulse, we get exactly
      one output pulse, whose energy is the sum of all the input-pulse energies,
      and whose position is the centroid of the input-pulse positions.

*/

#ifndef GateAdder_h
#define GateAdder_h 1

#include "GateVDigitizerModule.hh"
#include "GateDigi.hh"
#include "GateDigitizer.hh"
#include "GateClockDependent.hh"

#include "globals.hh"

#include "GateAdderMessenger.hh"

typedef enum {kEnergyCentroid,
              kEnergyWinner} adder_policy_t;

class GateAdder : public GateVDigitizerModule
{
public:
  
  GateAdder(G4String DMname, GateDigitizer *digitizer);
  ~GateAdder();
  
  void Digitize() override;


  void SetPositionPolicy(const G4String& policy);
  
  void MergePositionEnergyWin(GateDigi *);
  void CentroidMerge(GateDigi *);

  void DescribeMyself(size_t );

protected:
  adder_policy_t   m_positionPolicy;

private:
  GateAdderMessenger *fMessenger;

  GateDigi* m_outputDigi;
  GateDigiCollection*  OutputDigiCollection;
  GateDigitizer *m_digitizer;


};

#endif









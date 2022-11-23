/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

// OK GND 2022

/*! \class  GateEnergyFraming
    \brief  GateEnergyFraming applies an energy window selection
    ex-GateThresholder + ex-GateUpholder

    - GateEnergyFraming - by olga.kochebina@cea.fr

    \sa GateEnergyFraming, GateEnergyFramingMessenger
*/

#ifndef GateEnergyFraming_h
#define GateEnergyFraming_h 1

#include "GateVDigitizerModule.hh"
#include "GateDigi.hh"
#include "GateDigitizer.hh"
#include "GateClockDependent.hh"
#include "GateCrystalSD.hh"

#include "globals.hh"

#include "GateEnergyFramingMessenger.hh"


class GateEnergyFraming : public GateVDigitizerModule
{
public:
  
  GateEnergyFraming(GateDigitizer *digitizer);
  ~GateEnergyFraming();
  
  void Digitize() override;

  void SetMin(G4double val)   { m_min = val;  }
  G4double GetMin()   	      { return m_min; }

  void SetMax(G4double val)   { m_max = val;  }
  G4double GetMax()   	      { return m_max; }
  

  void DescribeMyself(size_t );

protected:
  G4double   m_min;
  G4double   m_max;

private:
  GateDigi* m_outputDigi;

  GateEnergyFramingMessenger *m_Messenger;

  GateDigiCollection*  m_OutputDigiCollection;

  GateDigitizer *m_digitizer;


};

#endif









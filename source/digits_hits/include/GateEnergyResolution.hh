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


/*! \class  GateEnergyResolution
    \brief  GateEnergyResolution does some dummy things with input digi
    to create output digi

    - GateEnergyResolution - by name.surname@email.com

    \sa GateEnergyResolution, GateEnergyResolutionMessenger
*/

#ifndef GateEnergyResolution_h
#define GateEnergyResolution_h 1

#include "GateVDigitizerModule.hh"
#include "GateDigi.hh"
#include "GateDigitizer.hh"
#include "GateClockDependent.hh"
#include "GateCrystalSD.hh"

#include "globals.hh"

#include "GateEnergyResolutionMessenger.hh"


class GateEnergyResolution : public GateVDigitizerModule
{
public:
  
  GateEnergyResolution(GateDigitizer *digitizer);
  ~GateEnergyResolution();
  void SetEnergyResolutionParameters();

  void Digitize() override;

  void SetResolution(G4double val)   { m_reso = val;  }
  void SetResolutionMin(G4double val)   { m_resoMin = val;  }
  void SetResolutionMax(G4double val)   { m_resoMax = val;  }
  void SetEnergyRef(G4double val)   { m_eref = val;  }
  void SetSlope(G4double val)   { m_slope = val;  }


  void DescribeMyself(size_t );

protected:
  G4double m_reso;
  G4double m_resoMin;
  G4double m_resoMax;
  G4double m_eref;
  G4double m_slope;

private:
  GateDigi* m_outputDigi;
  GateEnergyResolutionMessenger *m_Messenger;
  GateDigiCollection*  m_OutputDigiCollection;
  GateDigitizer *m_digitizer;
  //G4bool m_IsFirstEntrance;


};

#endif









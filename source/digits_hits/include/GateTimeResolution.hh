/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

// OK GND 2022
/*This class is not used by GATE !
  The purpose of this class is to help to create new users digitizer module(DM).
  Please, check GateTimeResolution.cc for more detals
  */


/*! \class  GateTimeResolution
    \brief  GateTimeResolution does some dummy things with input digi
    to create output digi

    - GateTimeResolution - by name.surname@email.com

    \sa GateTimeResolution, GateTimeResolutionMessenger
*/

#ifndef GateTimeResolution_h
#define GateTimeResolution_h 1

#include "GateVDigitizerModule.hh"
#include "GateDigi.hh"
#include "GateDigitizer.hh"
#include "GateClockDependent.hh"
#include "GateCrystalSD.hh"

#include "globals.hh"

#include "GateTimeResolutionMessenger.hh"


class GateTimeResolution : public GateVDigitizerModule
{
public:
  
  GateTimeResolution(GateDigitizer *digitizer);
  ~GateTimeResolution();
  
  void Digitize() override;


  //! Returns the time resolution
  G4double GetFWHM()   	      { return m_fwhm; }

  //! Set the time resolution
  void SetFWHM(G4double val)   { m_fwhm = val;  }


  void DescribeMyself(size_t );

protected:
  G4double m_fwhm;

private:
  GateDigi* m_outputDigi;

  GateTimeResolutionMessenger *m_Messenger;

  GateDigiCollection*  m_OutputDigiCollection;

  GateDigitizer *m_digitizer;


};

#endif









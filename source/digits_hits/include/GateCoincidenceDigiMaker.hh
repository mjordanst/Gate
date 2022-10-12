/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/
//GND:ClassToRemove

#ifndef GateCoincidenceDigiMaker_h
#define GateCoincidenceDigiMaker_h 1

#include "globals.hh"

#include "GateVDigiMakerModule.hh"

class GateDigitizerOld;

/*! \class  GateCoincidenceDigiMaker
    \brief  It processes a pulse-list, generating Coincidence digis.

    - GateCoincidenceDigiMaker - by Daniel.Strul@iphe.unil.ch

*/
class GateCoincidenceDigiMaker : public GateVDigiMakerModule
{
public:

  //! Constructor
  GateCoincidenceDigiMaker(GateDigitizerOld* itsDigitizer,
                           const G4String& itsInputName,
                           G4bool itsOutputFlag);

  //! Destructor
  ~GateCoincidenceDigiMaker();

  //! Convert a pulse list into a Coincidence Digi collection
  void Digitize();

 protected:


};

#endif

/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateDigitizer
  Last modification in 12/2011 by Abdul-Fattah.Mohamad-Hadi@subatech.in2p3.fr, for the multi-system approach.
*/

#ifndef GateDigitizer_h
#define GateDigitizer_h 1

//#include "GateDigi.hh"
#include "globals.hh"



class GateDigitizerMessenger;


class GateDigitizer
{
public:
	static GateDigitizer* GetInstance();

public:

	GateDigitizer();
  ~GateDigitizer();

  void Initialize();

  void RunDigitizer();

  void SetNewModuleName(G4String name){m_moduleName=name;}



private:

  G4String m_moduleName;

  GateDigitizerMessenger *fMessenger;

  static GateDigitizer*  theDigitizer;



};
#endif

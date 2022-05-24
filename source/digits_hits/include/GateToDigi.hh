/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#ifndef GateToDigi_H
#define GateToDigi_H

 #include "GateVOutputModule.hh"

class GateOutputModuleMessenger;
//OK GND 2022
//class GateDigitizerOld;
class GateDigitizer;

// Class of GateVOutputModule
//This class is used mainly/only to start digitizer after GateAnalysis
// when variables independent of SD are filled, ex. eventID, runID etc.

class GateToDigi :  public GateVOutputModule
{
public:

  GateToDigi(const G4String& name, GateOutputMgr* outputMgr,
      	     DigiMode digiMode);
  virtual ~GateToDigi();
  const G4String& GiveNameOfFile();

  void RecordBeginOfAcquisition();
  void RecordEndOfAcquisition();
  void RecordBeginOfRun(const G4Run *);
  void RecordEndOfRun(const G4Run *);
  void RecordBeginOfEvent(const G4Event *);
  void RecordEndOfEvent(const G4Event *);
  void RecordStepWithVolume(const GateVVolume * v, const G4Step *);
  //! saves the geometry voxel information
  void RecordVoxels(GateVGeometryVoxelStore *) {};

  //OK GND 2022
  //! Get the digitizer
  //inline GateDigitizerOld*   GetDigitizer()
   //   { return m_digitizer; }

  inline GateDigitizer*   GetDigitizer()
       { return m_digitizer; }


private:

  GateOutputModuleMessenger* m_digiMessenger;
      	      	      	      	      	      	      	  //!< crystal-hits into pulses that can be processed
							  //!< by the pulse-processor hits
  //OK GND 2022
  //GateDigitizerOld* m_digitizer;
  GateDigitizer* m_digitizer;

  G4String       m_noFileName;
};

#endif

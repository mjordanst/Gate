/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

#include "GateDigitizerMessenger.hh"
#include "GateConfiguration.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"

#include "GateVDigitizerModule.hh"
#include "GateDigitizer.hh"
#include "GateDigitizerMng.hh"
#include "GateAdder.hh"
#include "GateReadout.hh"



#include "GatePileup.hh"
#include "GateThresholder.hh"
#include "GateUpholder.hh"
#include "GateDeadTime.hh"
#include "GateBlurring.hh"
#include "GateLocalTimeDelay.hh"
#include "GateLocalBlurring.hh"
#include "GateLocalEfficiency.hh"
#include "GateEnergyEfficiency.hh"
#include "GateNoise.hh"
#include "GateBuffer.hh"
#include "GateDiscretizer.hh"
#include "GateBlurringWithIntrinsicResolution.hh"
#include "GateLightYield.hh"
#include "GateTransferEfficiency.hh"
#include "GateCrosstalk.hh"
#include "GateQuantumEfficiency.hh"
#include "GateSigmoidalThresholder.hh"
#include "GateCalibration.hh"
#include "GateSpblurring.hh"
#include "GatePulseAdder.hh"
#include "GatePulseAdderLocal.hh"
#include "GatePulseAdderCompton.hh"
#include "GatePulseAdderComptPhotIdeal.hh"
#include "GatePulseAdderComptPhotIdealLocal.hh"
#include "GateCrystalBlurring.hh"
#include "GateTemporalResolution.hh"
#include "GateLocalClustering.hh"
#include "GateClustering.hh"
#include "GateEnergyThresholder.hh"
#include "GateLocalEnergyThresholder.hh"
#include "GateCC3DlocalSpblurring.hh"
#include "GateDoIModels.hh"
#include "GateGridDiscretization.hh"
#include "GateLocalMultipleRejection.hh"
#include "GateLocalTimeResolution.hh"

#ifdef GATE_USE_OPTICAL
#include "GateOpticalAdder.hh"
#endif
#include "GateSystemFilter.hh"

GateDigitizerMessenger::GateDigitizerMessenger(GateDigitizer* itsDigitizer)
:GateListMessenger(itsDigitizer)
{
	G4cout<<"GateDigitizerMessenger constr"<<G4endl;
  pInsertCmd->SetCandidates(DumpMap());

  G4String cmdName;

  cmdName = GetDirectoryName()+"setInputCollection";
  SetInputNameCmd = new G4UIcmdWithAString(cmdName,this);
  SetInputNameCmd->SetGuidance("Set the name of the input pulse channel");
  SetInputNameCmd->SetParameterName("Name",false);
}




GateDigitizerMessenger::~GateDigitizerMessenger()
{
  delete SetInputNameCmd;
}




void GateDigitizerMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
	G4cout<<"GateDigitizerMessenger SetNewValue "<< newValue <<G4endl;

  if (command == SetInputNameCmd)
    { GetDigitizer()->SetInputName(newValue); }
  else
    GateListMessenger::SetNewValue(command,newValue);
}




const G4String& GateDigitizerMessenger::DumpMap()
{
   static G4String theList = "readout pileup thresholder energyThresholder localEnergyThresholder DoImodel upholder blurring localBlurring localTimeDelay localEfficiency energyEfficiency noise discretizer buffer transferEfficiency crosstalk lightYield quantumEfficiency intrinsicResolutionBlurring sigmoidalThresholder calibration spblurring sp3Dlocalblurring adder adderLocal adderCompton adderComptPhotIdeal adderComptPhotIdealLocal localClustering  clustering deadtime crystalblurring timeResolution localTimeResolution opticaladder systemFilter gridDiscretization  localMultipleRejection";
  return theList;
}



void GateDigitizerMessenger::DoInsertion(const G4String& childTypeName)
{

  if (GetNewInsertionBaseName().empty())
    SetNewInsertionBaseName(childTypeName);

  AvoidNameConflicts();

  GateVDigitizerModule* newDM=0;
  //G4cout<<"Input name "<<GetDigitizer()->GetInputName()<<G4endl; ;
  G4String newInsertionName = GetDigitizer()->MakeElementName(GetNewInsertionBaseName());

  G4String collName=GetDigitizer()->m_digitizerName;

  if (childTypeName=="readout")
  {
	  newDM = new GateReadout( "GateReadout", GetDigitizer() );
	  GetDigitizer()->AddNewModule(newDM);
	  G4DigiManager::GetDMpointer()->AddNewModule(newDM);
  }
   // newDM = new GateReadout(GetDigitizer(),newInsertionName);
/*  else if (childTypeName=="pileup")
    newDM = new GatePileup(GetDigitizer(),newInsertionName);
  else if (childTypeName=="discretizer")
    newDM = new GateDiscretizer(GetDigitizer(),newInsertionName);
  else if (childTypeName=="thresholder")
    newDM = new GateThresholder(GetDigitizer(),newInsertionName,50.*keV);
  else if (childTypeName=="energyThresholder")
    newDM = new GateEnergyThresholder(GetDigitizer(),newInsertionName,50.*keV);
  else if (childTypeName=="localEnergyThresholder")
    newDM = new GateLocalEnergyThresholder(GetDigitizer(),newInsertionName);
  else if (childTypeName=="DoImodel")
    //newDM = new GateDoIModels(GetDigitizer(),newInsertionName,G4ThreeVector(0.,0.,1.));
    newDM = new GateDoIModels(GetDigitizer(),newInsertionName);
  else if (childTypeName=="upholder")
    newDM = new GateUpholder(GetDigitizer(),newInsertionName,150.*keV);
  else if (childTypeName=="deadtime")
    newDM = new GateDeadTime(GetDigitizer(),newInsertionName);
  else if (childTypeName=="blurring")
    newDM = new GateBlurring(GetDigitizer(),newInsertionName);
  else if (childTypeName=="localBlurring")
    newDM = new GateLocalBlurring(GetDigitizer(),newInsertionName);
  else if (childTypeName=="localTimeDelay")
    newDM = new GateLocalTimeDelay(GetDigitizer(),newInsertionName);
  else if (childTypeName=="transferEfficiency")
    newDM = GateTransferEfficiency::GetInstance(GetDigitizer(),newInsertionName);
  else if (childTypeName=="lightYield")
    newDM = GateLightYield::GetInstance(GetDigitizer(),newInsertionName);
  else if (childTypeName=="crosstalk")
    newDM = GateCrosstalk::GetInstance(GetDigitizer(),newInsertionName,0.,0.);
  else if (childTypeName=="quantumEfficiency")
    newDM = GateQuantumEfficiency::GetInstance(GetDigitizer(),newInsertionName);
  else if (childTypeName=="intrinsicResolutionBlurring")
    newDM = new GateBlurringWithIntrinsicResolution(GetDigitizer(),newInsertionName);
  else if (childTypeName=="sigmoidalThresholder")
    newDM = new GateSigmoidalThresholder(GetDigitizer(),newInsertionName,0.,1.,0.5);
  else if (childTypeName=="calibration")
    newDM = new GateCalibration(GetDigitizer(),newInsertionName);
  else if (childTypeName=="spblurring")
    newDM = new GateSpblurring(GetDigitizer(),newInsertionName,0.1);
  else if (childTypeName=="sp3Dlocalblurring")
    newDM = new GateCC3DlocalSpblurring(GetDigitizer(),newInsertionName);
  */else if (childTypeName=="adder")
  {
	  newDM = new GateAdder( "GateAdder", GetDigitizer() );
	  GetDigitizer()->AddNewModule(newDM);
	  G4DigiManager::GetDMpointer()->AddNewModule(newDM);
  }
  /*  else if (childTypeName=="adderLocal")
    newDM = new GatePulseAdderLocal(GetDigitizer(),newInsertionName);
  else if (childTypeName=="adderCompton")
    newDM = new GatePulseAdderCompton(GetDigitizer(),newInsertionName);
  else if (childTypeName=="adderComptPhotIdeal")
    newDM = new GatePulseAdderComptPhotIdeal(GetDigitizer(),newInsertionName);
  else if (childTypeName=="adderComptPhotIdealLocal")
    newDM = new GatePulseAdderComptPhotIdealLocal(GetDigitizer(),newInsertionName);
  else if (childTypeName=="localClustering")
    newDM = new GateLocalClustering(GetDigitizer(),newInsertionName);
  else if (childTypeName=="clustering")
    newDM = new GateClustering(GetDigitizer(),newInsertionName);
  else if (childTypeName=="crystalblurring")
    newDM = new GateCrystalBlurring(GetDigitizer(),newInsertionName,-1.,-1.,1.,-1.*keV);
  else if (childTypeName=="localEfficiency")
    newDM = new GateLocalEfficiency(GetDigitizer(),newInsertionName);
  else if (childTypeName=="energyEfficiency")
    newDM = new GateEnergyEfficiency(GetDigitizer(),newInsertionName);
  else if (childTypeName=="noise")
    newDM = new GateNoise(GetDigitizer(),newInsertionName);
  else if (childTypeName=="buffer")
    newDM = new GateBuffer(GetDigitizer(),newInsertionName);
  else if (childTypeName=="timeResolution")
    newDM = new GateTemporalResolution(GetDigitizer(),newInsertionName,0. * ns);
  else if (childTypeName=="localTimeResolution")
    newDM = new GateLocalTimeResolution(GetDigitizer(),newInsertionName);
  else if (childTypeName=="systemFilter")
     newDM = new GateSystemFilter(GetDigitizer(),newInsertionName);
 // else if (childTypeName=="stripSpDiscretization")
  //   newDM = new GateStripSpatialDiscretization(GetDigitizer(),newInsertionName);
else if (childTypeName=="gridDiscretization")
     newDM = new GateGridDiscretization(GetDigitizer(),newInsertionName);
else if (childTypeName=="localMultipleRejection")
     newDM = new GateLocalMultipleRejection(GetDigitizer(),newInsertionName);
#ifdef GATE_USE_OPTICAL
  else if (childTypeName=="opticaladder")
    newDM = new GateOpticalAdder(GetDigitizer(), newInsertionName);
#endif
*/
  else {
    G4cout << "Pulse-processor type name '" << childTypeName << "' was not recognised --> insertion request must be ignored!\n";
    return;
  }

  //GetDigitizer()->InsertProcessor(newDM);

  SetNewInsertionBaseName("");
}


G4bool GateDigitizerMessenger::CheckNameConflict(const G4String& name)
{
  // Check whether an object with the same name already exists in the list
  return ( GetListManager()->FindElement( GetListManager()->GetObjectName() + "/" + name ) != 0 ) ;
}






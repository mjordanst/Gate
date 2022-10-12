/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

//GND:ClassToRemove

#include "GateCoincidenceDigiOld.hh"

#include "G4UnitsTable.hh"

#include "GatePulse.hh"
#include "GateCoincidencePulse.hh"

#include <iomanip>
#include <fstream>


std::vector<G4bool> GateCoincidenceDigiOld::m_coincidenceASCIIMask;
G4bool                GateCoincidenceDigiOld::m_coincidenceASCIIMaskDefault;

G4Allocator<GateCoincidenceDigiOld> GateCoincidenceDigiOldAllocator;



GateCoincidenceDigiOld::GateCoincidenceDigiOld()
{
  pulseVector[0] = GatePulse();
  pulseVector[1] = GatePulse();
}



GateCoincidenceDigiOld::GateCoincidenceDigiOld(GateCoincidencePulse* coincidencePulse)
{
  pulseVector[0] = (*coincidencePulse)[0];
  pulseVector[1] = (*coincidencePulse)[1];
}


GateCoincidenceDigiOld::GateCoincidenceDigiOld(const GateCoincidencePulse& coincidencePulse)
{
  pulseVector[0] = coincidencePulse[0];
  pulseVector[1] = coincidencePulse[1];
}


void GateCoincidenceDigiOld::Draw()
{;}





void GateCoincidenceDigiOld::Print()
{

  G4cout << this << Gateendl;

}



std::ostream& operator<<(std::ostream& flux, GateCoincidenceDigiOld& digi)
{
  flux    << "GateCoincidenceDigiOld("
	  << digi.pulseVector[0] << Gateendl
	  << digi.pulseVector[1] << Gateendl
      	  << ")\n";

  return flux;
}

std::ofstream& operator<<(std::ofstream& flux, GateCoincidenceDigiOld* digi)
{
  GatePulse pulse;
  for (G4int iP=0; iP<2; iP++) {
    pulse = digi->GetPulse(iP);
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(0) ) flux << " " << std::setw(7) << pulse.GetRunID();
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(1) ) flux << " " << std::setw(7) << pulse.GetEventID();
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(2) ) flux << " " << std::setw(5) << pulse.GetSourceID();
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(3) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setprecision(3)  << pulse.GetSourcePosition().x()/mm;
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(4) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setprecision(3)  << pulse.GetSourcePosition().y()/mm;
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(5) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setprecision(3)  << pulse.GetSourcePosition().z()/mm;
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(6) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setprecision(23) << pulse.GetTime()/s;
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(7) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setprecision(3)  << pulse.GetEnergy()/MeV;
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(8) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setprecision(3)  << pulse.GetGlobalPos().x()/mm;
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(9) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setprecision(3)  << pulse.GetGlobalPos().y()/mm;
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(10) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setprecision(3)  << pulse.GetGlobalPos().z()/mm;
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(11) ) flux << " " << std::setw(5) << pulse.GetOutputVolumeID();
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(12) ) flux << " " << std::setw(5) << pulse.GetNPhantomCompton();
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(13) ) flux << " " << std::setw(5) << pulse.GetNCrystalCompton();
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(14) ) flux << " " << std::setw(5) << pulse.GetNPhantomRayleigh();
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(15) ) flux << " " << std::setw(5) << pulse.GetNCrystalRayleigh();
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(16) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setprecision(3)  << pulse.GetScannerPos().z()/mm;
    if ( GateCoincidenceDigiOld::GetCoincidenceASCIIMask(17) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setprecision(3)  << pulse.GetScannerRotAngle()/deg;;
  }
  flux << Gateendl;

  return flux;
}



void GateCoincidenceDigiOld::SetCoincidenceASCIIMask(G4bool newValue)
{
  m_coincidenceASCIIMaskDefault = newValue;
  for (G4int iMask=0; ((unsigned int) iMask)<m_coincidenceASCIIMask.size(); iMask++) {
    m_coincidenceASCIIMask[iMask] = newValue;
  }
}


void GateCoincidenceDigiOld::SetCoincidenceASCIIMask(std::vector<G4bool> newMask)
{
  m_coincidenceASCIIMask = newMask;
}

G4bool GateCoincidenceDigiOld::GetCoincidenceASCIIMask(G4int index)
{
  G4bool mask = m_coincidenceASCIIMaskDefault;
  if ((index >=0 ) && (((unsigned int) index) < m_coincidenceASCIIMask.size())) mask = m_coincidenceASCIIMask[index];
  return mask;
}

std::vector<G4bool> GateCoincidenceDigiOld::GetCoincidenceASCIIMask()
{
  return m_coincidenceASCIIMask;
}

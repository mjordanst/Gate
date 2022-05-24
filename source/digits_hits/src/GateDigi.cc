/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

#include "GateDigi.hh"
#include "G4UnitsTable.hh"
#include "GatePulse.hh"
#include <iomanip>



G4Allocator<GateDigi> GateDigiAllocator;




GateDigi::GateDigi():
	  m_runID(-1),
      m_eventID(-1),
      m_sourceID(-1),
      m_time(0),
      m_energy(0),
	  m_max_energy(0),
      m_nPhantomCompton(-1),
      m_nPhantomRayleigh(-1),
      #ifdef GATE_USE_OPTICAL
      m_optical(false),
      #endif
      m_energyError(0.0),
      m_globalPosError(0.0),
      m_localPosError(0.0)
{
}

void GateDigi::Draw()
{;}





void GateDigi::Print()
{

  G4cout << this << Gateendl;

}



std::ostream& operator<<(std::ostream& flux, const GateDigi& digi)
{
  flux    << "GateDigi(\n"
	  //<< digi.m_pulse
      	  << ")\n";

  return flux;
}

std::ofstream& operator<<(std::ofstream& flux, GateDigi* digi)
{
 /* if ( GateDigi::GetSingleASCIIMask(0) ) flux << " " << std::setw(7) << digi->GetRunID();
  if ( GateDigi::GetSingleASCIIMask(1) ) flux << " " << std::setw(7) << digi->GetEventID();
  if ( GateDigi::GetSingleASCIIMask(2) ) flux << " " << std::setw(5) << digi->GetSourceID();
  if ( GateDigi::GetSingleASCIIMask(3) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3) << digi->GetSourcePosition().x()/mm;
  if ( GateDigi::GetSingleASCIIMask(4) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3) << digi->GetSourcePosition().y()/mm;
  if ( GateDigi::GetSingleASCIIMask(5) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3) << digi->GetSourcePosition().z()/mm;
  if ( GateDigi::GetSingleASCIIMask(6) ) flux << " " << std::setw(5) << digi->GetOutputVolumeID();
  if ( GateDigi::GetSingleASCIIMask(7) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(30) << std::setprecision(23) << digi->GetTime()/s;
  if ( GateDigi::GetSingleASCIIMask(8) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3)  << digi->GetEnergy()/MeV;
  if ( GateDigi::GetSingleASCIIMask(9) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3)  << digi->GetGlobalPos().x()/mm;
  if ( GateDigi::GetSingleASCIIMask(10) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3)  << digi->GetGlobalPos().y()/mm;
  if ( GateDigi::GetSingleASCIIMask(11) ) flux << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3)  << digi->GetGlobalPos().z()/mm;
  if ( GateDigi::GetSingleASCIIMask(12) ) flux << " " << std::setw(4) << digi->GetNPhantomCompton();
  if ( GateDigi::GetSingleASCIIMask(13) ) flux << " " << std::setw(4) << digi->GetNCrystalCompton();
  if ( GateDigi::GetSingleASCIIMask(14) ) flux << " " << std::setw(4) << digi->GetNPhantomRayleigh();
  if ( GateDigi::GetSingleASCIIMask(15) ) flux << " " << std::setw(4) << digi->GetNCrystalRayleigh();
  if ( GateDigi::GetSingleASCIIMask(16) ) flux << " " << digi->GetComptonVolumeName();
  if ( GateDigi::GetSingleASCIIMask(17) ) flux << " " << digi->GetRayleighVolumeName();
  flux << Gateendl;
*/
  return flux;
}


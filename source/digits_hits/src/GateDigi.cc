/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

#include "GateDigi.hh"
#include "G4UnitsTable.hh"

#include <iomanip>

std::vector<G4bool> GateDigi::m_singleASCIIMask;
G4bool                GateDigi::m_singleASCIIMaskDefault;

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
      flux    << "\t----GateDigi----"     	      	      	      	      	      	      	      	      	      	               << Gateendl
              << "\t\t" << "Run           " << digi.m_runID                      	         	      	      	      	       << Gateendl
              << "\t\t" << "Event         " << digi.m_eventID   	      	      	      	              	      	      	       << Gateendl
              << "\t\t" << "Src           " << digi.m_sourceID << " [ " << G4BestUnit(digi.m_sourcePosition,"Length")     << "]\n"
              << "\t\t" << "Time          " << G4BestUnit(digi.m_time,"Time")      	      	      	      	      	       << Gateendl
              << "\t\t" << "Energy        " << G4BestUnit(digi.m_energy,"Energy")          	      	      	      	       << Gateendl
              << "\t\t" << "localPos      [ " << G4BestUnit(digi.m_localPos,"Length")        	      	      	      	<< "]\n"
              << "\t\t" << "globalPos     [ " << G4BestUnit(digi.m_globalPos,"Length")   	      	      	      	      	<< "]\n"
              << "\t\t" << "           -> ( R="   << G4BestUnit(digi.m_globalPos.perp(),"Length")     << ", "
              << "phi="   << digi.m_globalPos.phi()/degree       	      	   << " deg,"
              << "z="     << G4BestUnit(digi.m_globalPos.z(),"Length")     	     	      	<< ")\n"
              << "\t\t" << "VolumeID      " << digi.m_volumeID      	      	      	      	      	      	               << Gateendl
              << "\t\t" << "OutputID      " << digi.m_outputVolumeID     	      	      	      	      	      	      	       << Gateendl
              << "\t\t" << "#Compton      " << digi.m_nPhantomCompton      	      	      	      	      	      	       << Gateendl
              << "\t\t" << "#Rayleigh     " << digi.m_nPhantomRayleigh      	      	      	      	      	      	       << Gateendl
              << "\t\t" << "scannerPos    [ " << G4BestUnit(digi.m_scannerPos,"Length")        	      	      	      	<< "]\n" << Gateendl
              << "\t\t" << "scannerRotAngle " << digi.m_scannerRotAngle/degree           	      	      	      	     << " deg\n" << Gateendl
              << "\t-----------------\n";

  return flux;
}

std::ofstream& operator<<(std::ofstream& flux, GateDigi* digi)
{
  flux << " " << std::setw(7) << digi->GetRunID()
    << " " << std::setw(7) << digi->GetEventID()
    << " " << std::setw(5) << digi->GetSourceID()
    << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3) << digi->GetSourcePosition().x()/mm
    << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3) << digi->GetSourcePosition().y()/mm
    << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3) << digi->GetSourcePosition().z()/mm
    << " " << std::setw(5) << digi->GetOutputVolumeID()
    << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(30) << std::setprecision(23) << digi->GetTime()/s
    << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3)  << digi->GetEnergy()/MeV
    << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3)  << digi->GetGlobalPos().x()/mm
    << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3)  << digi->GetGlobalPos().y()/mm
    << " " << std::resetiosflags(std::ios::floatfield) << std::setiosflags(std::ios::scientific) << std::setw(10) << std::setprecision(3)  << digi->GetGlobalPos().z()/mm
    << " " << std::setw(4) << digi->GetNPhantomCompton()
    << " " << std::setw(4) << digi->GetNCrystalCompton()
    << " " << std::setw(4) << digi->GetNPhantomRayleigh()
    << " " << std::setw(4) << digi->GetNCrystalRayleigh()
    << " " << digi->GetComptonVolumeName()
    << " " << digi->GetRayleighVolumeName()
    << Gateendl;

  return flux;
}


void GateDigi::SetSingleASCIIMask(G4bool newValue)
{
	G4cout<<"GateDigi::SetSingleASCIIMask1"<<G4endl;
  m_singleASCIIMaskDefault = newValue;
  for (G4int iMask=0; ((unsigned int)iMask)<m_singleASCIIMask.size(); iMask++) {
    m_singleASCIIMask[iMask] = newValue;
  }
}


void GateDigi::SetSingleASCIIMask(std::vector<G4bool> newMask)
{
	G4cout<<"GateDigi::SetSingleASCIIMask2"<<G4endl;
  m_singleASCIIMask = newMask;
}

G4bool GateDigi::GetSingleASCIIMask(G4int index)
{
  G4bool mask = m_singleASCIIMaskDefault;
  if ((index >=0 ) && (((unsigned int)index) < m_singleASCIIMask.size())) mask = m_singleASCIIMask[index];
  return mask;
}

std::vector<G4bool> GateDigi::GetSingleASCIIMask()
{
  return m_singleASCIIMask;
}






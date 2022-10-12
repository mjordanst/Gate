/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/
//GND:ClassToRemove

#ifndef GateCoincidenceDigiOld_h
#define GateCoincidenceDigiOld_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"


#include "GateCoincidencePulse.hh"


class GateCoincidenceDigiOld : public G4VDigi
{

public:

  GateCoincidenceDigiOld();
  GateCoincidenceDigiOld(GateCoincidencePulse* coincidencePulse);
  GateCoincidenceDigiOld(const GateCoincidencePulse& coincidencePulse);
  virtual inline ~GateCoincidenceDigiOld() {}

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  void Draw();
  void Print();

  //
  //printing methods
  //
  friend std::ostream& operator<<(std::ostream&, GateCoincidenceDigiOld&);

  friend std::ofstream& operator<<(std::ofstream&, GateCoincidenceDigiOld*);

public:

      inline GatePulse& GetPulse(G4int i)                     { return pulseVector[i]; }
      inline void SetPulse(G4int i, const GatePulse& value)   { pulseVector[i] = value; }

private:

      GatePulse pulseVector[2];

public:
  static void SetCoincidenceASCIIMask(G4bool);
  static void SetCoincidenceASCIIMask(std::vector<G4bool>);
  static std::vector<G4bool> GetCoincidenceASCIIMask();
  static G4bool GetCoincidenceASCIIMask(G4int index);

protected:
  static std::vector<G4bool> m_coincidenceASCIIMask;
  static G4bool                m_coincidenceASCIIMaskDefault;
};





typedef G4TDigiCollection<GateCoincidenceDigiOld> GateCoincidenceDigiOldCollection;

extern G4Allocator<GateCoincidenceDigiOld> GateCoincidenceDigiOldAllocator;





inline void* GateCoincidenceDigiOld::operator new(size_t)
{
  void* aDigi;
  aDigi = (void*) GateCoincidenceDigiOldAllocator.MallocSingle();
  return aDigi;
}





inline void GateCoincidenceDigiOld::operator delete(void* aDigi)
{
  GateCoincidenceDigiOldAllocator.FreeSingle((GateCoincidenceDigiOld*) aDigi);
}

#endif

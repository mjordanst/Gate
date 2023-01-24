/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/
//GND:ClassToRemove

#ifndef GatePileupOld_h
#define GatePileupOld_h 1

#include "globals.hh"
#include <iostream>
#include <vector>
#include "G4ThreeVector.hh"

#include "GateVPulseProcessor.hh"

class GatePileupOldMessenger;
class GateOutputVolumeID;

/*! \class  GatePileupOld
    \brief  Pulse-processor modelling a PileupOld (maximum energy wins) of a crystal-block

    - The PileupOld is parameterised by its 'depth': pulses will be summed up if their volume IDs
      are identical up to this depth. For instance, the default depth is 1: this means that
      pulses will be considered as taking place in a same block if the first two figures
      of their volume IDs are identical
    - A second parameter is added : the width of the pilup window

    - The class is largely inspired from the GateReadout class,
      but is aimed to work by time and not by event.

      \sa GateVPulseProcessor
*/
class GatePileupOld : public GateVPulseProcessor
{
  public:

    //! Constructs a new PileupOld attached to a GateDigitizerOld
    GatePileupOld(GatePulseProcessorChain* itsChain,const G4String& itsName) ;

    //! Destructor
    virtual ~GatePileupOld() ;

    //! Implementation of the pure virtual method declared by the base class GateClockDependent
    //! print-out the attributes specific of the PileupOld
    virtual void DescribeMyself(size_t indent);

    //! Returns the depth of the PileupOld
    inline G4int GetDepth() const  	      	{ return m_depth; }

    //! Set the depth of the PileupOld
    inline void  SetDepth(G4int aDepth)         { m_depth = aDepth; }

    //! Returns the time of the PileupOld
    inline G4double GetPileupOld() const  	      	{ return m_PileupOld; }

    //! Set the time of the PileupOld
    inline void  SetPileupOld(G4double aPileupOld)         { m_PileupOld = aPileupOld; }

  protected:
    //! Implementation of the pure virtual method declared by the base class GateVPulseProcessor
    //! This methods processes one input-pulse
    //! It is is called by ProcessPulseList() for each of the input pulses
    //! The result of the pulse-processing is incorporated into the output pulse-list
    virtual GatePulseList* ProcessPulseList(const GatePulseList* inputPulseList);
    virtual void ProcessOnePulse(const GatePulse* inputPulse,GatePulseList& outputPulseList);

  private:
    //! The default is the one parameter that defines how a PileupOld works:
    //! pulses will be summed up if their volume IDs are identical up to this depth.
    //! For instance, the default depth is 1: this means that pulses will be considered as
    //! taking place in a same block if the first two figures of their volume IDs are identical
    G4int m_depth;
    G4double m_PileupOld;
    GatePulseList m_waiting;

    GatePileupOldMessenger *m_messenger;	  //!< Messenger for this PileupOld
};


#endif

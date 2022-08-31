/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/


#ifndef GateReadoutOld_h
#define GateReadoutOld_h 1

#include "globals.hh"
#include <iostream>
#include <vector>
#include "G4ThreeVector.hh"

#include "GateVPulseProcessor.hh"
#include "GateVSystem.hh"
#include "GateArrayComponent.hh"
#include "GateObjectStore.hh"

//#define ReadoutOld_POLICY_WINNER 0
//#define ReadoutOld_POLICY_CENTROID 1

class GateReadoutOldMessenger;
class GateOutputVolumeID;

/*! \class  GateReadoutOld
    \brief  Pulse-processor modelling a simple PMT ReadoutOld (maximum energy wins) of a crystal-block

    - GateReadoutOld - by Daniel.Strul@iphe.unil.ch

    - The ReadoutOld is parameterised by its 'depth': pulses will be summed up if their volume IDs
      are identical up to this depth. For instance, the default depth is 1: this means that
      pulses will be considered as taking place in a same block if the first two figures
      of their volume IDs are identical

      \sa GateVPulseProcessor
*/
class GateReadoutOld : public GateVPulseProcessor
{
  public:

    //! Constructs a new ReadoutOld attached to a GateDigitizerOld
    GateReadoutOld(GatePulseProcessorChain* itsChain,const G4String& itsName) ;

    //! Destructor
    virtual ~GateReadoutOld() ;

    //! Implementation of the pure virtual method declared by the base class GateClockDependent
    //! print-out the attributes specific of the ReadoutOld
    virtual void DescribeMyself(size_t indent);

    //! Returns the depth of the ReadoutOld
    inline G4int GetDepth() const  	      	{ return m_depth; }

    //! Set the depth of the ReadoutOld
    inline void  SetDepth(G4int aDepth)         { m_depth = aDepth; }

    //! Set the policy of the ReadoutOld
    inline void SetPolicy(const G4String& aPolicy)  { m_policy = aPolicy; };
    inline G4String GetPolicy() const  	      	{ return m_policy; }

    //! Set the volume for the ReadoutOld
    inline void SetVolumeName(const G4String& aName) { m_volumeName = aName; };
    inline G4String GetVolumeName() const  	      	{ return m_volumeName; }

    //! Set the volume for the ReadoutOld even for centroid policy
     inline void ForceDepthCentroid(const G4bool& value) { m_IsForcedDepthCentroid = value; };
     inline G4bool IsDepthForcedCentroid() const  	      	{ return m_IsForcedDepthCentroid; }

    //! Set how the resulting positions should be defined
    inline void SetResultingXY(const G4String& aString) { m_resultingXY= aString;};
    inline G4String GetResultingXY() const  	      	{ return m_resultingXY; };

    inline void SetResultingZ(const G4String& aString){m_resultingZ= aString;};
    inline G4String GetResultingZ() const  	      	{ return m_resultingZ; };


    void SetReadoutOldParameters();


  protected:
    //! Implementation of the pure virtual method declared by the base class GateVPulseProcessor
    //! This methods processes one input-pulse
    //! It is is called by ProcessPulseList() for each of the input pulses
    //! The result of the pulse-processing is incorporated into the output pulse-list
    void ProcessOnePulse(const GatePulse* inputPulse,GatePulseList& outputPulseList);
    //! Overload the virtual (not pure) method of GateVPulseProcessor
    GatePulseList* ProcessPulseList(const GatePulseList* inputPulseList);



  private:
    //! The default is the one parameter that defines how a ReadoutOld works:
    //! pulses will be summed up if their volume IDs are identical up to this depth.
    //! For instance, the default depth is 1: this means that pulses will be considered as
    //! taking place in a same block if the first two figures of their volume IDs are identical
    G4int m_depth;

    //! S. Stute: add an option to choose the policy of the ReadoutOld (using two define integers; see the beginning of this file)
    //G4int m_policy;
    G4String m_policy;
    GateVSystem* m_system;
    G4int m_nbCrystalsX;
    G4int m_nbCrystalsY;
    G4int m_nbCrystalsZ;
    G4int m_nbCrystalsXY;
    G4int m_systemDepth;
    G4int m_crystalDepth;
    GateArrayComponent* m_crystalComponent;

    G4String m_volumeName;
    G4bool m_IsForcedDepthCentroid;

    G4String m_resultingXY;
    G4String m_resultingZ;
    G4bool   m_IsFirstEntrance;//Entrance

    std::vector<int> numberOfComponentForLevel; //!< Table of number of element for each geometric level
    G4int numberOfHigherLevels ;  //!< number of geometric level higher than the one chosen by the user
    G4int numberOfLowerLevels ;  //!< number of geometric level higher than the one chosen by the user
    GateReadoutOldMessenger *m_messenger;	  //!< Messenger for this
};


#endif

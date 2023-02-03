/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/


#include "GateListManager.hh"
#include "GateNamedObject.hh"
#include "GateDetectorConstruction.hh"
#include "GateTools.hh"

//--------------------------------------------------------------------------------------
GateListManager::GateListManager(const G4String& itsName,
				 const G4String& itsElementTypeName,
    		    	  	 G4bool canBeDisabled,
				 G4bool acceptNewElements)
  : GateClockDependent(itsName,canBeDisabled),
    mElementTypeName(itsElementTypeName),
    bAcceptNewElements(acceptNewElements)
{
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
GateListManager::~GateListManager()
{  
  for (GateListOfNamedObject::iterator it = theListOfNamedObject.begin(); it != theListOfNamedObject.end(); )
    {
      //delete (*it);
      it = theListOfNamedObject.erase(it);
    }
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
GateNamedObject* GateListManager::FindElement(const G4String& name)
{


	 //G4cout<<"GateListManager::FindElement "<<name<<G4endl;
	 //G4cout<<size()<<G4endl;
  for (GateListOfNamedObject::iterator it = theListOfNamedObject.begin(); it != theListOfNamedObject.end(); it++)
  {
//	 G4cout<<"GateListManager::FindElement name: "<<(*it)->GetObjectName() <<" "<<name<<G4endl;
	  if (name.compare((*it)->GetObjectName()) == 0)
	  {
	//	  G4cout<<"found "<<G4endl;
	//	  G4cout<<(*it)->GetObjectName()<<G4endl;
		  return *it;
	  }
  }
 //G4cout<<"No named objects"<<G4endl;
  return 0;
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
//void GateListManager::ListElements(size_t indent) const
void GateListManager::TheListElements(size_t indent) const
{
  G4cout << GateTools::Indent(indent) << "Nb of elements:     " << size() << Gateendl;
  for (GateListOfNamedObject::const_iterator it = theListOfNamedObject.begin(); it != theListOfNamedObject.end(); it++)
    G4cout << GateTools::Indent(indent+2) << '\'' << (*it)->GetObjectName() << '\'' << Gateendl;
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Method overloading GateClockDependent::Describe()
// Print-out a description of the object
void GateListManager::Describe(size_t indent)
{
  GateClockDependent::Describe(indent);
  TheListElements(indent);
}
//--------------------------------------------------------------------------------------

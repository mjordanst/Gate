
/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

/*!
  \class  GateSpatialResolution
  \brief  Digitizer Module for simulating a Gaussian blurring on the position.

  Includes functionalities from:
  	  GateSpblurring
	  GateCC3DlocalSpblurring
	  GateDoIModels

  Previous authors: Steven.Staelens@rug.ac.be(?), AE

  - modified by Adrien Paillet 11/2022
  	  This blurring has been validated up to a given FWHM of 10mm.
  	  At higher FWHM, the number of "relocated" digis is no longer negligible. The blurring effect is then so compensated that resolution will improve compared to lower values of FWHM.

*/

#include "GateSpatialResolution.hh"
#include "GateSpatialResolutionMessenger.hh"
#include "GateDigi.hh"

#include "GateDigitizerMgr.hh"
#include "GateObjectStore.hh"
#include "GateConstants.hh"


#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"

GateSpatialResolution::GateSpatialResolution(GateSinglesDigitizer *digitizer)
  :GateVDigitizerModule("spatialResolution","digitizerMgr/"+digitizer->GetSD()->GetName()+"/SinglesDigitizer/"+digitizer->m_digitizerName+"/spatialResolution",digitizer,digitizer->GetSD()),
   m_fwhm(0),
   m_fwhmX(0),
   m_fwhmY(0),
   m_fwhmZ(0),
   m_IsConfined(false),
   m_GPnew(0,0,0),
   m_PV(0),
   m_Navigator(0),
   m_Touchable(0),
   m_systemDepth(-1),
   m_outputDigi(0),
   m_OutputDigiCollection(0),
   m_digitizer(digitizer)
 {
	G4String colName = digitizer->GetOutputName() ;
	collectionName.push_back(colName);
	m_Messenger = new GateSpatialResolutionMessenger(this);
}


GateSpatialResolution::~GateSpatialResolution()
{
  delete m_Messenger;

}


void GateSpatialResolution::Digitize()
{
	if( m_fwhm!=0 && (m_fwhmX!=0 || m_fwhmY!=0 || m_fwhmZ!=0 ) )
		{
			GateError("***ERROR*** Spatial Resolution is ambiguous: you can set unique /fwhm for 3 axis OR set /fhwmX, /fhwmY, /fhwmZ!");
		}

	G4double fwhmX;
	G4double fwhmY;
	G4double fwhmZ;

	if (m_fwhmX==0 && m_fwhmY==0 && m_fwhmZ==0 )
	{
		fwhmX=m_fwhm;
		fwhmY=m_fwhm;
		fwhmZ=m_fwhm;
	}
	else
	{
		fwhmX=m_fwhmX;
		fwhmY=m_fwhmY;
		fwhmZ=m_fwhmZ;
	}


	GateVSystem* m_system = this->GetDigitizer()->GetSystem();
		 if (m_system==NULL) G4Exception( "GateSpatialResolution::Digitize", "Digitize", FatalException,
				 "Failed to get the system corresponding to that digitizer. Abort.\n");

	m_systemDepth = m_system->GetTreeDepth();


	G4String digitizerName = m_digitizer->m_digitizerName;
	G4String outputCollName = m_digitizer-> GetOutputName();

	m_OutputDigiCollection = new GateDigiCollection(GetName(),outputCollName); // to create the Digi Collection

	G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();

	GateDigiCollection* IDC = 0;
	IDC = (GateDigiCollection*) (DigiMan->GetDigiCollection(m_DCID));

	GateDigi* inputDigi = new GateDigi();

	//Getting world Volume
	// Do not use from TransportationManager as it is not recommended
	G4Navigator *navigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
	G4VPhysicalVolume *WorldVolume = navigator->GetWorldVolume();
	m_Navigator = new G4Navigator();
	m_Navigator->SetWorldVolume(WorldVolume);

	//GateDigi* tmpDigi;

  if (IDC)
     {
	  G4int n_digi = IDC->entries();

	  //loop over input digits
	  for (G4int i=0;i<n_digi;i++)
	  {
		  inputDigi=(*IDC)[i];
		  m_outputDigi = new GateDigi(*inputDigi);


		  G4ThreeVector P = inputDigi->GetVolumeID().MoveToBottomVolumeFrame(inputDigi->GetGlobalPos()); //TC

		  G4double Px = P.x();
		  G4double Py = P.y();
		  G4double Pz = P.z();
		  G4double PxNew = G4RandGauss::shoot(Px,fwhmX/GateConstants::fwhm_to_sigma);
		  G4double PyNew = G4RandGauss::shoot(Py,fwhmY/GateConstants::fwhm_to_sigma);
		  G4double PzNew = G4RandGauss::shoot(Pz,fwhmZ/GateConstants::fwhm_to_sigma); //TC


		   UpdatePos(PxNew,PyNew,PzNew);
		   //LocateGlobalPointAndSetup returns the lowest physical volume that contains the given coordinates
		   //expected value is a crystal.
		   //this volume is recorded automatically in the touchable created after
		   m_PV = m_Navigator->LocateGlobalPointAndSetup(m_GPnew);
		   m_Touchable = m_Navigator->CreateTouchableHistoryHandle();

		   G4int hdepth = m_Touchable->GetHistoryDepth();

		   if (m_IsConfined)
		   {
			   LocateOutputDigi(inputDigi,PxNew,PyNew,PzNew);
		   }
		   else
		   {
		   if ( hdepth == m_systemDepth  )
		      {
		      // 	    G4cout << " blurred" << G4endl;
			   UpdateVolumeID();
		       }
		       else //pulse is out of any cristal : position must be re calculated
		            //the choice has been made to relocate at boundaries of crystal
		            //a better approach may be to associate to the nearest crystal
		       	   {
				      // 	    G4cout << "relocated blurred" << G4endl;
		    	   	   LocateOutputDigi(inputDigi,PxNew,PyNew,PzNew);
		       	   }
		   }
		  m_OutputDigiCollection->insert(m_outputDigi);

	  }
    }
  else
    {
  	  if (nVerboseLevel>1)
  	  	G4cout << "[GateSpatialResolution::Digitize]: input digi collection is null -> nothing to do\n\n";
  	    return;
    }
  StoreDigiCollection(m_OutputDigiCollection);

}


void GateSpatialResolution::UpdatePos(G4double PxNew,G4double PyNew,G4double PzNew)
{
	G4ThreeVector Pnew = G4ThreeVector(PxNew,PyNew,PzNew);
	m_outputDigi->SetLocalPos(Pnew);
	m_GPnew = m_outputDigi->GetVolumeID().MoveToAncestorVolumeFrame(m_outputDigi->GetLocalPos());
	m_outputDigi->SetGlobalPos(m_GPnew);

}

void GateSpatialResolution::LocateOutputDigi(GateDigi* inputDigi, G4double PxNew,G4double PyNew,G4double PzNew)
{

	G4double PxNewEp;
	G4double PyNewEp;
	G4double PzNewEp;

	 inputDigi->GetVolumeID().GetBottomCreator()->GetLogicalVolume()->GetSolid()->CalculateExtent(kXAxis, limits, at, Xmin, Xmax);
	 inputDigi->GetVolumeID().GetBottomCreator()->GetLogicalVolume()->GetSolid()->CalculateExtent(kYAxis, limits, at, Ymin, Ymax);
	 inputDigi->GetVolumeID().GetBottomCreator()->GetLogicalVolume()->GetSolid()->CalculateExtent(kZAxis, limits, at, Zmin, Zmax);
	 /*
	  inputDigi->GetVolumeID().GetCreator(m_depth+1)->GetLogicalVolume()->GetSolid()->CalculateExtent(kXAxis, limits, at, Xmin, Xmax);
	  inputDigi->GetVolumeID().GetCreator(m_depth+1)->GetLogicalVolume()->GetSolid()->CalculateExtent(kYAxis, limits, at, Ymin, Ymax);
	  inputDigi->GetVolumeID().GetCreator(m_depth+1)->GetLogicalVolume()->GetSolid()->CalculateExtent(kZAxis, limits, at, Zmin, Zmax);
	 */

	 G4double epsilon = 1e-9;
	 //add a small epsilon
	 //for recalculation of volumeID, if the position is exactly at the border -> doesn't know to which volume should put -> segFault
	  if(PxNew<Xmin)
	  {
		  PxNew=Xmin;
		  PxNewEp=Xmin+epsilon;
	  }
	  if(PyNew<Ymin)
	  {
		  PyNew=Ymin;
		  PyNewEp=Ymin+epsilon;
	  }
	  if(PzNew<Zmin)
	  {
		  PzNew=Zmin;
		  PzNewEp=Zmin+epsilon;
	  }
	  if(PxNew>Xmax)
	  {
		  PxNew=Xmax;
		  PxNewEp=Xmax-epsilon;
	  }
	  if(PyNew>Ymax)
	  {
		  PyNew=Ymax;
		  PyNewEp=Ymax-epsilon;
	  }
	  if(PzNew>Zmax)
	  {
		  PzNew=Zmax;
		  PzNewEp=Zmax-epsilon;
	  }

	  //Update position to find volume ID
	  UpdatePos(PxNewEp,PyNewEp,PzNewEp);
	  m_PV = m_Navigator->LocateGlobalPointAndSetup(m_GPnew);
	  m_Touchable = m_Navigator->CreateTouchableHistoryHandle();
	  UpdateVolumeID();

	  //Update position to save
	  UpdatePos(PxNew,PyNew,PzNew);
}


void GateSpatialResolution::UpdateVolumeID()
{

	for (G4int i=1;i<m_systemDepth;i++)
		{
		//G4cout<<i<<" "<<m_systemDepth-1-i<<G4endl;
		G4int CopyNo = m_Touchable->GetReplicaNumber(m_systemDepth-1-i);
		m_outputDigi->ChangeVolumeIDAndOutputVolumeIDValue(i,CopyNo);
		}


}

void GateSpatialResolution::DescribeMyself(size_t indent )
{
	if(m_fwhm)
	  G4cout << GateTools::Indent(indent) << "Spatial resolution : " << m_fwhm  << Gateendl;
	else
	  G4cout << GateTools::Indent(indent) << "Spatial resolution : " << m_fwhmX <<" "<< m_fwhmY<< " "<<m_fwhmZ<< Gateendl;
}

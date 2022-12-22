/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See LICENSE.md for further details
----------------------*/

//LF
//#include <strstream>
#include <sstream>
//LF
#include "GateUIterminal.hh"


G4int GateUIterminal::ReceiveG4cout(const G4String& coutString)
{
  if ( coutString == "G4PhysicalVolumeModel::Validate() called.\n" )
    return 0;
  if ( coutString == "  Volume of the same name and copy number (\"world_P\", copy 0) still exists and is being used.\n" )
    return 0;
  if ( coutString == "  Be warned that this does not necessarily guarantee it's the same\n" )
    return 0;
  if ( coutString == "  volume you originally specified in /vis/scene/add/.\n" )
    return 0;

  std::cout << coutString << std::flush;
  return 0;
}


G4int GateUIterminal::ReceiveG4cerr(const G4String& cerrString)
{
	std::cerr << "[G4-cerr] " <<  cerrString << std::flush;
	// Check if this error is 'command not found' (or related) to stop Gate
    bool isMacroError = false;
    std::string::size_type i = cerrString.find("***** COMMAND NOT FOUND <", 0);
    isMacroError = isMacroError || (i != std::string::npos);
    i = cerrString.find("***** Illegal application state <", 0);
    isMacroError = isMacroError || (i != std::string::npos);
    i = cerrString.find("***** Illegal parameter (", 0);
    isMacroError = isMacroError || (i != std::string::npos);
    i = cerrString.find("***** Can not open a macro file <", 0);
    isMacroError = isMacroError || (i != std::string::npos);
    i = cerrString.find("ERROR: Can not open a macro file <", 0);
    isMacroError = isMacroError || (i != std::string::npos);

    if (isMacroError) {
      std::cerr << "[Gate] Sorry, error in a macro command : abort.\n";
      std::cerr << cerrString<<G4endl;
      if (G4StrUtil::contains(cerrString, "digitizer"))
      {
    	  std::cerr << "------------------------ [GateSinglesDigitizer Messenger Problem]------------------------ \n";
    	  std::cerr << "Probably you try to use a command for the old version of the digitizer.\n";
    	  std::cerr << "Try </gate/digitizerMgr> commands instead, you can find the documentation here: XXXX \n"; //TODO insert the link to the documentation page
    	  std::cerr << "A tool to automatically convert your old digitizer macro to a new is also available here: XXXX \n"; //TODO insert the link to tool page
    	  std::cerr << "---------------------------------------------------------------------------------- \n";
      }
      if (G4StrUtil::contains(cerrString, "output"))
            {
          	  std::cerr << "------------------------ [GateOutput Messenger Problem]------------------------ \n";
          	  std::cerr << "Probably the command that you try to use is obsolete.\n";
          	  if(G4StrUtil::contains(cerrString, "root"))
              {
          		 std::cerr << "Instead of /gate/output/root/setRootSinglesFlag, please use: /gate/output/root/setRootSingles_<DetectorName>Flag, "
                 		  "where <DetectorName> = name that you use in command(s) /gate/<DetectorName>/attachCrystalSD\n";
              }
          	  if(G4StrUtil::contains(cerrString, "tree"))
          	  {
          		  std::cerr << "Instead of /gate/output/tree/hits/enable, please use: /gate/output/tree/addHitsCollection <DetectorName>,"
          				  "where <DetectorName> = name that you use in command /gate/<DetectorName>/attachCrystalSD\n";
          		  std::cerr << "Instead of /gate/output/tree/addCollection Singles, please use: /gate/output/tree/addCollection Singles_<DetectorName>,"
          		          				  "where <DetectorName> = name that you use in command(s) /gate/<DetectorName>/attachCrystalSD\n";
          	  }
          	  if(G4StrUtil::contains(cerrString, "ascii"))
          	  {
          		  std::cerr << "Instead of /gate/output/ascii/setOutFileSinglesFlag, please use: /gate/output/ascii/setOutFileSingles_<DetectorName>Flag,"
          	          		          				  "where <DetectorName> = name that you use in command(s) /gate/<DetectorName>/attachCrystalSD\n";
          	  }
          	  if(G4StrUtil::contains(cerrString, "binary"))
          	  {
          		  std::cerr << "Instead of /gate/output/binary/setOutFileSinglesFlag, please use: /gate/output/binary/setOutFileSingles_<DetectorName>Flag,"
          				  "where <DetectorName> = name that you use in command(s) /gate/<DetectorName>/attachCrystalSD\n";
          	   }
          	  if(G4StrUtil::contains(cerrString, "projection"))
          	  {
          		  std::cerr << "Instead of /gate/output/projection/setInputDataName Window1, please use: /gate/output/projection/setInputDataName Window1_<DetectorName>,"
          				  "where <DetectorName> = name that you use in command(s) /gate/<DetectorName>/attachCrystalSD\n";
          	  }

          	  std::cerr << "---------------------------------------------------------------------------------- \n";
            }


      exit(-1);
    }

  return 0;
}


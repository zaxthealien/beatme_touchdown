
#include "btm_td.h"
#include "stdafx.h"

namespace btm_td{

	int ScanMidiAssetsInfo(){
		std::vector<std::string> found;
		btm_td::helper::ListAllMidi(btm_td::PATH_ASSETS_MIDI.c_str(), &found);
		
		for (auto path : found){

		}
		return 0;
	}

	int ScanMidiAssetsVars(){
		return 0;
	}

}
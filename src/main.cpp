
#include <string>
#include "btm_td.h"
#include "stdafx.h"

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		
		btm_td::InitLogger("log/btm_td.log", spdlog::level::debug, 65536 * 32);
		btm_td::console->info() << "Beatme! Touchdown! tester";
		//btm_td::console = spdlog::stdout_logger_mt("console");

		/*std::vector<std::string> found = std::vector<std::string>();
		std::vector<std::string> tnames;
		std::vector<uchar> instnames;
		std::vector<bool> noteInTracks;
		int count = 0;
		
		btm_td::console->info() << "List all midi at " << argv[1];
		btm_td::helper::ListAllMidi(argv[1], &found);
		for (auto path : found){
			btm_td::console->info() << "Found: " << path << "\n";
		}*/
	
		/*std::shared_ptr<spdlog::logger> log_file;
		log_file = spdlog::rotating_logger_st("log_file", "/log/btm_td.log", 65536, 1, true);*/

		//for (auto path : found){
		//	btm_td::logger->info() << "Found: " << path << "\n" << "\tStarting to parse . . .";
		//	btm_td::console->info() << "Found: " << path << " -- " << "Starting to parse . . .";

		//	jdksmidi::MIDIMultiTrack mlt;
		//	btm_td::jdksmidi_helper::ParseMidiFile(path.c_str(), &mlt);
		//	std::vector<uchar> instypes = btm_td::jdksmidi_helper::GetMIDIFirstInstrumentTypes(&mlt);
		//	for (int i = 0; i < instypes.size(); i++){
		//		if (instypes[i]<128)
		//			btm_td::console->info() << "\tChannel" << i << ": " << btm_td::music::MIDIInstrumentName[instypes[i]];
		//	}
		//	count = btm_td::jdksmidi_helper::IsNoteInMIDITracks(&mlt, &noteInTracks);
		//	tnames = btm_td::jdksmidi_helper::GetAllMIDITrackNames(&mlt);
		//	btm_td::console->info() << "\t" << ((count == 2) ? "" : "Not ") << "Two Tracks";
		//	if (count == 2){
		//		for (int i = 0; i < noteInTracks.size(); i++){
		//			if (noteInTracks[i]){
		//				btm_td::console->info() << "Track " << i << ": " << tnames[i];
		//			}
		//		}
		//	}
		//	//for (int i = 0; i < tnames.size(); i++){
		//	//	if (/*tnames[i].size() > 0 && */btm_td::jdksmidi_helper::IsNoteInMIDITrack(mlt.GetTrack(i))){
		//	//		btm_td::logger->info() << "\tTrack" << i << ":\t" << tnames[i];
		//	//	}
		//	//}
		//	btm_td::logger->info() << "Finished parsing " << path;
		//}

		/*std::string outfilename(argv[1]);
		outfilename = "log/" + outfilename.substr(0, outfilename.find_last_of(".")) + ".log";*/

		/*const char * _dbpath = btm_td::helper::db::DEFAULT_SONGINFO_DB;*/

		//btm_td::helper::db::InitDB<btm_td::helper::db::SQLite3>(btm_td::helper::db::DEFAULT_SONGINFO_DB);
		//btm_td::helper::db::songInfoDB = new btm_td::helper::db::SQLite3(btm_td::helper::db::DEFAULT_SONGINFO_DB);
		//btm_td::helper::db::InitDB<btm_td::helper::db::SQLite3>(btm_td::helper::db::DEFAULT_SONGINFO_DB, btm_td::helper::db::DEFAULT_SONGVARS_DB);

		//std::vector<uchar> instruments = {0,0};
		//btm_td::console->debug()<<"result addsonginfo: " << 
		//	btm_td::helper::db::songInfoDB->AddSongInfo("Hungarian Dance no.1 in G Minor", 
		//	"/assets/midi/classical/Brahms",
		//	"hungdan1.mid", 
		//	"Hungarian Dances", 
		//	"Brahms", 
		//	"Classical", 
		//	"Folksong", 
		//	2,
		//	120,
		//	500000,
		//	60,
		//	{ {4,2,24,8} },
		//	instruments);

		
		/*long int row = -1;
		const char * songname = NULL;
		const char * filepath = "/assets/midi/classical/brahms";
		const char * filename = "hungdan1.mid";
		const char * songgroup = NULL;
		const char * composer = NULL;
		const char * genre = NULL;
		const char * subgenre = NULL;
		uchar num_tracks = 0;
		uchar clksperbeat = 0;
		uint firsttempo = 0;
		uchar firstkey = 0;
		std::array<uchar, 4> firsttimesig;
		std::vector<uchar> instruments2;

		btm_td::console->debug() << "result GetSongInfo: " << 
			btm_td::helper::db::songInfoDB->GetSongInfo(&row, &songname, &filepath, &filename, &songgroup, &composer, &genre, &subgenre,
			&num_tracks, &clksPerBeat, &firstTempo, &firstKey, &firstTimeSig, &instruments2);
		char buff[1024];
		sprintf_s(buff, 1024, "GetSongInfo: %d %s%s %s %s %s %s %s %d %d %d %d [%d,%d,%d,%d] %d",
			row, filepath, filename, songname, songgroup, composer, genre, subgenre, num_tracks,
			clksPerBeat, firstTempo, firstKey, firstTimeSig[0], firstTimeSig[1], firstTimeSig[2], firstTimeSig[3], instruments2.size());
		btm_td::console->debug() << "result GetSongInfo row: " << buff;

		btm_td::music::TDMusicHeader header;
		btm_td::console->debug() << "result GetSongInfo TDHeader: " <<
			btm_td::helper::db::songInfoDB->GetSongInfo(&row, &filepath, &filename, &header);

		sqlite3pp::database dbTest(btm_td::helper::db::DEFAULT_SONGINFO_DB);
		sqlite3pp::query dbQry(dbTest, "");*/

		/*btm_td::music::TDMusic tdm = btm_td::music::TDMusic();
		std::string pathStr = std::string(".");
		pathStr += filepath; pathStr += "/"; pathStr += filename;
		fprintf(stdout, "\nTestScan: %s", pathStr.c_str());
		int res = tdm.ScanMidi(pathStr.c_str());
		uchar numtracks = tdm.GetNumTracks();
		ulong numevents = tdm.GetNumEvents();
		const std::vector<btm_td::music::TDMusicTrack *> * tracks = tdm.GetTracks();
		std::string tdmStr = tdm.JSONStrSerialize();
		fprintf(stdout, "%s\n", tdmStr.c_str());
		FILE * f = fopen("/testdump.txt", "w");
		if(f!=NULL)fprintf(f, "%s\n", tdmStr.c_str());
		fprintf(stdout, " %d\n", res);*/

		//int res = 0;
		//long int _row = -1;
		//uchar _num_tracks = 0;
		//uchar _clksPerBeat = 0;
		//uchar _firstTempo = 0;
		//uchar _firstKey = 0;
		//std::array<uchar, 4> _firstTimeSig = { 0, 0, 0, 0 };
		//std::vector<uchar> _instruments;


		//if (row >= 0){
		//	res += dbQry.prepare(btm_td::helper::db::query::SONGINFO_SELECT_ROW);
		//	res += dbQry.bind(":id", row);
		//}
		//else if (filepath != NULL && filepath != "" && filename != NULL && filename != ""){
		//	res += dbQry.prepare(btm_td::helper::db::query::SONGINFO_SELECT_FILE);
		//	res += dbQry.bind(":filepath", filepath);
		//	res += dbQry.bind(":filename", filename);
		//}
		//if (res == 0){

		//	sqlite3pp::query::iterator it = dbQry.begin();
		//	if (it != dbQry.end()){
		//		_row = (*it).get<long int>(0);
		//		row = _row;
		//		btm_td::console->debug() << "found row: " << row;
		//		filepath = (*it).get<const char *>(1);
		//		filename = (*it).get<const char *>(2);
		//		songname = (*it).get<const char *>(3);
		//		songgroup = (*it).get<const char *>(4);
		//		songgroup;
		//		composer = (*it).get<const char *>(5);
		//		composer;
		//		genre = (*it).get<const char *>(6);
		//		genre;
		//		subgenre = (*it).get<const char *>(7);
		//		subgenre;
		//		_num_tracks = (*it).get<uchar>(8);
		//		/*if (num_tracks != NULL)
		//			*num_tracks = _num_tracks;
		//		else
		//			num_tracks = &_num_tracks;
		//		_clksPerBeat = (*it).get<uchar>(9);
		//		if (clksPerBeat != NULL)
		//			*clksPerBeat = _clksPerBeat;
		//		else
		//			clksPerBeat = &_clksPerBeat;
		//		_firstTempo = (*it).get<uchar>(10);
		//		if (firstTempo != NULL)
		//			*firstTempo = _firstTempo;
		//		else
		//			firstTempo = &_firstTempo;
		//		_firstKey = (*it).get<uchar>(11);
		//		if (firstKey != NULL)
		//			*firstKey = _firstKey;
		//		else
		//			firstKey = &_firstKey;
		//		const char * firstTimeSigC = (*it).get<const char *>(12);
		//		Json::Value jsonFirstTimeSig(firstTimeSigC);
		//		for (int i = 0; i < jsonFirstTimeSig.size(); ++i){
		//			_firstTimeSig[i] = jsonFirstTimeSig[i].asUInt();
		//		}
		//		firstTimeSig = &_firstTimeSig;
		//		const char * instrumentsC = (*it).get<const char *>(13);
		//		Json::Value jsonInstrumentsC(firstTimeSigC);
		//		for (int i = 0; i < jsonInstrumentsC.size(); ++i){
		//			_instruments[i] = jsonInstrumentsC[i].asUInt();
		//		}
		//		instruments = &_instruments;*/
		//	}
		//	else {
		//		//return SQL_ENTRY_NOT_FOUND;
		//	}
		//}
		jdksmidi::MIDIFileReadStreamFile rs(argv[1]);
		jdksmidi::MIDIMultiTrack tracks(64);
		jdksmidi::MIDIFileReadMultiTrack track_loader(&tracks);
		jdksmidi::MIDIFileRead reader(&rs, &track_loader);
		jdksmidi::MIDISequencerGUIEventNotifierText gui(stdout);
		jdksmidi::MIDISequencer seq(&tracks, NULL);
		jdksmidi::MIDIDriverWin32 driver(128);
		jdksmidi::MIDIManager mgr(&driver, &gui);
		reader.Parse();
		driver.StartTimer(10);
		driver.OpenMIDIOutPort(MIDI_MAPPER);
		seq.GoToZero();
		mgr.SetSeq(&seq);
		mgr.SetTimeOffset(timeGetTime());
		mgr.SeqPlay();
		ulong offstart;
		ulong offtime = 0;
		while (getchar() != 'a'){
			if (mgr.IsSeqPlay()){ 
				offstart = timeGetTime();
				driver.StopTimer();
				mgr.SeqStop();
			}
			else { 
				mgr.SetSeqOffset(offtime+=timeGetTime()-offstart);
				driver.StartTimer(10);
				mgr.SeqPlay();
			}
		}
		mgr.SeqStop();
		
		//btm_td::music::GetPossibleKeys();
		
		system("pause");
		return 0;
	}
	return 0;
}


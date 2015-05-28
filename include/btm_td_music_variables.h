
#ifndef BTM_TD_MUSIC_VARIABLES_H
#define BTM_TD_MUSIC_VARIABLES_H

#include "btm_td_music.h"

namespace btm_td{

	namespace music_vars{

		
		class MusicVars{
		public:

			MusicVars();
			MusicVars(const char * midiFile);
			MusicVars(jdksmidi::MIDIMultiTrack * mlt);
			MusicVars(btm_td::music::TDMusic * tdMusic);
			MusicVars(MusicVars& other);
			~MusicVars();

			virtual btm_td::music::TDMusic nextBar();
			virtual btm_td::music::TDMusic nextBar(btm_td::music::TDMusic * baseMusic);
			
			virtual btm_td::music::TDMusic nextWord();
			virtual btm_td::music::TDMusic nextword(btm_td::music::TDMusic * baseMusic);

			virtual btm_td::music::TDMusic nextSentence();
			virtual btm_td::music::TDMusic nextSentence(btm_td::music::TDMusic * baseMusic);

			virtual btm_td::music::TDMusic nextSong();
			virtual btm_td::music::TDMusic nextSong(btm_td::music::TDMusic baseMusic);

			virtual int GetVars(const char * midiFile);
			virtual int GetVars(btm_td::music::TDMusic * tdMusic);
			virtual int GetVars(btm_td::music::TDMusicHeader header = btm_td::music::TDMusicHeader());
			virtual int GetVars(std::string _songgroup = "",
				std::string _composer = "",
				std::string _genre = "",
				std::string _subgenre = "",
				uchar _clksPerBeat = 120,
				uint _firstTempo = 500000,
				uchar _firstKey = 60,
				std::array<uchar, 4> _firstTimeSig = { { 4, 2, 24, 8 } },
				std::array<uchar, 5> _moods = { { 3, 3, 3, 3, 3 } });

			virtual int StoreVars(const char * dbFile = btm_td::helper::db::DEFAULT_SONGVARS_DB);

			virtual class TDMusicVars{
			protected:
				TDMusicVars();
			};

		protected:

			TDMusicVars * vars;
			btm_td::music::TDMusic * processing;


		};

		typedef int(__stdcall * CreateVars)(MusicVars * musicVars);

		int LoadMusicVardDL(const char * path);
		int LoadDLL(MusicVars * musicVars, const char * dllpath = "./mvars/mVarsDefault.dll");

	}

}

#endif
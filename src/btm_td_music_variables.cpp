#include "btm_td_music_variables.h"
#include "stdafx.h"

namespace btm_td{
	namespace music_vars{

		int LoadDLL(MusicVars * musicVars, const char * dllpath){
			wchar_t * dllpath_w = NULL;
			mbstowcs(dllpath_w, dllpath, strlen(dllpath) + 1);
			HINSTANCE hGetProcIDDLL = LoadLibrary(dllpath_w);

			if (!hGetProcIDDLL) {
				std::cout << "could not load the dynamic library" << std::endl;
				return -1;
			}

			CreateVars createVars = (CreateVars)GetProcAddress(hGetProcIDDLL, "CreateVars");
			if (!createVars) {
				std::cout << "could not locate the CreateVars function" << std::endl;
				return -1;
			}

			return createVars(musicVars);
		}

		btm_td::music::TDMusic MusicVars::nextBar(){
			throw(BaseClassException());
			return btm_td::music::TDMusic();
		}

		btm_td::music::TDMusic MusicVars::nextBar(btm_td::music::TDMusic * baseMusic){
			throw(BaseClassException());
			return btm_td::music::TDMusic();
		}

		btm_td::music::TDMusic MusicVars::nextWord(){
			throw(BaseClassException());
			return btm_td::music::TDMusic();
		}

		btm_td::music::TDMusic MusicVars::nextword(btm_td::music::TDMusic * baseMusic){
			throw(BaseClassException());
			return btm_td::music::TDMusic();
		}

		btm_td::music::TDMusic MusicVars::nextSentence(){
			throw(BaseClassException());
			return btm_td::music::TDMusic();
		}

		btm_td::music::TDMusic MusicVars::nextSentence(btm_td::music::TDMusic * baseMusic){
			throw(BaseClassException());
			return btm_td::music::TDMusic();
		}

		btm_td::music::TDMusic MusicVars::nextSong(){
			throw(BaseClassException());
			return btm_td::music::TDMusic();
		}

		btm_td::music::TDMusic MusicVars::nextSong(btm_td::music::TDMusic baseMusic){
			throw(BaseClassException());
			return btm_td::music::TDMusic();
		}

		int MusicVars::GetVars(const char * midiFile){
			throw(BaseClassException());
			return 0;
		}

		int MusicVars::GetVars(btm_td::music::TDMusic * tdMusic){
			throw(BaseClassException());
			return 0;
		}

		int MusicVars::GetVars(btm_td::music::TDMusicHeader header){
			throw(BaseClassException());
			return 0;
		}

		int MusicVars::GetVars(std::string _songgroup,
			std::string _composer,
			std::string _genre,
			std::string _subgenre,
			uchar _clksPerBeat,
			uint _firstTempo,
			uchar _firstKey,
			std::array<uchar, 4> _firstTimeSig,
			std::array<uchar, 5> _moods){
			throw(BaseClassException());
			return 0;
		}

		MusicVars::TDMusicVars::TDMusicVars(){
				throw(BaseClassException());
		}

	}
}
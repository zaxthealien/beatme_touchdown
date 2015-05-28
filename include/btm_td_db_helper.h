#ifndef BTM_TD_DB_HELPER_H
#define BTM_TD_DB_HELPER_H

#include <sqlite3.h>
#include <sqlite3pp.h>
#include <vector>
#include "btm_td_helper.h"

namespace btm_td{

	namespace helper{
		namespace db{
			BTM_TD_DLL_API const int DB_INIT_SUCCESS = 0x0;
			BTM_TD_DLL_API const int DB_INIT_FAILED_SONGINFO = 0x1;
			BTM_TD_DLL_API const int DB_INIT_FAILED_SONGVARS = 0x2;
			extern BTM_TD_DLL_API const char * DEFAULT_SONGINFO_DB;
			extern BTM_TD_DLL_API const char * DEFAULT_SONGVARS_DB;

			namespace query{
				extern const char * SONGINFO_CREATE_TABLE;
				extern const char * SONGINFO_INSERT;
				extern const char * SONGINFO_UPDATE_ROW;
				extern const char * SONGINFO_UPDATE_FILE;
				extern const char * SONGINFO_SELECT_ROW;
				extern const char * SONGINFO_SELECT_FILE;
				extern const char * SONGINFO_SELECT_OTHERS;

			}

			class DBHelper{
			public:
				virtual btm_td::music::TDMusicHeader* ReadSongInfo(const char * filepath, const char * filename);
				virtual int AddSongInfo(const char * songname = "song",
					const char * filepath = btm_td::PATH_ASSETS_MIDI.c_str(),
					const char * filename = "song.midi",
					const char * songgroup = "",
					const char * composer = "",
					const char * genre = "",
					const char * subgenre = "",
					uchar num_tracks = 0,
					uchar clksPerBeat = 120,
					uint firstTempo = 500000,
					uchar firstKey = 60,
					std::array<uchar, 4> firstTimeSig = { { 4, 2, 24, 8 } },
					std::vector<uchar> instruments = {  });
				virtual int AddSongInfo(const char * filepath = btm_td::PATH_ASSETS_MIDI.c_str(),
					const char * filename = "song.midi",
					btm_td::music::TDMusicHeader header = btm_td::music::TDMusicHeader());
				virtual int UpdateSongInfo(long int row,
					const char * songname = "song",
					const char * filepath = btm_td::PATH_ASSETS_MIDI.c_str(),
					const char * filename = "song.midi",
					const char * songgroup = "",
					const char * composer = "",
					const char * genre = "",
					const char * subgenre = "",
					uchar num_tracks = 0,
					uchar clksPerBeat = 120,
					uint firstTempo = 500000,
					uchar firstKey = 60,
					std::array<uchar, 4> firstTimeSig = { { 4, 2, 24, 8 } },
					std::vector<uchar> instruments = {  });
				virtual int UpdateSongInfo(long int row,
					const char * filepath = btm_td::PATH_ASSETS_MIDI.c_str(),
					const char * filename = "song.midi",
					btm_td::music::TDMusicHeader header = btm_td::music::TDMusicHeader());
				virtual int GetSongInfo(long int * row,
					const char ** songname,
					const char ** filepath,
					const char ** filename,
					const char ** songgroup,
					const char ** composer,
					const char ** genre,
					const char ** subgenre,
					uchar * num_tracks,
					uchar * clksPerBeat,
					uint * firstTempo,
					uchar * firstKey,
					std::array<uchar, 4> * firstTimeSig,
					std::vector<uchar> * instruments);
				virtual int GetSongInfo(long int * row,
					const char ** filepath,
					const char ** filename,
					btm_td::music::TDMusicHeader * header);
				DBHelper(const char * dbname = "");
				~DBHelper();

			protected:
				const char * dbname;
				uchar td_dbtype;
				virtual int Open(const char * _dbname);
				virtual int Close();
				virtual int CreateTables();
				DBHelper& operator=(DBHelper& other);
			};

			class SQLite3 : public DBHelper{
			public:
				SQLite3(const char * path = "");
				SQLite3(sqlite3pp::database * db);
				~SQLite3();

				btm_td::music::TDMusicHeader* ReadSongInfo(const char * filepath, const char * filename);
				int AddSongInfo(const char * songname = "song",
					const char * filepath = "/assets/midi",
					const char * filename = "song.midi",
					const char * songgroup = "",
					const char * composer = "",
					const char * genre = "",
					const char * subgenre = "",
					uchar num_tracks = 0,
					uchar clksPerBeat = 120,
					uint firstTempo = 500000,
					uchar firstKey = 60,
					std::array<uchar, 4> firstTimeSig = { { 4, 2, 24, 8 } },
					std::vector<uchar> instruments = {});
				int AddSongInfo(const char * filepath = btm_td::PATH_ASSETS_MIDI.c_str(),
					const char * filename = "song.midi",
					btm_td::music::TDMusicHeader header = btm_td::music::TDMusicHeader());
				int UpdateSongInfo(long int row,
					const char * songname = "song",
					const char * filepath = "/assets/midi",
					const char * filename = "song.midi",
					const char * songgroup = "",
					const char * composer = "",
					const char * genre = "",
					const char * subgenre = "",
					uchar num_tracks = 0,
					uchar clksPerBeat = 120,
					uint firstTempo = 500000,
					uchar firstKey = 60,
					std::array<uchar, 4> firstTimeSig = { { 4, 2, 24, 8 } },
					std::vector<uchar> instruments = {});
				int UpdateSongInfo(long int row,
					const char * filepath = btm_td::PATH_ASSETS_MIDI.c_str(),
					const char * filename = "song.midi",
					btm_td::music::TDMusicHeader header = btm_td::music::TDMusicHeader());
				int GetSongInfo(long int * row,
					const char ** songname,
					const char ** filepath,
					const char ** filename,
					const char ** songgroup,
					const char ** composer,
					const char ** genre,
					const char ** subgenre,
					uchar * num_tracks,
					uchar * clksPerBeat,
					uint * firstTempo,
					uchar * firstKey,
					std::array<uchar, 4> * firstTimeSig,
					std::vector<uchar> * instruments);
				int GetSongInfo(long int * row,
					const char ** filepath,
					const char ** filename,
					btm_td::music::TDMusicHeader * header);

			protected:
				uchar td_dbtype;
				sqlite3pp::database * db;

				int Open(const char * _dbname);
				int Close();
				int CreateTables();

				SQLite3& operator=(SQLite3 & other);
			};

			//postgresql not implemented yet
			//class PostgreSQL :DBHelper{
			//public:
			//	PostgreSQL();
			//	PostgreSQL(char * path);
			//	PostgreSQL(PostgreSQL & other);
			//	~PostgreSQL();

			//protected:

			//	int Open(char * dbname);
			//	int Close();
			//};

			extern DBHelper *songInfoDB;
			extern DBHelper *songVarsDB;
			template <class DBHelperType> 
			int InitDB(const char * songInfo_file = DEFAULT_SONGINFO_DB, 
				const char * songVars_file = DEFAULT_SONGVARS_DB){
				songInfoDB = new DBHelperType(songInfo_file);
				songVarsDB = new DBHelperType(songVars_file);
				if (songInfoDB != NULL && songVarsDB != NULL)
					return DB_INIT_SUCCESS;
				return 0 | 
					(songInfoDB==NULL?DB_INIT_FAILED_SONGINFO:0) | 
					(songVarsDB==NULL?DB_INIT_FAILED_SONGVARS:0) ;
			};

		}
	}
}

#endif
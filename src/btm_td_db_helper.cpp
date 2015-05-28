
#include "btm_td_db_helper.h"
#include "stdafx.h"

namespace btm_td{
	namespace music{
		struct TDMusicHeader;
	}

	namespace helper{
		namespace db{

			enum StatusEnum{
				SQL_OK = 0,
				SQL_ENTRY_NOT_FOUND = 1,
				SQL_BIND_ERROR = 25,
				INVALID_ARGUMENTS = -1,
				UNKNOWN_ERROR = -99,

			};

			const char * DEFAULT_SONGINFO_DB = "./data/songinfo.db";
			const char * DEFAULT_SONGVARS_DB = "./data/songvars.db";

			namespace query{
				const char * SONGINFO_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS songinfo ( "
					"id INTEGER PRIMARY KEY AUTOINCREMENT, "
					"filepath TEXT, "
					"filename TEXT, "
					"songname TEXT, "
					"songgroup TEXT, "
					"composer TEXT, "
					"genre TEXT, "
					"subgenre TEXT, "
					"num_tracks INTEGER, "
					"clksPerBeat INTEGER, "
					"firstTempo INTEGER, "
					"firstKey INTEGER, "
					"firstTimeSig TEXT, "
					"instruments TEXT, "
					"CONSTRAINT file UNIQUE( "
					"	filepath, "
					"	filename "
					"	) "
					"); ";
				const char * SONGINFO_INSERT = "INSERT INTO songinfo (filepath, filename, songname, songgroup, composer, genre, subgenre, num_tracks, clksPerBeat, firstTempo, firstKey, firstTimeSig, instruments) "
					"VALUES (:filepath, :filename, :songname, :songgroup, :composer, :genre, :subgenre, :num_tracks, :clksPerBeat, :firstTempo, :firstKey, :firstTimeSig, :instruments); ";
				const char * SONGINFO_UPDATE_ROW = "UPDATE songinfo "
					"SET songname = :songname, "
					"songgroup = :songgroup, "
					"composer = :composer, "
					"genre = :genre, "
					"subgenre = :subgenre, "
					"num_tracks = :num_tracks, "
					"clksPerBeat = :clksPerBeat, "
					"firstTempo = :firstTempo, "
					"firstKey = :firstKey, "
					"firstTimeSig = :firstTimeSig, "
					"instruments = :instruments "
					"WHERE id = :id; ";
				const char * SONGINFO_UPDATE_FILE = "UPDATE songinfo "
					"SET songname = :songname, "
					"songgroup = :songgroup, "
					"composer = :composer, "
					"genre = :genre, "
					"subgenre = :subgenre, "
					"num_tracks = :num_tracks, "
					"clksPerBeat = :clksPerBeat, "
					"firstTempo = :firstTempo, "
					"firstKey = :firstKey, "
					"firstTimeSig = :firstTimeSig, "
					"instruments = :instruments "
					"WHERE filepath = :filepath AND filename = :filename; ";
				const char * SONGINFO_SELECT_ROW = "SELECT id, filepath, filename, songname, songgroup, composer, genre, subgenre, num_tracks, clksPerBeat, firstTempo, firstKey, firstTimeSig, instruments "
					"FROM songinfo "
					"WHERE id=:id;";
				const char * SONGINFO_SELECT_FILE = "SELECT id, filepath, filename, songname, songgroup, composer, genre, subgenre, num_tracks, clksPerBeat, firstTempo, firstKey, firstTimeSig, instruments "
					"FROM songinfo "
					"WHERE filepath=:filepath AND filename=:filename;";
//				const char * SONGINFO_SELECT_OTHERS = "SELECT :columns WHERE :conditions";
			}


			DBHelper::DBHelper(const char * _dbname) :
				dbname(_dbname)
			{
			}

			DBHelper::~DBHelper(){

			}

			btm_td::music::TDMusicHeader* DBHelper::ReadSongInfo(const char * filepath, const char * filename){
				throw(BaseClassException());
				return new btm_td::music::TDMusicHeader();
			}

			int DBHelper::AddSongInfo(const char * songname,
				const char * filepath,
				const char * filename,
				const char * songgroup,
				const char * composer,
				const char * genre,
				const char * subgenre,
				uchar num_tracks,
				uchar clksPerBeat,
				uint firstTempo,
				uchar firstKey,
				std::array<uchar, 4> firstTimeSig,
				std::vector<uchar> instruments){
				throw(BaseClassException());
				return 0;
			}

			int DBHelper::AddSongInfo(const char * filepath,
				const char * filename,
				btm_td::music::TDMusicHeader header){
				throw(BaseClassException());
				return 0;
			}

			int DBHelper::UpdateSongInfo(long int row,
				const char * songname,
				const char * filepath,
				const char * filename,
				const char * songgroup,
				const char * composer,
				const char * genre,
				const char * subgenre,
				uchar num_tracks,
				uchar clksPerBeat,
				uint firstTempo,
				uchar firstKey,
				std::array<uchar, 4> firstTimeSig,
				std::vector<uchar> instrument){
				throw(BaseClassException());
				return row;
			}

			int DBHelper::UpdateSongInfo(long int row,
				const char * filepath,
				const char * filename,
				btm_td::music::TDMusicHeader header){
				throw(BaseClassException());
				return row;
			}

			int DBHelper::GetSongInfo(long int * row,
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
				std::vector<uchar> * instrumentss){
				throw(BaseClassException());
				return 0;
			}

			int DBHelper::GetSongInfo(long int * row,
				const char ** filepath,
				const char ** filename,
				btm_td::music::TDMusicHeader * header){
				throw(BaseClassException());
				return 0;
			}

			int DBHelper::Open(const char * _dbname){
				throw(BaseClassException());
				return 0;
			}
			int DBHelper::Close(){
				throw(BaseClassException());
				return 0;
			}
			int DBHelper::CreateTables(){
				throw(BaseClassException());
				return 0;
			}


			SQLite3::SQLite3(const char * path){
				if (this->Open(path) != 0)
					throw(InvalidDBException("Failed to open database."));
				if (this->CreateTables()!=0)
					throw(InvalidDBException("Failed to create tables."));
			}
			SQLite3::SQLite3(sqlite3pp::database * _db){
				if (_db != NULL)
					this->db = _db;
				else{
					throw(InvalidDBException("SQLite3 db constructor's argument cannot be NULL."));
				}
			}

			SQLite3::~SQLite3(){
				delete this->db;
			}

			btm_td::music::TDMusicHeader* SQLite3::ReadSongInfo(const char * filepath, const char * filename){
				btm_td::music::TDMusicHeader* ret = NULL;
				ret = new btm_td::music::TDMusicHeader();
				return ret;
			}

			int SQLite3::AddSongInfo(const char * songname,
				const char * filepath,
				const char * filename,
				const char * songgroup,
				const char * composer,
				const char * genre,
				const char * subgenre,
				uchar num_tracks,
				uchar clksPerBeat,
				uint firstTempo,
				uchar firstKey,
				std::array<uchar, 4> firstTimeSig,
				std::vector<uchar> instruments)
			{
				int res = 0;
				sqlite3pp::command cmd(*(this->db), query::SONGINFO_INSERT);
				res += cmd.bind(":songname", songname);
				res += cmd.bind(":filepath", filepath);
				res += cmd.bind(":filename", filename);
				res += cmd.bind(":songgroup", songgroup);
				res += cmd.bind(":composer", composer);
				res += cmd.bind(":genre", genre);
				res += cmd.bind(":subgenre", subgenre);
				res += cmd.bind(":num_tracks", num_tracks);
				res += cmd.bind(":clksPerBeat", clksPerBeat);
				res += cmd.bind(":firstTempo", (long long) firstTempo);
				res += cmd.bind(":firstKey", firstKey);
				res += cmd.bind(":firstTimeSig", btm_td::helper::jsonSerialize(firstTimeSig));
				res += cmd.bind(":instruments", btm_td::helper::jsonSerialize(instruments));

				if (res == SQL_OK){
					try {
						res = cmd.execute_all();
						cmd.finish();
					}
					catch (std::exception e){
						logger->warn() << e.what();
						console->warn() << e.what();
					}
				}
				if (res != SQL_OK)
					console->warn() << "Failed to add entry: SQLite3 SQL error " << res;
				return res;
			}

			int SQLite3::AddSongInfo(const char * filepath,
				const char * filename,
				btm_td::music::TDMusicHeader header){
				return AddSongInfo(header.songname.c_str(), filepath, filename, header.songgroup.c_str(),
					header.composer.c_str(), header.genre.c_str(), header.subgenre.c_str(), header.numTracks,
					header.clksPerBeat, header.firstTempo, header.firstKey, header.firstTimeSig, 
					header.instruments
					);
			}

			int SQLite3::UpdateSongInfo(long int row,
				const char * songname,
				const char * filepath,
				const char * filename,
				const char * songgroup,
				const char * composer,
				const char * genre,
				const char * subgenre,
				uchar num_tracks,
				uchar clksPerBeat,
				uint firstTempo,
				uchar firstKey,
				std::array<uchar, 4> firstTimeSig,
				std::vector<uchar> instruments){

				if (row < 0){
					btm_td::music::TDMusicHeader header;
					if (this->GetSongInfo(&row, &filepath, &filename, &header) != SQL_OK){
						return this->AddSongInfo(songname, filepath, filename, songgroup, composer, genre, subgenre, num_tracks,
							clksPerBeat, firstTempo, firstKey, firstTimeSig, instruments);
					}
				}
				else {
					int res = 0;
					sqlite3pp::command cmd(*(this->db), query::SONGINFO_UPDATE_ROW);
					res += cmd.bind(":songname", songname);
					res += cmd.bind(":songgroup", songgroup);
					res += cmd.bind(":composer", composer);
					res += cmd.bind(":genre", genre);
					res += cmd.bind(":subgenre", subgenre);
					res += cmd.bind(":num_tracks", num_tracks);
					res += cmd.bind(":clksPerBeat", clksPerBeat);
					res += cmd.bind(":firstTempo", (long long)firstTempo);
					res += cmd.bind(":firstKey", firstKey);
					res += cmd.bind(":firstTimeSig", btm_td::helper::jsonSerialize(firstTimeSig));
					res += cmd.bind(":instruments", btm_td::helper::jsonSerialize(instruments));

					if (res == 0){
						res = cmd.execute_all();
						cmd.finish();
					}
					else {
						return SQL_BIND_ERROR;
					}
					return res;
				}


				return UNKNOWN_ERROR;
			}

			int SQLite3::UpdateSongInfo(long int row,
				const char * filepath,
				const char * filename,
				btm_td::music::TDMusicHeader header){
				return this->UpdateSongInfo(row, header.songname.c_str(), filepath, filename,
					header.songgroup.c_str(), header.composer.c_str(), header.genre.c_str(),
					header.subgenre.c_str(), header.numTracks, header.clksPerBeat,
					header.firstTempo, header.firstKey, header.firstTimeSig,
					header.instruments);
				return row;
			}

			int SQLite3::GetSongInfo(long int * row,
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
				std::vector<uchar> * instruments){

				sqlite3pp::query dbQry(*(this->db),"");
				const char * get;

				int res = 0;
				std::array<uchar, 4> _firstTimeSig = { 0, 0, 0, 0 };
				std::vector<uchar> _instruments;


				if (*row >= 0){
					res += dbQry.prepare(query::SONGINFO_SELECT_ROW);
					res += dbQry.bind(":id", *row);
				}
				else if (*filepath!=NULL && *filepath!="" && *filename!=NULL && *filename!=""){
					res += dbQry.prepare(query::SONGINFO_SELECT_FILE);
					res += dbQry.bind(":filepath", *filepath);
					res += dbQry.bind(":filename", *filename);
				}
				else {
					throw (InvalidArgumentsException("Row must be >=0 or filepath-filename argument can't be null nor empty."));
				}
				if (res == 0){

					sqlite3pp::query::iterator it = dbQry.begin();
					if (it != dbQry.end()){
						*row = (*it).get<long int>(0);
						*filepath = btm_td::helper::cpConstChar((*it).get<const char *>(1));
						*filename = btm_td::helper::cpConstChar((*it).get<const char *>(2));
						*songname = btm_td::helper::cpConstChar((*it).get<const char *>(3));
						*songgroup = btm_td::helper::cpConstChar((*it).get<const char *>(4));
						*composer = btm_td::helper::cpConstChar((*it).get<const char *>(5));
						*genre = btm_td::helper::cpConstChar((*it).get<const char *>(6));
						*subgenre = btm_td::helper::cpConstChar((*it).get<const char *>(7));
						*num_tracks = (*it).get<uchar>(8);
						*clksPerBeat = (*it).get<uchar>(9);
						*firstTempo = (*it).get<uchar>(10);
						*firstKey = (*it).get<uchar>(11);
						*firstTimeSig = btm_td::helper::jsonDeserializeToArray<uchar,4>(btm_td::helper::cpConstChar((*it).get<const char *>(12)));
						*instruments = btm_td::helper::jsonDeserializeToVector<uchar>(btm_td::helper::cpConstChar( (*it).get<const char *>(13)));
					}
					else {
						return SQL_ENTRY_NOT_FOUND;
					}
				}
				
				return SQL_OK;
			}

			int SQLite3::GetSongInfo(long int * row,
				const char ** filepath,
				const char ** filename,
				btm_td::music::TDMusicHeader * header){
				if (header != NULL){
					const char * songname = NULL;
					const char * songgroup = NULL;
					const char * composer = NULL;
					const char * genre = NULL;
					const char * subgenre = NULL;
					uchar num_tracks = 0;
					uchar clksPerBeat = 0;
					uint firstTempo = 0;
					uchar firstKey = 0;
					std::array<uchar, 4> firstTimeSig;
					std::vector<uchar> instruments;

					this->GetSongInfo(row, &songname, filepath, filename, &songgroup, &composer, &genre, &subgenre,
						&num_tracks, &clksPerBeat, &firstTempo, &firstKey, &firstTimeSig, &instruments);

					*header = btm_td::music::TDMusicHeader(songname,songgroup,composer,genre,subgenre,num_tracks,
						clksPerBeat,firstTempo,firstKey,firstTimeSig,instruments);

					return 0;
				}
				throw NullPointerException();
				return 0;
			}

			int SQLite3::Open(const char * _dbname){
				this->dbname = _dbname;
				this->db = new sqlite3pp::database(_dbname);
				if (this->db != NULL) return 0;
				return -1;
			}

			int SQLite3::Close(){
				delete this;
				return 0;
			}

			int SQLite3::CreateTables(){
				sqlite3pp::query q(*(this->db), query::SONGINFO_CREATE_TABLE);
				for (sqlite3pp::query::iterator it = q.begin(); it != q.end(); ++it){
					btm_td::console->debug() << (*it).data_count();
				}
				return 0;
			}

			DBHelper * songInfoDB;
			DBHelper * songVarsDB;

		}
	}
}
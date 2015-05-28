
#ifndef BTM_TD_HELPER_H
#define BTM_TD_HELPER_H

#include <list>
#include <string>
#include <bitset>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>
#include <spdlog/spdlog.h>
#include <json/json.h>
#include <dirent.h>
#include "jdksmidi_incl.h"
#include "btm_td_strings.h"
#include "btm_td_exceptions.h"
#include "btm_td_dll.h"
#include "stdafx.h"

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;

namespace btm_td {
	
	extern std::string PATH_ASSETS;
	extern std::string PATH_ASSETS_MIDI;
	extern std::string PATH_LOG;
	extern std::string PATH_DATA;
	extern std::string LOG_FILE;

	extern std::shared_ptr<spdlog::logger> logger;
	extern std::shared_ptr<spdlog::logger> console;

	void InitLogger(spdlog::level::level_enum level = spdlog::level::info);
	void InitLogger(const char * filename = LOG_FILE.c_str(), spdlog::level::level_enum level = spdlog::level::info, size_t maxFileSize = 65536 * 16, size_t maxFile = 1, bool forceFlush = true);

	namespace helper{

		void ListAllMidi(const char *dirname, std::vector<std::string> *found);

		const char * cpConstChar(const char * other);

		template<class T>
		const char * jsonSerialize(std::vector<T> vector){
			Json::Value json;
			for (auto i : vector){
				json.append(i);
			}
			return btm_td::helper::cpConstChar(json.toStyledString().c_str());
		};

		template<class T, size_t size>
		const char * jsonSerialize(std::array<T, size> array){
			Json::Value json;
			for (auto i : array){
				json.append(i);
			}
			return btm_td::helper::cpConstChar(json.toStyledString().c_str());
		};
		
		template<typename T>
		std::vector<T> jsonDeserializeToVector(const char * json){
			Json::Reader jsonReader;
			Json::Value jsonValue;
			std::vector<T> vect;
			bool is_signed = std::numeric_limits<T>::is_signed;
			bool is_integer = std::numeric_limits<T>::is_integer;
			jsonReader.parse(json, json + strlen(json), jsonValue, false);
			for (uint i = 0; i < jsonValue.size(); ++i){
				vect.push_back(is_integer?
					is_signed?
						jsonValue[i].asInt64():
						jsonValue[i].asUInt64():
					jsonValue[i].asDouble());
			}
			return vect;
		}

		template<typename T, size_t size>
		std::array<T, size> jsonDeserializeToArray(const char * json){
			Json::Reader jsonReader;
			Json::Value jsonValue;
			std::array<T, size> arr;
			bool is_signed = std::numeric_limits<T>::is_signed;
			bool is_integer = std::numeric_limits<T>::is_integer;
			jsonReader.parse(json, json + strlen(json), jsonValue, false);
			for (uint i = 0; i < jsonValue.size(); ++i){
				arr[i] = is_integer ?
					is_signed ?
						jsonValue[i].asInt64() :
						jsonValue[i].asUInt64() :
					jsonValue[i].asDouble();
			}
			return arr;
		}
	}

	namespace music{
		typedef struct TDMusicHeader {

			std::string songname;
			std::string songgroup;
			std::string composer;
			std::string genre;
			std::string subgenre;
			uchar numTracks;
			uchar clksPerBeat;
			uint firstTempo;
			uchar firstKey;
			std::array<uchar, 4> firstTimeSig;
			std::vector<uchar> instruments;
			std::array<uchar, 5> moods;

			TDMusicHeader(std::string _songname = "",
				std::string _songgroup = "",
				std::string _composer = "",
				std::string _genre = "",
				std::string _subgenre = "",
				uchar _numTracks = 0,
				uint _clksPerBeat = 120,
				uint _firstTempo = 500000,
				uchar _firstKey = 60,
				std::array<uchar, 4> _firstTimeSig = { { 4, 2, 24, 8 } },
				std::vector<uchar> _instruments = {},
				std::array<uchar, 5> _moods = { { 3, 3, 3, 3, 3 } }) :
				songname(_songname),
				songgroup(_songgroup),
				composer(_composer),
				genre(_genre),
				subgenre(_subgenre),
				numTracks(_numTracks),
				clksPerBeat(_clksPerBeat),
				firstTempo(_firstTempo),
				firstKey(_firstKey),
				firstTimeSig(_firstTimeSig),
				instruments(_instruments),
				moods(_moods)
			{}

			Json::Value JSONSerialize(){
				Json::Value jsonValue;
				jsonValue["songname"] = songname;
				jsonValue["songgroup"] = songgroup;
				jsonValue["composer"] = composer;
				jsonValue["genre"] = genre;
				jsonValue["subgenre"] = subgenre;
				jsonValue["numTracks"] = numTracks;
				jsonValue["clksPerBeat"] = clksPerBeat;
				jsonValue["firstTempo"] = firstTempo;
				jsonValue["firstKey"] = firstKey;
				Json::Value jsonFirstTimeSig;
				for (auto it = firstTimeSig.begin(); it != firstTimeSig.end(); ++it){
					jsonFirstTimeSig.append(Json::Value(*it));
				}
				jsonValue["firstTimeSig"] = jsonFirstTimeSig;
				Json::Value jsonInstruments;
				for (auto it = instruments.begin(); it != instruments.end(); ++it){
					jsonInstruments.append(Json::Value(*it));
				}
				jsonValue["instruments"] = jsonInstruments;
				Json::Value jsonMoods;
				for (auto it = moods.begin(); it != moods.end(); ++it){
					jsonMoods.append(Json::Value(*it));
				}
				jsonValue["moods"] = jsonMoods;
				return jsonValue;
			}
			std::string JSONStrSerialize(){
				Json::Value jsonValue = this->JSONSerialize();
				return jsonValue.toStyledString();
			};
			void JSONDeserialize(std::string jsonStr = ""){

			};

		} _TDMusicHeader;

		typedef struct MoodMeter{
			std::string key;
			uchar val;
		} _mood_meter;

		class Moods{
		public:
			uchar operator[] (std::string key);
			MoodMeter operator[] (uint index);

		private:
			std::array<MoodMeter, 5> moods /*= { { { "Mood1", 3 }, { "Mood2", 3 }, { "Mood3", 3 }, { "Mood4", 3 }, { "Mood5", 3 } } }*/;
		};

	}

}

#endif
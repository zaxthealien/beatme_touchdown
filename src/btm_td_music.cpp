
#include "btm_td_music.h"
#include "stdafx.h"

using namespace btm_td;

namespace btm_td{
	namespace music{
		const uchar RAW_OCTAVE_SIZE = 12;
		const uchar TD_OCTAVE_SIZE = 7;
		const uchar key_mapping_table[2][7] = { { 0, 2, 3, 5, 7, 8, 10 }, { 0, 2, 4, 5, 7, 9, 11 } };
		const char * key_name_table[24] = {
			"C Minor", "Db Minor", "D Minor", "Eb Minor", "E Minor", "F Minor",
			"Gb Minor", "G Minor", "Ab Minor", "A Minor", "Bb Minor", "B Minor",
			"C Major", "Db Major", "D Major", "Eb Major", "E Major", "F Major",
			"Gb Major", "G Major", "Ab Major", "A Major", "Bb Major", "B Major"
		};

		const char * JSON_CONSTRUCTOR = "constructor";

		void InitBtmTdMusic(){

		}

		MIDIRawNote GetRawFromKeyNoteDelta(TDNote note, MusicKey key, uchar octave){
			return key.key + key_mapping_table[key.major ? 1 : 0][note] + octave * RAW_OCTAVE_SIZE;
		}

		MIDIRawNote GetKeyNoteRawDelta(MusicKey key, MIDIRawNote note){
			MIDIRawNote delta = (note - key.key) % RAW_OCTAVE_SIZE;
			return delta < 0 ? RAW_OCTAVE_SIZE + delta : delta;
		}

		TDNote GetKeyNoteDelta(MusicKey key, MIDIRawNote note){
			char delta = GetKeyNoteRawDelta(key, note);
			uchar major = key.major ? 1 : 0;
			const uchar* res = std::find(std::begin(key_mapping_table[major]), std::end(key_mapping_table[major]), delta);
			if (res == std::end(key_mapping_table[major])){
				return -1;
			}
			else {
				return res - key_mapping_table[major];
			}
		}

		char GetNoteOctave(MIDIRawNote note, MusicKey key){
			return ((note - key.key) / RAW_OCTAVE_SIZE) - 1;
		}

		bool IsNoteInKey(MIDIRawNote note, MusicKey key){
			return GetKeyNoteDelta(key, note) >= 0;
		}

		MusicKey GetKeyFromKey(uchar k){
			MusicKey key; key.key = k % RAW_OCTAVE_SIZE; key.major = ((k / RAW_OCTAVE_SIZE) > 0);
			return key;
		}

		uchar GetKeyFromKey(MusicKey key){
			return key.key + (key.major ? 1 : 0) * RAW_OCTAVE_SIZE;
		}

		std::vector<MusicKey> GetPossibleKeys(std::vector<MIDIRawNote> notes){
			std::vector<MusicKey> ret;
			bool inKeys[24] = {};
			std::fill(inKeys, inKeys + 24, true);

			for (uchar i = 0; i < 24; i++){
				MusicKey key = GetKeyFromKey(i);
				for (auto note : notes){
					inKeys[i] = IsNoteInKey(note, key) && inKeys[i];
				}
				if (inKeys[i])
					ret.push_back(key);
			}
			return ret;
		}

		MoodMeter Moods::operator[](uint index){ return (this->moods)[index]; }

		// TDMusicMsg

		const char * TDMusicMsg::JSON_TD_MUSIC_MSG_CONSTRUCTOR = "td_music_message";
		const char * TDMusicMsg::JSON_TD_MUSIC_MSG_TYPE = "type";
		const char * TDMusicMsg::JSON_TD_MUSIC_MSG_TIME_DELTA = "time_delta";
		const char * TDMusicMsg::JSON_TD_MUSIC_MSG_DATA_BYTES = "data_bytes";

		TDMusicMsg::TDMusicMsg(){

		}
		TDMusicMsg::TDMusicMsg(TDTimef timeDelta, enums::TDMsgType::TDMsgType type):
			timeDelta(timeDelta), type(type)
		{

		}
		TDMusicMsg::TDMusicMsg(const TDMusicMsg &msg){

		}
		TDMusicMsg::~TDMusicMsg(){

		}
		TDMusicMsg& TDMusicMsg::operator = (const TDMusicMsg & other){
			type = other.type;
			timeDelta = other.timeDelta;
			return *this;
		}
		
		uchar TDMusicMsg::GetType() { return this->type; }
		TDTimef TDMusicMsg::GetTimeDelta() { return this->timeDelta; }

		enums::TDMsgType::TDMsgType TDMusicMsg::SetType(enums::TDMsgType::TDMsgType _type) { this->type = _type; return this->type; }
		TDTimef TDMusicMsg::SetTimeDelta(TDTimef _timeDelta) { this->timeDelta = _timeDelta; return _timeDelta; }

		Json::Value TDMusicMsg::JSONSerialize(){
			Json::Value jsonValue;
			jsonValue[JSON_CONSTRUCTOR] = JSON_TD_MUSIC_MSG_CONSTRUCTOR;
			jsonValue[JSON_TD_MUSIC_MSG_TYPE] = this->type;
			jsonValue[JSON_TD_MUSIC_MSG_TIME_DELTA] = this->timeDelta;
			Json::Value jsonDataBytes;
			for (int i = 0; i < 6; i++){
				jsonDataBytes[i] = this->dataBytes[i];
			}
			jsonValue[JSON_TD_MUSIC_MSG_DATA_BYTES] = jsonDataBytes;
			return jsonValue;
		}

		const uchar * TDMusicMsg::setData(uchar data[6]){
			for (int i = 0; i < 6; i++){
				this->dataBytes[i] = data[i];
			}
			return this->dataBytes;
		}
		const uchar * TDMusicMsg::getData(){
			return this->dataBytes;
		}

		std::string TDMusicMsg::JSONStrSerialize(){
			Json::Value jsonValue = this->JSONSerialize();
			return jsonValue.toStyledString();
		}
		
		void TDMusicMsg::JSONDeserialize(std::string jsonStr){

		}
		void TDMusicMsg::JSONDeserialize(Json::Value jsonValue){

		}

		//TDChannelMsg

		const char * TDChannelMsg::JSON_TD_CHANNEL_MSG_CONSTRUCTOR = "channel_msg";

		TDChannelMsg::TDChannelMsg(){

		}
		TDChannelMsg::TDChannelMsg(const TDChannelMsg &other){
			
		}
		TDChannelMsg::~TDChannelMsg(){

		}
		TDChannelMsg& TDChannelMsg::operator = (const TDChannelMsg & other){
			return *this;
		}


		Json::Value TDChannelMsg::JSONSerialize(){
			Json::Value jsonValue = this->TDMusicMsg::JSONSerialize();
			jsonValue[JSON_CONSTRUCTOR] = JSON_TD_CHANNEL_MSG_CONSTRUCTOR;
			return jsonValue;
		}
		std::string TDChannelMsg::JSONStrSerialize(){
			Json::Value jsonValue = this->JSONSerialize();
			return jsonValue.toStyledString();
		}
		
		void TDChannelMsg::JSONDeserialize(std::string jsonStr){

		}
		void TDChannelMsg::JSONDeserialize(Json::Value jsonValue){

		}

		//TDNoteMsg

		const char * TDNoteMsg::JSON_TD_NOTE_MSG_CONSTRUCTOR = "note_msg";
		const char * TDNoteMsg::JSON_TD_NOTE_MSG_NOTE = "note";
		const char * TDNoteMsg::JSON_TD_NOTE_MSG_VELOCITY = "velocity";
		const char * TDNoteMsg::JSON_TD_NOTE_MSG_LENGTH = "note_length";
		const char * TDNoteMsg::JSON_TD_NOTE_MSG_NEXT_TIME_DELTA = "next_note_time_delta";

		TDNoteMsg::TDNoteMsg(){ note = 0; velocity = 0; noteLength = 0; nextNoteTimeDelta = 0; }
		TDNoteMsg::TDNoteMsg(uchar note, uchar velocity, TDTimef noteLength, TDTimef nextNoteTimeDelta, TDTimef timeDelta):
			note(note), velocity(velocity), noteLength(noteLength), nextNoteTimeDelta(nextNoteTimeDelta)
		{
			this->timeDelta = timeDelta;
			this->type = enums::TDMsgType::NOTE;
		}
		TDNoteMsg::TDNoteMsg(const TDNoteMsg &other){
			note = other.note;
			velocity = other.velocity;
			noteLength = other.noteLength;
			nextNoteTimeDelta = other.nextNoteTimeDelta;
		}
		TDNoteMsg::~TDNoteMsg(){

		}
		TDNoteMsg& TDNoteMsg::operator = (const TDNoteMsg & other){
			note = other.note;
			velocity = other.velocity;
			noteLength = other.noteLength;
			nextNoteTimeDelta = other.nextNoteTimeDelta;
			return *this;
		}

		TDTimef TDNoteMsg::GetNoteLength() { return this->noteLength; }
		uchar TDNoteMsg::GetNote() { return this->note; }
		uchar TDNoteMsg::GetVelocity() { return this->velocity; }
		TDTimef TDNoteMsg::GetNextNoteTimeDelta() { return this->nextNoteTimeDelta; }

		TDTimef TDNoteMsg::setNoteLength(TDTimef _noteLength) { this->noteLength = _noteLength; return this->noteLength; }
		uchar TDNoteMsg::SetNote(uchar _note) { this->note = _note; return this->note; }
		uchar TDNoteMsg::SetVelocity(uchar _velocity) { this->velocity = _velocity; return this->velocity; }
		TDTimef TDNoteMsg::SetNextNoteTimeDelta(TDTimef _nextNoteTimeDelta) { this->nextNoteTimeDelta = _nextNoteTimeDelta; return this->nextNoteTimeDelta; }

		Json::Value TDNoteMsg::JSONSerialize(){
			Json::Value jsonValue = this->TDChannelMsg::JSONSerialize();
			jsonValue[JSON_CONSTRUCTOR] = JSON_TD_NOTE_MSG_CONSTRUCTOR;
			jsonValue[JSON_TD_NOTE_MSG_NOTE] = this->note;
			jsonValue[JSON_TD_NOTE_MSG_VELOCITY] = this->velocity;
			jsonValue[JSON_TD_NOTE_MSG_LENGTH] = this->noteLength;
			jsonValue[JSON_TD_NOTE_MSG_NEXT_TIME_DELTA] = this->nextNoteTimeDelta;
			return jsonValue;
		}
		std::string TDNoteMsg::JSONStrSerialize(){
			Json::Value jsonValue = this->JSONSerialize();
			return jsonValue.toStyledString();
		}
		
		void TDNoteMsg::JSONDeserialize(std::string jsonStr){

		}
		void TDNoteMsg::JSONDeserialize(Json::Value jsonValue){

		}

		// TDMetaMsg
		const char * TDMetaMsg::JSON_TD_META_MSG_CONSTRUCTOR = "meta_msg";
		const char * TDMetaMsg::JSON_TD_META_MSG_TYPE = "meta_type";

		TDMetaMsg::TDMetaMsg(){

		}
		TDMetaMsg::TDMetaMsg(TDTimef timeDelta){
			this->type = enums::TDMsgType::META;
			this->timeDelta = timeDelta;
		}
		TDMetaMsg::TDMetaMsg(TDMetaMsg &msg){
			for (int i = 0; i < 6; i++){ dataBytes[i] = msg.dataBytes[0]; }
			this->type = msg.type;
			this->timeDelta = msg.timeDelta;
		}
		TDMetaMsg::~TDMetaMsg(){

		}
		TDMetaMsg& TDMetaMsg::operator = (const TDMetaMsg & other){
			for (int i = 0; i < 6; i++){ (*this).dataBytes[i] = other.dataBytes[0]; }
			(*this).type = other.type;
			(*this).timeDelta = other.timeDelta;
			return *this;
		}

		std::string TDMetaMsg::JSONStrSerialize(){
			return this->JSONSerialize().toStyledString();
		}
		Json::Value TDMetaMsg::JSONSerialize(){
			Json::Value jsonValue = this->TDMusicMsg::JSONSerialize();
			jsonValue[JSON_CONSTRUCTOR] = JSON_TD_META_MSG_CONSTRUCTOR;
			jsonValue[JSON_TD_META_MSG_TYPE] = this->metaType;
			return jsonValue;
		}
		void TDMetaMsg::JSONDeserialize(std::string jsonStr){

		}
		void TDMetaMsg::JSONDeserialize(Json::Value jsonValue){

		}


		// TDTempoMsg

		const char * TDTempoMsg::JSON_TD_TEMPO_MSG_CONSTRUCTOR = "tempo_msg";
		const char * TDTempoMsg::JSON_TD_TEMPO_MSG_TEMPO = "tempo";

		TDTempoMsg::TDTempoMsg(){

		}
		TDTempoMsg::TDTempoMsg(uint tempo, TDTimef timeDelta):
			tempo(tempo)
		{
			this->timeDelta = timeDelta;
			this->type = enums::TDMsgType::META;
			this->metaType = enums::TDMsgType::TEMPO;
		}
		TDTempoMsg::TDTempoMsg(TDTempoMsg &msg){
			for (int i = 0; i < 6; i++){ dataBytes[i] = msg.dataBytes[0]; }
			tempo = msg.tempo;
			type = msg.type;
			timeDelta = msg.timeDelta;
		}
		TDTempoMsg::~TDTempoMsg(){

		}
		TDTempoMsg& TDTempoMsg::operator = (const TDTempoMsg & other){
			for (int i = 0; i < 6; i++){ dataBytes[i] = other.dataBytes[0]; }
			tempo = other.tempo;
			type = other.type;
			timeDelta = other.timeDelta;
			return *this;
		}

		std::string TDTempoMsg::JSONStrSerialize(){
			return this->JSONSerialize().toStyledString();
		}
		Json::Value TDTempoMsg::JSONSerialize(){
			Json::Value jsonValue = TDMetaMsg::JSONSerialize();
			jsonValue[JSON_CONSTRUCTOR] = JSON_TD_TEMPO_MSG_CONSTRUCTOR;
			jsonValue[JSON_TD_TEMPO_MSG_TEMPO] = this->tempo;
			return jsonValue;
		}
		void TDTempoMsg::JSONDeserialize(std::string jsonStr){

		}
		void TDTempoMsg::JSONDeserialize(Json::Value jsonValue){

		}

		//Timesig
		const char * TDTimeSigMsg::JSON_TD_TIMESIG_MSG_CONSTRUCTOR = "timesig_msg";
		const char * TDTimeSigMsg::JSON_TD_TIMESIG_MSG_TIMESIG = "timesig";

		TDTimeSigMsg::TDTimeSigMsg(){

		}
		TDTimeSigMsg::TDTimeSigMsg(std::array<uchar, 4> timesig, TDTimef timeDelta):
			timesig(timesig)
		{
			this->timeDelta = timeDelta;
			this->metaType = enums::TDMsgType::TIMESIG;
		}
		TDTimeSigMsg::TDTimeSigMsg(TDTimeSigMsg &msg){
			this->timesig = msg.timesig;
			this->timeDelta = msg.timeDelta;
			this->type = msg.type;
		}
		TDTimeSigMsg::~TDTimeSigMsg(){

		}
		TDTimeSigMsg& TDTimeSigMsg::operator = (const TDTimeSigMsg & other){
			(*this).timesig = other.timesig;
			(*this).timeDelta = other.timeDelta;
			(*this).type = other.type;
			return (*this);
		}

		std::string TDTimeSigMsg::JSONStrSerialize(){
			return this->JSONSerialize().toStyledString();
		}
		Json::Value TDTimeSigMsg::JSONSerialize(){
			Json::Value jsonValue = this->TDMetaMsg::JSONSerialize();
			jsonValue[JSON_CONSTRUCTOR] = JSON_TD_TIMESIG_MSG_CONSTRUCTOR;
			Json::Value jsonTimeSig = helper::jsonSerialize(timesig);
			jsonValue[JSON_TD_TIMESIG_MSG_TIMESIG] = jsonTimeSig;
			return jsonValue;
		}
		void TDTimeSigMsg::JSONDeserialize(std::string jsonStr){

		}
		void TDTimeSigMsg::JSONDeserialize(Json::Value jsonValue){

		}

		// TDMusicTrack

		const char * TDMusicTrack::JSON_TD_MUSIC_TRACK_CONSTRUCTOR = "td_music_track";
		const char * TDMusicTrack::JSON_TD_MUSIC_TRACK_INSTRUMENT = "instrument";
		const char * TDMusicTrack::JSON_TD_MUSIC_TRACK_IS_TRACK_ZERO = "track_zero";
		const char * TDMusicTrack::JSON_TD_MUSIC_TRACK_MESSAGES = "messages";

		TDMusicTrack::TDMusicTrack(){

		}
		TDMusicTrack::TDMusicTrack(const TDMusicTrack &other){
			messages = other.messages;
			inst_num = other.inst_num;
			track_zero = other.track_zero;
		}
		TDMusicTrack::~TDMusicTrack(){

		}
		TDMusicTrack& TDMusicTrack::operator = (const TDMusicTrack & other){
			messages = other.messages;
			inst_num = other.inst_num;
			track_zero = other.track_zero;
			return *this;
		}

		enums::MIDIInstrument::MIDIInstrument TDMusicTrack::GetInstrument(){
			return this->inst_num;
		}
		enums::MIDIInstrument::MIDIInstrument TDMusicTrack::SetInstrument(enums::MIDIInstrument::MIDIInstrument _inst_num){
			return this->inst_num=_inst_num;
		}

		const std::vector<TDMusicMsg *> * TDMusicTrack::GetMessages(){
			return &(this->messages);
		}
		void TDMusicTrack::AppendMsg(TDMusicMsg * msg){
			this->messages.push_back(msg);
		}
		void TDMusicTrack::RemoveMsg(std::vector<TDMusicMsg *>::iterator msg){
			this->messages.erase(msg);
		}

		ulong TDMusicTrack::size(){
			return this->messages.size();
		}

		Json::Value TDMusicTrack::JSONSerialize(){
			Json::Value jsonValue;
			jsonValue[JSON_CONSTRUCTOR] = JSON_TD_MUSIC_TRACK_CONSTRUCTOR;
			jsonValue[JSON_TD_MUSIC_TRACK_INSTRUMENT] = this->inst_num;
			jsonValue[JSON_TD_MUSIC_TRACK_IS_TRACK_ZERO] = this->track_zero;
			Json::Value jsonMessages;
			for (auto it = this->messages.begin(); it != this->messages.end(); ++it){
				jsonMessages.append(Json::Value((*it)->JSONSerialize()));
			}
			jsonValue[JSON_TD_MUSIC_TRACK_MESSAGES] = jsonMessages;
			return jsonValue;
		}
		std::string TDMusicTrack::JSONStrSerialize(){
			Json::Value jsonValue = this->JSONSerialize();
			return jsonValue.toStyledString();
		}
		
		void TDMusicTrack::JSONDeserialize(std::string jsonStr){

		}
		void TDMusicTrack::JSONDeserialize(Json::Value jsonValue){

		}

		// Beatme! Touchdown! style TDMusic

		const char * TDMusic::JSON_TD_MUSIC_CONSTRUCTOR = "td_music";
		const char * TDMusic::JSON_TD_MUSIC_HEADER = "header";
		const char * TDMusic::JSON_TD_MUSIC_IS_DELTA = "is_delta";
		const char * TDMusic::JSON_TD_MUSIC_TRACKS = "tracks";

		TDMusic::TDMusic(){

		}
		TDMusic::TDMusic(const char * midi_file_path, bool _isDelta) :
			isDelta(_isDelta){

		}
		TDMusic::TDMusic(jdksmidi::MIDIMultiTrack *mlt, bool _isDelta) :
			isDelta(_isDelta){

		}
		TDMusic::TDMusic(TDMusic &other){
			header = other.header;
			tracks = other.tracks;
			isDelta = other.isDelta;
		}
		TDMusic::~TDMusic(){

		}
		TDMusic& TDMusic::operator =(const TDMusic & other){
			header = other.header;
			tracks = other.tracks;
			isDelta = other.isDelta;
			return *this;
		}


		bool TDMusic::IsDelta() { return isDelta; }
		bool TDMusic::IsDelta(bool _delta){ this->isDelta = isDelta; return this->isDelta; }

		int TDMusic::ScanMidi(const char * midi_file_path){
			jdksmidi::MIDIMultiTrack * mlt = new jdksmidi::MIDIMultiTrack();
			helper::jdksmidi_helper::ParseMidiFile(midi_file_path, mlt);
			return ScanMidi(mlt);
		}
		int TDMusic::ScanMidi(jdksmidi::MIDIMultiTrack *mlt){
			if (mlt != NULL){
				jdksmidi::MIDIMultiTrackIterator it = jdksmidi::MIDIMultiTrackIterator(mlt);
				uchar num_tracks = mlt->GetNumTracks();
				uint num_events = mlt->GetNumEvents();
				std::unordered_map<uchar, uchar> chanInstMap;
				std::unordered_map<uchar, uchar> trackMap;

				uchar ppq = mlt->GetClksPerBeat();

				if (num_tracks > 0 && num_events > 0){
					tracks = std::vector<TDMusicTrack *>();
					TDMusicTrack * track_zero = new TDMusicTrack();
					tracks.push_back(track_zero);

					header = TDMusicHeader();

					int track_num = 0;
					const jdksmidi::MIDITimedBigMessage *msg;

					it.GoToTime(0);
					do {
						it.GetCurEvent(&track_num, &msg);
						if (track_num == 0 || msg->IsMetaEvent()){
							TDMusicMsg * tdMsg = GetMusicMessage(it, ppq);
							tracks[0]->AppendMsg(tdMsg);
						}
						if (msg->GetType() == jdksmidi::PROGRAM_CHANGE){
							uchar channel = msg->GetChannel();
							uchar inst = msg->GetPGValue();

							auto it = chanInstMap.find(channel);
							if (it != chanInstMap.end())
								if (it->second != inst)
									it->second = inst;
								else
									chanInstMap.insert(std::pair<uchar, uchar>(channel, inst));
							else
								chanInstMap.insert(std::pair<uchar, uchar>(channel, inst));
						}
						else if (msg->GetType() == jdksmidi::NOTE_ON && msg->GetVelocity()>0) {
							TDMusicTrack * track;
							TDMusicMsg * tdMsg = GetMusicMessage(it, ppq);
							uchar channel = msg->GetChannel();
							auto it = trackMap.find(track_num);
							if (it == trackMap.end()){
								track = new TDMusicTrack();
								auto iti = chanInstMap.find(channel);
								if (iti != chanInstMap.end()){
									track->SetInstrument((enums::MIDIInstrument::MIDIInstrument)iti->second);
								}
								tracks.push_back(track);
								trackMap.insert(std::pair<uchar, uchar>(track_num, tracks.size()-1));
							}
							else {
								track = tracks[it->second];
							}
							track->AppendMsg(tdMsg);
						}



					} while (it.GoToNextEvent());
				}

				return 0;
			}
			else
				return -1;
		}


		jdksmidi::MIDIMultiTrack TDMusic::ToJdksMidi(){
			jdksmidi::MIDIMultiTrack ret;
			return ret;
		}
		int TDMusic::ToMidiFile(FILE * file){
			jdksmidi::MIDIMultiTrack mlt = this->ToJdksMidi();

			return 0;
		}

		const std::vector<TDMusicTrack *> * TDMusic::GetTracks(){
			return &(this->tracks);
		}
		void TDMusic::AppendTrack(TDMusicTrack * track){
			this->tracks.push_back(track);
		}
		void TDMusic::RemoveTrack(std::vector<TDMusicTrack *>::iterator track){
			this->tracks.erase(track);
		}

		uchar TDMusic::GetNumTracks(){
			return (uchar)(this->tracks.size());
		}
		ulong TDMusic::GetNumEvents(){
			ulong count = 0;
			for (auto it = this->tracks.begin(); it != this->tracks.end(); ++it){
				count += (*it)->GetMessages()->size();
			}
			return count;
		}

		Json::Value TDMusic::JSONSerialize(){
			Json::Value jsonValue;
			jsonValue[JSON_CONSTRUCTOR] = JSON_TD_MUSIC_CONSTRUCTOR;
			jsonValue[JSON_TD_MUSIC_HEADER] = this->header.JSONSerialize();
			jsonValue[JSON_TD_MUSIC_IS_DELTA] = this->isDelta;

			Json::Value jsonTracksValue;
			for (auto it = this->tracks.begin(); it != this->tracks.end(); ++it){
				jsonTracksValue.append(Json::Value((*it)->JSONSerialize()));
			}
			jsonValue[JSON_TD_MUSIC_TRACKS] = jsonTracksValue;
			return jsonValue;
		}
		std::string TDMusic::JSONStrSerialize(){
			Json::Value jsonValue = this->JSONSerialize();
			return jsonValue.toStyledString();
		}

		void TDMusic::JSONDeserialize(std::string jsonStr){

		}
		void TDMusic::JSONDeserialize(Json::Value jsonValue){

		}


		// others

		bool MsgNotNoteOff(const jdksmidi::MIDITimedBigMessage * msg){
			uchar type = msg->GetType();
			return (type == jdksmidi::NOTE_OFF ||
				(type == jdksmidi::NOTE_ON && msg->GetVelocity() == 0) ||
				(type == jdksmidi::CONTROL_CHANGE &&
				msg->GetController() == jdksmidi::C_ALL_NOTES_OFF || msg->GetController() == jdksmidi::C_ALL_SOUNDS_OFF));
		}

		uint GetNextNoteTime(jdksmidi::MIDIMultiTrackIterator it, enums::MIDIMsgType::MIDIMsgType type){
			const jdksmidi::MIDITimedBigMessage* cur;
			const jdksmidi::MIDITimedBigMessage* next;
			int cur_track;
			uchar next_type = 0;
			uchar next_vel = 0;
			int next_track;
			bool comparison = false;

			it.GetCurEvent(&cur_track, &cur);
			if (cur->GetType() == jdksmidi::NOTE_ON){
				uchar note = cur->GetNote();
				while (it.GoToNextEvent()){
					it.GetCurEvent(&next_track, &next);
					if (next_track == cur_track){
						if (note == next->GetNote()){
							next_type = next->GetType();
							comparison = type == enums::MIDIMsgType::NOTE_OFF ?
								(next_type == jdksmidi::NOTE_OFF ||
								(next_type == jdksmidi::NOTE_ON && next->GetVelocity() == 0) ||
								(next_type == jdksmidi::CONTROL_CHANGE &&
								next->GetController() == jdksmidi::C_ALL_NOTES_OFF || next->GetController() == jdksmidi::C_ALL_SOUNDS_OFF)) :
								type == enums::MIDIMsgType::NOTE_ON ?
								(next_type == jdksmidi::NOTE_ON && next->GetVelocity() > 0) :
								false;
							if (comparison){
								return next->GetTime();
							}
						}
					}
				}
			}
			return 0;
		}

		uint GetNoteOffTime(jdksmidi::MIDIMultiTrackIterator it){
			return GetNextNoteTime(it, enums::MIDIMsgType::NOTE_OFF);
		}

		uint GetNextNoteOnTime(jdksmidi::MIDIMultiTrackIterator it){
			return GetNextNoteTime(it, enums::MIDIMsgType::NOTE_ON);
		}

		TDMusicMsg * GetMusicMessage(jdksmidi::MIDIMultiTrackIterator it, ushort ppq){
			jdksmidi::MIDIMultiTrackIterator it2 = it;
			int track_num; 
			const jdksmidi::MIDITimedBigMessage *msg;
			it2.GetCurEvent(&track_num, &msg);
			TDMusicMsg * ret = NULL;

			if (msg->IsChannelEvent()){
				int type = msg->GetType();
				uchar velocity;
				uint time = msg->GetTime();
				uint offtime;
				uint nexttime;

				switch (type){
				case jdksmidi::NOTE_ON:
					velocity = msg->GetVelocity();
					offtime = GetNoteOffTime(it2);
					nexttime = GetNextNoteOnTime(it2);
					if (velocity > 0){
						ret = new TDNoteMsg(msg->GetNote(), velocity,
							btm_td::helper::jdksmidi_helper::GetTimeInBeats(offtime - time, ppq),
							btm_td::helper::jdksmidi_helper::GetTimeInBeats(nexttime, ppq),
							btm_td::helper::jdksmidi_helper::GetTimeInBeats(time, ppq));
					}
					break;
				default:
					if (MsgNotNoteOff(msg)){
						ret = new TDMusicMsg(btm_td::helper::jdksmidi_helper::GetTimeInBeats(time, ppq), enums::TDMsgType::UNKNOWN);
					}
					break;
				}
			}
			else if (msg->IsMetaEvent()){
				int metaType = msg->GetMetaType();
				uint tempo;
				uint time = msg->GetTime();;
				TDTimef timef = btm_td::helper::jdksmidi_helper::GetTimeInBeats(time, ppq);
				std::array<uchar, 4> timesig;
				switch (metaType){
				case jdksmidi::META_TEMPO:
					tempo = msg->GetTempo();
					ret = new TDTempoMsg(tempo, timef);
					break;
				case jdksmidi::META_TIMESIG:
					timesig = helper::jdksmidi_helper::GetMIDITimeSig(msg);
					ret = new TDTimeSigMsg(timesig, timef);
					break;
				default:
					ret = new TDMetaMsg(timef);
					break;
				}
			}
			if (ret != NULL){
				uchar data[6] = { msg->GetByte1(),
					msg->GetByte2(),
					msg->GetByte3(),
					msg->GetByte4(),
					msg->GetByte5(),
					msg->GetByte6() };
				ret->setData(data);
			}
			return ret;
		}
		
	}
}
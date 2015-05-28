
#ifndef BTM_TD_MUSIC_H
#define BTM_TD_MUSIC_H

#include "btm_td_enums.h"
#include "btm_td_jdksmidi_helper.h"
#include "btm_td_db_helper.h"

namespace btm_td {
	namespace music{
		extern const uchar RAW_OCTAVE_SIZE;
		extern const uchar TD_OCTAVE_SIZE;
		extern const uchar key_mapping_table[2][7];
		extern const char* key_name_table[24];

		extern const char * JSON_CONSTRUCTOR;

		void InitBtmTdMusic();

		typedef struct MusicKey{
			/**	Touchdown-style music key struct container
			*/
			uchar key;
			/// The music key, in raw, 0(C) to 11(B)
			bool major;
			/// True for major, false for minor
			uchar getUChar()
				/// Get the key in 0(C) to 11(B) if major, 12(C) to 23(B) if minor
			{
				return key + (major ? 1 : 0) * RAW_OCTAVE_SIZE;
			}
			MusicKey() :
				/// Default constructor, Default key is C Major
				key(0), major(true){}
			MusicKey(uchar _key) :
				/// Constructor from 0 to 23 key-style
				key(_key % RAW_OCTAVE_SIZE), major(key / RAW_OCTAVE_SIZE>0){}
			MusicKey(uchar _key, bool _major) :
				/// Constructor from 0 to 11 key and major/minor key-style
				key(_key), major(_major){}
		} _MusicKey;

		typedef char TDNote;
		/// Touchdown-style key-note difference
		typedef float TDTimef;
		/// Touchdown-style time, measured in beats

		typedef uchar MIDIRawNote;
		/// MIDI raw note style
		typedef uint MIDIRawTime;
		/// MIDI raw time style, the value is a quarter note (a beat) multiplied by PPQ

		MIDIRawNote GetRawFromKeyNoteDelta(TDNote note, MusicKey key = MusicKey(), uchar octave = 0);
		/**	Gets MIDI raw note code from Touchdown style key and note value
		*	Returns: MIDI raw note code
		*	Params:
		*		note:	Touchdown style key-note delta
		*		key:	Touchdown style music key, default is C Major
		*		octave:	Touchdown style note octave, default is 0
		*
		*/

		MIDIRawNote GetKeyNoteRawDelta(MusicKey key, MIDIRawNote note);
		/**	Gets MIDI raw difference from MIDI raw note code to Touchdown-style 
		*	music key modulo-ed by octave
		*	Returns:	MIDI raw note-key difference
		*	Params:
		*		key:	Touchdown style music key, default is C Major
		*		note:	Touchdown style key-note delta
		*/

		TDNote GetKeyNoteDelta(MusicKey key, MIDIRawNote note);
		/**	Gets Touchdown-style difference between key and MIDI raw note code
		*	Returns:	Touchdown-style key-(raw)note difference, 
		*				-1 if the note not in the music key
		*	Params:
		*		key:	Touchdown style music key, default is C Major
		*		note:	MIDI raw note code
		*/

		char GetNoteOctave(MIDIRawNote note, MusicKey key = MusicKey());
		/**	Gets the octave the MIDI raw note is in. 
		*	Returns:	Touchdown-style key-(raw)note difference,
		*				-1 if the note not in the music key
		*	Params:
		*		note:	MIDI raw note code
		*		key:	Touchdown style music key, default is C Major
		*/

		bool IsNoteInKey(MIDIRawNote note, MusicKey key = MusicKey());
		/**	Gets the octave the MIDI raw note is in.
		*	Returns:	True if the note is in the key
		*				False if the note is not in the key
		*	Params:
		*		note:	MIDI raw note code
		*		key:	Touchdown style music key, default is C Major
		*/

		std::vector<MusicKey> GetPossibleKeys(std::vector<MIDIRawNote> notes);
		/**	Gets all possible keys all of the MIDI raw notes is in
		*	Returns:	Vector of possible MusicKeys
		*	Params:
		*		notes:	Vector of MIDI raw notes which keys to be get
		*/

		class TDMusicMsg 
		/** Container of Touchdown-style Music Message, derived from MIDI Message
		*/
		{
		public:
			static const char * JSON_TD_MUSIC_MSG_CONSTRUCTOR;
			static const char * JSON_TD_MUSIC_MSG_TYPE;
			static const char * JSON_TD_MUSIC_MSG_TIME_DELTA;
			static const char * JSON_TD_MUSIC_MSG_DATA_BYTES;

			TDMusicMsg();
			TDMusicMsg(TDTimef timeDelta, enums::TDMsgType::TDMsgType type);
			TDMusicMsg(const TDMusicMsg &msg);
			~TDMusicMsg();
			TDMusicMsg& operator = (const TDMusicMsg & other);

			uchar GetType();
			TDTimef GetTimeDelta();

			enums::TDMsgType::TDMsgType SetType(enums::TDMsgType::TDMsgType _type);
			TDTimef SetTimeDelta(TDTimef _timeDelta);
			const uchar * setData(uchar data[6]);
			const uchar * getData();

			virtual std::string JSONStrSerialize();
			virtual Json::Value JSONSerialize();
			virtual void JSONDeserialize(std::string jsonStr="");
			virtual void JSONDeserialize(Json::Value jsonValue);

		protected:
			enums::TDMsgType::TDMsgType type;
			TDTimef timeDelta;
			uchar dataBytes[6];
		};

		class TDChannelMsg : public TDMusicMsg {
		public:
			static const char * JSON_TD_CHANNEL_MSG_CONSTRUCTOR;
			TDChannelMsg();
			TDChannelMsg(const TDChannelMsg &other);
			~TDChannelMsg();
			TDChannelMsg& operator = (const TDChannelMsg & other);

			virtual std::string JSONStrSerialize();
			virtual Json::Value JSONSerialize();
			virtual void JSONDeserialize(std::string jsonStr="");
			virtual void JSONDeserialize(Json::Value jsonValue);

		protected:
			
		};

		class TDNoteMsg : public TDChannelMsg {
		public:
			static const char * JSON_TD_NOTE_MSG_CONSTRUCTOR;
			static const char * JSON_TD_NOTE_MSG_NOTE;
			static const char * JSON_TD_NOTE_MSG_VELOCITY;
			static const char * JSON_TD_NOTE_MSG_LENGTH;
			static const char * JSON_TD_NOTE_MSG_NEXT_TIME_DELTA;

			TDNoteMsg();
			TDNoteMsg(uchar note, uchar velocity, TDTimef noteLength, TDTimef nextNoteTimeDelta, TDTimef timeDelta);
			TDNoteMsg(const TDNoteMsg &other);
			~TDNoteMsg();
			TDNoteMsg& operator = (const TDNoteMsg & other);

			TDTimef GetNoteLength();
			uchar GetNote();
			uchar GetVelocity();
			TDTimef GetNextNoteTimeDelta();

			TDTimef setNoteLength(TDTimef _noteLength);
			uchar SetNote(uchar _note);
			uchar SetVelocity(uchar _velocity);
			TDTimef SetNextNoteTimeDelta(TDTimef _nextNoteTimeDelta);

			std::string JSONStrSerialize();
			Json::Value JSONSerialize();
			void JSONDeserialize(std::string jsonStr="");
			void JSONDeserialize(Json::Value jsonValue);

		protected:
			uchar note;
			uchar velocity;
			TDTimef noteLength;
			TDTimef nextNoteTimeDelta;

		};

		class TDControlMsg : public TDChannelMsg {
		public:
			TDControlMsg();
			TDControlMsg(TDControlMsg &msg);
			~TDControlMsg();
			TDControlMsg& operator = (const TDControlMsg & other);

			virtual std::string JSONStrSerialize();
			virtual Json::Value JSONSerialize();
			virtual void JSONDeserialize(std::string jsonStr = "");
			virtual void JSONDeserialize(Json::Value jsonValue);

		protected:

		};

		class TDChannelControlMsg : public TDChannelMsg {
		public:
			TDChannelControlMsg();
			TDChannelControlMsg(TDChannelControlMsg &msg);
			~TDChannelControlMsg();
			TDChannelControlMsg& operator = (const TDChannelControlMsg & other);

			std::string JSONStrSerialize();
			Json::Value JSONSerialize();
			void JSONDeserialize(std::string jsonStr="");
			void JSONDeserialize(Json::Value jsonValue);

		protected:

		};

		class TDMetaMsg : public TDMusicMsg{
		public:
			static const char * JSON_TD_META_MSG_CONSTRUCTOR;
			static const char * JSON_TD_META_MSG_TYPE;

			TDMetaMsg();
			TDMetaMsg(TDTimef timeDelta);
			TDMetaMsg(TDMetaMsg &msg);
			~TDMetaMsg();
			TDMetaMsg& operator = (const TDMetaMsg & other);

			virtual std::string JSONStrSerialize();
			virtual Json::Value JSONSerialize();
			virtual void JSONDeserialize(std::string jsonStr="");
			virtual void JSONDeserialize(Json::Value jsonValue);

		protected:
			enums::TDMsgType::TDMetaMsgType metaType;
		};

		class TDTextMsg : public TDMetaMsg {
		public:
			TDTextMsg();
			TDTextMsg(TDTextMsg &msg);
			~TDTextMsg();
			TDTextMsg& operator = (const TDTextMsg & other);

			std::string JSONStrSerialize();
			Json::Value JSONSerialize();
			void JSONDeserialize(std::string jsonStr="");
			void JSONDeserialize(Json::Value jsonValue);

		protected:

		};

		class TDTempoMsg : public TDMetaMsg {
		public:
			static const char * JSON_TD_TEMPO_MSG_CONSTRUCTOR;
			static const char * JSON_TD_TEMPO_MSG_TEMPO;

			TDTempoMsg();
			TDTempoMsg(uint tempo, TDTimef timeDelta);
			TDTempoMsg(TDTempoMsg &msg);
			~TDTempoMsg();
			TDTempoMsg& operator = (const TDTempoMsg & other);

			uint SetTempo(uint tempo){ return this->tempo = tempo; };
			uint GetTempo() { return this->tempo; };

			std::string JSONStrSerialize();
			Json::Value JSONSerialize();
			void JSONDeserialize(std::string jsonStr="");
			void JSONDeserialize(Json::Value jsonValue);

		protected:
			uint tempo;
		};

		class TDTimeSigMsg : public TDMetaMsg {
		public:
			static const char * JSON_TD_TIMESIG_MSG_CONSTRUCTOR;
			static const char * JSON_TD_TIMESIG_MSG_TIMESIG;

			TDTimeSigMsg();
			TDTimeSigMsg(std::array<uchar, 4> timesig, TDTimef timeDelta);
			TDTimeSigMsg(TDTimeSigMsg &msg);
			~TDTimeSigMsg();
			TDTimeSigMsg& operator = (const TDTimeSigMsg & other);

			std::array<uchar, 4> GetTimeSig() { return this->timesig; };
			std::array<uchar, 4> SetTimeSig(std::array<uchar, 4> timesig) { return this->timesig = timesig; };

			std::string JSONStrSerialize();
			Json::Value JSONSerialize();
			void JSONDeserialize(std::string jsonStr = "");
			void JSONDeserialize(Json::Value jsonValue);

		protected:
			std::array<uchar, 4> timesig;
		};

		class TDKeySigMsg : public TDMetaMsg {
		public:
			TDKeySigMsg();
			TDKeySigMsg(TDKeySigMsg &msg);
			~TDKeySigMsg();
			TDKeySigMsg& operator = (const TDKeySigMsg & other);

			std::string JSONStrSerialize();
			Json::Value JSONSerialize();
			void JSONDeserialize(std::string jsonStr="");
			void JSONDeserialize(Json::Value jsonValue);

		protected:

		};

		

		class TDMusicTrack{
		public:
			static const char * JSON_TD_MUSIC_TRACK_CONSTRUCTOR;
			static const char * JSON_TD_MUSIC_TRACK_INSTRUMENT;
			static const char * JSON_TD_MUSIC_TRACK_IS_TRACK_ZERO;
			static const char * JSON_TD_MUSIC_TRACK_MESSAGES;
			TDMusicTrack();
			TDMusicTrack(const TDMusicTrack &track);
			~TDMusicTrack();
			TDMusicTrack& operator = (const TDMusicTrack & other);

			enums::MIDIInstrument::MIDIInstrument GetInstrument();
			enums::MIDIInstrument::MIDIInstrument SetInstrument(enums::MIDIInstrument::MIDIInstrument _inst_num);

			const std::vector<TDMusicMsg *> * GetMessages();
			void AppendMsg(TDMusicMsg * msg);
			void RemoveMsg(std::vector<TDMusicMsg *>::iterator msg);

			ulong size();

			void GetNumEvents();

			std::string JSONStrSerialize();
			Json::Value JSONSerialize();
			void JSONDeserialize(std::string jsonStr="");
			void JSONDeserialize(Json::Value jsonValue);

		protected:
			std::vector<TDMusicMsg *> messages;
			enums::MIDIInstrument::MIDIInstrument inst_num;
			bool track_zero;
		};

		class TDMusic {
		public:
			static const char * JSON_TD_MUSIC_CONSTRUCTOR;
			static const char * JSON_TD_MUSIC_HEADER;
			static const char * JSON_TD_MUSIC_IS_DELTA;
			static const char * JSON_TD_MUSIC_TRACKS;
			TDMusic();
			TDMusic(const char * midi_file_path, bool _isDelta = false);
			TDMusic(jdksmidi::MIDIMultiTrack *mlt, bool _isDelta = false);
			TDMusic(std::string jsonStr);
			TDMusic(TDMusic &msc);
			~TDMusic();
			TDMusic& operator =(const TDMusic & other);

			bool IsDelta();
			bool IsDelta(bool _delta);

			int ScanMidi(const char * midi_file_path);
			int ScanMidi(jdksmidi::MIDIMultiTrack * mlt);

			jdksmidi::MIDIMultiTrack ToJdksMidi();
			int ToMidiFile(FILE * file);

			TDMusicHeader GetHeader();
			TDMusicHeader SetHeader(TDMusicHeader header);
			TDMusicHeader SetHeader( std::string songname = "",
				std::string songgroup = "",
				std::string composer = "",
				std::string genre = "",
				std::string subgenre = "",
				uchar clksPerBeat = 120,
				uint firstTempo = 500000,
				uchar firstKey = 60,
				std::array<uchar, 4> firstTimeSig = { { 4, 2, 24, 8 } },
				std::array<uchar, 5> moods = { { 3, 3, 3, 3, 3 } });

			const std::vector<TDMusicTrack *> * GetTracks();
			void AppendTrack(TDMusicTrack * track);
			void RemoveTrack(std::vector<TDMusicTrack *>::iterator track);

			uchar GetNumTracks();
			ulong GetNumEvents();

			std::string JSONStrSerialize();
			Json::Value JSONSerialize();
			void JSONDeserialize(std::string jsonStr="");
			void JSONDeserialize(Json::Value jsonValue);

		protected:
			TDMusicHeader header;
			std::vector<TDMusicTrack *> tracks;
			bool isDelta;

		};

		//int ScanAssets;
		uint GetNextNoteTime(jdksmidi::MIDIMultiTrackIterator it, enums::MIDIMsgType::MIDIMsgType type = enums::MIDIMsgType::NOTE_OFF);
		uint GetNoteOffTime(jdksmidi::MIDIMultiTrackIterator it);
		uint GetNextNoteTime(jdksmidi::MIDIMultiTrackIterator it);
		TDMusicMsg * GetMusicMessage(jdksmidi::MIDIMultiTrackIterator it, ushort ppq=96);
	}
}

#endif
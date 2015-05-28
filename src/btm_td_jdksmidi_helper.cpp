#include "btm_td_jdksmidi_helper.h"
#include "stdafx.h"

using namespace btm_td;

namespace btm_td {
	namespace helper {
		namespace jdksmidi_helper {
			std::string GetCustomSongName(jdksmidi::MIDIMultiTrack *mlt){
				int type;
				jdksmidi::MIDIMultiTrackIterator i(mlt);
				const jdksmidi::MIDITimedBigMessage *msg;
				std::ostringstream returnStream;

				i.GoToTime(0);

				do
				{
					int trk_num;

					if (i.GetCurEvent(&trk_num, &msg))
					{
						type = msg->GetMetaType();

						if (type == jdksmidi::META_TRACK_NAME){
							std::ostringstream stringStream;
							int len = msg->GetSysEx()->GetLength();
							int i = 0;
							for (i; i < len && i < 256; i++){
								stringStream << msg->GetSysEx()->GetData(i);
							}
							if (stringStream.str() != "untitled")
								returnStream << stringStream.str() << " ";
						}
					}
				} while (i.GoToNextEvent());

				return returnStream.str();
			}

			ushort GetBPM(uint midiTempo){
				return ONE_MINUTE_IN_MICROSECONDS / (midiTempo * 4);
			}

			uint GetMidiTempo(ushort bpm){
				return ONE_MINUTE_IN_MICROSECONDS / (bpm * 4);
			}

			uint GetMidiTick(ushort bpm, ushort ppq){
				return (ONE_MINUTE_IN_MICROSECONDS) / (bpm * ppq);
			}

			float GetTimeInBeats(uint midiTime, ushort ppq){
				return (float) midiTime / (float) ppq;
			}

			int ParseMidiFile(const char* fileName, jdksmidi::MIDIMultiTrack * tracks){
				jdksmidi::MIDIFileReadStreamFile rs(fileName);
				jdksmidi::MIDIFileReadMultiTrack track_loader(tracks);
				jdksmidi::MIDIFileRead reader(&rs, &track_loader);
				if (reader.Parse())
					if (tracks != NULL)
						return 0;
				return -1;
			}

			std::string GetMIDIText(jdksmidi::MIDITrack * track, uchar metatype){
				jdksmidi::MIDITimedBigMessage * msg;
				std::string ret = "";
				for (int i = 0; i < track->GetNumEvents(); i++){
					msg = track->GetEvent(i);
					if (msg->GetMetaType() == metatype){
						if (msg->GetSysEx() != NULL)
							ret += " " + msg->GetSysExString();
					}
				}
				return ret;
			}

			std::vector<std::string> GetMIDITexts(jdksmidi::MIDITrack * track, uchar metatype){
				jdksmidi::MIDITimedBigMessage * msg;
				std::vector<std::string> ret;
				for (int i = 0; i < track->GetNumEvents(); i++){
					msg = track->GetEvent(i);
					if (msg->GetMetaType() == metatype){
						if (msg->GetSysEx() != NULL)
							ret.push_back(msg->GetSysExString());
					}
				}
				return ret;
			}

			std::string GetMIDIInstrumentName(jdksmidi::MIDITrack * track){
				return GetMIDIText(track, jdksmidi::META_INSTRUMENT_NAME);
			}

			std::string GetMIDITrackName(jdksmidi::MIDITrack * track){
				return GetMIDIText(track, jdksmidi::META_TRACK_NAME);
			}

			std::vector<std::string> GetAllMIDITrackNames(jdksmidi::MIDIMultiTrack *mlt) {
				std::vector<std::string> ret;
				for (int i = 0; i < mlt->GetNumTracks(); ++i)
				{
					if (mlt->GetTrack(i)->GetNumEvents() > 0)
					{
						ret.push_back(GetMIDITrackName(mlt->GetTrack(i)));
					}
					else {
						ret.push_back("");
					}
				}
				return ret;
			}

			bool IsNoteInMIDITrack(jdksmidi::MIDITrack * track){
				jdksmidi::MIDITimedBigMessage * msg;
				for (int i = 0; i < track->GetNumEvents(); i++){
					msg = track->GetEvent(i);
					if (msg->GetType() == jdksmidi::NOTE_ON){
						return true;
					}
				}
				return false;
			}

			std::vector<bool> IsNoteInMIDITracks(jdksmidi::MIDIMultiTrack * tracks){
				std::vector<bool> ret;
				for (int i = 0; i < tracks->GetNumTracks(); i++){
					ret.push_back(IsNoteInMIDITrack(tracks->GetTrack(i)));
				}
				return ret;
			}

			int IsNoteInMIDITracks(jdksmidi::MIDIMultiTrack * tracks, std::vector<bool> * note_in_tracks){
				uchar count = 0;
				*note_in_tracks = IsNoteInMIDITracks(tracks);
				for (auto it : *note_in_tracks){
					if (it)
						count++;
				}
				return count;
			}

			std::vector<uchar> GetMIDIFirstInstrumentTypes(jdksmidi::MIDIMultiTrack * tracks){
				std::vector<uchar> ret(16);
				bool filled[16];
				std::fill(filled, filled + 16, false);
				std::fill(ret.begin(), ret.end(), 128);
				jdksmidi::MIDIMultiTrackIterator it(tracks);
				const jdksmidi::MIDITimedBigMessage * msg;
				int track_num;
				uchar chan_num, inst_num;
				it.GoToTime(0);
				do {
					if (it.GetCurEvent(&track_num, &msg))
						if (msg->GetType() == jdksmidi::PROGRAM_CHANGE){
							chan_num = msg->GetChannel();
							inst_num = msg->GetByte1();
							if (filled[chan_num] == false){
								filled[chan_num] = true;
								ret[chan_num] = inst_num;
							}
							if (std::find(std::begin(filled), std::end(filled), false) == std::end(filled)){
								break;
							}
						}
						else if (msg->GetType() == jdksmidi::NOTE_ON){
							if (filled[chan_num = msg->GetChannel()] == false){
								ret[chan_num] = 0;
							}
						}

				} while (it.GoToNextEvent());
				return ret;
			}

			std::array<uchar, 4> GetMIDITimeSig(const jdksmidi::MIDITimedBigMessage * msg){
				std::array<uchar, 4> ret = { { 0, 0, 0, 0 } };
				if (msg->IsMetaEvent()){
					if (msg->GetMetaType() == jdksmidi::META_TIMESIG){
						uchar n = msg->GetByte1();
						uchar d = msg->GetByte4();
						uchar c = msg->GetByte5();
						uchar b = msg->GetByte6();
						ret = { { n, d, c, b } };
					}
				}
				return ret;
			}

		}
	}
}
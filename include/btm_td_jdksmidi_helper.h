#ifndef BTM_TD_JDKSMIDI_HELPER_H
#define BTM_TD_JDKSMIDI_HELPER_H

#include "jdksmidi_incl.h"
#include "btm_td_helper.h"

namespace btm_td {
	namespace helper {
		namespace jdksmidi_helper {
			const uint ONE_MINUTE_IN_MICROSECONDS = 60000000;

			std::list<std::string> ParseTrackNames(jdksmidi::MIDIMultiTrack *mlt);
			/** Parse midi file and search for track name text messages.
			*	Returns:
			*		std::list<std::string> containing track names found
			*	Params:
			*		mlt:	midi to parse in jdksmidi MIDIMultiTrack.
			*/
			std::string GetCustomSongName(jdksmidi::MIDIMultiTrack *mlt);
			/** Parse midi file and search for track name text messages, and concatenate them
			*	into a string.
			*	Returns:
			*		String containing track names found concatenated.
			*	Params:
			*		mlt:	midi to parse in jdksmidi MIDIMultiTrack.
			*/

			ushort GetBPM(uint midiTempo);
			/** Get BPM from Midi style tempo.
			*	Returns:
			*		Beats per Minute
			*	Params:
			*		midiTempo:	Midi style tempo (microseconds per quarter note).
			*/
			uint GetMidiTempo(ushort bpm);
			/** Get Midi style tempo (microseconds per quarter note) from BPM.
			*	Returns:
			*		Midi style tempo
			*	Params:
			*		bpm:	Beats per Minute.
			*/
			uint GetMidiTick(ushort bpm, ushort ppq);
			/** Get Midi tick time in microseconds from BPM and PPQ.
			*	Returns:
			*		Midi tick time
			*	Params:
			*		bpm:	Beats pe Minute.
			*		ppq:	Parts per quarter note.
			*/
			float GetTimeInBeats(uint midiTime, ushort ppq);
			/** Get time in beats from midi style time in ticks.
			*	Returns:
			*		Time in beats
			*	Params:
			*		midiTime:	Midi style time in ticks.
			*		ppq:		Parts per quarter note.
			*/

			void DumpMIDITimedBigMessage(const jdksmidi::MIDITimedBigMessage *msg);
			/** Dumps MIDI timed big message to logger
			*/
			int ParseMidiFile(const char* fileName, jdksmidi::MIDIMultiTrack * tracks);
			/**	Parse a MIDI File to jdksmidi MIDIMultiTrack.
			*/

			std::string GetMIDIInstrumentName(jdksmidi::MIDITrack * track);
			/** Parse midi track and search for Midi instrument name text meta messages,
			*	and concatenate them.
			*	Returns:
			*		Instrument name.
			*	Params:
			*		track:	midi track to parse in jdksmidi MIDITrack.
			*/
			std::vector<std::string> GetMIDITexts(jdksmidi::MIDITrack * track, uchar metatype);
			/** Parse midi track and search for text meta messages.
			*	Returns:
			*		Vector of text meta messages
			*	Params:
			*		track:		midi track to parse in jdksmidi MIDITrack.
			*		metatype:	text meta type to search
			*/
			std::string GetMIDIText(jdksmidi::MIDITrack * track, uchar metatype);
			/** Parse midi track and search for text meta messages,
			*	and concatenate them.
			*	Returns:
			*	text meta messages.
			*	Params:
			*		track:		midi track to parse in jdksmidi MIDITrack.
			*		metatype:	text meta type to search
			*/
			std::string GetMIDITrackName(jdksmidi::MIDITrack * track);
			/** Parse midi track and search for track name text meta messages.
			*	Returns:
			*		Track name text meta messages, concatenated.
			*	Params:
			*		track:		midi track to parse in jdksmidi MIDITrack.
			*/
			std::vector<std::string> GetAllMIDITrackNames(jdksmidi::MIDIMultiTrack *mlt);
			/** Parse midi multitrack and search for text meta messages.
			*	Returns:
			*		Vector of text meta messages.
			*	Params:
			*		mlt:	midi tracks to parse in jdksmidi MIDIMultiTrack.
			*/


			std::vector<uchar> GetMIDIFirstInstrumentTypes(jdksmidi::MIDIMultiTrack * tracks);

			bool IsNoteInMIDITrack(jdksmidi::MIDITrack * track);
			/** Parse midi track and search for a note message.
			*	Returns:
			*		True if there's at least a note message in the track, false otherwise.
			*	Params:
			*		track:	midi track to parse in jdksmidi MIDITrack.
			*/
			std::vector<bool> IsNoteInMIDITracks(jdksmidi::MIDIMultiTrack * tracks);
			/** Parse midi multi track and search for a note message in tracks.
			*	Returns:
			*		Vector of boolean, where every entry represents a track:
			*		True if there's at least a note message in the track, false otherwise.
			*	Params:
			*		track:	midi tracks to parse in jdksmidi MIDIMultiTrack.
			*/
			int IsNoteInMIDITracks(jdksmidi::MIDIMultiTrack * tracks, std::vector<bool> * note_in_tracks);
			/** Parse midi multi track and search for a note message in tracks.
			*	Returns:
			*		0 if sucessfully parsed.
			*	Params:
			*		track:	midi tracks to parse in jdksmidi MIDIMultiTrack.
			*		note_in_tracks:
			*				Pointer to vector of boolean, will be written with the output
			*				where every entry represents a track:
			*				True if there's at least a note message in the track, false otherwise.
			*/

			std::array<uchar, 4> GetMIDITimeSig(const jdksmidi::MIDITimedBigMessage * msg);
			/** Get MIDI time signature from jdksmidi MIDITimedBigMessage
			*	Returns:
			*	std::array<uchar, 4> contains MIDI time signature
			*	Params:
			*		msg:	Pointer to jdksmidi MIDITimedBigMessage that contains MIDI time signature.
			*/

		}
	}
}

#endif
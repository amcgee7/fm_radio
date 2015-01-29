#
/*
 *    Copyright (C)  2014
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Programming
 *
 *    This file is part of the SDR-J.
 *    Many of the ideas as implemented in SDR-J are derived from
 *    other work, made available through the GNU general Public License. 
 *    All copyrights of the original authors are recognized.
 *
 *    SDR-J is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    SDR-J is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with SDR-J; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef __GUI
#define __GUI

#include	<sndfile.h>
#include	"fm-constants.h"
#include	"ringbuffer.h"
#include	"fft.h"
#include	"fir-filters.h"
#include	<gst/gst.h>
class	keyPad;

class	fmProcessor;
class	rdsDecoder;
class	audioSink;
class	virtualInput;
/** This is the main interface for the FM radio.  Originally it was
    the main GUI class.
 */
class RadioInterface {
public:
		RadioInterface		(int32_t = KHz(96700));
		~RadioInterface		();

	/** Get demodulated stereo interleaved audio samples.  This
	 * function will block until there are samples available.
	 * Request up to @length samples and store them in the array pointed to by @data.
	 * Returns: the actual number of samples written to @data
	 */
	uint32_t	getSamples		(DSPFLOAT *data, uint32_t length);
	/** Set the tuner to receive @frequency Hz */
	void		setTuner		(int32_t frequency);

	/** Callback type for seek function.
	 * FIXME: more docs
	 */
	typedef void (*StationCallback) (int32_t frequency, void *userdata);

	/** Start seeking for a station.  After this function returns,
	 * the RadioInterface will start sampling different
	 * frequencies for @interval milliseconds, adding @frequencyStep Hz each iteration,
	 * wrapping at the lower and upper bounds of @minFrequency and
	 * @maxFrequency, respectively.  The seek will continue either
	 * until cancelSeek() is called or until a station is found,
	 * in which case @callback is called with the station
	 * frequency and @userdata.
	 * \param threshold The signal level over which a signal is considered to be a station
	 * \param interval How long to scan for a station on each
	 * frequency, in milliseconds
	 * \param callback A function to call when a station is found
	 * \param userdata A pointer to be provided to @callback
	 */
	void		seek			(int16_t threshold,
						 int32_t minFrequency, int32_t maxFrequency,
						 int32_t frequencyStep, int32_t interval,
						 StationCallback callback, void *userdata);

	void		cancelSeek		();

private:
	bool		doInit;
	int16_t		outputDevice;
	void		localConnects		(void);

	int32_t		inputRate;
	int32_t		fmRate;
	int32_t		workingRate;
	int32_t		audioRate;
	audioSink	*our_audioSink;
	virtualInput	*myRig;

	uint8_t		HFviewMode;
	uint8_t		inputMode;

	void		setDetectorScreen	(int16_t);

	GstClock        *systemClock;
	GstClockID      periodicClockId;
	int32_t         preSeekFrequency;
	int32_t		seekMin;
	int32_t		seekMax;
	int32_t		seekStep;
	StationCallback seekCallback; 
	void *		seekUserdata;

	void            cancelSeekTimeout ();
	void            resetSeekMembers ();

	static void	stationCallback(int32_t frequency, void *userdata);
	void		stationCallback(int32_t frequency);
	
        static gboolean seekTimeout (GstClock *clock, GstClockTime time,
				     GstClockID id, gpointer user_data);
	gboolean        seekTimeout ();

	int32_t		Panel;
	int16_t		CurrentRig;

	bool		audioDumping;
	SNDFILE		*audiofilePointer;

	fmProcessor	*myFMprocessor;
	rdsDecoder	*myRdsDecoder;
	int8_t		rdsModus;

	int32_t		currentPIcode;
	int32_t		frequencyforPICode;
	int16_t		logTime;
	FILE		*logFile;
	int8_t		latencyLevel;
	int8_t		runMode;

	void		showStrength		(void);
	bool		squelchMode;
/*
 *	The private slots link the GUI elements
 *	to the GUI code
 */
private:
	void	setStart		(void);
	void	clickPause		(void);
	void	setGainSelector		(int);

	void	setAttenuation		(int);

	void	setStreamOutSelector	(int);
	void	abortSystem		(int);
	void	TerminateProcess	(void);
	void	setVolume		(int);
	void	set_audioDump		(const std::string &);

	void	setfmMode		(const std::string &);
	void	setfmRdsSelector	(const std::string &);
	void	setfmDecoder		(const std::string &);
	void	setfmChannelSelector	(const std::string &);
	void	setfmDeemphasis		(const std::string &);

	bool	setupSoundOut		(audioSink *,
	                                 int32_t, int16_t *);
	void	set_squelchValue	(int);
	void	set_squelchMode		(void);
	/*
public:
	void	setCRCErrors		(int);
	void	setSyncErrors		(int);
	void	setbitErrorRate		(double);
	void	setGroup		(int);
	void	setPTYCode		(int);
	void	setPiCode		(int);
	void	clearStationLabel	(void);
	void	setStationLabel		(char *, int);
	void	clearRadioText		(void);
	void	setRadioText		(char *, int);
	void	setRDSisSynchronized	(bool);
	void	setMusicSpeechFlag	(int);
	void	clearMusicSpeechFlag	(void);
	*/
};

#endif


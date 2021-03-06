#
/*
 *    Copyright (C) 2014
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Programming
 *
 *    This part of the FM demodulation software is largely
 *    a rewrite and local adaptation of FMSTACK software
 *    Technical University of Munich, Institute for Integrated Systems (LIS)
 *    FMSTACK Copyright (C) 2010 Michael Feilen
 * 
 *    Author(s)       : Michael Feilen (michael.feilen@tum.de)
 *    Initial release : 01.09.2009
 *    Last changed    : 09.03.2010
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
 */

#ifndef	__RDS_GROUP_DECODER
#define	__RDS_GROUP_DECODER

#include	"fm-constants.h"
#include	"rds-group.h"

typedef void (*ClearCallback)(void *userdata);
typedef void (*StringCallback)(const char * string, void *userdata);

class	rdsGroupDecoder {
public:
	rdsGroupDecoder		(ClearCallback, StringCallback, StringCallback,
				 ClearCallback, StringCallback, StringCallback,
				 void *);
	~rdsGroupDecoder	(void);
bool	decode			(RDSGroup *);
void	reset			(void);

//	group 1 constants
//
static const uint32_t NUMBER_OF_NAME_SEGMENTS	= 4;
static const uint32_t STATION_LABEL_SEGMENT_SIZE = 2;
static const uint32_t STATION_LABEL_LENGTH =
          NUMBER_OF_NAME_SEGMENTS * STATION_LABEL_SEGMENT_SIZE;

//	Group 2 constants 
static const uint32_t NUM_CHARS_PER_RTXT_SEGMENT	= 4;
static const uint32_t NUM_OF_FRAGMENTS			= 16;
static const uint32_t NUM_OF_CHARS_RADIOTEXT = 
	        NUM_CHARS_PER_RTXT_SEGMENT * NUM_OF_FRAGMENTS;

static const char END_OF_RADIO_TEXT		= 0x0D;

private:
	void		Handle_Basic_Tuning_and_Switching (RDSGroup *);
	void		Handle_RadioText		  (RDSGroup *);
	void		Handle_Time_and_Date		  (RDSGroup *);
	void		addtoStationLabel	(uint32_t, uint32_t);
	void		additionalFrequencies	(uint16_t);
	void		addtoRadioText		(uint16_t, uint16_t, uint16_t);
	uint32_t	m_piCode;

//	Group 1 members
	char   stationLabel [STATION_LABEL_LENGTH + 1];
	int8_t   m_grp1_diCode;
	uint32_t stationNameSegmentRegister;

//	Group 2 members 
	uint32_t textSegmentRegister;
	int32_t  textABflag;
	char   textBuffer [NUM_OF_CHARS_RADIOTEXT];

	// Callback members
	ClearCallback labelClearCallback;
	StringCallback labelChangeCallback;
	StringCallback labelCompleteCallback;
	ClearCallback textClearCallback;
	StringCallback textChangeCallback;
	StringCallback textCompleteCallback;
	void *callbackUserData;

	//signals:
	void	setGroup		(int);
	void	setPTYCode		(int);
	void	setMusicSpeechFlag	(int);
	void	clearMusicSpeechFlag	(void);
	void	setPiCode		(int);
	void	clearStationLabel	(void);
	void	setStationLabel		(char *, int);
	void	clearRadioText		(void);
	void	setRadioText		(char *, int);
	void	setAFDisplay		(int);
};

#endif

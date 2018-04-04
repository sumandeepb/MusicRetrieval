/*
    Copyright (C) 2006-2018 Sumandeep Banerjee

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
    wave.cpp - Class source file for reading / writing .WAV format
    Beginning Date : May 30, 2006
    Completion Date : May 31, 2006
    Latest Modification : June 20, 2006
    
    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

// standard incldue files
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// project input files
#include "wave.h"

/**
    Reads WAVE format files. Extracts the file parameters and the filepointer to the wave data block

	filename (input) : Valid WAVE (.wav) format file path/name. Must be uncompressed, 16-bit PCM sample
*/
void Wave :: waveRead (char * filename) {
	long temp;	// temp variable for file stream cursor position

	// open .wav file, exit if error occured
	if(!(pointerWaveFile = fopen (filename, "rb")))
	{
		printf ("Can't open file %s\n", filename);
		exit (0);
	}

	// read RIFF header confirmation tag
	fseek (pointerWaveFile, OFFSET_CHUNK_ID, SEEK_SET);
	fread (ChunkID, sizeof (ChunkID), 1, pointerWaveFile);
	// exit if RIFF tag not found
	if (memcmp (ChunkID, _HEADER, sizeof (ChunkID)))
	{
		printf ("\nFormat mismatch : File not RIFF %s \n", _HEADER);
    	exit (0);
	}

	// read (WAVE header + PCM data) size
	fread (&ChunkSize, sizeof (ChunkSize), 1, pointerWaveFile);
	fseek (pointerWaveFile, 0L, SEEK_END);
	// exit if (header + data) size mismatch with physical file size
	if ((temp = ftell (pointerWaveFile)) != (ChunkSize + 8))
	{
		printf ("\nCorrupt file : Incorrect file size\n");
		exit (0);
	}

	// read WAVE fonfirmation tag
	fseek (pointerWaveFile, OFFSET_FORMAT, SEEK_SET);
	fread (Format, sizeof (Format), 1, pointerWaveFile);
	// exit if WAVE tag not found
	if (memcmp (Format, _CHUNK, sizeof (Format)))
	{
		printf ("\nFormat mismatch : File not .WAV\n");
		exit (0);
	}

	// read and confirm header chunk tag
	fread (SubChunk1ID, sizeof (SubChunk1ID), 1, pointerWaveFile);
	if (memcmp (SubChunk1ID, _SUB_CHUNK_1, sizeof (SubChunk1ID)))
	{
		printf ("\nFormat mismatch : No header chunk present\n");
		exit (0);
	}

	// read and confirm header chunk size
	// PCM encoded file header size = 16
	fread (&SubChunk1Size, sizeof (SubChunk1Size), 1, pointerWaveFile);
	if (SubChunk1Size != _SUB_CHUNK_1_SIZE)
	{
		printf ("\nFormat mismatch : Only PCM files valid 1\n");
		exit (0);
	}

	// read audio format code
	fread (&AudioFormat, sizeof (AudioFormat), 1, pointerWaveFile);
	// exit if audio format != PCM format code
	if (AudioFormat != _AUDIO_FORMAT) //change
	{
		printf ("\nFormat mismatch : Only PCM files valid 2\n");
		exit (0);
	}

	// read number of channels in audio file
	fread (&NumChannels, sizeof (NumChannels), 1, pointerWaveFile);

	// read sample rate of PCM
	fread (&SampleRate, sizeof (SampleRate), 1, pointerWaveFile);

    // read block size for each sample, all channels combined
    fseek (pointerWaveFile, OFFSET_BLOCK_ALIGN, SEEK_SET);
    fread (&BlockAlign, sizeof (BlockAlign), 1, pointerWaveFile);

	// read sample resolution of PCM
	fseek (pointerWaveFile, OFFSET_BITS_PER_SAMPLE, SEEK_SET);
	fread (&BitsPerSample, sizeof (BitsPerSample), 1, pointerWaveFile);
	// exit if sample resolution is not 16 bits
	if (BitsPerSample != _BITS_PER_SAMPLE)
	{
		printf ("\nFormat mismatch : Incorrect PCM resolution\n");
		exit (0);
	}

	// read and confirm data chunk tag
	fread (SubChunk2ID, sizeof (SubChunk2ID), 1, pointerWaveFile);
	if (!strcmp (SubChunk2ID, _SUB_CHUNK_2))
	{
		printf ("\nFormat mismatch : No data chunk present\n");
		exit (0);
	}

	// read data chunk size
	fread (&SubChunk2Size, sizeof (SubChunk2Size), 1, pointerWaveFile);
	// exit if data chunk size != filesize - total header size
	if ((SubChunk2Size + OFFSET_DATA) != temp)
	{
		printf ("\nCorrupt file : Incorrect amount of data\n");
		exit (0);
	}

	// calculate number of samples per channel in the file
	NumSamplesPerChannel = (SubChunk2Size * 8) / (NumChannels * BitsPerSample);

    pointerWaveFile = pointerWaveFile;

} // end of waveRead

/**
    Loads chunks of audio signal from the wave file (file pointer extracted by waveRead) into data block

    startSampleIndex (input) : Index of the first audio signal sample to be read

    numSamples (input) : The number of audio samples to be read from the wavefile

    data (output) : The data block (must be pre allocated of size numSamples * NumChannels)
*/
void Wave :: waveLoad (long startSampleIndex, long numSamples, short * data) {
    if (startSampleIndex + numSamples <= NumSamplesPerChannel)
    {
        fseek (pointerWaveFile, OFFSET_DATA + (BlockAlign * startSampleIndex), SEEK_SET);
        fread (data, sizeof (short), numSamples * NumChannels, pointerWaveFile);
    }
    else
    {
        printf ("\nIncorrect Sample Index\n");
        exit (0);
    }
}

/**
    closes file pointer to wave file
*/
void Wave :: waveClose () {
    fclose (pointerWaveFile);
}

/**
    Writes data block into filename as WAVE (.wav) format

    Note : Incomplete
*/
void Wave :: waveWrite (const char * filename, short * data) {

}

/**
    Performs downmixing of the audio tracks in the input wave file, resulting in a mono channel for further extraction of mfcc coefficients
*/
void Wave :: waveDownmix (short * data, short * dataDownMix) {
    long i;
    if (NumChannels == 2) // supports only stereo and mono. Does not still support surround sound
    {
        for (i = 0; i < NumSamplesPerChannel; i ++)
        {
            dataDownMix [i]= (data [2 * i] / 2) + (data [(2 * i) + 1] / 2);
        }
    }
    else if (NumChannels == 1)
    {
        dataDownMix = data;
    }
} // end of MFCCdownmix

/**
    Returns the number of channels in the input wave file
*/
short Wave :: getNumChannels () {
    return NumChannels;
}

/**
    Returns the number of samples in each channel in in entire wave file
*/
long Wave :: getNumSamplesPerChannel () {
    return NumSamplesPerChannel;
}

/**
    Returns the sampling rate of the audio signal being read from the wave file
*/
long Wave ::  getSampleRate () {
    return SampleRate;
}

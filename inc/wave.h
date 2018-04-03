/*
    wave.h - Class header file for reading / writing .WAV format
    Beginning Date : May 30, 2006
    Completion Date : May 31, 2006
    Latest Modification : June 1, 2006
    
    Code written by Sumandeep Banerjee, DFKI, Kaiserslautern, Germany
    sumandeep.banerjee@gmail.com
*/

/**
    \class Wave
    \brief Microsoft(R) RIFF (Resource Interchange File Format) WAVE PCM soundfile

    The Microsoft(R) RIFF (Resource Interchange File Format) WAVE PCM soundfile
format is a popular medium for storing / processing raw, uncompressed audio file.
The Wave class provides functions for reading and writing WAVE format files.
*/

#if !defined (_WAVE_H)
#define _WAVE_H

// standard include files
#include <stdio.h>

// WAVE format identification tags
#define _HEADER "RIFF"
#define _CHUNK "WAVE"
#define _SUB_CHUNK_1 "fmt "
#define _SUB_CHUNK_1_SIZE 16
#define _SUB_CHUNK_2 "data"
#define _AUDIO_FORMAT 1
#define _BITS_PER_SAMPLE 16

class Wave {
    private:
        // file offset positions for .wav header
        static const long OFFSET_CHUNK_ID = 0;			// Microsoft(R) RIFF (Resource Interchange File Format) specification for multimedia files
        static const long OFFSET_CHUNK_SIZE = 4;		// total data size (header + subchunks)
        static const long OFFSET_FORMAT = 8;			// "WAVE" format tag identifier
        static const long OFFSET_SUBCHUNK1_ID = 12;	    // header chunk ID
        static const long OFFSET_SUBCHUNK1_SIZE = 16;	// header chunk size
        static const long OFFSET_AUDIO_FORMAT = 20;	    // compression format PCM = 1
        static const long OFFSET_NUM_CHANNELS = 22;	    // number of audio channels mono = 1, stereo = 2
        static const long OFFSET_SAMPLE_RATE = 24;		// sampling rate 8000, 11025, 22050, 44100 etc
        static const long OFFSET_BYTE_RATE = 28;		// number of bytes per second
        static const long OFFSET_BLOCK_ALIGN = 32;		// bytes for each sample of all channels combined
        static const long OFFSET_BITS_PER_SAMPLE = 34;	// bites for each sample
        static const long OFFSET_SUBCHUNK2_ID = 36;	    // data chunk ID
        static const long OFFSET_SUBCHUNK2_SIZE = 40;	// data chunk size
        static const long OFFSET_DATA = 44;			    // data chunk
    protected:
        // wave file header parameters
        char ChunkID [4], Format [4], SubChunk1ID [4], SubChunk2ID [4];
	    long ChunkSize, SampleRate, ByteRate, SubChunk1Size, SubChunk2Size, NumSamplesPerChannel;
	    short AudioFormat, NumChannels, BlockAlign, BitsPerSample;
        // file pointer to wave
        FILE * pointerWaveFile;
    public:
        void waveRead (char * filename);
        void waveLoad (long startSampleIndex, long numSamples, short * data);
        void waveClose ();
        void waveWrite (const char * filename, short * data);
        void waveDownmix (short * data, short * dataDownMix);
        short getNumChannels ();
        long getNumSamplesPerChannel ();
        long getSampleRate ();
};

#endif

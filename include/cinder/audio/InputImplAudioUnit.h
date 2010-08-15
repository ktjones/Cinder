/*
 Copyright (c) 2009, The Barbarian Group
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and
	the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
	the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "cinder/Cinder.h"
#include "cinder/audio/Input.h"
#include "cinder/audio/PcmBuffer.h"

#include <AudioUnit/AudioUnit.h>
#include <AudioToolbox/AudioToolbox.h>

#include <vector>
#include <boost/circular_buffer.hpp>
#include <boost/thread/mutex.hpp>

namespace cinder { namespace audio {

class InputImplAudioUnit : public InputImpl {
 public:
	InputImplAudioUnit();
	~InputImplAudioUnit();
	
	void start();
	void stop();
	PcmBuffer32fRef getPcmBuffer();
	bool isCapturing() const { return mIsCapturing; }
	
	uint32_t getSampleRate() const { return mSampleRate; };
	uint16_t getChannelCount() const { return mChannelCount; };
 protected:
	static OSStatus inputCallback( void*, AudioUnitRenderActionFlags*, const AudioTimeStamp*, UInt32, UInt32, AudioBufferList* );
 
	void setup();
 
	bool							mIsCapturing;
	AudioComponentInstance			mInputUnit;
	AudioDeviceID					mDeviceId;
	AudioBufferList					* mInputBuffer;
	float							* mInputBufferData;
	
	std::vector<boost::circular_buffer<float> *>	mBuffers;
	boost::mutex								mBufferMutex;
	
	AudioStreamBasicDescription		mFormatDescription;
	uint32_t mSampleRate;
	uint16_t mChannelCount;
};


}} //namespace
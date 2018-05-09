/*
 * SoundFX.c
 *
 *  Created on: Apr 25, 2018
 *      Author: d
 */

#include <arm_math.h>
#include "DataTypeDefinitions.h"
#include "arm_math.h"
#include "SoundFX.h"
#include <math.h>
/*Sampling frequency used by the ADC*/
#define FS 60000

/*Maximum delays for every effect*/
#define MAXFLANGERDELAY 0.010f
#define MAXCHORUSDELAY 0.075f
#define MAXSLAPBACKDELAY 0.060f
#define MAXDISTORTIONDELAY 0.015f

#define MAXCLIP 2100
#define MINCLIP 1900
#define SINEAMPLITUDE 2
#define MAXPERCENTAGE 100

/*Maximum samples in the circular buffer*/
#define MAXSAMPLES 4500

/*Offsets to adjust effects*/
#define SAMPLEOFFSET 2048
#define FLANGEROFFSET 512
#define TREMOLOOFFSET 310
#define FLANGERAMPLIFIER 8
#define ATTENUATIONFACTOR 2

/*Circular buffer for past outputs*/
static volatile uint16 outputs[MAXSAMPLES];

/*Indexes used for samples and circular buffer*/
static volatile uint32 sampleIndex;
static volatile uint32 currentSampleIndex;
static uint16 actualIndex;
static uint16 sampleCounter;

/*Value returned once the effect is applied*/
static volatile flo32 returnValue;

/*Sample modifiers*/
static flo32 modulationSignal;
static flo32 tremFX;
static flo32 amplitudeCoefficient;
static flo32 distFactor;
static flo32 distCoefficient;
static flo32 realSample;
static flo32 absSample;
flo32 exponentialValue;
/*Value read by the DAC*/
static uint16 processedSample;


uint16 flanger(uint16 input, uint32 sampleIndex, flo32 modulationSignal, flo32 amplitudeCoefficient){

	/*Obtaining the absolute value of the modulation signal*/
	if(modulationSignal < 0){
		modulationSignal = -modulationSignal;
	}

	currentSampleIndex = sampleIndex*modulationSignal;

	/*Adding the modulated past output to the input*/
	returnValue = input + (amplitudeCoefficient)*(outputs[(currentSampleIndex) % (MAXSAMPLES-1)]);

	return (uint16)(returnValue - FLANGEROFFSET);
}

uint16 tremolo(uint16 input, flo32 modulationSignal, flo32 amplitudeCoefficient){

	/*Using the amplitude and the modulation signal to calculate the tremolo factor*/
	tremFX = 1 + (amplitudeCoefficient/1.5)*modulationSignal;

	returnValue = tremFX*input;

	/*Applying an offset to the output signal to avoid noise*/
	if(returnValue == 0){
		returnValue = returnValue + TREMOLOOFFSET;
	}

	return (uint16) returnValue;
}

uint16 chorus(uint16 input, uint32 sampleIndex, flo32 amplitudeCoefficient){

	currentSampleIndex = sampleIndex;

	/*Adding the past outputs with an amplitude coefficient and attenuated by an attenuation factor*/
	returnValue = input + (amplitudeCoefficient/ATTENUATIONFACTOR)*(outputs[currentSampleIndex/ATTENUATIONFACTOR]);

	return (uint16)returnValue;

}

uint16 slapback(uint16 input, uint32 sampleIndex, flo32 amplitudeCoefficient){

	currentSampleIndex = sampleIndex;

	/*Adding a past output with an amplitude coefficient*/
	returnValue = input + (amplitudeCoefficient/4)*(outputs[currentSampleIndex]);

	return (uint16)returnValue;

}


uint16 distortion(uint16 input, flo32 amplitudeCoefficient, uint32 sampleIndex){

	realSample = input - SAMPLEOFFSET;


		exponentialValue = exp((realSample*realSample) / absSample);

		returnValue = (realSample / absSample) * (1-exponentialValue);

		return (uint16) ((amplitudeCoefficient/4)*returnValue + SAMPLEOFFSET+ ((amplitudeCoefficient/6)*(outputs[currentSampleIndex])));
}

uint16 FXPercentage(FXType selectedFX, uint16 input, uint8 percentage, flo32 amplitude){

	/*Using a switch to define the effect modifiers for every effect and
	 * then setting the return value as processedSample*/
	switch(selectedFX){
	case CHORUS:
		sampleIndex = (actualIndex + (uint16)((percentage * MAXCHORUSDELAY * MAXSAMPLES) / MAXPERCENTAGE)) % (MAXSAMPLES-1);
		processedSample = chorus(input, sampleIndex, amplitude);
		break;
	case FLANGER:
		sampleIndex = (actualIndex + (uint16)((percentage * MAXFLANGERDELAY * MAXSAMPLES) / MAXPERCENTAGE)) % (MAXSAMPLES-1);
		modulationSignal = arm_sin_f32(SINEAMPLITUDE * PI * sampleIndex * FLANGERAMPLIFIER / MAXSAMPLES);
		processedSample = flanger(input,sampleIndex, modulationSignal, amplitude);
		break;
	case TREMOLO:
		sampleIndex = (actualIndex) % (MAXSAMPLES-1);
		modulationSignal = arm_sin_f32(SINEAMPLITUDE * PI * sampleIndex * percentage / (MAXSAMPLES*MAXPERCENTAGE));
		processedSample = tremolo(input, modulationSignal, amplitude);
		break;
	case SLAPBACK:
		sampleIndex = (actualIndex + (uint16)((percentage * MAXSLAPBACKDELAY * MAXSAMPLES) / MAXPERCENTAGE)) % (MAXSAMPLES-1);
		processedSample = chorus(input, sampleIndex, amplitude);
		break;
	case DISTORTION:
		sampleIndex = (actualIndex + (uint16)((percentage * MAXDISTORTIONDELAY * MAXSAMPLES) / MAXPERCENTAGE)) % (MAXSAMPLES-1);
		processedSample = distortion(input, amplitude, sampleIndex);
		break;
	case CLEAN:
		processedSample = input;
		break;
	default:
		processedSample = input;
		break;
	}

	return processedSample;
}

void setSampleArray(uint16 input){
	/*Filling the circular buffer once to avoid referencing past outputs that don't exist*/
	if(sampleCounter < MAXSAMPLES){
		outputs[sampleCounter] = input;
		sampleCounter++;
	}

	/*Setting the new input as a sample of the circular buffer*/
	else if(sampleCounter == MAXSAMPLES){

		outputs[actualIndex] = input;

		actualIndex++;

		if(actualIndex == MAXSAMPLES-1){
			actualIndex = actualIndex % (MAXSAMPLES-1);
		}
	}
}

void initSampleArray(void){
	/*Initializing circular buffer with 0*/
	for(sampleCounter = 0; sampleCounter < MAXSAMPLES; sampleCounter++){
			outputs[sampleCounter] = 0;
	}
}

void initSampleCounter(void){
	/*Initializing counter for the first samples to be taken*/
	sampleCounter = 0;
}


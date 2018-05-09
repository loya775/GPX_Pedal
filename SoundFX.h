/*
 * SoundFX.h
 *
 *  Created on: Apr 25, 2018
 *      Author: d
 */

#ifndef SOUNDFX_H_
#define SOUNDFX_H_

typedef enum{FLANGER, CHORUS, TREMOLO, SLAPBACK, DISTORTION, CLEAN} FXType;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 The flanger effect is produced by mixing two identical signals together
 	 one signal delayed by a changing period modified by a modulation signal
 	 \param[in] It receives the input sample, the sample index to determine the delay, the modulation signal used to actual delay and the amplitude to control the gain
 	 \return It returns the modified sample
 */
uint16 flanger(uint16 input, uint32 sampleIndex, flo32 modulationSignal, flo32 amplitudeCoefficient);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 The tremolo effect is produced by modulating the amplitude
 	 of a signal with changing values of a modulation signal
 	 \param[in] It receives the input sample, the modulation signal used to actual delay and the amplitude to control the gain
 	 \return It returns the modified sample
 */
uint16 tremolo(uint16 input, flo32 modulationSignal, flo32 amplitudeCoefficient);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 The chorus effect is a delay based effect that produces multiple echos
 	 in a short amount of time simulating the presence of various instruments
 	 \param[in] It receives the input sample, the sample index used to add an echo
 	 and the amplitude to control the gain
 	 \return It returns the modified sample
 */
uint16 chorus(uint16 input, uint32 sampleIndex, flo32 amplitudeCoefficient);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 The slapback effect is a delay based effect that produces an echo
 	 in a short amount of time
 	 \param[in] It receives the input sample, the sample index used to add an echo
 	 and the amplitude to control the gain
 	 \return It returns the modified sample
 */
uint16 slapback(uint16 input, uint32 sampleIndex, flo32 amplitudeCoefficient);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 The distortion is achieved by clipping the input samples that exceed
 	 a threshold determined to filter high amplitude signals
 	 \param[in] It receives the input sample, the amplitude to control the gain and the sample index to add an echo
 	 \return It returns the modified sample
 */
uint16 distortion(uint16 input, flo32 ampltideCoefficient, uint32 sampleIndex);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It selects the effect to be applied to the sample and it also modifies the parameters of the effect
 	 like its intesity level and amplitude
 	 \param[in] It receives the selected effect defined as an enum, the input sample and the percentage and amplitude of the effect to be applied
 	 \return It returns the modified sample
 */
uint16 FXPercentage(FXType selectedFX, uint16 input, uint8 percentage, flo32 amplitude);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It set the input sample and saves it in the circular buffer and it also refreshes the indexes involved
 	 \param[in] It receives the input sample to be set in the circular buffer
 	 \return It doesn't have a return
 */
void setSampleArray(uint16);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It initializes the circular buffer with 0 to avoid referencing garbage
 	 \param[in] It doesn't receive a parameter
 	 \return It doesn't have a return
 */
void initSampleArray(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It initializes the counter used to fill the buffer for the first time
 	 \param[in] It doesn't receive a parameter
 	 \return It doesn't have a return
 */
void initSampleCounter(void);

#endif /* SOUNDFX_H_ */

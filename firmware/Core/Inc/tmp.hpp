/*
 * tmp.hpp
 *
 *  Created on: Feb 11, 2025
 *      Author: lenovo
 */

#ifndef INC_TMP_HPP_
#define INC_TMP_HPP_

#include "main.h"

const size_t numFrameWords = 6; // Number of words in a full ADS131M04 SPI frame
unsigned long spiDummyWord[numFrameWords] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; // Dummy word frame to write ADC during ADC data reads

bool firstRead = true; // Flag to tell us if we are reading ADC data for the// first time
signed long adcData; // Location where DMA will store ADC data in memory,
// length defined elsewhere
/*
Interrupt the MCU each time DRDY asserts when collecting data
*/
void DRDYinterupt()
{
	if(firstRead)
	{ // Clear the ADC's 2-deep FIFO on the first read
		for(i=0; i< numFrameWords; i++) SPI.write(spiDummyWord + i);
		for(i=0; i< numFrameWords; i++) SPI.read();
		firstRead = false; // Clear the flag
		DMA.enable(); // Let the DMA start sending ADC data to memory
	}
	for (i=0; i<numFrameWords; i++) SPI.write(spiDummyWord + i); // Send the dummy data to the ADC to get// the ADC data
}
/*
adcRegisterWrite
Short function that writes one ADC register at a time. Blocks return until SPI
is idle. Returns false if the word length is wrong.
param
addrMask: 16-bit register address mask
data: data to write
adcWordLength: word length which ADC expects. Either 16, 24 or 32.
return
true if word length was valid
false if not
*/
bool adcRegisterWrite(unsigned short addrMask, unsigned short data, unsigned char adcWordLength)
{
	unsigned char shiftValue; 							// Stores the amount of bit shift based on // ADC word length
	if(adcWordLength==16) shiftValue = 0; 				// If length is 16, no shift
	else if(adcWordLength==24) shiftValue = 8; 			// If length is 24, shift left by 8
	else if(adcWordLength==32) shiftValue = 16; 		// If length is 32, shift left by 16
	else return false; // If not, invalid length
	SPI.write((WREG_OPCODE | addrMask) << shiftValue); 	// Write address and opcode  // Shift to accommodate ADC word length
	SPI.write(data << shiftValue);						// Write register data
	while(SPI.isBusy()); 								// Wait for data to complete sending
	return true;
}
/*
main routine
*/
void main()
{
	enableSupplies();
	GPIO.inputEnable('input'); 				// Enable GPIO connected to DRDY
	clkout.enable(8192000);					// Enable 8.192 MHz clock to CLKIN
	SPI.enable(); 							// Enable SPI port
	SPI.wordLengthSet(24); 					// ADC default word length is 24 bits
	SPI.configCS(STAY_ASSERTED);			// Configure CS to remain asserted until frame// is complete
	while(!GPIO.read()) { } 				// Wait for DRDY to go high indicating it is ok// to talk to ADC
	adcRegisterWrite(CLOCK_ADDR, 			// Write CLOCK register
	ALL_CH_DISABLE_MASK | 					// Turn off all channels so short// frames can be written during// config
	OSR_1024_MASK | PWR_HR_MASK, 24); 		// Re-write defaults for other bits// in CLOCK register
	adcRegisterWrite(MODE_ADDR, 			// Write MODE register
	RESET_MASK | DRDY_FMT_PULSE_MASK | 		// Clear the RESET flag, make DRDY// active low pulse
	WLENGTH_24_MASK | 						// Re-write defaults for other bits
	SPI_TIMEOUT_MASK, 24); 					// in MODE register
	adcRegisterWrite(GAIN1_ADDR, 			// Write GAIN1 register
	PGAGAIN3_32_MASK | 						// Set channels 1 and 3 PGA gain to
	PGAGAIN1_32_MASK, 24); 					// 32 in this example// Leave channels 0 and 2 at default // gain of 1
	adcRegisterWrite(THRSHLD_LSB_ADDR, 0x09, 24); 	// Write THRSHLD_LSB register  // Set DCBLOCK filter to have a// corner frequency of 622 mHz
	DMA.triggerSet(SPI);					// Configure DMA to trigger when data comes in// on the MCU SPI port
	DMA.txAddrSet(SPI.rxAddr());			// Set the DMA to take from the incoming SPI // port
	DMA.rxAddrSet(&adcData);				// Set the DMA to send ADC data to a predefined // memory location
	adcRegisterWrite(MODE_ADDR, 			// Write MODE register
	WLENGTH_32_SIGN_EXTEND_MASK | 			// Make ADC word size 32 bits to// accommodate DMA
	DRDY_FMT_PULSE_MASK | 					// Re-write other set bits in MODE
	SPI_TIMEOUT_MASK, 24); 					// register
	SPI.wordLengthSet(32); 					// Set SPI word size to 32 bits to// accomodate DMA
	adcRegisterWrite(CLOCK_ADDR, ALL_CH_ENABLE_MASK | OSR_1024_MASK | PWR_HR_MASK, 32); // Write CLOCK register  // Re-write defaults for other bits// in CLOCK register
	GPIO.interuptEnable();					// Enable DRDY interrupt and begin streaming data
}



#endif /* INC_TMP_HPP_ */

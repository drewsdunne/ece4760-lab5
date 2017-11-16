/* 
 * File:   spi_ram_dac.h
 * Author: Lab User
 *
 * Created on October 26, 2017, 12:12 PM
 */

#ifndef SPI_RAM_DAC_H
#define	SPI_RAM_DAC_H

#include <plib.h>

// === RAM commands ======================================================
// from 23LC1024 datasheet
// http://ww1.microchip.com/downloads/en/DeviceDoc/20005142C.pdf
// Default setup includes data streaming from current address
// This is used in the array read/write functions
#define RAM_WRITE_CMD (0x2000000) // top 8 bits -- 24 bits for address
#define RAM_READ_CMD  (0x3000000) // top 8 bits -- 24 bits for address
// command format consists of a read or write command ORed with a 24-bit
// address, even though the actual address is never more than 17 bits
// general procedure will be:
// Drop chip-select line
// Do a 32-bit SPI transfer with command ORed with address
// switch to 8-bit SPI mode
// Send one or more data bytes
// Raise chip-select line
//
// At 20 MHz SPI bus rate:
// Command ORed with address, plus mode change, takes 2.2 microsec
// Each byte takes 0.75 microseconds 

/* ====== MCP4822 control word =========================================
bit 15 A/B: DACA or DACB Selection bit
1 = Write to DACB
0 = Write to DACA
bit 14 ? Don?t Care
bit 13 GA: Output Gain Selection bit
1 = 1x (VOUT = VREF * D/4096)
0 = 2x (VOUT = 2 * VREF * D/4096), where internal VREF = 2.048V.
bit 12 SHDN: Output Shutdown Control bit
1 = Active mode operation. VOUT is available. ?
0 = Shutdown the selected DAC channel. Analog output is not available at the channel that was shut down.
VOUT pin is connected to 500 k???typical)?
bit 11-0 D11:D0: DAC Input Data bits. Bit x is ignored.
*/
// A-channel, 1x, active
#define DAC_config_chan_A 0b0011000000000000
#define DAC_config_chan_B 0b1011000000000000

// === spi bit widths ====================================================
// hit the SPI control register directly
inline void Mode16(void);
// ========

inline void Mode8(void);
// ========

inline void Mode32(void);

inline void ram_write_open(const int cs, const int addr);

inline void ram_write(const short data);

inline void ram_write_close(const int cs);

inline void ram_write_open2(const int cs, const int addr);

inline void ram_write2(const short data);

inline void ram_write_close2(const int cs);

inline void ram_dac_write_open(const int ram_cs, const int addr);

inline void ram_dac_write();

inline void ram_dac_write_close(const int cs);

int ram_read_short(int cs, int addr);

inline void ram_read_open(const int ram_cs, const int addr);

inline int ram_read();

inline void ram_read_close(const int cs);

void dac_write_short(int data);

void ram_write_byte_cs(int cs, int addr, char data);

int ram_read_byte_cs(int cs, int addr);

// === DAC byte write =====================================================
// address between 0 and 2^17-1
// data bytes
void dac_write_byte(int data);

// === RAM byte write =====================================================
// address between 0 and 2^17-1
// data bytes
void ram_write_byte(int addr, char data);

// === RAM array write =====================================================
// address, pointer to an array containing the data, number of BYTES to store
void ram_write_byte_array(int addr, char* data, int count);

// === RAM byte read ======================================================
int ram_read_byte(int addr);

// === RAM array read ======================================================
// address, pointer to an array receiving the data, number of BYTES to read
int ram_read_byte_array(int addr, char* data, int count);

inline void spi_ram_dac_setup();

#endif	/* SPI_RAM_DAC_H */

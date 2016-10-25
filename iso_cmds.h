#ifndef _ISO_CMDS_H
#define _ISO_CMDS_H
/** Custom iso14230 SID commands implemented by the kernel */

/* (c) copyright fenugrec 2016
 * GPLv3
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#define SID_RMBA 0x23	/* ReadMemByAddress. format : <SID_RMBA> <AH> <AM> <AL> <SIZ>  , siz <= 251. */
				/* response : <SID + 0x40> <D0>....<Dn> <AH> <AM> <AL> */

#define SID_WMBA 0x3D	/* WriteMemByAddress (RAM only !) . format : <SID_WMBA> <AH> <AM> <AL> <SIZ> <DATA> , siz <= 250. */
				/* response : <SID + 0x40> <AH> <AM> <AL> */

#define SID_TP	0x3E	/* TesterPresent; not required but available. */

#define SID_DUMP 0xBD	/* format : 0xBD <AS> <BH BL> <AH AL>  ; AS=0 for EEPROM, =1 for ROM */
	#define SID_DUMP_EEPROM	0
	#define SID_DUMP_ROM 1

/* SID_FLASH and subcommands */
#define SID_FLASH 0xBC	/* low-level reflash commands; only available after successful RequestDownload */
	#define SIDFL_UNPROTECT 0x55	//enable erase / write. format : <SID_FLASH> <SIDFL_UNPROTECT> <~SIDFL_UNPROTECT>
	#define SIDFL_EB	0x01	//erase block. format : <SID_FLASH> <SIDFL_EB> <BLOCK #>
	#define SIDFL_WB	0x02	//write n-byte block. format : <SID_FLASH> <SIDFL_WB> <A2> <A1> <A0> <D0>...<D(SIDFL_WB_DLEN -1)> <CRC>
						// Address is <A2 A1 A0>;   CRC is calculated on address + data.
	#define SIDFL_WB_DLEN	128	//bytes per block

/* SID_CONF and subcommands */
#define SID_CONF 0xBE /* set & configure kernel */
	#define SID_CONF_SETSPEED 0x01	/* set comm speed (BRR divisor reg) : <SID_CONF> <SID_CONF_SETSPEED> <new divisor> */
			//this requires a new StartComm request at the new speed
	#define SID_CONF_SETEEPR 0x02	/* set eeprom_read() function address <SID_CONF> <SID_CONF_SETEEPR> <AH> <AM> <AL> */
	#define SID_CONF_CKS1	0x03	//verify if <CRCH:CRCL> hash is valid for a 256B chunk of the ROM (starting at <CNH:CNL> * 256)
								//<SID_CONF> <SID_CONF_CKS1> <CRCH> <CRCL> <CNH> <CNL>
		#define SID_CONF_CKS1_BADCKS	0x77	//NRC when crc is bad

#define SID_FLREQ 0x34	/* RequestDownload */
/* SID_FLREQ (0x34 RequestDownload) neg response codes */
#define SID34_BADFCCS	0x81
#define SID34_BADRAMER	0x82
#define SID34_BADDL_ERASE	0x83
#define SID34_BADDL_WRITE	0x84
#define SID34_BADINIT_ERASE	0x85
#define SID34_BADINIT_WRITE	0x86

#define SID_RESET 0x11	/* restart ECU */

#endif

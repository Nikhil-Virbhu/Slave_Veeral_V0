/* File description: This file will list out all the faults and their reset mechanism
 */
#include"main.h"

typedef union
{
	struct
	{
		uint8_t over_Ilink : 1;           //bit 0
		uint8_t over_Vlink : 1;           //bit 1
		uint8_t over_Iout : 1;         //bit 2
		uint8_t rsvd3 : 1;           //bit 3
		uint8_t rsvd4 : 1;       //bit 4
		uint8_t rsvd5 : 1;             //bit 5
		uint8_t rsvd6 : 1;          //bit 6
		uint8_t overTimed_Iout : 1;          //bit 7
	}bits;
	uint8_t byte;
}fault1_t;

typedef union
{
	struct
	{
		uint8_t rsvd0 : 1;           //bit 0
		uint8_t underVlink : 1;           //bit 1
		uint8_t rsvd2 : 1;         //bit 2
		uint8_t rsvd3 : 1;           //bit 3
		uint8_t rsvd4 : 1;       //bit 4
		uint8_t rsvd5 : 1;             //bit 5
		uint8_t rsvd6 : 1;          //bit 6
		uint8_t rsvd7 : 1;          //bit 7
	}bits;
	uint8_t byte;
}fault2_t;

typedef union
{
	struct
	{
		uint8_t ext_fault : 1;                  //bit 0
		uint8_t emergency_stop : 1;             //bit 1
		uint8_t driver_not_ready : 1;                      //bit 2
		uint8_t mcu_error : 1;                  //bit 3
		uint8_t can_1_fail : 1;                   //bit 4
		uint8_t parallel_port_fail : 1;         //bit 5
		uint8_t eeprom_fault : 1;                      //bit 6
		uint8_t can_2_fail : 1;                      //bit 7
	}bits;
	uint8_t byte;
}fault3_t;

typedef union
{
	struct
	{
		uint8_t overTemp_afe : 1;              //bit 0
		uint8_t overTemp_trafo : 1;            //bit 1
		uint8_t overTemp_psfb : 1;             //bit 2
		uint8_t overTemp_diode : 1;            //bit 3
		uint8_t rsvd4 : 1;                      //bit 4
		uint8_t rsvd5 : 1;                      //bit 5
		uint8_t rsvd6 : 1;                      //bit 6
		uint8_t rsvd7 : 1;                      //bit 7
	}bits;
	uint8_t byte;
}fault4_t;

typedef union
{
	struct //B2 faults for PSFB, B1 faults for AFE
	{
		uint8_t B1F1_fault : 1;
		uint8_t B1F2_fault : 1;
		uint8_t B1F3_fault : 1;
		uint8_t B1F4_fault : 1;
		uint8_t B2F1_fault : 1;
		uint8_t B2F2_fault : 1;
		uint8_t B2F3_fault : 1;
		uint8_t B2F4_fault : 1;
	}bits;
	uint8_t byte;
}fault5_t;

typedef union
{
	struct
	{
		uint8_t rsvd0 : 1;
		uint8_t rsvd1 : 1;
		uint8_t rsvd2 : 1;
		uint8_t rsvd3 : 1;
		uint8_t rsvd4 : 1;
		uint8_t rsvd5 : 1;
		uint8_t rsvd6 : 1;
		uint8_t rsvd7 : 1;
	}bits;
	uint8_t byte;
}fault6_t;

typedef union
{
	struct
	{
		uint8_t ocf_m : 1;
		uint8_t ocf_d : 1;
		uint8_t cellAddress_fault : 1;
		uint8_t rsvd3 : 1;
		uint8_t rsvd4 : 1;
		uint8_t rsvd5 : 1;
		uint8_t rsvd6 : 1;
		uint8_t rsvd7 : 1;
	}bits;
	uint8_t byte;
}fault7_t;

typedef union
{
	struct
	{
		uint8_t rsvd0 : 1;
		uint8_t rsvd1 : 1;
		uint8_t rsvd2 : 1;
		uint8_t rsvd3 : 1;
		uint8_t rsvd4 : 1;
		uint8_t rsvd5 : 1;
		uint8_t rsvd6 : 1;
		uint8_t rsvd7 : 1;
	}bits;
	uint8_t byte;
}fault8_t;

typedef union
{
	struct
	{
		uint8_t system_on : 1;
		uint8_t fault_reset : 1;
		uint8_t emergency_stop : 1;
		uint8_t psfb_on : 1;
		uint8_t afe_pwm_mask : 1;
		uint8_t Parameter_Save : 1;
		uint8_t rsvd6 : 1;
		uint8_t rsvd7 : 1;
	}bits;
	uint8_t byte;
}command_t;
typedef union
{
	struct
	{
		uint8_t sHealthStatus: 1;
		uint8_t psfbFeedback : 1;
		uint8_t rsvd2 : 1;
		uint8_t rsvd3 : 1;
		uint8_t rsvd4 : 1;
		uint8_t rsvd5 : 1;
		uint8_t rsvd6 : 1;
		uint8_t rsvd7 : 1;
	}bits;
	uint8_t byte;
}status1_t;

typedef union
{
	struct
	{
		uint8_t rsvd0 : 1;
		uint8_t rsvd1 : 1;
		uint8_t rsvd2 : 1;
		uint8_t rsvd3 : 1;
		uint8_t rsvd4 : 1;
		uint8_t rsvd5 : 1;
		uint8_t rsvd6 : 1;
		uint8_t rsvd7 : 1;
	}bits;
	uint8_t byte;
}status2_t;

typedef union
{
	struct
	{
		uint8_t rsvd0 : 1;
		uint8_t rsvd1 : 1;
		uint8_t rsvd2 : 1;
		uint8_t rsvd3 : 1;
		uint8_t rsvd4 : 1;
		uint8_t rsvd5 : 1;
		uint8_t rsvd6 : 1;
		uint8_t rsvd7 : 1;
	}bits;
	uint8_t byte;
}status3_t;

/*ovL - Over limit*/
typedef struct
{
	uint16_t ovlCount;
	uint16_t ovlFault;
	uint16_t ovlResetCount;
	uint16_t ovlNoOfReset;
	uint16_t ovlFaultLatched;
	uint32_t ovlCoolDownCount;
	uint16_t threshold;
	float threshold_time; // threshold_time
	uint16_t reset_threshold;
	float reset_threshold_time;// reset_threshold_time
	uint8_t autoreset;
	uint8_t cooldown_enable;
	uint32_t cooldown_time;
	uint8_t no_of_reset;
	uint16_t sampleFreq;
}ovLFault_t;

/*underLimit (underL*/
typedef struct
{
	uint16_t underLCount;
	uint16_t underLFault;
	uint16_t underLResetCount;
	uint16_t underLNoOfReset;
	uint16_t underLFaultLatched;
	uint16_t underLCoolDownCount;
	uint16_t threshold;
	float threshold_time;
	uint16_t reset_threshold;
	float reset_threshold_time;
	uint8_t autoreset;
	uint8_t cooldown_enable;
	uint32_t cooldown_time;
	uint8_t no_of_reset;
	uint16_t sampleFreq;
}underLFault_t;

#ifdef _PROTECTION_
	fault1_t fault1;
	fault2_t fault2;
	fault3_t fault3;
	fault4_t fault4;
	fault5_t fault5;
	fault6_t fault6;
	fault7_t fault7;
	fault8_t fault8;
	command_t cmd;
	status1_t status1;
	status2_t status2;
	status3_t status3;

	ovLFault_t overlinkCurr, overlinkVolt, overIout, overDiodeTemp, overPsfbTemp, overAfeTemp, overTrafoTemp;
	//ovLFault_t overVout, overIac, overVsupply, overIsupply; 	// This section is not mounted on PCB
	underLFault_t underlinkVolt;
	//underLFault_t underVout, underSupplyVolt;		// This section is not mounted on PCB
	void faultInit(void);
	void check_over_limit(ovLFault_t *fhand, float value);
	void check_over_limitI(ovLFault_t *fhand, float value);
	void check_under_limit(underLFault_t *fhand, float value);
	void manual_fault_reset(void);
	void read_fecFault(void);
	void reset_driver(void);
	uint8_t sHealthStatus;
	void slave_health(void);
	void faultDetection(void);

#else

	extern fault1_t fault1;
	extern fault2_t fault2;
	extern fault3_t fault3;
	extern fault4_t fault4;
	extern fault5_t fault5;
	extern fault6_t fault6;
	extern fault7_t fault7;
	extern fault8_t fault8;
	extern command_t cmd;
	extern status1_t status1;
	extern status2_t status2;
	extern status3_t status3;

	extern 	ovLFault_t overlinkCurr, overlinkVolt, overIout, overDiodeTemp, overPsfbTemp, overAfeTemp, overTrafoTemp;
	//extern ovLFault_t overVout, overIac, overVsupply, overIsupply; 	// This section is not mounted on PCB
	extern underLFault_t underlinkVolt;
	//extern underLFault_t underVout, underSupplyVolt;		// This section is not mounted on PCB
	extern void reset_driver(void);
	extern void faultInit(void);
	extern void check_over_limit(ovLFault_t *fhand, float value);
	extern void check_over_limitI(ovLFault_t *fhand, float value);
	extern void check_under_limit(underLFault_t *fhand, float value);
	extern void manual_fault_reset(void);
	extern void read_fecFault(void);
	extern uint8_t sHealthStatus;
	extern void slave_health(void);
	extern void faultDetection(void);
#endif


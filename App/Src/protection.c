#define _PROTECTION_
#include "protection.h"
#include "process.h"
#include "interface.h"
#include "error_display.h"
uint8_t fault_timer=0;

void reset_driver()
{
//	HAL_GPIO_WritePin(DRST_GPIO_Port, DRST_Pin, GPIO_PIN_RESET);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(DRST_GPIO_Port, DRST_Pin, GPIO_PIN_SET);
}

/*
 * We will set the value of ovlFault to 1 or 0 to depict the occurrence of fault
 * We will check the parameter after calling the function
 * That will enable us to set the fault bit
 */
//Currently dummy values are given to the faults
void faultInit(void)
{
	//Over Idc (link current) parameters
	overlinkCurr.ovlCount = 0; //always initialized as 0
	overlinkCurr.ovlFault = 0; //always initialized as 0
	overlinkCurr.ovlResetCount = 0; //always initialized as 0
	overlinkCurr.ovlNoOfReset = 3;
	overlinkCurr.ovlFaultLatched = 0;
	overlinkCurr.ovlCoolDownCount = 0; //always initialized as 0
	overlinkCurr.threshold = 17.0f;
	overlinkCurr.threshold_time = 5.0f/1000.0f;
	overlinkCurr.reset_threshold = 0; //Not applicable for current
	overlinkCurr.reset_threshold_time = 0; //Not applicable for current
	overlinkCurr.no_of_reset = 0; //Not applicable for current
	overlinkCurr.autoreset = 0;  //Not applicable for current
	overlinkCurr.cooldown_enable = 1;
	overlinkCurr.cooldown_time = 86400;
	overlinkCurr.sampleFreq = 5000.0f;

	//Over output current parameters
	overIout.ovlCount = 0; //always initialized as 0
	overIout.ovlFault = 0; //always initialized as 0
	overIout.ovlResetCount = 0; //always initialized as 0
	overIout.ovlNoOfReset = 3;
	overIout.ovlFaultLatched = 0;
	overIout.ovlCoolDownCount = 0; //always initialized as 0
	overIout.threshold = 17.0f;
	overIout.threshold_time = 5.0f/1000.0f;
	overIout.reset_threshold = 0; //Not applicable for current
	overIout.reset_threshold_time = 0; //Not applicable for current
	overIout.no_of_reset = 0; //Not applicable for current
	overIout.autoreset = 0;  //Not applicable for current
	overIout.cooldown_enable = 1;
	overIout.cooldown_time = 86400;
	overIout.sampleFreq = 5000.0f;

	//Over Vdc (link voltage) parameters
	overlinkVolt.ovlCount = 0;  //always initialized as 0
	overlinkVolt.ovlFault = 0; //always initialized as 0
	overlinkVolt.ovlResetCount = 0;
	overlinkVolt.ovlNoOfReset = 3;
	overlinkVolt.ovlFaultLatched = 0;
	overlinkVolt.ovlCoolDownCount = 0; //always initialized as 0
	overlinkVolt.threshold = 1190.0f;
	overlinkVolt.threshold_time = 5.0f/1000.0f;
	overlinkVolt.reset_threshold = 900; //TBD
	overlinkVolt.reset_threshold_time =5.0f/1000.0f;
	overlinkVolt.no_of_reset = 0;
	overlinkVolt.autoreset = 0;
	overlinkVolt.cooldown_enable = 1;
	overlinkVolt.cooldown_time = 86400;
	overlinkVolt.sampleFreq = 5000.0f;

	//Under Vdc (link voltage) parameters
	underlinkVolt.underLCount = 0; //always initialized as 0
	underlinkVolt.underLFault = 0; //always initialized as 0
	underlinkVolt.underLResetCount = 0; //always initialized as 0
	underlinkVolt.underLNoOfReset = 3;
	underlinkVolt.underLFaultLatched = 0;
	underlinkVolt.underLCoolDownCount = 0;
	underlinkVolt.threshold = 90; //TBD
	underlinkVolt.threshold_time = 5.0f/1000.0f;
	underlinkVolt.reset_threshold = 95; //TBD
	underlinkVolt.reset_threshold_time = 5.0f/1000.0f;
	underlinkVolt.no_of_reset = 3;
	underlinkVolt.autoreset = 0;
	underlinkVolt.cooldown_enable = 1;
	underlinkVolt.cooldown_time = 86400;
	underlinkVolt.sampleFreq = 5000.0f;

	//Over output voltage parameters
/*	This section is not mounted on PCB
 * overVout.ovlCount = 0; //always initialized as 0
	overVout.ovlFault = 0; //always initialized as 0
	overVout.ovlResetCount = 0; //always initialized as 0
	overVout.ovlNoOfReset = 3;
	overVout.ovlFaultLatched = 0;
	overVout.ovlCoolDownCount = 0; //always initialized as 0
	overVout.threshold = 1200.0f;
	overVout.threshold_time = 5.0f/1000.0f;
	overVout.reset_threshold = 1000; //TBD
	overVout.reset_threshold_time = 5.0f/1000.0f;
	overVout.no_of_reset = 0;
	overVout.autoreset = 0;
	overVout.cooldown_enable = 1;
	overVout.cooldown_time = 86400;
	overVout.sampleFreq = 5000.0f;*/

/*	//Under output voltage parameters
 * This section is not mounted on PCB
	underVout.underLCount = 0; //always initialized as 0
	underVout.underLFault = 0; //always initialized as 0
	underVout.underLResetCount = 0; //always initialized as 0
	underVout.underLNoOfReset = 3;
	underVout.underLFaultLatched = 0;
	underVout.underLCoolDownCount = 0;
	underVout.threshold = 900; // TBD
	underVout.threshold_time = 5.0f/1000.0f;
	underVout.reset_threshold = 950; //TBD
	underVout.reset_threshold_time = 5.0f/1000.0f;
	underVout.no_of_reset = 0;
	underVout.autoreset = 0;
	underVout.cooldown_enable = 1;
	underVout.cooldown_time = 86400;
	underVout.sampleFreq = 5000.0f;*/

/*	//Over AC current (Iac) parameters
 * This section is not mounted on PCB
	overIac.ovlCount = 0; //always initialized as 0
	overIac.ovlFault = 0; //always initialized as 0
	overIac.ovlResetCount = 0; //always initialized as 0
	overIac.ovlNoOfReset = 3;
	overIac.ovlFaultLatched = 0;
	overIac.ovlCoolDownCount = 0; //always initialized as 0
	overIac.threshold = 10.0f;
	overIac.threshold_time = 100.0f/1000.0f;
	overIac.reset_threshold = 0; //Not applicable for current
	overIac.reset_threshold_time = 0; //Not applicable for current
	overIac.no_of_reset = 0; //Not applicable for current
	overIac.autoreset = 0; //Not applicable for current
	overIac.cooldown_enable = 1;
	overIac.cooldown_time = 86400;
	overIac.sampleFreq = 50.0f;*/

/*	//Over supply voltage parameters
 * This section is not mounted on PCB
	overVsupply.ovlCount = 0; //always initialized as 0
	overVsupply.ovlFault = 0; //always initialized as 0
	overVsupply.ovlResetCount = 0; //always initialized as 0
	overVsupply.ovlNoOfReset = 3;
	overVsupply.ovlFaultLatched = 0;
	overVsupply.ovlCoolDownCount = 0; //always initialized as 0
	overVsupply.threshold = 13000.0f;
	overVsupply.threshold_time = 100.0f/1000.0f;
	overVsupply.reset_threshold = 12000.0f;
	overVsupply.reset_threshold_time = 100.0f/1000.0f;
	overVsupply.no_of_reset = 0;
	overVsupply.autoreset = 0;
	overVsupply.cooldown_enable = 1;
	overVsupply.cooldown_time = 86400;
	overVsupply.sampleFreq = 50.0f;*/

/*	//Under supply voltage parameters
 * This section is not mounted on PCB
	underSupplyVolt.underLCount = 0; //always initialized as 0
	underSupplyVolt.underLFault = 0; //always initialized as 0
	underSupplyVolt.underLResetCount = 0; //always initialized as 0
	underSupplyVolt.underLNoOfReset = 3;
	underSupplyVolt.underLFaultLatched = 0;
	underSupplyVolt.underLCoolDownCount = 0;
	underSupplyVolt.threshold = 11000.0f; //TBD
	underSupplyVolt.threshold_time = 100.0f/1000.0f;;
	underSupplyVolt.reset_threshold = 12000.0f; //TBD
	underSupplyVolt.reset_threshold_time = 100.0f/1000.0f;;
	underSupplyVolt.no_of_reset = 0;
	underSupplyVolt.autoreset = 0;
	underSupplyVolt.cooldown_enable = 1;
	underSupplyVolt.cooldown_time = 86400;
	underSupplyVolt.sampleFreq = 50.0f;*/

/*	//Over supply current parameters
 * This section is not mounted on PCB
	overIsupply.ovlCount = 0; //always initialized as 0
	overIsupply.ovlFault = 0; //always initialized as 0
	overIsupply.ovlResetCount = 0; //always initialized as 0
	overIsupply.ovlNoOfReset = 3;
	overIsupply.ovlFaultLatched = 0;
	overIsupply.ovlCoolDownCount = 0; //always initialized as 0
	overIsupply.threshold = 10.0f;
	overIsupply.threshold_time = 100.0f/1000.0f;
	overIsupply.reset_threshold = 0; //Not applicable for current
	overIsupply.reset_threshold_time = 0; //Not applicable for current
	overIsupply.no_of_reset = 0; //Not applicable for current
	overIsupply.autoreset = 0; //Not applicable for current
	overIsupply.cooldown_enable = 1;
	overIsupply.cooldown_time = 86400;
	overIsupply.sampleFreq = 50.0f;*/

//	//Over timed Idc (Iout current) parameters
//	overtimedIout.ovlCount = 0; // Dynamic parameters will change during the course of execution
//	overtimedIout.ovlFault = 0;
//	overtimedIout.ovlResetCount = 0;
//	overtimedIout.ovlNoOfReset = 0;
//	overtimedIout.ovlFaultLatched = 0;
//	overtimedIout.ovlCoolDownCount = 0;
//	overtimedIout.threshold = 300.0f; // Static parameters can be configured using ConfigPara
//	overtimedIout.threshold_time = 1000;
//	overtimedIout.reset_threshold = 250.0f;
//	overtimedIout.reset_threshold_time = 1000;
//	overtimedIout.no_of_reset = 3;
//	overtimedIout.autoreset = 0;
//	overtimedIout.cooldown_enable = 1;
//	overtimedIout.cooldown_time = 1000;
//	overtimedIout.sampleFreq = 5000.0f;

// Over diode temperature parameters
	overDiodeTemp.ovlCount = 0; //always initialized as 0
	overDiodeTemp.ovlFault = 0; //always initialized as 0
	overDiodeTemp.ovlResetCount = 0; //always initialized as 0
	overDiodeTemp.ovlNoOfReset = 3;
	overDiodeTemp.ovlFaultLatched = 0;
	overDiodeTemp.ovlCoolDownCount = 0;
	overDiodeTemp.threshold =  90;
	overDiodeTemp.threshold_time = 1000; // 1/40*5
	overDiodeTemp.reset_threshold = 80;
	overDiodeTemp.reset_threshold_time = 1000; // 1/40*5
	overDiodeTemp.no_of_reset = 0;
	overDiodeTemp.autoreset = 0;
	overDiodeTemp.cooldown_enable = 1;
	overDiodeTemp.cooldown_time = 1000;
	overDiodeTemp.sampleFreq = 40.0f;

	// Over psfb temperature parameters
	overPsfbTemp.ovlCount = 0; //always initialized as 0
	overPsfbTemp.ovlFault = 0; //always initialized as 0
	overPsfbTemp.ovlResetCount = 0; //always initialized as 0
	overPsfbTemp.ovlNoOfReset = 3;
	overPsfbTemp.ovlFaultLatched = 0;
	overPsfbTemp.ovlCoolDownCount = 0;
	overPsfbTemp.threshold = 90;
	overPsfbTemp.threshold_time = 1000; // 1/40*5
	overPsfbTemp.reset_threshold = 80;
	overPsfbTemp.reset_threshold_time = 1000; // 1/40*5
	overPsfbTemp.no_of_reset = 0;
	overPsfbTemp.autoreset = 0;
	overPsfbTemp.cooldown_enable = 1;
	overPsfbTemp.cooldown_time = 1000;
	overPsfbTemp.sampleFreq = 40.0f;

	// Over AFE temperature parameters
	overAfeTemp.ovlCount = 0; //always initialized as 0
	overAfeTemp.ovlFault = 0; //always initialized as 0
	overAfeTemp.ovlResetCount = 0; //always initialized as 0
	overAfeTemp.ovlNoOfReset = 3;
	overAfeTemp.ovlFaultLatched = 0;
	overAfeTemp.ovlCoolDownCount = 0;
	overAfeTemp.threshold = 90;
	overAfeTemp.threshold_time = 1000; // 1/40*5
	overAfeTemp.reset_threshold = 80;
	overAfeTemp.reset_threshold_time = 1000; // 1/40*5
	overAfeTemp.no_of_reset = 0;
	overAfeTemp.autoreset = 0;
	overAfeTemp.cooldown_enable = 1;
	overAfeTemp.cooldown_time = 1000;
	overAfeTemp.sampleFreq = 40.0f;

	// Over Trafo temperature parameters
	overTrafoTemp.ovlCount = 0; //always initialized as 0
	overTrafoTemp.ovlFault = 0; //always initialized as 0
	overTrafoTemp.ovlResetCount = 0; //always initialized as 0
	overTrafoTemp.ovlNoOfReset = 3;
	overTrafoTemp.ovlFaultLatched = 0;
	overTrafoTemp.ovlCoolDownCount = 0;
	overTrafoTemp.threshold = 90;
	overTrafoTemp.threshold_time = 1000; // 1/40*5
	overTrafoTemp.reset_threshold = 80;
	overTrafoTemp.reset_threshold_time = 1000; // 1/40*5
	overTrafoTemp.no_of_reset = 0;
	overTrafoTemp.autoreset = 0;
	overTrafoTemp.cooldown_enable = 1;
	overTrafoTemp.cooldown_time = 1000;
	overTrafoTemp.sampleFreq = 40.0f;
}


void check_over_limit(ovLFault_t *fhand, float value)
{


	if(fhand->ovlFault!=1){
	//check if the quantity is above the threshold
		if(value > fhand->threshold){
			fhand->ovlCount = fhand->ovlCount + 1;
		}else{
			fhand->ovlCount = 0;
		}


		//check if the quantity is above the threshold for given time

		if(fhand->ovlCount > (fhand->sampleFreq*fhand->threshold_time)){
			fhand->ovlCount = 0;
			fhand->ovlFault = 1;
					}

	}else{
		//try auto reset if the fault is not latched
		if(fhand->autoreset && (!fhand->ovlFaultLatched)){
		 //check if the voltage is below the reset threshold
			if(value < fhand->reset_threshold){
				fhand->ovlResetCount = fhand->ovlResetCount + 1;
			}else{
				fhand->ovlResetCount =0;
			}
			//check if the quantity is below the reset threshold for given time
			if(fhand->ovlResetCount > (fhand->sampleFreq*fhand->reset_threshold_time)){
				fhand->ovlResetCount = 0;
				fhand->ovlFault = 0;
				fhand->ovlNoOfReset = fhand->ovlNoOfReset + 1;
			}
		}
	}
	//cool down time means that "no_of_reset" will be reduced by one for every given time
	//this is to prevent the fault accumulation.
	//example: if one over voltage fault occurred today and next one occurred previous week
	//with COOLDOWN_ENABLE "no_of_reset" will be 1
	//without COOLDOWN_ENABLE "no_of_reset" will be 2
	if(fhand->cooldown_enable){
		if(fhand->ovlNoOfReset > 0){
			fhand->ovlCoolDownCount = fhand->ovlCoolDownCount + 1;
			if(fhand->ovlCoolDownCount > (fhand->sampleFreq*fhand->cooldown_time)){
				fhand->ovlCoolDownCount = 0;
				fhand->ovlNoOfReset = fhand->ovlNoOfReset - 1;
			}
		}
	}
	//if the fault is reset for given number of times, latch the fault
	if(fhand->ovlNoOfReset > fhand->no_of_reset){
		fhand->ovlNoOfReset = 0;
		fhand->ovlFaultLatched = 1;
	}
}



/*
* Function Description: To check under limit of quantities
* Input:
* Return:
*/
void check_under_limit(underLFault_t *fhand, float value){
	if(fhand->underLFault!=1){
		//check if the quantity is below the threshold
			if(value < fhand->threshold){
				fhand->underLCount = fhand->underLCount + 1;
			}else{
				fhand->underLCount = 0;
			}

			//check if the quantity is below the threshold for given time
			if(fhand->underLCount < (fhand->sampleFreq*fhand->threshold_time)){
				fhand->underLCount = 0;
				fhand->underLFault = 1;
			}
		}else{
			//try auto reset if the fault is not latched
			if(fhand->autoreset && (!fhand->underLFaultLatched)){
			 //check if the voltage is above the reset threshold
				if(value > fhand->reset_threshold){
					fhand->underLResetCount = fhand->underLResetCount + 1;
				}else{
					fhand->underLResetCount =0;
				}
				//check if the quantity is above the reset threshold for given time
				if(fhand->underLResetCount < (fhand->sampleFreq*fhand->reset_threshold_time)){
					fhand->underLResetCount = 0;
					fhand->underLFault = 0;
					fhand->underLNoOfReset = fhand->underLNoOfReset + 1;
				}
			}
		}
	//cool down time means that "no_of_reset" will be reduced by one for every given time
	//this is to prevent the fault accumulation.
	//example: if one over voltage fault occurred today and next one occurred previous week
	//with COOLDOWN_ENABLE "no_of_reset" will be 1
	//without COOLDOWN_ENABLE "no_of_reset" will be 2
	if(fhand->cooldown_enable){
		if(fhand->underLNoOfReset > 0){
			fhand->underLCoolDownCount = fhand->underLCoolDownCount + 1;
			if(fhand->underLCoolDownCount > (fhand->sampleFreq*fhand->cooldown_time)){
				fhand->underLCoolDownCount = 0;
				fhand->underLNoOfReset = fhand->underLNoOfReset - 1;
			}
		}
	}

		//if the fault is reset for given number of times, latch the fault
		if(fhand->underLNoOfReset > fhand->no_of_reset){
			fhand->underLNoOfReset = 0;
			fhand->underLFaultLatched = 1;
		}
}

void check_over_limitI(ovLFault_t *fhand, float value)
{
	if(fhand->ovlFault!=1){
	//check if the quantity is above the threshold
		if(value > fhand->threshold){
			fhand->ovlCount = fhand->ovlCount + 1;
		}else{
			fhand->ovlCount = 0;
		}

		//check if the quantity is above the threshold for given time
		if(fhand->ovlCount > (fhand->sampleFreq*fhand->threshold_time)){
			fhand->ovlCount = 0;
			fhand->ovlFault = 1;
			fhand->ovlNoOfReset += 1;
		}
	}
			//cool down time means that "no_of_reset" will be reduced by one for every given time
			//this is to prevent the fault accumulation.
			//example: if one over voltage fault occurred today and next one occurred previous week
			//with COOLDOWN_ENABLE "no_of_reset" will be 1
			//without COOLDOWN_ENABLE "no_of_reset" will be 2
	if(fhand->cooldown_enable){
		if(fhand->ovlNoOfReset > 0){
			fhand->ovlCoolDownCount = fhand->ovlCoolDownCount + 1;
			if(fhand->ovlCoolDownCount > (fhand->sampleFreq*fhand->cooldown_time)){
				fhand->ovlCoolDownCount = 0;
				fhand->ovlNoOfReset = fhand->ovlNoOfReset - 1;
			}
		}
	}

	//if the fault is reset for given number of times, latch the fault
	if(fhand->ovlNoOfReset > fhand->no_of_reset){
		fhand->ovlNoOfReset = 0;
		fhand->ovlFaultLatched = 1;
	}
}

void slave_health()
{

	if(fault1.byte != 0|| /*fault2.byte != 0 || fault3.byte != 0|| fault4.byte != 0 ||*/ fault5.byte != 0 /*|| fault6.byte != 0 || fault7.byte != 0*/)
	{
		status1.bits.sHealthStatus = 1;
		fault_timer++;
		if (fault_timer > 250)
		{
			//LED2_TOGGLE;
			fault_timer = 0;
		}
	}
}
/*
 * This function will try to reset the fault if the faults are no longer present.
 * whenever cmd.bits.fault_reset = 1; this function will be executed once
 */
void manual_fault_reset(void)
{
	status1.bits.sHealthStatus = 0;
	sHealthStatus = 0;
	cmd.bits.fault_reset = 0;
	turnOff();
	LED2_OFF;
	if (fault5.byte!= 0)
	{
	reset_driver(); //reset the driver
	fault5.byte = 0;
	remove_error_from_list(18);
	remove_error_from_list(19);
	remove_error_from_list(20);
	remove_error_from_list(21);
	remove_error_from_list(22);
	remove_error_from_list(23);
	remove_error_from_list(24);
	remove_error_from_list(25);
	}
	if(fault1.bits.over_Ilink == 1){ //check if fault is present
		overlinkCurr.ovlFault = 0;
		remove_error_from_list(1);
	}
	if(fault1.bits.over_Vlink == 1){
		overlinkVolt.ovlFault = 0;
		remove_error_from_list(2);

	}
/*	This section is not mounted on PCB
 * if(fault1.bits.overIsup == 1){
		overIsupply.ovlFault = 0;
	}
	if(fault1.bits.overVsup == 1){
		overVsupply.ovlFault = 0;
	}
	if(fault1.bits.over_Iafe == 1){
		overIac.ovlFault = 0;
	}
		if(fault1.bits.over_Vout == 1){
		overVout.ovlFault = 0;
	}
		if(fault2.bits.underSupVolt == 1){
		underSupplyVolt.underLFault = 0;
	}
		if(fault2.bits.under_Vout == 1){
		underVout.underLFault = 0;
	}
	*/
	if(fault1.bits.over_Iout == 1){
		overIout.ovlFault = 0;
		remove_error_from_list(3);
	}

//	if(fault1.bits.overTimed_Iout == 1){
//		overtimedIout.ovlFault = 0;
//	}

	if(fault2.bits.underVlink == 1){
		underlinkVolt.underLFault = 0;
		remove_error_from_list(5);
	}

	if(fault4.bits.overTemp_diode == 1){
		overDiodeTemp.ovlFault = 0;
		remove_error_from_list(17);
	}
	if(fault4.bits.overTemp_afe == 1){
		overAfeTemp.ovlFault = 0;
		remove_error_from_list(14);
	}
	if(fault4.bits.overTemp_psfb == 1){
		overPsfbTemp.ovlFault = 0;
		remove_error_from_list(16);
	}
	if(fault4.bits.overTemp_trafo == 1){
		overTrafoTemp.ovlFault = 0;
		remove_error_from_list(15);
	}
	if(fault3.bits.driver_not_ready == 1){
		reset_driver();
		fault3.bits.driver_not_ready= 0;
		remove_error_from_list(8);
	}
}

void faultDetection(void){

//	if((HAL_GPIO_ReadPin(AFEF1_GPIO_Port, AFEF1_Pin) == 0) && fault5.bits.B1F1_fault == 0){
//		fault5.bits.B1F1_fault = 1;
//		add_error_to_list(18);
//	}
//	if((HAL_GPIO_ReadPin(AFEF2_GPIO_Port, AFEF2_Pin) == 0) && fault5.bits.B1F2_fault == 0){
//		fault5.bits.B1F2_fault = 1;
//		add_error_to_list(19);
//	}
//	if((HAL_GPIO_ReadPin(AFEF3_GPIO_Port, AFEF3_Pin) == 0) && fault5.bits.B1F3_fault == 0){
//		fault5.bits.B1F3_fault = 1;
//		add_error_to_list(20);
//	}
//	if((HAL_GPIO_ReadPin(AFEF4_GPIO_Port, AFEF4_Pin) == 0) && fault5.bits.B1F4_fault == 0){
//		fault5.bits.B1F4_fault = 1;
//		add_error_to_list(21);
//	}
//	if((HAL_GPIO_ReadPin(PSFBF1_GPIO_Port, PSFBF1_Pin) == 0) && fault5.bits.B2F1_fault == 0){
//		fault5.bits.B2F1_fault = 1;
//		add_error_to_list(22);
//	}
//	if((HAL_GPIO_ReadPin(PSFBF2_GPIO_Port, PSFBF2_Pin) == 0) && fault5.bits.B2F2_fault == 0){
//		fault5.bits.B2F2_fault = 1;
//		add_error_to_list(23);
//	}
//	if((HAL_GPIO_ReadPin(PSFBF3_GPIO_Port, PSFBF3_Pin) == 0) && fault5.bits.B2F3_fault == 0){
//		fault5.bits.B2F3_fault = 1;
//		add_error_to_list(24);
//	}
//	if((HAL_GPIO_ReadPin(PSFBF4_GPIO_Port, PSFBF4_Pin) == 0) && fault5.bits.B2F4_fault == 0){
//		fault5.bits.B2F4_fault = 1;
//		add_error_to_list(25);
//	}
/*	if((HAL_GPIO_ReadPin(OCFd_GPIO_Port, OCFd_Pin) == 0) && fault7.bits.ocf_d == 0){
		fault7.bits.ocf_d  = 1;
		add_error_to_list(27);
	}
	if((HAL_GPIO_ReadPin(OCFm_GPIO_Port, OCFm_Pin) == 0) && fault7.bits.ocf_m == 0){
		fault7.bits.ocf_m = 1;
		add_error_to_list(26);
	}*/
}

/*
 * LEDConfig.h
 *
 *  Created on: Aug 4, 2023
 *      Author: User
 */

#ifndef LEDCONFIG_H_
#define LEDCONFIG_H_

#define CALL_RED_LED_1_POS 4
#define CALL_RED_LED_2_POS 5
#define CALL_RED_LED_3_POS 6
#define CALL_RED_LED_4_POS 7
#define CALL_RED_LED_5_POS 0
#define CALL_RED_LED_6_POS 1
#define CALL_RED_LED_7_POS 2
#define CALL_RED_LED_8_POS 3

#define CALL_GREEN_LED_1_POS 3
#define CALL_GREEN_LED_2_POS 2
#define CALL_GREEN_LED_3_POS 1
#define CALL_GREEN_LED_4_POS 0
#define CALL_GREEN_LED_5_POS 7
#define CALL_GREEN_LED_6_POS 6
#define CALL_GREEN_LED_7_POS 5
#define CALL_GREEN_LED_8_POS 4

#define RESP_GREEN_LED_1_POS 3
#define RESP_GREEN_LED_2_POS 2
#define RESP_GREEN_LED_3_POS 1
#define RESP_GREEN_LED_4_POS 0
#define RESP_GREEN_LED_5_POS 7
#define RESP_GREEN_LED_6_POS 6
#define RESP_GREEN_LED_7_POS 5
#define RESP_GREEN_LED_8_POS 4

#define RESP_RED_LED_1_POS 4
#define RESP_RED_LED_2_POS 5
#define RESP_RED_LED_3_POS 6
#define RESP_RED_LED_4_POS 7
#define RESP_RED_LED_5_POS 0
#define RESP_RED_LED_6_POS 1
#define RESP_RED_LED_7_POS 2
#define RESP_RED_LED_8_POS 3

#define LED_ON 1
#define LED_OFF 0

#define NUMBER_OF_COLORS 4
#define NOTHING_COLOR 0
#define GREEN_COLOR 1
#define RED_COLOR 2
#define YELLOW_COLOR 3

#define CALL_OK_COLOR GREEN_COLOR
#define CALL_INCORRECT_COLOR YELLOW_COLOR
#define CALL_BROKEN_LINE_COLOR RED_COLOR
#define RESP_OK_COLOR GREEN_COLOR
#define RESP_INCORRECT_COLOR YELLOW_COLOR
#define RESP_BROKEN_LINE_COLOR RED_COLOR
#define RESP_EXPECTED_LINE_COLOR RED_COLOR

// todo: number of repeatitions

#define USE_TIMER 1

#define PERIOD_OF_RINGING_LINE_US 10

#define TIME_BLINKING_LED_MS 100
#define TIME_CABLE_DATA_LED_MS 1000

//#define CLOCK_FREQUENCY 16000000
//#define CLOCK_PRESCALER 125
//#define CLOCK_PERIOD 32499

#define NUMBER_OF_LINES 8
#define NUMBER_OF_LEDS 16

#define NUMBER_OF_SR 2

#define SR_DATA_bm 0b00000001
#define SR_DATA_CALL 0b11111111

#define WIRE_NACK 0
#define WIRE_ACK 1


#endif /* LEDCONFIG_H_ */

/*!*********************************************************************************************************************
@file user_app1.h
@brief Header file for user_app1

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
1. Follow the instructions at the top of user_app1.c
2. Use ctrl-h to find and replace all instances of "user_app1" with "yournewtaskname"
3. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
4. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
5. Add #include yournewtaskname.h" to configuration.h
6. Add/update any special configurations required in configuration.h (e.g. peripheral assignment and setup values)
7. Delete this text (between the dashed lines)
----------------------------------------------------------------------------------------------------------------------

**********************************************************************************************************************/

#ifndef __USER_APP1_H
#define __USER_APP1_H

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/


/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */
/*--------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */
/*--------------------------------------------------------------------------------------------------------------------*/
void UserApp1Initialize(void);
void UserApp1RunActiveState(void);


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */
/*--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
State Machine Declarations
***********************************************************************************************************************/
static void UserApp1SM_Idle(void);
static void UserApp1SM_Error(void);

static void LedPatternManager(void);
static void SetLeds(const u8 u8Pattern_, const u8 u8Value_);
static void SetAllLedsOff(void);
static void SetBinaryCounterLeds(const u8 u8Value_);
static void SetRightToLeftLeds(const u8 u8Value_);
static void SetLeftToRightLeds(const u8 u8Value_);
static void SetOddLeds(void);
static void SetEvenLeds(void);
static void SetRightHalfLeds(void);
static void SetLeftHalfLeds(void);

static void LcdPwmManager(void);

/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/
#define U16_BLINK_PERIOD_MS ((u16)250)
#define U16_LCD_BACKLIGHT_COLORS_MAX ((u16)7)
#define U8_CHANGE_PATTERN_ROLL_COUNT ((u8)6)
#define U8_PATTERN_NUMBER ((u8)5)

#define U8_LCD_BACKLIGHT_UPDATE_MS ((u8)40)

#endif /* __USER_APP1_H */

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/

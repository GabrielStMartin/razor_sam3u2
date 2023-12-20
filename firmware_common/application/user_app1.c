/*!*********************************************************************************************************************
@file user_app1.c
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1RunActiveState(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                          /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags;                /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_<type>" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_pfStateMachine;               /*!< @brief The state machine function pointer */
//static u32 UserApp1_u32Timeout;                           /*!< @brief Timeout counter used across states */

static u16 u16BlinkCounter;
static u8 u8BinaryCounter;
static const LedNameType aBinaryCounterLeds[] = {RED, ORANGE, YELLOW, GREEN};
static u8 u8LcdColorIndex;

/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserApp1Initialize(void)

@brief
Initializes the State Machine and its variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserApp1Initialize(void)
{
  u16BlinkCounter = 0;
  u8BinaryCounter = 0;
  u8LcdColorIndex = 0;
  SetAllLedsOff();

  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_pfStateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_pfStateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */


/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserApp1RunActiveState(void)

@brief Selects and runs one iteration of the current state in the state machine.

All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
- State machine function pointer points at current state

Promises:
- Calls the function to pointed by the state machine function pointer

*/
void UserApp1RunActiveState(void)
{
  UserApp1_pfStateMachine();

} /* end UserApp1RunActiveState */


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/
/* What does this state do? */
static void UserApp1SM_Idle(void)
{
  if(++u16BlinkCounter == U16_BLINK_PERIOD_MS)
  {
    u16BlinkCounter = 0;

    /* Update the counter and roll at 16 */
    if(++u8BinaryCounter == 16)
    {
      u8BinaryCounter = 0;
    }
    SetBinaryCounterLeds(u8BinaryCounter);

    /* Manage to LCD backlight color */
    if(++u8LcdColorIndex == U16_LCD_BACKLIGHT_COLORS_MAX)
    {
      u8LcdColorIndex = 0;
    }
    SetLcdBacklightColor(u8LcdColorIndex);
  }
} /* end UserApp1SM_Idle() */

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)
{

} /* end UserApp1SM_Error() */

/*-------------------------------------------------------------------------------------------------------------------*/
/* Set all discrete LEDs off */
static void SetAllLedsOff(void)
{
  for(u8 i = 0; i < U8_TOTAL_LEDS; ++i)
  {
    LedOff(i);
  }
} /* SetAllLedsOff() */

/*-------------------------------------------------------------------------------------------------------------------*/
/* Set the binary counter LEDs based from u8Value */
static void SetBinaryCounterLeds(const u8 u8Value)
{
  for(u8 i = 0; i < 4; ++i)
  {
    if(u8Value & (1 << i))
    {
      LedOn(aBinaryCounterLeds[i]);
    }
    else
    {
      LedOff(aBinaryCounterLeds[i]);
    }
  }
} /* SetBinaryCounterLeds() */

/*-------------------------------------------------------------------------------------------------------------------*/
/* Set the LCD backlight color from u8Value */
static void SetLcdBacklightColor(const u8 u8Value)
{
  switch (u8Value)
  {
    case 0:
      /* white */
      LedOn(LCD_RED);
      LedOn(LCD_GREEN);
      LedOn(LCD_BLUE);
      break;

    case 1:
      /* purple */
      LedOn(LCD_RED);
      LedOff(LCD_GREEN);
      LedOn(LCD_BLUE);
      break;

    case 2:
      /* blue */
      LedOff(LCD_RED);
      LedOff(LCD_GREEN);
      LedOn(LCD_BLUE);
      break;

    case 3:
      /* cyan */
      LedOff(LCD_RED);
      LedOn(LCD_GREEN);
      LedOn(LCD_BLUE);
      break;

    case 4:
      /* green */
      LedOff(LCD_RED);
      LedOn(LCD_GREEN);
      LedOff(LCD_BLUE);
      break;

    case 5:
      /* yellow */
      LedOn(LCD_RED);
      LedOn(LCD_GREEN);
      LedOff(LCD_BLUE);
      break;

    case 6:
      /* red */
      LedOn(LCD_RED);
      LedOff(LCD_GREEN);
      LedOff(LCD_BLUE);
      break;

    default:
      /* off */
      LedOff(LCD_RED);
      LedOff(LCD_GREEN);
      LedOff(LCD_BLUE);
      break;
  }
} /* SetLcdBacklightColor() */

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************
 *****************************************************PROTOTYPE********************************************************
 *********************************************************************************************************************/
void Init(void);
/*!
 *Function: {void} Init(void)
 *
 *@Brief: Configure 2 LED pins as GPIO output and 2 Switch pins as GPIO input
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void swPressed(void);
/*!
 *Function: {void} swPressed(void)
 *
 *@Brief: Check if any Switch is pressed
 *		   	If Sw1 is pressed, Toggle RED LED
 *			 	If Sw2 is pressed, Toggle GREEN LED
 *		   	Else keep them Lighting up
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
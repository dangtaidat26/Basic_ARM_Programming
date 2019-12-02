/**********************************************************************************************************************
 *****************************************************PROTOTYPE********************************************************
 *********************************************************************************************************************/
void InitLED(void);
/*!
 *Function: {void} InitLED(void)
 *
 *@Brief: Configure GREEN LED pin as GPIO output
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void BlinkLED1(void);
/*!
 *Function: {void} BlinkLED1(void)
 *
 *@Brief: Blink LED Directly base on Port Data Output register
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void BlinkLED2(void);
/*!
 *Function: {void} BlinkLED2(void)
 *
 *@Brief: Blink LED by Setting and Clearing Data Output register
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void BlinkLED3(void);
/*!
 *Function: {void} BlinkLED3(void)
 *
 *@Brief: Blink LED by Toggling current Data Output register 
 *
 *@Param: <none>
 *
 *@Return: <none>
 */

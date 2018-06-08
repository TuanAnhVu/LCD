/*
 * Get value for row3 -> output display row3;
 * Get value for row1 -> output display row2;
 * Get value for row2 -> output display row1;
 * 
 */
#include"LCD.h"

double LCD::setRow(double num) {
  double row = num;
  return row;
}

double LCD::getRow() {

}

//Compare number -> LCD
int *LCD::compareNum(double num) {
  static int list_num[6];
  for (;;) {
			// Ten Million
		if (num >= 10000000) {
      list_num[5] = fmod(num/100, 10);
      list_num[4] = fmod(num/1000, 10);
      list_num[3] = fmod(num/10000, 10);
      list_num[2] = fmod(num/100000, 10);
			list_num[1] = fmod(num/1000000, 10);
			list_num[0] = fmod(num/10000000, 10);
      break;
		   //Million.
    } else if (num >= 1000000) {   
      list_num[5] = fmod(num/10, 10);
      list_num[4] = fmod(num/100, 10);
      list_num[3] = fmod(num/1000, 10);
      list_num[2] = fmod(num/10000, 10);
      list_num[1] = fmod(num/100000, 10);
			list_num[0] = fmod(num/1000000, 10);
      break;
			//hundredThousands.
		} else if (num >= 100000) {   
      list_num[5] = fmod(num, 10);
      list_num[4] = fmod(num/10, 10);
      list_num[3] = fmod(num/100, 10);
      list_num[2] = fmod(num/1000, 10);
      list_num[1] = fmod(num/10000, 10);
      list_num[0] = fmod(num/100000, 10);
      break;
      //tenThousands.
    } else if(num >= 10000) {
      list_num[5] = fmod(num, 10);
      list_num[4] = fmod(num/10, 10);
      list_num[3] = fmod(num/100, 10);
      list_num[2] = fmod(num/1000, 10);
      list_num[1] = fmod(num/10000, 10);
      list_num[0] = 10;
      break;
      //oneThousands.
    } else if(num >= 1000) {
      list_num[5] = fmod(num, 10);
      list_num[4] = fmod(num/10, 10);
      list_num[3] = fmod(num/100, 10);
      list_num[2] = fmod(num/1000, 10);
      list_num[1] = 10;
      list_num[0] = 10;
      break;
      //Hundreds.
    } else if(num >= 100) {
      list_num[5] = fmod(num, 10);
      list_num[4] = fmod(num/10, 10);
      list_num[3] = fmod(num/100, 10);
      list_num[2] = 0;
      list_num[1] = 10;
      list_num[0] = 10;
      break;
      //Tens.
    } else if(num >= 10) {
      list_num[5] = fmod(num, 10);
      list_num[4] = fmod(num/10, 10);
      list_num[3] = 0;
      list_num[2] = 0;
      list_num[1] = 10;
      list_num[0] = 10;
      break;
      //ones
    } else if(num >= 0) {
      list_num[5] = fmod(num, 10);
      list_num[4] = 0;
      list_num[3] = 0;
      list_num[2] = 0;
      list_num[1] = 10;
      list_num[0] = 10;
      break;
    } else if(num < 0) {
      list_num[5] = 0;
      list_num[4] = 0;
      list_num[3] = 0;
      list_num[2] = 0;
      list_num[1] = 10;
      list_num[0] = 10;
      break;
    }
  }
  return list_num;
}

/***************************************************************/
/* Display out put number in 1 row */

double LCD::printNorRow(double num) {
  static int *p_nor_row;
  p_nor_row = compareNum(num+0.5);
#ifdef __NO_USE_MANUAL_LATCH		
	digitalWrite(latchPin, LOW);
	digitalWrite(latchPin2, LOW);
#endif
   shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_nor_row)]);
   shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_nor_row+1)]);
   shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_nor_row+2)]);
   shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_nor_row+3)]);
   shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_nor_row+4)]);
   shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_nor_row+5)]);
#ifdef __USE_EXTRA_LCD_DISPLAY	 
   shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_nor_row)]);
   shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_nor_row+1)]);
   shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_nor_row+2)]);
   shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_nor_row+3)]);
   shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_nor_row+4)]);
   shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_nor_row+5)]);	 
#endif	 
  
#ifdef __NO_USE_MANUAL_LATCH		
	digitalWrite(latchPin, HIGH);
	digitalWrite(latchPin2, HIGH);
	delay(50);
#endif
  return num;
}

//Display output X.XXX if num > 1000.
double LCD::printDotRow(double num) {
  static int *p_dot_row;
  p_dot_row = compareNum(num);
  
#ifdef __NO_USE_MANUAL_LATCH		
	digitalWrite(latchPin, LOW);
	digitalWrite(latchPin2, LOW);
#endif
	if (num > 10000000) {
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row)]);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+1)]);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+2)] & dec_point_mask);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+3)]);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+4)]);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+5)] & dec_point_mask);
	}
	else if (num > 1000000) {
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row)]);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+1)] & dec_point_mask);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+2)]);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+3)]);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+4)] & dec_point_mask);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+5)]);
	} else {
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row)]);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+1)]);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+2)]);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+3)] & dec_point_mask);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+4)]);
		shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[*(p_dot_row+5)]);

	}
	
 #ifdef __USE_EXTRA_LCD_DISPLAY		 
	if (num > 10000000) {
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row)]);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+1)]);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+2)] & dec_point_mask);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+3)]);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+4)]);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+5)] & dec_point_mask);
	}
	else if (num > 1000000) {
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row)]);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+1)] & dec_point_mask);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+2)]);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+3)]);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+4)] & dec_point_mask);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+5)]);
	} else {
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row)]);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+1)]);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+2)]);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+3)] & dec_point_mask);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+4)]);
		shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[*(p_dot_row+5)]);

	}
#endif	 
  
#ifdef __NO_USE_MANUAL_LATCH		
	digitalWrite(latchPin, HIGH);
	digitalWrite(latchPin2, HIGH);
	delay(50);
#endif
  return num;
}


void LCD::startLatch() {
#ifndef __NO_USE_MANUAL_LATCH	
	 digitalWrite(latchPin, LOW);
#ifdef __USE_EXTRA_LCD_DISPLAY	 
	 digitalWrite(latchPin2, LOW);
#endif
#endif
}

void LCD::stopLatch() {
#ifndef __NO_USE_MANUAL_LATCH		
	 digitalWrite(latchPin, HIGH);
#ifdef __USE_EXTRA_LCD_DISPLAY		 
	 digitalWrite(latchPin2, HIGH);
#endif
#endif
}
/***************************************************************/
/* Display output value of rows */

double LCD::valuePrintRow1(double row2, double row3) {
  double row1;
  row1 = row3*row2;
  printDotRow(row1);
  return row1;
}

//Display output value row2.
double LCD::valuePrintRow2(double row1, double row3) {
  double row2;
  row2 = row1/row3;
  printDotRow(row2);
  return row2;
}
/****************************************************************/
/*  Display out put:     0 */

void LCD::printRowNull() {
#ifdef __NO_USE_MANUAL_LATCH		
	digitalWrite(latchPin, LOW);
	digitalWrite(latchPin2, LOW);
#endif
	shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[10]);
	shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[10]);
	shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[10]);
	shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[10]);
	shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[10]);
	shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[0]);	
#ifdef __USE_EXTRA_LCD_DISPLAY		
	shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[10]);
	shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[10]);
	shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[10]);
	shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[10]);
	shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[10]);
	shiftOut(dataPin2, clockPin2, MSBFIRST, dec_digits[0]);		
#endif	
#ifdef __NO_USE_MANUAL_LATCH		
	digitalWrite(latchPin, HIGH);
	digitalWrite(latchPin2, HIGH);
	delay(50);
#endif
}


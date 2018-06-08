#ifndef LCD_H
#define LCD_H

#include "Arduino.h"
// Define Ser, Latch, Clock;

// #define __NO_USE_MANUAL_LATCH
// #define __USE_EXTRA_LCD_DISPLAY

#define dataPin 37	
#define latchPin 36
#define clockPin 35

#define dataPin2 38	
#define latchPin2 40
#define clockPin2 39

class LCD {
  private:
    
    const byte dec_digits[11] = { 0b11000000, // 0
                                0b11110110, // 1
                                0b10101000, // 2
                                0b10100010, // 3
                                0b10010110, // 4
                                0b10000011, // 5
                                0b10000001, // 6
                                0b11100110, // 7
                                0b10000000, // 8
                                0b10000010, // 9
                                0b11111111  // rm led
    };

    const byte dec_point_mask = 0b01111111;
    
  public:
    double setRow(double num);
    double getRow();
 
    int *compareNum(double num);

    //2 type of Display output number: dot/null
		void startLatch();
		void stopLatch();
    double printNorRow(double num);
    double printDotRow(double num);
    // Display row1 while 
    double valuePrintRow1(double row2, double row3);
    double valuePrintRow2(double row1, double row3);
    void printRowNull();
    
};

#endif //LCD_H

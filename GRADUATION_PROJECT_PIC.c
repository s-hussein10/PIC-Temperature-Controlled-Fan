// Init LCD
// Lcd pinout settings
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D7 at RB3_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D4 at RB0_bit;

// Pin direction
sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB0_bit;

// init leds and motor pins
sbit Green_LED at    RD0_bit;
sbit Yellow_LED at   RD1_bit;
sbit Red_LED at      RD2_bit;
sbit Motor_Signal at RD3_bit;

sbit Green_LED_Direction at    TRISD0_bit;
sbit Yellow_LED_Direction at   TRISD1_bit;
sbit Red_LED_Direction at      TRISD2_bit;
sbit Motor_Signal_Direction at TRISD3_bit;


// init varibales used in program
unsigned int adc_value;
float voltage_mv;
int temperature_c;
char temp_text[7];

// THE main FUNC
void main() 
{
  CMCON = 0x07;
  // Init I/O peripheral
  TRISA = 0x01;
  PORTA = 0x00;

  TRISB = 0x00;
  PORTB = 0x00;

  TRISD = 0x00;
  PORTD = 0x00;
  
// init the output devics
  ADC_Init();
  Lcd_Init();

  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);

  Lcd_Out(1, 1, "Temp:");
  Lcd_Chr(1, 15, 223);
  Lcd_Chr(1, 16, 'C');

  while(1)
  {
  // read the value of LM35
    adc_value = ADC_Read(0);

    // convert value from sensor to TEMP
    voltage_mv = (adc_value * 5000.0) / 1023.0;
    temperature_c = (int)(voltage_mv / 10.0);

    // Write the TEMP value in LCD
    IntToStr(temperature_c, temp_text);
    Lcd_Out(1, 7, temp_text);
    Lcd_Out_Cp("  ");

    // controling in  LEDS and MOTOR
    if (temperature_c >= 35) 
    {
      Red_LED    = 1;
      Motor_Signal = 1;
      Yellow_LED = 0;
      Green_LED  = 0;
    }
    else if (temperature_c >= 30) 
    {
      Red_LED    = 0;
      Motor_Signal = 0;
      Yellow_LED = 1;
      Green_LED  = 0;
    }
    else if (temperature_c >= 25) 
    {
      Red_LED    = 0;
      Motor_Signal = 0;
      Yellow_LED = 0;
      Green_LED  = 1;
    }
    else 
    {
      Red_LED    = 0;
      Motor_Signal = 0;
      Yellow_LED = 0;
      Green_LED  = 0;
    }

    Delay_ms(500);
  }
}
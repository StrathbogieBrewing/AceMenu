#include "AceMenu.h"
#include "Terminal.h"

#define kTemperatureDelta 3

#define kEepromSetpoint ((uint16_t *)0)
#define kEepromHysteresis ((uint16_t *)2)



int temperature = 200;
int heater = 0;

// getter functions
int getTemperature() { return (temperature); }
int getHeater() { return heater; }
int getSetPoint() { return (int)eeprom_read_word(kEepromSetpoint); }
int getHysteresis() { return (int)eeprom_read_word(kEepromHysteresis); }

// setters functions, no setter for the temperature and heater read only
void setSetPoint(int v) { eeprom_write_word(kEepromSetpoint, (uint16_t)v); }
void setHysteresis(int v) { eeprom_write_word(kEepromHysteresis, (uint16_t)v); }

// menu contents
menuItem menuItems[] = {
    // name, getter, setter, format, min value , max value
    {"TEMP", getTemperature, NULL, Format::deci, 0, 0},
    {"SET", getSetPoint, setSetPoint, Format::deci, 100, 400},
    {"HYST", getHysteresis, setHysteresis, Format::deci, 5, 100},
    {"HEAT", getHeater, NULL, Format::boolean, 0, 1},
};
#define kMenuCount (sizeof(menuItems) / sizeof(menuItem))

Terminal terminal(Serial, 9600);

AceMenu menu = AceMenu(menuItems, kMenuCount, terminal, terminal);

static volatile unsigned char rtc_seconds;
static volatile unsigned int rtc_minutes;
static volatile unsigned char rtc_days;
// static volatile unsigned char stayAwakeTimer;

ISR(TIMER2_OVF_vect) {
  static unsigned long m = 0;

  unsigned int t = TCNT0;

  // unsigned long d =



  // if (stayAwakeTimer)
  //   stayAwakeTimer--;
  if (++rtc_seconds >= 60) {
    rtc_seconds = 0;
    if (rtc_minutes >= 1440) {
      rtc_minutes = 0;
      rtc_days++;
    }
  }
}


#define kSetTCCR2 ((1 << CS22) | (1 << CS20)) // overflow at 1 Hz
#define kStayAwakeSeconds (10)

void RTC_begin(void){
  rtc_seconds = 0;
  rtc_minutes = 0;
  rtc_days = 0;
  // stayAwakeTimer = kStayAwakeSeconds;

  ASSR |= (1 << AS2); // enable asynchronous clock
  TCNT2 = 0;          // reset counter / timer 2
  TCCR2 = kSetTCCR2;  // initialise prescaler for 1 Hz overflow
  while (ASSR & ((1 << TCN2UB) | (1 << OCR2UB) | (1 << TCR2UB))) ;

  TIMSK |= (1 << TOIE2); // Set 8-bit Timer/Counter2 Overflow Interrupt Enable
  sei();
}

void setup() {
  RTC_begin();
  // initialise the menu
  menu.begin();
}

void loop() {
  // update the menu
  menu.update();

  // update temperature control
  if (heater == true) {
    if (temperature > getSetPoint() + getHysteresis())
      heater = false;
  } else {
    if (temperature < getSetPoint() - getHysteresis())
      heater = true;
  }

  // for demo make the temperature value change every 500 ms
  static int temperatureDelta = kTemperatureDelta;
  static long unsigned int waitUntil = 0;
  if (millis() > waitUntil) {
    waitUntil = millis() + 500L;
    // ramp up and down
    temperature += temperatureDelta;
    if (temperature > 250)
      temperatureDelta = -kTemperatureDelta;
    if (temperature < 150)
      temperatureDelta = kTemperatureDelta;
  }
}

// void OSCCAL_calibration(void)
// {
//     unsigned char calibrate = FALSE;
//     int temp;
//     unsigned char tempL;
//
//     // CLKPR = (1<<CLKPCE);        // set Clock Prescaler Change Enable
//     // set prescaler = 8, Inter RC 8Mhz / 8 = 1Mhz
//     // CLKPR = (1<<CLKPS1) | (1<<CLKPS0);
//
//     // TIMSK2 = 0;             //disable OCIE2A and TOIE2
//
//     ASSR = (1<<AS2);        //select asynchronous operation of timer2 (32,768kHz)
//
//     // OCR2A = 200;            // set timer2 compare value
//
//     // TIMSK0 = 0;             // delete any interrupt sources
//
//     // TCCR1B = (1<<CS10);     // start timer1 with no prescaling
//     TCCR2A = (1<<CS20);     // start timer2 with no prescaling
//
//     while (ASSR & ((1 << TCN2UB) | (1 << OCR2UB) | (1 << TCR2UB)));
//
//     Delay(1000);    // wait for external crystal to stabilise
//
//     while(!calibrate)
//     {
//         __disable_interrupt();  // disable global interrupt
//
//         TIFR1 = 0xFF;   // delete TIFR1 flags
//         TIFR2 = 0xFF;   // delete TIFR2 flags
//
//         TCNT1H = 0;     // clear timer1 counter
//         TCNT1L = 0;
//         TCNT2 = 0;      // clear timer2 counter
//
//         while ( !(TIFR2 & (1<<OCF2A)) );   // wait for timer2 compareflag
//
//         TCCR1B = 0; // stop timer1
//
//         __enable_interrupt();  // enable global interrupt
//
//         if ( (TIFR1 & (1<<TOV1)) )
//         {
//             temp = 0xFFFF;      // if timer1 overflows, set the temp to 0xFFFF
//         }
//         else
//         {   // read out the timer1 counter value
//             tempL = TCNT1L;
//             temp = TCNT1H;
//             temp = (temp << 8);
//             temp += tempL;
//         }
//
//         if (temp > 6250)
//         {
//             OSCCAL--;   // the internRC oscillator runs to fast, decrease the OSCCAL
//         }
//         else if (temp < 6120)
//         {
//             OSCCAL++;   // the internRC oscillator runs to slow, increase the OSCCAL
//         }
//         else
//             calibrate = TRUE;   // the interRC is correct
//
//         TCCR1B = (1<<CS10); // start timer1
//     }
// }

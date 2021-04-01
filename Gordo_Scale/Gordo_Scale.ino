#include <LiquidCrystal.h>
#include <WheatstoneBridge.h>
#include <StrainGaugeShieldAndLCDSupportFunctions.h>

// custom lcd characters 
byte can[8] = {
  B00000,
  B00000,
  B10000,
  B01000,
  B00111,
  B00111,
  B00111, 
  B00111
};

byte can2[8] = {
  B00001,
  B00001,
  B10010,
  B01000,
  B00111,
  B00111,
  B00111,
  B00111
};

byte can3[8] = {
  B00000,
  B00100,
  B10010,
  B01000,
  B00111,
  B00111,
  B00111,
  B00111
};

byte gordi[8] = {
  B01010,
  B01110,
  B10101,
  B01110,
  B00100,
  B01110,
  B11111,
  B10101
};

// specifiy the numbers of the LCD interface pins to Arduino
const int pin_RS = 8;
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10; // arduino pin wired to LCD backlight circuit

// initialize lcd screen with the numbers of the interface pins
LiquidCrystal lcd(pin_RS, pin_EN, pin_d4, pin_d5, pin_d6, pin_d7);

// calibrating values
const int CST_STRAIN_IN_MIN = 350;     // raw value calibration lower point
const int CST_STRAIN_IN_MAX = 650;     // raw value calibration upper point
const int CST_STRAIN_OUT_MIN = 0;      // weight calibration lower point
const int CST_STRAIN_OUT_MAX = 1000;   // weight calibration upper point

// setting lower and upper bounds + step sizes for calculated force values
const int CST_CAL_FORCE_MIN = 0; 
const int CST_CAL_FORCE_MAX = 32000;
const int CST_CAL_FORCE_STEP = 50;
const int CST_CAL_FORCE_STEP_LARGE = 500;

// initialize wheatstone bridge interface objects
WheatstoneBridge wsb_strain1(A0, CST_STRAIN_IN_MIN, CST_STRAIN_IN_MAX, CST_STRAIN_OUT_MIN, CST_STRAIN_OUT_MAX);
WheatstoneBridge wsb_strain2(A1, CST_STRAIN_IN_MIN, CST_STRAIN_IN_MAX, CST_STRAIN_OUT_MIN, CST_STRAIN_OUT_MAX);


void check_buttons(int x){
  lcd.setCursor(0,1);
  if (x < 60) {
    lcd.print("Right button.   ");
  }
  else if (x < 200) {
    lcd.print("Up button.      ");
  }
  else if (x < 400) {
    lcd.print("Down button.    ");
  }
  else if (x < 600) {
    lcd.print("Left button.    ");
  }
  else if (x < 800){
    lcd.print("Select button.  ");
  }
  lcd. setCursor(15,1);
  lcd.write(random(1,4));
  lcd. setCursor(14,1);
  lcd.write(4);
  delay(150);  

  return 0;

}

void scroll_display(int text_len){
  
  // scroll 16 positions (len(text)) to the left
  for (int posCounter=0; posCounter < text_len; posCounter++){
    lcd.scrollDisplayLeft();
    delay(200); // scrolling speed
  }

  // scroll a positions (len(text + len(display)) to the right
  for(int posCounter=0; posCounter<text_len+16; posCounter++){
    lcd.scrollDisplayRight();
    delay(200);
  }

  // scroll 16 positions (len(display)) to the left
  for(int posCounter=0; posCounter<16; posCounter++){
    lcd.scrollDisplayLeft();
    delay(50);
  }
}

long force_to_weigt(int force){
  return force * 0.101971621298;
}

void setup() {
  // initialize serial communication 
  Serial.begin(9600);

  // initialize lcd screen + custom characters
  lcd.begin(16,2);
  lcd.createChar(1, can);
  lcd.createChar(2, can2);
  lcd.createChar(3, can3);
  lcd.createChar(4,gordi);


  // intro screens
  Serial.println("< Gordis Waage online, beep beep. >");
  Serial.println("");

  displayScreen("Gordis Waage, is", "online. BEEPBEEP");

  //up/down screen 
  displayScreen("Press up/dn/l/r", "to change values");
  Serial.println("Press up/down/left/right to change values");
  delay(2500);

  // select screen
  displayScreen("Press select to", "complete a step");
  Serial.println("Press select to complete a step");
  delay(2500);

  // calibration - linear interpolation
  int cal_adc_low = CST_STRAIN_IN_MIN; 
  int cal_adc_high = CST_STRAIN_IN_MAX;
  int cal_force_low = CST_STRAIN_OUT_MIN; 
  int cal_force_high = CST_STRAIN_OUT_MAX;  

  
  // calibration - low value
  displayScreen("* Calibration *", "low value");
  Serial.println("* Calibration * - low value");
  delay(2500);
  // get force value
  cal_force_low = getValueInRange("Set low force", "Force:", 7, cal_force_low, CST_CAL_FORCE_MIN, CST_CAL_FORCE_MAX, CST_CAL_FORCE_STEP, CST_CAL_FORCE_STEP_LARGE);
  // get ADC raw value
  cal_adc_low = getValueADC("Set low raw ADC", "Raw ADC:", 9, A0, btnSELECT);

  
  // calibration - high value
  displayScreen("* Calibration *", "high value");
  Serial.println("* Calibration * - high value");
  delay(2500);
  // get force value
  cal_force_high = getValueInRange("Set high force", "Force:", 7, cal_force_high, CST_CAL_FORCE_MIN, CST_CAL_FORCE_MAX, CST_CAL_FORCE_STEP, CST_CAL_FORCE_STEP_LARGE);
  // get ADC raw value
  cal_adc_high = getValueADC("Set high raw ADC", "Raw ADC:", 9, A0, btnSELECT);


  // perform calibration
  Serial.println("Wheatstone bridge calibration:");
  Serial.print(">> iMin = "); Serial.println(cal_adc_low);
  Serial.print(">> iMax = "); Serial.println(cal_adc_high);
  Serial.print(">> oMin = "); Serial.println(cal_force_low);
  Serial.print(">> oMax = "); Serial.println(cal_force_high);
  wsb_strain1.linearCalibration(cal_adc_low, cal_adc_high, cal_force_low, cal_force_high);

  // setup display labels
  displayScreen("[A0]:", "Force:"); 
}

// time management
long display_time_step = 1000;
long display_time = 0;

// force measurement & display
int strain1_adc;
int strain1_force;
int force_pos_offset;

void loop() {
  // check if it is time for a new measurement / to update the display
  if(millis() > (display_time_step + display_time)){
    // make force measurement and obtain calibrated force value
    strain1_force = wsb_strain1.measureForce();

    // obtain the raw ADC value from the last measurement
    strain1_adc = wsb_strain1.getLastForceRawADC();

    // compute force position offset (right-aligned text)
    force_pos_offset = (4 - countDigits(strain1_force));
    if(strain1_force <= 0){
      force_pos_offset -= 1;
    }

    // display raw ADC value
    lcd.setCursor(12,0); lcd.print("       ");
    lcd.setCursor(12,0); lcd.print(strain1_adc);
    Serial.print("A[0], raw ADC: ");
    Serial.println(strain1_adc, DEC);

    // display force value
    lcd.setCursor(11,1); lcd.print("     ");
    lcd.setCursor((11+force_pos_offset),1); lcd.print(strain1_force);
    Serial.print("A[0], force: ");
    Serial.println(strain1_force, DEC);

    // print empty line & reset timer
    Serial.println("");
    display_time = millis();
  }
}

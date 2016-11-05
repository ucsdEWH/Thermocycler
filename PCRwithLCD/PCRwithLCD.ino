/******
Author:      Noah Meurs
Start Date:  11/08/14
Project:     PCR Thermocycler Controller
Club:        Engineering World Health

Last Updated: 07/20/16
*******/


/****************************************BEGIN LIBRARIES*************************************************/

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <PID.h> //stores PID libraries and functions
#include "PCR_Thermocycler.h" //Our Header File

/****************************************END LIBRARIES**************************************************/

/*****************************************BEGIN DEFINE STATEMENTS*************************************/

/*******PIN ASSIGNMENT FOR PCB*******/

#define THERMISTOR_PIN A1   //Thermistor Pin on Arduino code

#define THERMISTOR_PIN_2 A2 //Not in use currently

#define OUT_PWM_1 10  //pwm for motor driver 1
#define ENABLE_1 9    //turn on motor 1
#define DIR_1 8       //set heat or cool for motor 1
#define CS_1 A0       //Current sense for motor 1

#define OUT_PWM_2 5   //pwm for motor driver 2
#define ENABLE_2 6    //turn on motor 2
#define DIR_2 7       //set heat or cool for motor 2
#define CS_2 A1       //Current sense for motor 2

#define EN_PIN  4
#define RW_PIN  5
#define RS_PIN  6
#define D4_PIN  0
#define D5_PIN  1
#define D6_PIN  2
#define D7_PIN  3

/*********LED ASSIGNMENT VALUES**********/
#define  LED_OFF  0
#define  LED_ON  1

/*********TEMPERATURES FOR EACH STEP********/

#define TEMPERATURE_STEP_1 95 //first step at 95C of 30 seconds
#define TEMPERATURE_STEP_2 50 //second step at 50C of 30 seconds
#define TEMPERATURE_STEP_3 72 //third step at 72C of 1 minute and hold for 10 minutes at end
#define TEMPERATURE_STEP_4 4  //final temperature at 4C to hold


/*********TIME DELAYS FOR EACH TEMPERATURE***********/

#define DELAY_FOR_TEMPERATURE_1 30000 //length of time at temperature 1 (30 seconds)
#define DELAY_FOR_TEMPERATURE_2 30000 //length of time at temperature 2 (30 seconds)
#define DELAY_FOR_TEMPERATURE_3 60000 //length of time at temperature 3 (60 seconds)
#define DELAY_FOR_TEMPERATURE_4 1000  //length of time at temperature 4 (placeholder only, holds indefinitely)

#define THERMISTOR_A 1.14307881
#define THERMISTOR_B 2.31852171
#define THERMISTOR_C 0.9649561035

/*********PID VALUES***********/

#define P95 100  //13
#define I95 0  //.1
#define D95 10  //0
#define A95 1500   //1500
#define P50 100  //10
#define I50 0  //.01
#define D50 10  //0
#define A50 11000   //11000
#define P72 100  //13
#define I72 0  //.1
#define D72 10  //0
#define A72 1000  //1000





#define TEMPERATURE_TOLERANCE 2

#define NUMBER_OF_CYCLES 105          // One cycle per temperature, so 3*number of cycles

#define DELAY_BETWEEN_READINGS 1000   //Delay between readings in milliseconds

#define I2C_ADDR    0x38              // Define I2C Address for LCD

#define BACKLIGHT_PIN  7

#define FAN_ON 3

#define MOTOR_DRIVER_RESISTANCE 0.16  //The internal current sense resistor for the Pololu motor driver is 0.16 Ohm

#define ONBOARD_RESISTANCE 9950       //Value of the onboard resistor

#define MAX_OUTPUT_VOLTAGE 255


/***********************************END DEFINE STATEMENTS********************************/



// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C  lcd(I2C_ADDR, EN_PIN, RW_PIN, RS_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);


/********PID ALGORITHM*********/

//NM: First array cell is the temp setpoint
PID_params par = {80, 0, 0, 0, 0, 0, 12.5, 0.1, 0, 1200};


/****
  struct PID_params {par->integral =
  double set; par->set
  double input;
  double output;
  double accumulated;
  double previous;
  double error;

  double proportional; (6)
  double integral;
  double derivative;

  double accLimit;
  *****/




//enables PID functions
PID pid = PID( & par);



/******NOTE: Commented Values Indicate What Gillie and Noah have calibrated so far********/


/**
 * Calls on PID Controller to Regulate current to thermocycler heating system.
 * @param   int tempGoal    Final temperature for the heating system to reach.
 * @param   int isHolding     Flag indicates whether temperature is currently holding
 */
void changeCurrent(int tempGoal, int isHolding) {
  double temp = Thermistor(analogRead(THERMISTOR_PIN));
  double ThermistorReading = analogRead(THERMISTOR_PIN);

  //Displays temperature on LCD
  showTemp(temp);

  //Inputs temp as current reading for PID
  pid.setInput(temp);

  //Calls PID Calculation
  pid.process(millis());

  //Records output of PID to set output voltage (1-5V on a scale of 0-255)
  long v_out = pid.getOutput();

  chooseHeatOrCool(v_out);

//Maxes output voltage at 255
  v_out = min(abs(v_out), MAX_OUTPUT_VOLTAGE);

//Sets output of Arduino to PID output
  analogWrite(OUT_PWM_1, v_out);

//Read the current sense data from motor 1
  double current_1_vsense = (5.0 / 1024.0) * analogRead(CS_1);


//Converts current_1_vsense to actual voltage value.
  double current_1 = current_1_vsense / MOTOR_DRIVER_RESISTANCE;


  printValues(temp, v_out, tempGoal, isHolding);
}


/**
 * Determines whether to heat or cool solution based on output voltage.
 * If
 * @param   long  v_out           The output voltage
 */
void chooseHeatOrCool(long v_out) {
  if (v_out < 0)
    cool();
  else
    heat();
}

/**
 * Attempts to reach desired temperature
 * @param   int     tempGoal    Final temperature to reach
 * @param   long  delayHold    Length of time to remain at final temperature
 */
void reachTemp(int tempGoal, long delayHold) {
  boolean isHeating;
  int currentTemp;

  pid.setSetPoint(tempGoal); //sets the final temperature goal for the PID

  currentTemp = Thermistor(analogRead(THERMISTOR_PIN)); //reads temperature

  isHeating = currentTemp < tempGoal; //isHeating is a 0 if cooling, 1 if heating

  while ((currentTemp < tempGoal - TEMPERATURE_TOLERANCE && isHeating == true) || (currentTemp > tempGoal + TEMPERATURE_TOLERANCE && isHeating == false)) {
    changeCurrent(tempGoal, 0); //Changes PWM current delivery based on PID
    currentTemp = Thermistor(analogRead(THERMISTOR_PIN));

    //Clears PID on the first time heating up
    static boolean isFirstHeating = true;

    if (isFirstHeating == true && tempGoal - currentTemp < 23) {
      pid.clearPID();
      isFirstHeating = 0;
    }

  }

  unsigned long desiredTime = millis() + delayHold;

//keep temperature at temp goal until delay is reached
  while (millis() < desiredTime) {
    changeCurrent(tempGoal, 1);
  }
  //Temperature Reached
}

/**
 * Converts Thermistor values to temperature reading
 * @param double RawADC Raw ADC value from thermistor
 */
float Thermistor(double RawADC) {
//Temp on 5/21/16 from Thermistor Datasheet plugged in to thermistor website linked on drive
  double A = THERMISTOR_A * pow(10, -3);
  double B = THERMISTOR_B * pow(10, -4);
  double C =  THERMISTOR_C * pow(10, -7);

  double voltage = convertADCToVoltage(RawADC);
  long double logResist = log(voltage * ONBOARD_RESISTANCE / (5 - voltage));
  double Temp = 1 / (A + B * logResist + C * pow(logResist, 3)) - 273.15;
  return Temp;
}

/**
 * Converts Raw ADC value to thermistor voltage
 * @param   double    RawADC                   The Raw ADC value
 * @return   double    thermistorVoltage    The voltage across the thermistor
 */
double convertADCToVoltage(double RawADC) {
  double resistorVoltage = RawADC * 5.0 / 1024.0; //Voltage Across Resistor
  double thermistorVoltage = 5 - resistorVoltage; //Voltage Across Thermistor

  return thermistorVoltage;
}


/**
 * Heats the thermocycler
 */
void heat() {
  digitalWrite(DIR_1, LOW);
  digitalWrite(FAN_ON, LOW);
  lcd.setCursor (15, 1); //sets cursor to top right corner
  lcd.write (byte(0)); //prints up arrow
}
/**
 * Cools the thermocycler
 */
void cool() {
  digitalWrite (DIR_1, HIGH);
  digitalWrite(FAN_ON, HIGH);
  lcd.setCursor (15, 1); //sets cursor to top right corner
  lcd.write (byte(1)); //prints down arrow
}

void setPIDValues(double P, double I, double D, double A) {
  pid.setProportional(P);
  pid.setIntegral(I);
  pid.setDerivative(D);
  pid.setAccLimit(A);
}

/**
 * Runs the three-step PCR process for an inputted number of cycles
 * @param     cycleNum    The total number of cycles.
 */
void runCycles() {
  static int cycleNum = 0;

  //Displays the current cycle being run.
  showCycle(cycleNum);

  if (cycleNum < NUMBER_OF_CYCLES) {

    //STEP 1
    setPIDValues(P95, I95, D95, A95);

    showGoal(TEMPERATURE_STEP_1);//On LCD

    reachTemp(TEMPERATURE_STEP_1, DELAY_FOR_TEMPERATURE_1);

    cycleNum++;

    showCycle(cycleNum); //for debugging purposes

    pid.clearPID();  //clear out accumulated error, error, input and previous


    //STEP 2
    setPIDValues(P50, I50, D50, A50);

    showGoal(TEMPERATURE_STEP_2);//On LCD

    reachTemp(TEMPERATURE_STEP_2, DELAY_FOR_TEMPERATURE_2);

    cycleNum++;

    showCycle(cycleNum);

    pid.clearPID();

    //STEP 3
    setPIDValues(P72, I72, D72, A72);

    showGoal(TEMPERATURE_STEP_3);//On LCD

    reachTemp(TEMPERATURE_STEP_3, DELAY_FOR_TEMPERATURE_3);

    cycleNum++;

    showCycle(cycleNum);

    pid.clearPID();
  }

  //HOLDING TEMPERATURE STAGE
  if (cycleNum == NUMBER_OF_CYCLES) {
    showGoal(TEMPERATURE_STEP_4);//On LCD

    reachTemp(TEMPERATURE_STEP_4, DELAY_FOR_TEMPERATURE_4);
  }
}


/**
 * Initializes the pins of the board.
 */
void initializePins() {
  pinMode(ENABLE_2, OUTPUT);
  pinMode(OUT_PWM_2, OUTPUT);
  pinMode(DIR_2, OUTPUT);

  digitalWrite(ENABLE_2, HIGH); //Turn on heated lid
  digitalWrite(OUT_PWM_2, HIGH); //Max power to heated lid
  digitalWrite(DIR_2, LOW); //Heated lid powered forward (probably doesn't matter)

  pinMode(ENABLE_1, OUTPUT);
  pinMode(OUT_PWM_1, OUTPUT);
  pinMode(DIR_1, OUTPUT);

  digitalWrite(ENABLE_1, HIGH); //Turn on Peltier heater

  pinMode(FAN_ON, OUTPUT);
}

/**
 * Prints values from device to either the Serial Monitor or the PLX-DAQ
 * @param temp            current temperature
 * @param v_out           current output voltage
 * @param tempGoal     desired final temperature
 * @param isHolding     boolean for holding stage.
 */
void printValues(double temp, long v_out, int tempGoal, int isHolding) {
  static unsigned long long lastprint = 0; //Only initializes the first time; keeps track of time

  const static boolean canPrintToPLXDAQ = false; //0 for readable printing, 1 for PLX-DAQ

  if ((millis() - lastprint) > DELAY_BETWEEN_READINGS) {
    lastprint = millis();
    if (canPrintToPLXDAQ == false)
      printToSerial(temp, v_out);
    else if (canPrintToPLXDAQ == true)
      printToPLXDAQ(temp, v_out, pid.getOutput(), tempGoal, isHolding, par.proportional);
  }
}

/**
 * Initializes pins on PCB and print data
 */
void setup() {
  initializeSerial();
  initializeLCD();
  initializePins();
}

/**
 * Runs PCR system using PID controller.
 */
void loop() {
  runCycles();
}




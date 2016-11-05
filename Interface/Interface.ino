#include <LiquidCrystal.h>


#define KNOB_PIN -1
#define BUTTON_PIN -2
#define DIGITAL_PIN2 -3
#define BUFFER_MAX 50

//global variables
int numberOfStages;
int temperatures[BUFFER_MAX];
int times[BUFFER_MAX];
int currentKnobValue;

//function declaration
boolean checkIfUsingPreviousRoutine();
void setStandardValues();
void waitForDepress();
void chooseNumberOfStages();
void setTemperatures(int);
void setTimes(int);
void displayVariablesOnArduinoMonitor();

//Initialize LCD
LiquidCrystal lcd(1,2,3,4,5,6);

void setup() {
  lcd.begin(16,2);
}

void loop() {

  boolean useStandard = checkIfUsingStandardRoutine();

  waitForDepress();

  if (useStandard)
  {
    setStandardValues();
  }

  else
  {
    chooseNumberOfStages();

    for (int i = 0; i < numberOfStages; i++)
    {
      waitForDepress();

      setTemperature(i);

      waitForDepress();

      setTime(i);
    }
  }

  displayVariablesOnArduinoMonitor();
}

/*
 * Waits until button is no longer pressed before
 * moving on to the next step of the program.
 */
void waitForDepress()
{
  while (digitalRead(BUTTON_PIN)) {}

  return;
}

/**
 * Checks to see if the standard routine should be
 * used for the current run.
 *
 * @return true if the standard routine should be used
 *         false if a new routine should be used instead
 */
boolean checkIfUsingStandardRoutine()
{
  boolean useStandard = true;
  char firstPrompt[] = "Standard routine or new routine?";
  while (!digitalRead(BUTTON_PIN))
  {
    lcd.clear();
    lcd.print(firstPrompt);
    currentKnobValue = analogRead(KNOB_PIN);
    useStandard = (currentKnobValue > 0) ? true : false;
    if(useStandard)
      lcd.print("Yes");
    else
      lcd.print("No");
  }

  return useStandard;
}

/**
 * Allows the user to choose the number of stages to run.
 * Number is chosen by using the knob. Button is pressed
 * to confirm selection
 */
void chooseNumberOfStages()
{
  char secondPrompt[] = "How many stages per cycle?";
  while (!digitalRead(BUTTON_PIN))
  {
    lcd.clear();
    lcd.print(secondPrompt);
    numberOfStages = analogRead(KNOB_PIN);
    lcd.print(numberOfStages);
  }
}

/**
 * Allows the user to set the temperature for the
 * inputted stage. Temperature is chosen by using the
 * knob. Button is pressed to confirm selection.
 */
void setTemperature(int stageNumber)
{
  char temperaturePrompt[32];
  sprintf(temperaturePrompt, "Temperature for Stage %d: ", stageNumber);

  while (!digitalRead(BUTTON_PIN))
  {
    lcd.clear();
    lcd.print(temperaturePrompt);
    currentKnobValue = analogRead(KNOB_PIN);
    lcd.print(currentKnobValue);
  }

  temperatures[stageNumber] = currentKnobValue;
}

/**
 * Allows the user to set the time length for the
 * inputted stage. Time length is chosen by using the
 * knob. Button is pressed to confirm selection.
 */
void setTime(int stageNumber)
{
  char timePrompt[32];
  sprintf(timePrompt, "What time for Stage %d: ", stageNumber);

  while (!digitalRead(BUTTON_PIN))
  {
    lcd.clear();
    lcd.print(timePrompt);
    currentKnobValue = analogRead(KNOB_PIN);
    lcd.print(currentKnobValue);
  }

  times[stageNumber] = currentKnobValue;
}

/**
 * Displays the number of stages, temperatures, and times
 * in the Arduino Monitor.
 */
void displayVariablesOnArduinoMonitor()
{

  Serial.println("Number of Stages: " + numberOfStages);
  Serial.println("Temperatures: ");
  for (int i = 0; i < sizeof(temperatures); i++)
    Serial.print(temperatures[i]);
  Serial.println("Times");
  for (int j = 0; j < sizeof(times); j++)
    Serial.print(times[j]);
}

void setStandardValues()
{
  numberOfStages = 3;
  temperatures[0] = 94;
  temperatures[1] = 54;
  temperatures[2] = 70;

  times[0] = 20;
  times[1] = 40;
  times[2] = 15;
}


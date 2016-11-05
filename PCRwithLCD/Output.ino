/**
 * Prints information for the PLX-DAQ in the serial monitor of the Arduino IDE
 * @param  double       temperature        current temperature of the device
 * @param  int          currentSpeed       speed at which the device is operating at.
 * @param  int          pid                value of PID output from algorithm
 * @param  int          tempgoal           final temperature that the device will attempt to reach
 * @param  int          holding            flag that indicates whether temperature is holding or changing
 * @param  double       proportional       proportional value used for the PID controller
 */
void printToPLXDAQ(double temperature, int currentSpeed, int pid, int tempgoal, int holding, double proportional) {
    static long startTime = millis();
    Serial.print("DATA,TIME,");
    Serial.print(temperature); Serial.print(",");
    Serial.print(currentSpeed); Serial.print(",");
    Serial.print(pid); Serial.print(",");
    Serial.print(tempgoal); Serial.print(",");
    Serial.print(holding); Serial.print(",");
    Serial.println(proportional);
}

/**
* Prints temperature and voltage values to the serial monitor
* @param     double    temp    the temperature
* @param     long        v_out   the output voltage
*/
void printToSerial(double temp, long v_out)
{
    double printVars[] = {temp, (double)v_out, pid.getOutput()};
    int numEls = sizeof(printVars) / sizeof(*printVars);
    for (int i = 1; i <= numEls; i++)
        Serial.print(printVars[i]); Serial.print("       ");
}

/**
 * Initalizes the serial monitor on the Arduino IDE
 */
void initializeSerial() {
    Serial.begin (9600);
}

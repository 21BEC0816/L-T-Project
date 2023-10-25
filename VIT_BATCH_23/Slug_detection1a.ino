

// Define the pins                  //NAME:- AYUSH SINHA ayush.sinha2021@vitstudent.ac.in
const int TRIGGER_PIN = 12;
const int ECHO_PIN = 13;
const int LED_PIN = 9;
const int LED_PIN2=7;
const int LED_PIN3=6;
const int BUZZER_PIN = 8;
const int PUMP_PIN=4;

// Define the distance threshold
const float DISTANCE_THRESHOLD = 10.0; // cm

void setup() {
  // Set the pins as outputs
  pinMode(LED_PIN, OUTPUT); //Led pins are selected as Outputs
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); //Echo Pin and //Trigger Pin is selected as Inputs.
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);	
  // Initialize the serial port
  Serial.begin(9600); //Selecting Baud Rate
}

void loop() {
  // Measure the distance to the sludge level
  float distance = measureDistance(); //Calling function is used.

  // Check if the distance is less than the threshold
  if (distance < DISTANCE_THRESHOLD) {
/*
    if the distance is less than the threshold distance 
    then RedLight gets on and buzzer gets on and then
    Water Pump will flush out the Water.

*/
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN2, LOW);
    digitalWrite(LED_PIN3, LOW);
    digitalWrite(PUMP_PIN, HIGH);
    Serial.println("The Water level is Under 10cm: ");
    Serial.println(distance);
  } else if(distance < 20) {

/*
    if the distance is b/w 10cm and 20cm then green light gets on
    and tell that Water tank is almost getting filled up.

*/

    digitalWrite(LED_PIN, LOW);
  	digitalWrite(LED_PIN2, HIGH);
    digitalWrite(LED_PIN3, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(PUMP_PIN, LOW);
    Serial.println("The Water level is b/w 10cm and 20cm: ");
    Serial.println(distance);
  } else {
/*
    The distance is more than the 20cm which indicates that Water
    tank is not filled.

*/
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN2, LOW);
    digitalWrite(LED_PIN3,HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(PUMP_PIN, LOW);
    Serial.println("The Water level is above 20cm: ");
    Serial.println(distance);
    // Stop the water pump
  }

  // Delay for 1 second
  delay(1000);
}
/*
  The Distance calculation in centimeters is based on the time
  it takes for the ultrasonic sensor wave to travel from the sensor to the object
  and back. The Speed of the sound in air approximately 343m/s or 0.0343cm/us.
  Therefore, the distance = (duration * 0.0343)/2

*/
float measureDistance() {
  // Send a pulse on the trigger pin
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure the time it takes for the pulse to return
  long pulseDuration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance
  float distance = pulseDuration * 0.034 / 2.0; // cm

  return distance;
}
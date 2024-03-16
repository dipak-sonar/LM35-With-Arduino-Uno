#include <TaskScheduler.h>

Scheduler scheduler;

const int sensorPin = A0; // LM35 connected to A0
const int ledPin = 13; // Onboard LED
float temperature;
bool ledState = false;

// Task to blink the LED
Task ledTask(250, TASK_FOREVER, [](){
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
});

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  // Attach the LED task to the scheduler
  scheduler.addTask(ledTask);
}

void loop() {
  int reading = analogRead(sensorPin);
  temperature = reading * 5.0 * 100.0 / 1024.0; // Convert reading to temperature

  // Determine the interval for LED blinking based on temperature
  if (temperature < 30) {
    ledTask.setInterval(250); // Blink every 250 milliseconds
  } else {
    ledTask.setInterval(500); // Blink every 500 milliseconds
  }

  // Run the scheduler
  scheduler.execute();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
}
#define BOUNCE 2
#define OFF 3

void setup() {
  Serial.begin(9600);
  pinMode(BOUNCE, OUTPUT);
  pinMode(OFF, OUTPUT);
  digitalWrite(BOUNCE, HIGH);
  // Wait 3 seconds
  delay(3000);
  // Keeps relay on
  digitalWrite(OFF, LOW);
}

void loop() {
  // Wait for Raspberry Pi to boot
  delay(30000);  // Increased initial delay to 40 seconds
  
  // Counter to track elapsed time
  unsigned long lastCheckTime = millis();
  
  while (true) {
    // Check for incoming serial data
    if (Serial.available() > 0) {
      delay(1000);
      // Stop BOUNCE if there is serial data
      digitalWrite(BOUNCE, HIGH);
      // Read the serial data
      char data = Serial.read();
      // Process the serial data if needed
      // Add your code here if you want to do something with the received data
    } else {
      // Check if it's time to check for serial data again
      if (millis() - lastCheckTime >= 30000) {
        // Update last check time
        lastCheckTime = millis();
        
        // Execute BOUNCE part if there is no serial data
        digitalWrite(BOUNCE, LOW);
        delay(200);
        digitalWrite(BOUNCE, HIGH);
        delay(1000);
      }
    }
    
    // Execute OFF part always
    digitalWrite(OFF, LOW);
    delay(1000); // Add a delay to prevent busy-waiting
  }
}
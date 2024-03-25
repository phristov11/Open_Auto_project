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
  while (true) {
    delay(30000);
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
      delay(35000);
      // Execute BOUNCE part if there is no serial data
      digitalWrite(BOUNCE, LOW);
      delay(200);
      digitalWrite(BOUNCE, HIGH);
      delay(1000);
    }
    
    
    // Execute OFF part always
    digitalWrite(OFF, LOW);
    delay(1000); // Add a delay to prevent busy-waiting
  }
}

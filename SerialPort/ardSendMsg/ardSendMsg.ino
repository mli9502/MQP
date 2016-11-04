void setup() {
    Serial.begin(9600);
}

void loop() {
    int bytesSent = Serial.write("Hello ");
    unsigned long time = millis();
    String timeStr = String(time);
    writeString(timeStr);
    Serial.write("\n");
    delay(1000);
}
void writeString(String stringData) { // Used to serially push out a String with Serial.write()
  for (int i = 0; i < stringData.length(); i++)
  {
      Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }
}// end writeString

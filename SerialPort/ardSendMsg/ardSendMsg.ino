void setup() {
    Serial.begin(9600);
}

void loop() {
    int bytesSent = Serial.write("Hello ");
    int time = millis();
    String timeStr = String(time);
    int arrLen = timeStr.length();
    char timeArr[arrLen];
    timeStr.toCharArray(timeArr, arrLen);
    Serial.write(timeArr);
    Serial.write("\n");
    delay(1000);
}


void setup() {
  Serial.begin(115200);
  logfile_setup();
  delay(1000);
  names_setup_log();
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
  
  client.setInsecure();
  //client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}

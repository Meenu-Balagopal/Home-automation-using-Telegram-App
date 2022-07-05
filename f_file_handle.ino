#define FORMAT_SPIFFS_IF_FAILED true

/*---------------------------------------------------- LOG FILE SETUP ------------------*/
void logfile_setup() {
  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  listDir(SPIFFS, "/", 0);
  Serial.println( "Test complete" );
}

/*---------------------------------------------------- LIST DIRECTORY ------------------*/
void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("\tSIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}


/*---------------------------------------------------- WRITE ------------------*/
void writeFileStr(fs::FS &fs, String path, String text) {
  Serial.println("Rewrite to file: " + path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("- failed to open file for rewriting");
    return;
  }
  if (file.print(text)) {
    Serial.print(text);
  } else {
    Serial.println("- write failed");
  }

  Serial.println("");
  Serial.print("File size: ");
  Serial.println(file.size());

  file.close();
}

/*---------------------------------------------------- READ LIST ------------------*/
String readFile(fs::FS &fs, String path) {
  Serial.println("Reading file: " + path);
  File file = fs.open(path);

  //no file exists,no file delete required
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return "";
  }

  Serial.print("File size: ");
  Serial.println(file.size());
  String debugLogData ;
  Serial.println("- read from file:");
  String received = "";
  char ch;
  while (file.available()) {
    ch = file.read();
    if (ch == '\n') {
      Serial.println(String(received));
    } else {
      received += ch;
    }
    delay(10);
  }
  file.close();
  return received;
}

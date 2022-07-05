
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
 
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
const int ledPin = 2;
bool ledState = LOW;

String pin_state(int pin_no);
void handleNewMessages(int numNewMessages);
void send_welcome_msge();
void send_configure_msge(String chat_id);
void control_device(int pin, int state);
void names_setup_log();

/********** File handling**********/
String Device_one_file = "/one.txt";
String Device_two_file = "/two.txt";
String Device_three_file = "/three.txt";
String Device_four_file = "/four.txt";

void logfile_setup();
void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
void writeFileStr(fs::FS &fs, String path, String text);
String readFile(fs::FS &fs, String path);

/***** configurations *****/

String device_one_name = "Device 1";
String device_two_name = "Device 2";
String device_three_name = "Device 3";
String device_four_name = "Device 4";

int device_one_pin = 2;
int device_two_pin = 4;
int device_three_pin = 18;
int device_four_pin = 19;

int flag_device_1 = 0;
int flag_device_2 = 0;
int flag_device_3 = 0;
int flag_device_4 = 0;

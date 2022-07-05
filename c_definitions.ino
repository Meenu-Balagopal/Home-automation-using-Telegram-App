
String pin_state(int pin_no) {
  int pin_state = digitalRead(pin_no);
  if (pin_state == 1) {
    return "ON";
  } else {
    return "OFF";
  }
}

void names_setup_log() {
  String names = "";
  names = readFile(SPIFFS, Device_one_file);
  if (names != "") {
    device_one_name = names;
    Serial.println(device_one_name);
  }

  names = readFile(SPIFFS, Device_two_file);
  if (names != "") {
    device_two_name = names;
    Serial.println(device_two_name);
  }

  names = readFile(SPIFFS, Device_three_file);
  if (names != "") {
    device_three_name = names;
    Serial.println(device_three_name);
  }

  names = readFile(SPIFFS, Device_four_file);
  if (names != "") {
    device_four_name = names;
    Serial.println(device_four_name);
  }

}

void change_device_name(int device_id, String text) {
  if (device_id == 1) {
    device_one_name = text;
    writeFileStr(SPIFFS, Device_one_file, device_one_name);
    flag_device_1 = 0;
  }
  if (device_id == 2) {
    device_two_name = text;
    writeFileStr(SPIFFS, Device_two_file, device_two_name);
    flag_device_2 = 0;
  }
  if (device_id == 3) {
    device_three_name = text;
    writeFileStr(SPIFFS, Device_three_file, device_three_name);
    flag_device_3 = 0;
  }
  if (device_id == 4) {
    device_four_name = text;
    writeFileStr(SPIFFS, Device_four_file, device_four_name);
    flag_device_4 = 0;
  }
}


void control_device(int pin, int state) {
  digitalWrite(pin, state);
}

void send_welcome_msge(String chat_id) {
  String welcome = "Hi user,\nWelcome to Home Automation System.\n\n";
  welcome += device_one_name;
  welcome += " - (PIN - 2)\n";
  welcome += "Current status - ";
  welcome += pin_state(2);
  welcome += "\n";
  welcome += "/Turn_ON_1  /Turn_OFF_1\n\n";

  welcome += device_two_name;
  welcome += " - (PIN - 4)\n";
  welcome += "Current status - ";
  welcome += pin_state(4);
  welcome += "\n";
  welcome += "/Turn_ON_2  /Turn_OFF_2\n\n";

  welcome += device_three_name;
  welcome += " - (PIN - 18)\n";
  welcome += "Current status - ";
  welcome += pin_state(18);
  welcome += "\n";
  welcome += "/Turn_ON_3  /Turn_OFF_3\n\n";

  welcome += device_four_name;
  welcome += " - (PIN - 19)\n";
  welcome += "Current status - ";
  welcome += pin_state(19);
  welcome += "\n";
  welcome += "/Turn_ON_4  /Turn_OFF_4\n";

  bot.sendMessage(chat_id, welcome, "");
}


void send_configure_msge(String chat_id) {
  String msge = "";
  msge += "Configure devices.\n\n";
  msge += device_one_name;
  msge += "\n/set_new_name_1 \n\n";
  msge += device_two_name;
  msge += "\n/set_new_name_2 \n\n";
  msge += device_three_name;
  msge += "\n/set_new_name_3 \n\n";
  msge += device_four_name;
  msge += "\n/set_new_name_4 \n\n";

  bot.sendMessage(chat_id, msge, "");
}


void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);
    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      send_welcome_msge(chat_id);
    } else if (text == "/Turn_ON_1") {
      bot.sendMessage(chat_id, device_one_name + " state set to ON", "");
      // Pin 2 - HIGH
      control_device(2, 1);
    } else if (text == "/Turn_ON_2") {
      bot.sendMessage(chat_id, device_two_name + " state set to ON", "");
      // Pin 4 - HIGH
      control_device(4, 1);
    } else if (text == "/Turn_ON_3") {
      bot.sendMessage(chat_id, device_three_name + " state set to ON", "");
      // Pin 18 - HIGH
      control_device(18, 1);
    } else if (text == "/Turn_ON_4") {
      bot.sendMessage(chat_id, device_four_name + " state set to ON", "");
      // Pin 19 - HIGH
      control_device(19, 1);
    } else if (text == "/Turn_OFF_1") {
      bot.sendMessage(chat_id, device_one_name + " state set to OFF", "");
      // Pin 2 - LOW
      control_device(2, 0);
    } else if (text == "/Turn_OFF_2") {
      bot.sendMessage(chat_id, device_two_name + " state set to OFF", "");
      // Pin 4 - LOW
      control_device(4, 0);
    } else if (text == "/Turn_OFF_3") {
      bot.sendMessage(chat_id, device_three_name + " state set to OFF", "");
      // Pin 18 - LOW
      control_device(18, 0);
    } else if (text == "/Turn_OFF_4") {
      bot.sendMessage(chat_id, device_four_name + " state set to OFF", "");
      // Pin 19 - LOW
      control_device(19, 0);
    } else if (text == "/configure") {
      send_configure_msge(chat_id);
    } else if (text == "/set_new_name_1") {
      flag_device_1 = 1;
      bot.sendMessage(chat_id, "Please send new name...");
    } else if (text == "/set_new_name_2") {
      flag_device_2 = 1;
      bot.sendMessage(chat_id, "Please send new name...");
    } else if (text == "/set_new_name_3") {
      flag_device_3 = 1;
      bot.sendMessage(chat_id, "Please send new name...");
    } else if (text == "/set_new_name_4") {
      flag_device_4 = 1;
      bot.sendMessage(chat_id, "Please send new name...");
    } else {
      Serial.println("Try to change device name");
      if (flag_device_1 == 1) {
        change_device_name(1, text);
        bot.sendMessage(chat_id, "Device 1 name changed to " + device_one_name);
      }

      if (flag_device_2 == 1) {
        change_device_name(2, text);
        bot.sendMessage(chat_id, "Device 2 name changed to " + device_two_name);
      }

      if (flag_device_3 == 1) {
        change_device_name(3, text);
        bot.sendMessage(chat_id, "Device 3 name changed to " + device_three_name);
      }

      if (flag_device_4 == 1) {
        change_device_name(4, text);
        bot.sendMessage(chat_id, "Device 4 name changed to " + device_four_name);
      }
    }





  }
}

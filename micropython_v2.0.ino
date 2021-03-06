/*************************************************************************************************/
/*MicroPython display on Nokia5110 LCD*/
/*Arduino Uno side*/
/*Copyright 2020 @raspiduino*/
/*Under MIT License*/
/*************************************************************************************************/
#include <PCD8544_HOANGSA.h> //You can download it here: http://arduino.vn/tutorial/1345-nokia5110-huong-dan-su-dung-va-chia-se-thu-vien-hoang-sa
#include <AltSoftSerial.h>

//String all_lcd_content = "";
//String command = "";
String input = "";
int x_char = 0;
int y_char = 0;
int x_key = 6;
int key = 32;
int enter = 0;

PCD8544 lcd(14,15,16,17,18); //Setup lcd pin: RST, DC, DIN, CLK. (Connect pin in Readme.md)
AltSoftSerial esp8266;

void printlcd();

void setup() {
  //Serial.begin(9600); //Open serial port to computer
  esp8266.begin(4800); //Open serial port to esp8266
  /*Reset the esp8266 module (reset pin of the esp8266 connected to digital pin 3 on Arduino Uno)*/
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(2, HIGH);
  /*Power the LCD*/
  pinMode(19, OUTPUT);//VCC
  digitalWrite(19, HIGH);//For VCC
  /*Starting the lcd*/
  lcd.ON();//Power on the LCD
  lcd.SET(25,0,0,0,4); //Just don't edit this
  /*Setup the keyboard*/
  /*
    Pin 3 is to select the character in the box in left way (<-)
    Pin 4 is to confirm the character in the box
    Pin 5 is to select the character in the box in right way (->)
    All three pin are connected to buttons and set as INPUT_PULLUP
    That means when you push the button, the value will be LOW
    And when you don't push it, the value will be HIGH
    Be careful!
  */
  for(int i = 3; i < 6; i++){
    //Set INPUT_PULLUP for pins 3 -> 5
    pinMode(i, INPUT_PULLUP);   
  }
  esp8266.println(""); //Press enter to esp8266
  //Serial.setTimeout(5000); //Set the serial timeout to 5000ms to read all character
}

void loop() {
  /*Draw the input box for typing*/
  //lcd.DrawLine(0,39,83,39,BLACK);
  lcd.Asc_Char(0,40,'>', BLACK);
  lcd.Rect(5,39,79,8,BLACK);//Clear the keys
  //lcd.Display();
  /*Read the data from esp8266*/
  while (esp8266.available() > 0) { //If the serial has incomming character, read it
    int incomingByte = esp8266.read(); //Read the character ASCII number to the incomingByte varrible
    if (incomingByte == -1 | incomingByte == 10 | incomingByte == 13) {
      if (incomingByte == 13) { //If the user press enter
        //all_lcd_content = String(all_lcd_content + '\n');
        //Serial.println("Next line"); //For debug, in real run please comment this!
        //Serial.println("");
        x_char = 0;
        y_char = y_char + 8;
      }
      //Serial.println(F("Not in range!"));
    } else {
      char esp8266_data = char(incomingByte); //Convert number to ASCII character
      //all_lcd_content = String(all_lcd_content + esp8266_data);
      //Serial.print(esp8266_data);
      printlcd(esp8266_data);
    }
  }
  /*Receive the command from the main Arduino serial for use in Arduino IDE*/
  /*while (Serial.available() > 0) { //If the serial has incomming character, read it
    int incomingByte = Serial.read(); //Read the character ASCII number to the incomingByte varrible
    if (incomingByte == -1 | incomingByte == 10 | incomingByte == 13) {
      if (incomingByte == 13) { //If the user press enter
        esp8266.println(command);
        command = "";
      }
      //Serial.println(F("Not in range!"));
    } else {
      char data = char(incomingByte); //Convert number to ASCII character
      command = String(command + data);
    }
  }*/
  /************************Get keys from keyboard**************************/
  /***LEFT button***/
  if(digitalRead(3) == LOW){ //LEFT button is pushed
    enter = 0;
    if(key > 31){
      key--;
      lcd.Asc_Char(x_key,40,key,BLACK);
    } else{
      //Out range, back to enter key(128). See below
      key = 126;
      lcd.Asc_Char(x_key, 40,126, BLACK);
    }
    delay(100); //Delay for checking the next click
  }
  /***Select button***/
  if(digitalRead(4) == LOW){ //Select button is pushed
    //Click 2 times is press enter!
    if(enter == 1){
      esp8266.print(input); //Sent data to esp8266
      esp8266.println(""); //Press enter
      //lcd.Rect(5,39,79,8,BLACK);//Clear the keys
      //lcd.Display();
      x_key = 6;
      enter = 0;
      input = "";
    } else{ //Not press enter
      input = String(input + char(key));
      //Serial.print(key);
      if(x_key < 80){ //Check if end of lcd
        x_key = x_key + 5;  
      } else{
        lcd.Rect(5,39,79,8,BLACK);//Clear the keys
        x_key = 6;  
      }
      enter = 1;
      delay(100);   
    }
  }
  /***RIGHT button***/
  if(digitalRead(5) == LOW){ //RIGHT button is pushed
    enter = 0;
    if(key < 127){
      key++;
      lcd.Asc_Char(x_key,40,key,BLACK); 
    } else{
      key = 32;
      lcd.Asc_Char(x_key, 40, " ", BLACK);
    }
  }
  lcd.Display();
  delay(100); //Delay for checking the next click
}

void printlcd(char data){
  if(x_char < 80 && y_char < 33){
    lcd.Asc_Char(x_char,y_char,data,BLACK);
    //lcd.Display();
    x_char = x_char + 5;
  } else {
    if(x_char > 74){
      x_char = 0;
      y_char = y_char + 8;
      lcd.Asc_Char(x_char,y_char,data,BLACK);
      //lcd.Display();
    }
    if(y_char > 32){
      lcd.Clear();
      x_char = 0;
      y_char = 0;
      lcd.Asc_Char(x_char,y_char,data,BLACK);
      //lcd.Display();
    }
  }
}

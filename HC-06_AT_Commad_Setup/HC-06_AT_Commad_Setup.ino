#include <SoftwareSerial.h>

//HC06 Bluetooth Module Command List
const char COMM_CHK[] = "AT";           //Check UART connection. Returns "OK" if correct baudrate, parity has been used and device is in AT mode
                                        //Module is in AT mode by default when unpaired (LEDs flashing if unpaired, steady ON if paired)
const char VERSION[] = "AT+VERSION";    //Get firmware, bluetooth, HCI and LMP version
const char NAME[] = "AT+NAME";          //Set device name. To set name, add it at end of string (20 char max) 
const char PIN[] = "AT+PINpppp";        //Set pin code for pairing. Replace 'pppp' with desired pin (default pin is 1234)
const char SET_BAUDRATE[] = "AT+BAUDx"; //Replace 'x' with character corresponding to desired speed from list below to set device baudrate:
                                        /*
                                          1 ——— 1200
                                          2 ——— 2400
                                          3 ——— 4800
                                          4 ——— 9600 (default)
                                          5 ——— 19200
                                          6 ——— 38400
                                          7 ——— 57600
                                          8 ——— 115200
                                          9 ——— 230400
                                          A ——— 460800
                                          B ——— 921600
                                          C ——— 1382400
                                        */
const char NOPARITY[] = "AT+PN";        //No parity check (default)
const char EVENPARITY[] = "AT+PE";      //Even parity check is set
const char ODDPARITY[] = "AT+PO";       //Odd parity is set
const char LEDON[] = "AT+LED1";         //turns (blue) board LED ON
const char LEDOFF[] = "AT+LED0";        //turns (blue) board LED OFF
const char SLAVEMODE[] = "AT+ROLE=S";   //set module into SLAVE mode (default)
const char MASTERMODE[] = "AT+ROLE=M";  //set module into MASTER mode
//------------------------------------

SoftwareSerial mySerial(4, 3); // RX, TX (connect to RX/TX of HC-06 module)

void send_AT_cmd(char *str) {
  //print command string to serial monitor
  Serial.println(str);
  
  //send command HC-06 Module
  mySerial.write(str);
  
  delay(1000); //arbitrary delay

  //print HC-06 reply to serial monitor
  if (mySerial.available()) {
    while (mySerial.available())Serial.write(mySerial.read());
  }
  Serial.println("");
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  delay(500);

  Serial.println("<<<<HC-06 AT commad setup>>>>!");

  //comm check
  send_AT_cmd(COMM_CHK);

  //get device firmware version
  send_AT_cmd(VERSION);

  //rename module
  char newNAME[30];
  strcpy(newNAME, NAME);
  strcat(newNAME, "WALL-e");
  send_AT_cmd(newNAME);

  //set new device pin
  send_AT_cmd(PIN);

}

void loop() {
  // put your main code here, to run repeatedly:

}

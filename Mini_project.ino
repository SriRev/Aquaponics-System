#include <SoftwareSerial.h>
#define SIM800_TX_PIN 10
#define SIM800_RX_PIN 11
//Create software serial object to communicate with SIM800 
SoftwareSerial serialSIM800(SIM800_TX_PIN, SIM800_RX_PIN);
#include <dht.h>
#define DHT11_PIN A5
int phvalue = 0;
unsigned long int avgval; //Store the average value of the sensor feedback
int buffer_arr[10], temp;
dht DHT;


void setup()
{
  Serial.begin(9600);
  serialSIM800.begin(9600);   // Setting the baud rate of GSM Module
  Serial.println ("SIM800C Ready");
}
void loop()
{
  for (int i = 0; i < 10; i++) //Get 10 sample value from the sensor for smooth the value
  {
    buffer_arr[i] = analogRead(A0);
    delay(30);
  }
  for (int i = 0; i < 9; i++) //sort the analog from small to large
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 2; i < 8; i++) //take the average value of 6 center sample
    avgval += buffer_arr[i];
  float volt = (float)avgval * 5.0 / 1024 / 6; //convert the analog into millivolt
  float ph_act = 3.5 * volt; //convert the millivolt into pH value
  Serial.println("Ph Value ");
  Serial.println(ph_act);

  if (ph_act >= 8) // PH value more that 8
  {
    Serial.println ("Sending Message");
    serialSIM800.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(1000);
    Serial.println ("Set SMS Number");
    serialSIM800.println("AT+CMGS=\"+918197865084\"\r"); //Mobile phone number to send message
    delay(1000);
    Serial.println ("Set SMS Content");
    serialSIM800.println("PH High");// Messsage content
    serialSIM800.println(ph_act);
    delay(100);
    Serial.println ("Finish");
    serialSIM800.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
    Serial.println ("Message has been sent");
    delay(10000);
  }
  if (ph_act <= 6)
  {
    Serial.println ("Sending Message");
    serialSIM800.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(1000);
    Serial.println ("Set SMS Number");
    serialSIM800.println("AT+CMGS=\"+918197865084\"\r"); //Mobile phone number to send message
    delay(1000);
    Serial.println ("Set SMS Content");
    serialSIM800.println("PH Low");
    serialSIM800.println(ph_act)  ;// Messsage content
    delay(100);
    Serial.println ("Finish");
    serialSIM800.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
    Serial.println ("Message has been sent");
    delay(10000);
  }
  else {}
  delay(1000);

  int water_sen = analogRead(A1);
  Serial.println("water level-->");
  Serial.println(water_sen);
  //lcd.setCursor(0, 1);
 if (water_sen == 0) {
    //lcd.print("Water Empty .....");
    Serial.print(" ");
    Serial.println("Water Empty...");
    delay(1000);
    Serial.println ("Sending Message");
    serialSIM800.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(1000);
    Serial.println ("Set SMS Number");
    serialSIM800.println("AT+CMGS=\"+918197865084\"\r"); //Mobile phone number to send message
    delay(1000);
    Serial.println ("Set SMS Content");
    serialSIM800.println("Water Empty");// Messsage content
    delay(100);
    Serial.println ("Finish");
    serialSIM800.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
    Serial.println ("Message has been sent");
    delay(10000);
  }
  else if (water_sen > 10 && water_sen < 350)
  {

    Serial.println("Water Low");
    delay(1000);
    Serial.println ("Sending Message");
    serialSIM800.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(1000);
    Serial.println ("Set SMS Number");
    serialSIM800.println("AT+CMGS=\"+918197865084\"\r"); //Mobile phone number to send message
    delay(1000);
    Serial.println ("Set SMS Content");
    serialSIM800.println("Water Low");// Messsage content
    delay(100);
    Serial.println ("Finish");
    serialSIM800.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
    Serial.println ("Message has been sent");
    delay(10000);
  }
  else if (water_sen > 350 && water_sen < 510)
  {

    Serial.println("Water MEDIUM "); delay(2000);
    Serial.print(water_sen);
    Serial.print(" ");
  }
  else if (water_sen > 510)
  {

    Serial.println("Water HIGH ");
    Serial.println ("Sending Message");
    serialSIM800.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(1000);
    Serial.println ("Set SMS Number");
    serialSIM800.println("AT+CMGS=\"+918197865084\"\r"); //Mobile phone number to send message
    delay(1000);
    Serial.println ("Set SMS Content");
    serialSIM800.println("Water High");// Messsage content
    delay(100);
    Serial.println ("Finish");
    serialSIM800.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
    Serial.println ("Message has been sent");
    delay(10000);
  }
  delay(10000);


  DHT.read11(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print(" humi:");
  Serial.println(DHT.humidity);


  if (DHT.temperature >= 30) // High temperature testing
  { Serial.println ("Sending Message");
    serialSIM800.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(1000);
    Serial.println ("Set SMS Number");
    serialSIM800.println("AT+CMGS=\"+918197865084\"\r"); //Mobile phone number to send message
    delay(1000);
    Serial.println ("Set SMS Content");
    serialSIM800.println("Temperature is greater than 30 C");// Messsage content
    delay(100);
    Serial.println ("Finish");
    serialSIM800.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
    Serial.println ("Message has been sent");
    delay(10000);
  }
  else if (DHT.temperature <= 27) // LOW temperature testing
  {
    Serial.println ("Sending Message");
    serialSIM800.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(1000);
    Serial.println ("Set SMS Number");
    serialSIM800.println("AT+CMGS=\"+918197865084\"\r"); //Mobile phone number to send message
    delay(1000);
    Serial.println ("Set SMS Content");
    serialSIM800.println("Temperature less than 27 C");// Messsage content
    delay(100);
    Serial.println ("Finish");
    serialSIM800.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
    Serial.println ("Message has been sent");
    delay(1000);
  }
  else {}
  delay(10000);
  
}

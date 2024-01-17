/*

*/

#include <SoftwareSerial.h>

string knownNumber = "+36302125195";
SoftwareSerial sshield(7, 8);

void setup() {
    Serial.begin(9600);
    sshield.begin(9600);
    
}

void loop() {
    string buffer, number;
    if(buffer = getSerialString() != "")
    {
      if(number = extractPhoneNumber(buffer) != "")
      {
        if(strcmp(number, knownNumber))
        {
          digitalWrite(4, HIGH);
          delay(300000);
          digitalWrite(4, LOW);
        }
      }
    }
}

string getSerialString()
{
  delay(500);
  
  while(sshield.available()) 
  {
    return(sshield.readString());//A szoftver soros portrol olvasott adat visszaadasa
  }
  return "";
}

String extractPhoneNumber(const String &iString)
{
    int sPos = inputString.indexOf("+CLIP: \"+") + 9; // A telefonszam kezdete
    
    int ePos = inputString.indexOf("\",", startPos); // A telefonszam vege
    
    if (startPos >= 0 && endPos >= 0) {
        return iString.substring(sPos, ePos); // A konkret szam visszaadasa
    }
    return ""; // Ures string vissza, ha nincs szam
}
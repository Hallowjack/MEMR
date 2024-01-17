
#include <SoftwareSerial.h>

String knownNumber = "+36302125195";
SoftwareSerial sshield(7, 8);

void setup() {
    Serial.begin(9600);
    sshield.begin(9600);
    
}

void loop() {
    String buffer, number;
    buffer = getSerialString();
    if(!buffer.equals(""))
    {
      number = extractPhoneNumber(buffer);
      if(!number.equals(""))
      {
        if(!number.equals(knownNumber))
        {
          digitalWrite(4, HIGH);
          delay(1000);
          digitalWrite(4, LOW);
          delay(300000);
          digitalWrite(4, HIGH);
          delay(1000);
          digitalWrite(4, LOW);
        }
      }
    }
}

String getSerialString()
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
    int sPos = iString.indexOf("+CLIP: \"+") + 9; // A telefonszam kezdete
    
    int ePos = iString.indexOf("\",", sPos); // A telefonszam vege
    
    if (sPos >= 0 && ePos >= 0) {
        return iString.substring(sPos, ePos); // A konkret szam visszaadasa
    }
    return ""; // Ures string vissza, ha nincs szam
}
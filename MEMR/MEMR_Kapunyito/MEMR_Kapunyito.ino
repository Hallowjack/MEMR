
#include <SoftwareSerial.h>

String knownNumber;
SoftwareSerial sshield(7, 8);

void setup() {
    Serial.begin(9600);
    sshield.begin(9600);
    
    sshield.println("AT+CMGF=1");
    sshield.println("AT+CNMI=1,2,0,0,0");
    
}

void loop() {
    String buffer, number;
    buffer = getSerialString();                                 //Olvasás a bufferba
    if(!buffer.equals(""))                                      //Ha van tartalom a bufferban akkor van miverl foglalkozni
    {
      number = extractPhoneNumber(buffer);                      //Kiszedjük a számot a bufferből, ha van benne
      if(!number.equals(""))
      {
        if(!number.equals(knownNumber))                         //Megnézzük hogy olyan számról hívtak-e amit ismerünk
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
      number = parseSMS(buffer);
      if(!number.equals(""))
      {
        knownNumber.append(number);
      }
    }
}

String getSerialString()
{
  delay(500);
  
  while(sshield.available()) 
  {
    return(sshield.readString());                               //A szoftveres soros portról olvasott adat visszaadása
  }
  return "";
}

String extractPhoneNumber(const String &iString)
{
    int sPos = iString.indexOf("+CLIP: \"+") + 13;               // A telefonszám kezdete
    
    int ePos = iString.indexOf("\",", sPos);                    // A telefonszám vége
    
    if (sPos >= 0 && ePos >= 0) {
        return iString.substring(sPos, ePos);                   // A konkrét szám visszaadása
    }
    return "";                                                  // Üres string vissza, ha nincs szám
}

String parseSMS(const String &receivedMessage)
{
  if (mySerial.available() > 0)
  {
    int mdIndex = receivedMessage.indexOf("MDnDGaTe01!");       // Megnézzük, hogy az sms tartalmazza-e a "MDnDGaTe01!" sztringet
    if (mdIndex != -1)
    {
      int plusIndex = receivedMessage.indexOf("+", mdIndex);    // Kiszedjük a telefonszámot az üzenetből
      if (plusIndex != -1)
      {
        String senderNumber = receivedMessage.substring(plusIndex, plusIndex + 13); // feltételezzük, hogy a telefonszám 13 karakter
        return senderNumber;
      }
    }
  }
  return "";                                                     // Üres sztringet adunk vissza, ha nincs találat.
}

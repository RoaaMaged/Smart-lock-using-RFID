#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 5 //define green LED pin
#define LED_R 4 //define red LED
#define RELAY 2 //relay pin
#define BUZZER 7 //buzzer pin
#define led    8
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.



// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x23, 16, 2);
 
void setup() 
{lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(4, 0);             // Set the cursor to the first character of the first line
  lcd.print("Hello :)"); 
  lcd.setCursor(2, 1);             // Set the cursor to the first character of the first line
  lcd.print("Plz put your ID: ");  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  noTone(BUZZER);
  digitalWrite(RELAY, HIGH);
  Serial.println("Plz put your ID...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "4C 84 65 4D") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    lcd.clear();
     lcd.setCursor(4, 0);             // Set the cursor to the first character of the first line
  lcd.print("Hello Mousa :)"); 
    Serial.println();
    delay(300);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    digitalWrite(LED_G, LOW);
  }
  else if(content.substring(1) == "97 A9 97 E3")
  {
    Serial.println("Authorized access");
    Serial.println();
     lcd.clear();
     lcd.setCursor(4, 0);             // Set the cursor to the first character of the first line
  lcd.print("Hello Roaa :)"); 
    delay(300);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    digitalWrite(LED_G, LOW);
  }
  else if(content.substring(1) == "97 4F E4 E3")
  {
    Serial.println("Authorized access");
    Serial.println();
     lcd.clear();
     lcd.setCursor(2, 0);             // Set the cursor to the first character of the first line
  lcd.print("Hello Ebrahim :)"); 
    delay(300);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    digitalWrite(LED_G, LOW);
  }
  else if(content.substring(1) == "57 84 65 E3")
  {
    Serial.println("Authorized access");
    Serial.println();
     lcd.clear();
     lcd.setCursor(4, 0);             // Set the cursor to the first character of the first line
  lcd.print("Hello Ahmed :)"); 
    delay(300);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
  }
 
 else   {
    Serial.println(" Access denied");
     lcd.clear();
     lcd.setCursor(2, 0);     
            // Set the cursor to the first character of the first line
  lcd.print("Access denied!");
   tone(BUZZER, 300); 
   digitalWrite(LED_G, HIGH); // Turn on the LED
   delay(1500);
    digitalWrite(LED_R, HIGH);
    delay(DENIED_DELAY);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
  }
  lcd.clear();
   lcd.setCursor(4, 0);             // Set the cursor to the first character of the first line
  lcd.print("Hello"); 
  lcd.setCursor(2, 1);             // Set the cursor to the first character of the first line
  lcd.print("Plz put your ID: ");  
}
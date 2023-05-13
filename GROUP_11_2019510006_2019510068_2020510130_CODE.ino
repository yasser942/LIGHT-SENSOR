#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2);

#define LED_PIN 3 
#define BUTTON_PIN 2
int photoPin = A0;
int LED_ACTIVATION_VALUE = 100;
int SERIAL_OUTPUT_FREQUENCY = 500;
String flag ="OFF";
bool button_state = false;
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), close, RISING);

  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  if(Serial.available()){
    int temp = Serial.parseInt();
    if(temp!=0)
  	  LED_ACTIVATION_VALUE = temp;
  }
  int light = analogRead(photoPin);
  if(!button_state){
    if(light<LED_ACTIVATION_VALUE){
      digitalWrite(LED_PIN,HIGH);
      flag ="ON";
    }
    else{
      digitalWrite(LED_PIN,LOW);
      flag="OFF";
    }
  }else
    digitalWrite(LED_PIN,HIGH);

  
  Serial.print("\nLIGHT SENSOR: ");
  Serial.println(light);
  Serial.print("LED STATUS: ");
  Serial.println(flag);
  lcd.setCursor(0,0);
  lcd.print("LIGHT SENSOR:");
  lcd.print(light);
  lcd.setCursor(0,1);
  lcd.print("LED STATUS:");
  lcd.print(flag);
  delay(SERIAL_OUTPUT_FREQUENCY);
  lcd.clear();
}
void close(){
  if(button_state)
    button_state= false;
  else
    button_state= true;
  
  
}
int morning;
int noon;
int preNight;
int midNight;  
int greenEW;
int yellowEW;
int redEW;
int greenNS;
int yellowNS;
int redNS;     


long currentMillis;
long previousMillis;



void setup()
{
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode (2, INPUT);                                      // 7am -9am
  pinMode (3, INPUT);                                      // 9am -4pm
  pinMode (4, INPUT);                                      // 4pm - 6pm
  pinMode (5, INPUT);                                      // 6pm - 7am
  
  pinMode (6, OUTPUT);                                     // E/W Green
  pinMode (7, OUTPUT);                                     // E/W Yellow
  pinMode (8, OUTPUT);                                     // E/W Red

  pinMode (9, OUTPUT);                                     // N/S Green
  pinMode (10, OUTPUT);                                    // N/S Yellow
  pinMode (11, OUTPUT);                                    // N/S Red

greenEW = 6;
yellowEW = 7;
redEW = 8;
greenNS = 9;
yellowNS = 10;
redNS = 11;  

}

long morningEvening()
{

    digitalWrite (greenNS, LOW);
    digitalWrite (yellowNS, LOW);
    digitalWrite (redNS, HIGH);
    digitalWrite (greenEW, HIGH);
    digitalWrite (yellowEW, LOW);
    digitalWrite (redEW, LOW);
    delay(12000);
    digitalWrite (greenNS, LOW);
    digitalWrite (yellowNS, LOW);
    digitalWrite (redNS, HIGH);
    digitalWrite (greenEW, LOW);
    digitalWrite (yellowEW, HIGH);
    digitalWrite (redEW, LOW);
    delay(2000);
    digitalWrite (greenNS, HIGH);
    digitalWrite (yellowNS, LOW);
    digitalWrite (redNS, LOW);
    digitalWrite (greenEW, LOW);
    digitalWrite (yellowEW, LOW);
    digitalWrite (redEW, HIGH);
    delay(6000);
    digitalWrite (greenNS, LOW);
    digitalWrite (yellowNS, HIGH);
    digitalWrite (redNS, LOW);
    digitalWrite (greenEW, LOW);
    digitalWrite (yellowEW, LOW);
    digitalWrite (redEW, HIGH);
    delay(2000);
 
}


long middayOvernight()
{
    digitalWrite (greenNS, LOW);
    digitalWrite (yellowNS, LOW);
    digitalWrite (redNS, HIGH);
    digitalWrite (greenEW, HIGH);
    digitalWrite (yellowEW, LOW);
    digitalWrite (redEW, LOW);
    delay(6000);
    digitalWrite (greenNS, LOW);
    digitalWrite (yellowNS, LOW);
    digitalWrite (redNS, HIGH);
    digitalWrite (greenEW, LOW);
    digitalWrite (yellowEW, HIGH);
    digitalWrite (redEW, LOW);
    delay(2000);
    digitalWrite (greenNS, HIGH);
    digitalWrite (yellowNS, LOW);
    digitalWrite (redNS, LOW);
    digitalWrite (greenEW, LOW);
    digitalWrite (yellowEW, LOW);
    digitalWrite (redEW, HIGH);
    delay(6000);
    digitalWrite (greenNS, LOW);
    digitalWrite (yellowNS, HIGH);
    digitalWrite (redNS, LOW);
    digitalWrite (greenEW, LOW);
    digitalWrite (yellowEW, LOW);
    digitalWrite (redEW, HIGH);
    delay(2000);

  
}

void loop()
{
morning = digitalRead(2);
noon = digitalRead(3);
preNight = digitalRead(4);
midNight = digitalRead(5);

if (morning == HIGH)
  {
  morningEvening();
  }
  if (noon == HIGH)
  {
    morningEvening();
  }
  else if (preNight == HIGH)
  {
    middayOvernight();
  }
  else if (midNight == HIGH)
  {
    middayOvernight();
  }
}
  


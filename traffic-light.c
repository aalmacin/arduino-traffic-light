int seconds = 0;
int previousSeconds = 0;
int lightSeconds = 0;

int morningEveningNS = 10;
int morningEveningEW = 5;

int middayOvernightNS = 5;
int middayOvernightEW = 3;

int nsSeconds = morningEveningNS;
int ewSeconds = morningEveningEW;

int morningPin = 2;
int middayPin = 3;
int eveningPin = 4;
int overnightPin = 5;

int ewGreen = 6;
int ewYellow = 7;
int ewRed = 8;

int nsGreen = 9;
int nsYellow = 10;
int nsRed = 11;

int pedPin = 12;

bool green = true;
bool ns = true;
bool emergency = false;

void setup() {
    // put your setup code here, to run once:
    Serial.begin (9600);
    pinMode (morningPin, INPUT);                                      // 7am -9am
    pinMode (middayPin, INPUT);                                      // 9am -4pm
    pinMode (eveningPin, INPUT);                                      // 4pm - 6pm
    pinMode (overnightPin, INPUT);                                      // 6pm - 7am

    pinMode (ewGreen, OUTPUT);                                     // E/W Green
    pinMode (ewYellow, OUTPUT);                                     // E/W Yellow
    pinMode (ewRed, OUTPUT);                                     // E/W Red

    pinMode (nsGreen, OUTPUT);                                     // N/S Green
    pinMode (nsYellow, OUTPUT);                                    // N/S Yellow
    pinMode (nsRed, OUTPUT);                                    // N/S Red

    pinMode (pedPin, INPUT);                                    // Pedestrian pin
}

int getSeconds() {
    return round(millis() / 1000);
}

void light() {

    if(ns) {
        if(green) {
            digitalWrite(nsGreen, HIGH);
            digitalWrite(nsYellow, LOW);
        } else {
            digitalWrite(nsGreen, LOW);
            digitalWrite(nsYellow, HIGH);
        }
        digitalWrite(nsRed, LOW);

        digitalWrite(ewGreen, LOW);
        digitalWrite(ewYellow, LOW);
        digitalWrite(ewRed, HIGH);
    } else {
        if(green) {
            digitalWrite(ewGreen, HIGH);
            digitalWrite(ewYellow, LOW);
        } else {
            digitalWrite(ewGreen, LOW);
            digitalWrite(ewYellow, HIGH);
        }
        digitalWrite(ewRed, LOW);

        digitalWrite(nsGreen, LOW);
        digitalWrite(nsYellow, LOW);
        digitalWrite(nsRed, HIGH);
    }
}

void changeLightSeconds() {
    if(previousSeconds != seconds) {
        lightSeconds++;
    }
    previousSeconds = seconds;
}

void changeLightState() {
    if(lightSeconds != 0 && green && ns && lightSeconds % nsSeconds == 0) {
        green = false;
        ns = true;
        lightSeconds = 0;
    } else if(lightSeconds != 0 && !green && ns && lightSeconds % 3 == 0) {
        green = true;
        ns = false;
        lightSeconds = 0;
    } else if(lightSeconds != 0 && green && !ns && lightSeconds % ewSeconds == 0) {
        green = false;
        ns = false;
        lightSeconds = 0;
    } else if(lightSeconds != 0 && !green && !ns && lightSeconds % 3 == 0) {
        green = true;
        ns = true;
        lightSeconds = 0;
    }
}

void checkTimeOfDayPin() {
    int morning = digitalRead(morningPin);
    int midday = digitalRead(middayPin);
    int evening = digitalRead(eveningPin);
    int overnight = digitalRead(overnightPin);

    if(morning == HIGH || evening == HIGH) {
        nsSeconds = morningEveningNS;
        ewSeconds = morningEveningEW;
    } else if(midday == HIGH || overnight == HIGH) {
        nsSeconds = middayOvernightNS;
        ewSeconds = middayOvernightEW;
    }
}

void checkPedestrianCrossing() {
    int activated = digitalRead(pedPin);
    if(!ns && green && activated) {
        green = false;
        lightSeconds = 0;
    }
}

void loop() {
    checkTimeOfDayPin();

    checkPedestrianCrossing();

    seconds = getSeconds();

    changeLightSeconds();
    changeLightState();
    light();

    Serial.println(lightSeconds);

    light();
}


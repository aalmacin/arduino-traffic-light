
int ewGreen = 6;
int ewYellow = 7;
int ewRed = 8;

int nsGreen = 9;
int nsYellow = 10;
int nsRed = 11;

int seconds = 0;
int previousSeconds = 0;
int lightSeconds = 0;
int green = true;
int ns = true;

void setup() {
    // put your setup code here, to run once:
    Serial.begin (9600);
    pinMode (2, INPUT);                                      // 7am -9am
    pinMode (3, INPUT);                                      // 9am -4pm
    pinMode (4, INPUT);                                      // 4pm - 6pm
    pinMode (5, INPUT);                                      // 6pm - 7am

    pinMode (ewGreen, OUTPUT);                                     // E/W Green
    pinMode (ewYellow, OUTPUT);                                     // E/W Yellow
    pinMode (ewRed, OUTPUT);                                     // E/W Red

    pinMode (nsGreen, OUTPUT);                                     // N/S Green
    pinMode (nsYellow, OUTPUT);                                    // N/S Yellow
    pinMode (nsRed, OUTPUT);                                    // N/S Red
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
    if(lightSeconds != 0 && green && ns && lightSeconds % 10 == 0) {
        green = false;
        ns = true;
        lightSeconds = 0;
    } else if(lightSeconds != 0 && !green && ns && lightSeconds % 3 == 0) {
        green = true;
        ns = false;
        lightSeconds = 0;
    } else if(lightSeconds != 0 && green && !ns && lightSeconds % 5 == 0) {
        green = false;
        ns = false;
        lightSeconds = 0;
    } else if(lightSeconds != 0 && !green && !ns && lightSeconds % 3 == 0) {
        green = true;
        ns = true;
        lightSeconds = 0;
    }
}

void loop() {
    //morningEveningSeq();
    seconds = getSeconds();

    changeLightSeconds();
    changeLightState();
    light();

    Serial.println(lightSeconds);

    light();
}
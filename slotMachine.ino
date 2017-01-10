#include <LiquidCrystal.h>

//arduino pins
const int greenLedPin = 10;
const int blueLedPin = 9;
const int greenButtonPressedPin = 13;
const int interruptPin = 2;
const int amountAnalogPin = 0;
const int yellowButton = 7;

volatile unsigned long milliseconds = 0;

//settings
const int minTimePerSlot = 1000;
const int maxTimePerSlot = 3000;

int betAmount = 0;
volatile int slotValues [] = {0, 0, 0};
const int slotPositions [] = {8, 10, 12};
volatile int currentSlotIndex = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 6);

void setup(){
    setupLCD();
    TIMSK0 |= _BV(OCIE0A);

    pinMode(interruptPin, INPUT_PULLUP);
    pinMode(greenButtonPressedPin, INPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(yellowButton, INPUT);
    pinMode(blueLedPin, OUTPUT);
    /*attachInterrupt(digitalPinToInterrupt(interruptPin), buttonPress, RISING);*/
    Serial.begin(9600);
    Serial.println("Initialized");
}

SIGNAL(TIMER0_COMPA_vect) {
    milliseconds++;
} 

unsigned long myMillis(){
    return milliseconds;
}

void loop(){
    /*int value = digitalRead(interruptPin);*/
    int betAmount = (int)(analogRead(amountAnalogPin)/100 + 1);

    lcd.setCursor(1, 0);
    lcd.print(String(betAmount) + " ");

    /*digitalWrite(greenLedPin, greenState);*/
    /*digitalWrite(blueLedPin, blueState);*/
    /*interrupted = false;*/

    startSpin();
    delay(5000);
}

void setupLCD(){
    lcd.begin(16, 2);
    lcd.print("$0    < 0 0 0 >");
    lcd.setCursor(0, 1);
    lcd.print("Welcome!");
}

void startSpin(){
    //Setting up LCD panel for initial spin
    Serial.println("starting spin");
    lcd.setCursor(0, 1);
    lcd.print("Rolling...");
    currentSlotIndex = 0; 

    int delays[3] = {random(minTimePerSlot, maxTimePerSlot)};
    delays[1] = delays[0] + random(minTimePerSlot, maxTimePerSlot);
    delays[2] = delays[1] + random(minTimePerSlot, maxTimePerSlot);

    [3000, 5000, 7000]

    int beginningTime = myMillis();

    while(currentSlotIndex <= 2) {
        for(int x = currentSlotIndex; x <= 2; x++){
            if(slotValues[x] >= 9){
                slotValues [x] = 0;
            }
            slotValues[x] = slotValues[x] + 1;
            lcd.setCursor(slotPositions[x], 0);
            lcd.print(slotValues[x]);
        }
        if(myMillis() - beginningTime > delays[currentSlotIndex]){
            currentSlotIndex++;
        }
        delay(100);
    }
    getResults();
}

void getResults(){

}

//interrupt for starting (press for any amount of time)
/*void buttonPress(){*/
    /*Serial.println("buttonPress");*/
    /*if(interrupted == false) {*/
        /*int value = digitalRead(greenButtonPressedPin);*/
        /*Serial.println(value);*/
        /*if(value == HIGH) {*/
            /*greenState = !greenState;*/
            /*digitalWrite(greenLedPin, greenState);*/
        /*} else {*/
            /*blueState = !blueState;*/
            /*digitalWrite(blueState, blueState);*/
        /*}*/
    /*}*/
    /*interrupted = true;*/
/*}*/

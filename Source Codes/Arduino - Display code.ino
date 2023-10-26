#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

// pin definition for Arduino UNO
#define TFT_RST  8  // Reset pin (you may need to change this)
#define TFT_CS   10 // Chip select pin
#define TFT_DC   9  // Data/command pin

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_ST7735 tft2 = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

  int faceX = 80;
  int faceY = 60;
  int faceRadius = 40;
int faceColorRed = 255;
int faceColorGreen = 255;
int faceColorBlue = 255;
int eyeColorR = 0;
int eyeColorG = 0;
int eyeColorB = 0;
int songI =0;

void setup() {
  //pinMode(3, OUTPUT);//buzzer
  myservo.attach(2,100,1000);  // (pin, min, max)
  Serial.begin(9600); // Starting Serial Terminal
  tft.initR(INITR_BLACKTAB); // Initialize the TFT screen
  tft.fillScreen(ST7735_BLACK); // Fill the screen with a black background
  tft.setRotation(3); // Rotate the screen 90 degrees clockwise
  tft.setTextColor(ST7735_WHITE); // Set text color to white
  tft.setTextSize(1); // Set text size
  tft.initR(INITR_BLACKTAB);
  printSearching();

}

void loop() {
   
   long cmValue = distanceValue();
   displayValue(cmValue);
   
   Serial.print(cmValue);
   //Serial.print("cm");
   Serial.println();
   delay(100);

}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void displayValue(long val){
  
  int val2= 100;
  if(val>1){
    val2= val;
  }
    
  //tft.setCursor(20, 45); // Adjust these values for centering
  if(val2 < 20){
    for(songI; songI<1; songI++){
      faceDisplay();
      eyeColor();
      printHello();
      sing();
    } 
    faceDisplay();
    eyeColor();
    handDetected();
    songI++;
  }else {
    delay(1000);
    printSearching();
  }  

}

void faceDisplay(){
  tft.setRotation(3); // Rotate the screen 90 degrees clockwise
  tft.fillScreen(ST7735_BLACK);
  
  // Adjust the circle face to the middle (x=80, y=64)
  

  // Draw the face (white circle)
  tft.fillCircle(faceX, faceY, faceRadius, tft.color565(0, 0, 0));
  tft.drawCircle(faceX, faceY, faceRadius+1, ST7735_ORANGE);
  tft.drawCircle(faceX, faceY, faceRadius+2, ST7735_ORANGE);
  tft.drawCircle(faceX, faceY, faceRadius, ST7735_ORANGE);
  
  // Draw the eyes (black)
  int leftEyeX = faceX - 15;
  int rightEyeX = faceX + 15;
  int eyeY = faceY - 10;
  int eyeRadius = 8;
  tft.fillCircle(leftEyeX, eyeY, eyeRadius, tft.color565(255, 255, 255));
  tft.fillCircle(rightEyeX, eyeY, eyeRadius, tft.color565(255, 255, 255));
  
  // Draw the nose (a small black triangle)
  int noseX = faceX;
  int noseY = faceY + 5;
  tft.fillTriangle(noseX, noseY - 5, noseX - 5, noseY + 5, noseX + 5, noseY + 5, ST7735_WHITE);
  
  // Draw the mouth (a curved line using drawLine)
  int mouthY = faceY + 20;
  int mouthStartX = faceX - 15;
  int mouthEndX = faceX + 15;
  int controlPointY = mouthY + 10;
  int lineThickness = 3; // Increase this value for thicker lines
  
  for (int i = 0; i < lineThickness; i++) {
    int offset = i - (lineThickness / 2);
    tft.drawLine(mouthStartX, mouthY + offset, faceX - 5, controlPointY + offset, ST7735_WHITE);
    tft.drawLine(faceX - 5, controlPointY + offset, faceX + 5, controlPointY + offset, ST7735_WHITE);
    tft.drawLine(faceX + 5, controlPointY + offset, mouthEndX, mouthY + offset, ST7735_WHITE);
  }
  //delay(1000);
  // Draw the hat (a rectangle)
  int hatX = faceX - 35;
  int hatY = faceY - (faceRadius+2);
  int hatWidth = 70;
  int hatHeight = 5;
  tft.fillRect(hatX, hatY, hatWidth, hatHeight, ST7735_GREEN);

  int triangleX1 = hatX;
  int triangleX2 = hatX + hatWidth;
  int triangleY = hatY - 15;
  tft.fillTriangle(faceX, hatY, triangleX1, triangleY, triangleX2, triangleY, ST7735_GREEN);




}

long distanceValue(){
  long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   return cm;
}

void printHello(){
  tft.setRotation(3); // Rotate the screen 90 degrees clockwise
  tft.setTextColor(ST7735_CYAN); // Set text color to white
  tft.setTextSize(1); // Set text size

  tft.setCursor(50, 110); // Adjust these values for centering
  tft.println("Hello Human");
  delay(2000);

  tft.setCursor(50, 110);
  tft.setTextColor(ST7735_BLACK);
  tft.print("Hello Human");

  handServo();

  tft.setCursor(40, 110); 
  tft.setTextColor(ST7735_CYAN);
  tft.print("I'm Dragon L");
  delay(2000);

  tft.setCursor(40, 110); 
  tft.setTextColor(ST7735_BLACK);
  tft.print("I'm Dragon L");

  handServo();


}

void handDetected(){
  tft.setRotation(3); // Rotate the screen 90 degrees clockwise
  tft.setTextColor(ST7735_CYAN); // Set text color to white
  tft.setTextSize(1); // Set text size

  tft.setCursor(40, 110); // Adjust these values for centering
  tft.println("Hand Detected");
  delay(2000);

  tft.setCursor(40, 110);
  tft.setTextColor(ST7735_BLACK);
  tft.print("Hand Detected");
}

void eyeColor(){
  eyeColorR =random(255);
  eyeColorG = random(255);
  eyeColorB =random(255);

  // Draw the eyes (black)
  int leftEyeX = faceX - 15;
  int rightEyeX = faceX + 15;
  int eyeY = faceY - 10;
  int eyeRadius = 6;
  tft.fillCircle(leftEyeX, eyeY, eyeRadius, tft.color565(eyeColorR, eyeColorG, eyeColorB));
  tft.fillCircle(rightEyeX, eyeY, eyeRadius, tft.color565(eyeColorR, eyeColorG, eyeColorB));
  
  delay(1000);
}

void printBye(){
    tft.setRotation(3); // Rotate the screen 90 degrees clockwise
    tft.setTextColor(ST7735_CYAN); // Set text color to white
    tft.setTextSize(1); // Set text size

    tft.setCursor(50, 110); // Adjust these values for centering
    tft.println("Bye Human");
    delay(2000);
    tft.fillScreen(ST7735_BLACK);

    tft.setCursor(56, 60);
    tft.setTextSize(3); // Set text size
    tft.setTextColor(ST7735_WHITE);
    tft.print("BYE");
    delay(2000);
    tft.fillScreen(ST7735_BLACK);
  
}
void printSearching(){
    tft.fillScreen(ST7735_BLACK);
    tft.setTextColor(ST7735_WHITE);
    tft.setRotation(3);
    tft.setTextSize(2);
    tft.setCursor(60, 24);
    tft.println("...");

    tft.setCursor(30, 50);
    tft.println("SEARCHING");
    delay(1000);
    tft.fillScreen(ST7735_BLACK); 
}

void handServo(){
  for(int i=0; i<2; i++){

    for(int j =135; j>=90; j--){
      myservo.write(j);              
      delay(20);
    }

    for(int j =90; j<=180; j++){
      myservo.write(j);              
      delay(20);
    }

    for(int j =180; j>=90; j--){
      myservo.write(j);              
      delay(20);
    }

    for(int j =90; j<=135; j++){
      myservo.write(j);              
      delay(20);
    }

  }
}

//................................................................................SONG...........................................................................................

// Define pin 10 for buzzer, you can use any other digital pins (Pin 0-13)
const int buzzer = 3;

// Change to 0.5 for a slower version of the song, 1.25 for a faster version
const float songSpeed = 1.0;

#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988

int notes[] = {
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0,

    NOTE_A4, NOTE_A4,
    //Repeat of first part
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0};

// Durations (in ms) of each music note of the song
// Quarter Note is 250 ms when songSpeed = 1.0
int durations[] = {
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375,

    250, 125,
    //Rpeat of First Part
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375};



void sing() {
  const int totalNotes = sizeof(notes) / sizeof(int);
  // Loop through each note
  for (int i = 0; i < totalNotes; i++)
  {
    const int currentNote = notes[i];
    float wait = durations[i] / songSpeed;
    // Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
    if (currentNote != 0)
    {
      tone(buzzer, notes[i], wait); // tone(pin, frequency, duration)
    }
    else
    {
      noTone(buzzer);
    }
    // delay is used to wait for tone to finish playing before moving to next loop
    delay(wait);
  }

  }
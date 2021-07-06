#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <LedMatrix.h>


//macros for led matrix
#define PIN 6
#define NUM_PIXELS 450
#define WIDTH 15
#define HEIGHT 30

Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GBR);
LedMatrix matrix(NUM_PIXELS, WIDTH, HEIGHT, &strip);


//sd test
#include <SD.h>
#include <SPI.h>

const int CS_PIN = 53;

File file;

const int chipSelect = 53;

File root;


void setup() {
  matrix.begin();

  // Open serial communications and wait for port to open:

  Serial.begin(9600);

  // wait for Serial Monitor to connect. Needed for native USB port boards only:

  while (!Serial);

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {

    Serial.println("initialization failed. Things to check:");

    Serial.println("1. is a card inserted?");

    Serial.println("2. is your wiring correct?");

    Serial.println("3. did you change the chipSelect pin to match your shield or module?");

    Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");

    while (true);
  }

  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");
}


void loop() {
  // put your main code here, to run repeatedly:
}


void printDirectory(File dir, int numTabs) {

  while (true) {

    File entry =  dir.openNextFile();

    if (! entry) {

      // no more files

      break;

    }

    for (uint8_t i = 0; i < numTabs; i++) {

      Serial.print('\t');

    }

    Serial.print(entry.name());

    if (entry.isDirectory()) {

      Serial.println("/");

      printDirectory(entry, numTabs + 1);

    } else {

      // files have sizes, directories do not

      Serial.print("\t\t");

      Serial.println(entry.size(), DEC);

    }

    entry.close();

  }
}

void initializeSD(){
  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {

    Serial.println("initialization failed!");

    while (1);

  }

  Serial.println("initialization done.");
}

int createFile(char filename[]){
  file = SD.open(filename, FILE_WRITE);

  if (file)
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}

int writeToFile(char text[]){
  if (file)
  {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else
  {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

void closeFile(){
  if (file)
  {
    file.close();
    Serial.println("File closed");
  }
}

int openFile(char filename[]){
  file = SD.open(filename);
  if (file)
  {
    Serial.println("File opened with success!");
    return 1;
  } else
  {
    Serial.println("Error opening file...");
    return 0;
  }
}

String readLine(){
  String received = "";
  char ch;
  while (file.available())
  {
    ch = file.read();
    if (ch == '\n')
    {
      return String(received);
    }
    else
    {
      received += ch;
    }
  }
  return "";
}

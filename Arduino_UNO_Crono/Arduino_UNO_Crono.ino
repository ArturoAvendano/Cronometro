#include <MD_MAX72xx.h>
#include <SoftwareSerial.h>
#include <SPI.h>
SoftwareSerial reloj(2, 3);
#define  USE_POT_CONTROL 0
#define PRINT_CALLBACK  0
#define PRINT(s, v) { reloj.print(F(s)); reloj.print(v); }
#define MAX_DEVICES 8
#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS


MD_MAX72XX mx = MD_MAX72XX(CS_PIN, MAX_DEVICES);
// En caso de usar potenciometro para modificar la velocidad
#if USE_POT_CONTROL
#define SPEED_IN  A5
#else
#define SCROLL_DELAY  50
#endif

#define CHAR_SPACING  1 // Separación de caracteres
#define BUF_SIZE  150
char curMessage[BUF_SIZE];
char newMessage[BUF_SIZE];
bool newMessageAvailable = false;
char message_static[BUF_SIZE] = {"Contador"};
bool newMessageAvailable_static = true;
uint16_t  scrollDelay;  // in milliseconds
byte selector = 4;
byte selec;
void setup()
{
  mx.begin();
  mx.setShiftDataInCallback(scrollDataSource);
  mx.setShiftDataOutCallback(scrollDataSink);
  pinMode(selector, INPUT_PULLUP);
#if USE_POT_CONTROL
  pinMode(SPEED_IN, INPUT);
#else
  scrollDelay = SCROLL_DELAY;
#endif

  strcpy(curMessage, " ");
  newMessage[0] = '\0';
  Serial.begin(9600);
  reloj.begin(57600);

}

void loop() {
  selec = digitalRead(selector);

  /// reloj
  while (selec == 0) {
    scrollDelay = getScrollDelay();
    readSerial_scroll();
    scrollText();
    selec = digitalRead(selector);
  }


  //// crono
  while (selec == 1) {
    readSerial_Static();
    if (newMessageAvailable_static)
    {
      PRINT("\nProcessing new message: ", message_static);
      printText(0, MAX_DEVICES - 1, message_static);
      newMessageAvailable_static = false;

    }
    selec = digitalRead(selector);
  }
}

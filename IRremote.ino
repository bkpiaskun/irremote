#include <IRremote.h>

int RECV_PIN = 10;
int RELAY_ONE_PIN = 12;
int RELAY_TWO_PIN = 13;

/* 
Pilot IR
1                              ffa25d
2                              ff629d
3                              ffe21d
4                              ff22dd
5                              ff02fd
6                              ffc23d
7                              ffe01f
8                              ffa857
9                              ff906f
*                              ff6897
0                              ff9867
#                              ffb04f
up                             ff18e7
left                           ff10ef
ok                             ff38c7
right                          ff5aa5
down                           ff4ab5
*/


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(112500);
  irrecv.enableIRIn();
  
  pinMode(RELAY_ONE_PIN, OUTPUT); //Relay one
  pinMode(RELAY_TWO_PIN, OUTPUT); //Relay twi

  digitalWrite(RELAY_ONE_PIN, HIGH);
  digitalWrite(RELAY_TWO_PIN, HIGH);
}
 
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(String(results.value, HEX));
    Serial.print(hexes[0]);
    irrecv.resume();
  }
  
  if (results.value == 0xffa25d) {
    relay_one();
    results.value = 0x00000000;
  }

  if (results.value == 0xff629d) {
    relay_two();
    results.value = 0x00000000;
  }
  
} 

void relay_one() {
  static int m = HIGH;
  m = !m;
  digitalWrite(RELAY_ONE_PIN, m);
} 

void relay_two() {
  static int m = HIGH;
  m = !m;
  digitalWrite(RELAY_TWO_PIN, m);
}

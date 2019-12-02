#include <Arduino.h>
#include <IRremote.h>

int RECV_PIN = 15;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  Serial.println("IR Receiver ready");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    Serial.print(" - ");
    switch (results.decode_type){
        case NEC: Serial.println("NEC"); break ;
        case SONY: Serial.println("SONY"); break ;
        case RC5: Serial.println("RC5"); break ;
        case RC6: Serial.println("RC6"); break ;
        case DISH: Serial.println("DISH"); break ;
        case SHARP: Serial.println("SHARP"); break ;
        case JVC: Serial.println("JVC"); break ;
        case SANYO: Serial.println("SANYO"); break ;
        case MITSUBISHI: Serial.println("MISUBISHI"); break ;
        case SAMSUNG: Serial.println("SAMSUNG"); break ;
        case LG: Serial.println("LG"); break ;
        case WHYNTER: Serial.println("WHYNTER"); break ;
        case AIWA_RC_T501: Serial.println("AIWARC_T501"); break ;
        case PANASONIC: Serial.println("PNASONIC"); break ;
        case DENON: Serial.println("DENON"); break ;
      default:
        case UNKNOWN: Serial.println("UNKNOWN"); break ;
      }
    irrecv.resume(); // Receive the next value
  }
  delay(300);
}

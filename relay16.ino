/* Send HEX string from "0000" to "FFFF" to set relays. Uncomment to use integer from 0 to 65535 */
#define HEX_CMD

const int CH[16] = {A2, A3, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, A4, A0, A1};

void setup() {
  int idx;
  Serial.begin(115200);
  Serial.setTimeout(10000);
  for (idx = 0; idx < 16; idx++) {
    pinMode(CH[idx], OUTPUT);
    digitalWrite(CH[idx], 0);
  }
}

void loop() {
  String input;
  int state;
  int idx;

  if (Serial.available() == 0) return;
  input = Serial.readStringUntil('\r');
#ifdef HEX_CMD
  if (input.length() != 4) return;
  if (!isHexadecimalDigit(input.charAt(0)) ) return;
  if (!isHexadecimalDigit(input.charAt(1)) ) return;
  if (!isHexadecimalDigit(input.charAt(2)) ) return;
  if (!isHexadecimalDigit(input.charAt(3)) ) return;
  state = strtol(input.c_str(), 0, 16);
#else
  if (input.length() > 5) return;
  for (idx = 0; idx < input.length(); idx++){if(!isDigit(input.charAt(idx))) return;}
  state = strtol(input.c_str(), 0, 10);
  if (state > 65535) return;
#endif
  for (idx = 0; idx < 16; idx++) digitalWrite(CH[idx], (state >> idx) & 1);
  Serial.println(input);
}

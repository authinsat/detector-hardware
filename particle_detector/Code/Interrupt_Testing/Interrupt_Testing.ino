int sipm = A0; //can change pin later
unsigned int sipm_val = 0;
unsigned int sipm_thresh = 1000;
byte analog_res = 12;
char msg[128];
int count_pin = 4;
int div_pin = 5;
volatile bool is_it_time_to_sample = false;
volatile bool data_time = false;
int values[100] = {};
int count = 0;
int tot = 0;
int avg = 0;
int i = 0;


void setup() {
  analogReadResolution(analog_res);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Ready.");
  pinMode(count_pin, INPUT_PULLUP);
  attachInterrupt(count_pin, ISR_PULSE, FALLING);
  pinMode(div_pin, INPUT_PULLUP);
  attachInterrupt(div_pin, ISR_SEND, FALLING);
}



void loop() {
  if (is_it_time_to_sample == true) {
    sipm_val = analogRead(sipm);
    Serial.println(sipm_val);
    values[count] = sipm_val;
    count++;
    is_it_time_to_sample = false;
  }
  if (data_time == true){
    for(i = 0; i < count; i = i + 1){
      tot = tot + values[i];
      }
    avg = tot/count;
    Serial.println("number:");
    Serial.println(count);
    Serial.println("average:");
    Serial.println(avg);
    count = 0;
    tot = 0;
    data_time = false;
  }
}



void ISR_PULSE() {
  is_it_time_to_sample = true;
}



void ISR_SEND() {
  data_time = true;
  }

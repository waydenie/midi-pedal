#include <MIDI.h>
/*
  Sustain or Sostenuto pedal
 */

// IO pins.
int SwitchPIN  = 0;
int PedalPIN   = 1;
int midiOutPIN = 8;

int last_SwitchSTATE = LOW;
int last_PedalSTATE  = LOW;
int SwitchSTATE      = LOW;
int PedalSTATE       = LOW;

void setup() {
  // Start MIDI and USB Serial
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(38400);

  pinMode(SwitchPIN,  INPUT);
  pinMode(PedalPIN,   INPUT);
  pinMode(midiOutPIN, OUTPUT);
  
  last_SwitchSTATE = digitalRead(SwitchPIN);
  last_PedalSTATE  = digitalRead(PedalPIN);
}

void loop() {
  // read input switches
  SwitchSTATE = digitalRead(SwitchPIN);
  PedalSTATE  = digitalRead(PedalPIN);

  // debounce switches
  if ((last_PedalSTATE != PedalSTATE) || (last_SwitchSTATE != SwitchSTATE)) {
    delay(50); // wait 50ms for the switches to settle, then re-read them.
    SwitchSTATE  = digitalRead(SwitchPIN);
    PedalSTATE   = digitalRead(PedalPIN);
    
    // output out the state of the pedal:
    if (PedalSTATE == HIGH && SwitchSTATE == LOW) //sustain off
    {
      Serial.println("sustain off");
      MIDI.sendControlChange(64,0,1);
    }  
    if (PedalSTATE == LOW && SwitchSTATE == LOW) //sustain on
    {
      Serial.println("sustain on");
      MIDI.sendControlChange(64,127,1);
    }
    if (PedalSTATE == HIGH && SwitchSTATE == HIGH) //sostenuto off
    {
      Serial.println("sostenuto off");
      MIDI.sendControlChange(66,0,1);
    }
    if (PedalSTATE == LOW && SwitchSTATE == HIGH) //sostenuto on
    {
      Serial.println("sostenuto on");
      MIDI.sendControlChange(66,127,1);
    }

    last_SwitchSTATE = SwitchSTATE;
    last_PedalSTATE  = PedalSTATE;
  }

  delay(5);
}


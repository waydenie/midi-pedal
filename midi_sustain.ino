#include <MIDI.h>
/*
  Sustain pedal
 */

// IO pins.
int PedalPIN   = 1;
int midiOutPIN = 8;

int last_PedalSTATE = LOW;
int PedalSTATE      = LOW;

void setup() {
  // Start MIDI and USB Serial
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(38400);

  pinMode(PedalPIN,   INPUT);
  pinMode(midiOutPIN, OUTPUT);
  
  last_PedalSTATE = digitalRead(PedalPIN);
}

void loop() {
  // read input switch
  PedalSTATE  = digitalRead(PedalPIN);

  // debounce switch
  if ( last_PedalSTATE != PedalSTATE ) {
    delay(50); // wait 50ms for the switch to settle, then re-read.
    PedalSTATE      = digitalRead(PedalPIN);
    
    // issue MIDI Control Change for pedal state
    if ( PedalSTATE == HIGH ) {         //sustain off
      Serial.println("sustain off");
      MIDI.sendControlChange(64,0,1);
    } else { //( PedalSTATE == LOW )    //sustain on 
      Serial.println("sustain on");
      MIDI.sendControlChange(64,127,1);
    }

    last_PedalSTATE = PedalSTATE;
  }

  delay(5);
}


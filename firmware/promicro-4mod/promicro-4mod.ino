/*
 * StageMod — Protótipo v0
 * Pro Micro (ATmega32U4) + 4× WS2812B em cadeia (1 LED por módulo)
 * MIDI USB → RGB completo por módulo
 *
 * Bibliotecas: MIDI Library (FortySevenEffects), FastLED
 * Placa: Arduino Leonardo / SparkFun Pro Micro (5V, 16MHz)
 */

#include <MIDI.h>
#include <FastLED.h>

#define LED_PIN     6
#define NUM_MODULES 4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

#define MIDI_NOTE_MODULE_1  60   // C3 = módulo 1
#define MIDI_CHANNEL        1    // 0 = omni

CRGB modules[NUM_MODULES];

// Cor RGB alvo de cada módulo (0–255) — editável via CC
uint8_t moduleR[NUM_MODULES];
uint8_t moduleG[NUM_MODULES];
uint8_t moduleB[NUM_MODULES];

MIDI_CREATE_DEFAULT_INSTANCE();

uint8_t masterBrightness = 255;

// CC 1–3 = Mod1 R,G,B · 4–6 = Mod2 · 9–11 = Mod3 · 12–14 = Mod4 · 7 = dimmer
static const uint8_t CC_RGB_MAP[][3] = {
  { 1,  2,  3  },  // módulo 0
  { 4,  5,  6  },  // módulo 1
  { 9,  10, 11 },  // módulo 2
  { 12, 13, 14 },  // módulo 3
};

uint8_t midiToByte(byte value) {
  return (uint8_t)map(value, 0, 127, 0, 255);
}

void applyModuleColor(int index) {
  if (index < 0 || index >= NUM_MODULES) return;
  modules[index] = CRGB(moduleR[index], moduleG[index], moduleB[index]);
}

void applyModuleColorScaled(int index, uint8_t scale) {
  if (index < 0 || index >= NUM_MODULES) return;
  modules[index] = CRGB(
    (uint8_t)((uint16_t)moduleR[index] * scale / 255),
    (uint8_t)((uint16_t)moduleG[index] * scale / 255),
    (uint8_t)((uint16_t)moduleB[index] * scale / 255)
  );
}

void showAll() {
  FastLED.show();
}

void blackout() {
  fill_solid(modules, NUM_MODULES, CRGB::Black);
  showAll();
}

void setModuleRgb(int index, uint8_t r, uint8_t g, uint8_t b) {
  if (index < 0 || index >= NUM_MODULES) return;
  moduleR[index] = r;
  moduleG[index] = g;
  moduleB[index] = b;
  applyModuleColor(index);
  showAll();
}

int ccToModuleChannel(byte cc, int *channel) {
  for (int m = 0; m < NUM_MODULES; m++) {
    for (int c = 0; c < 3; c++) {
      if (CC_RGB_MAP[m][c] == cc) {
        *channel = c;
        return m;
      }
    }
  }
  return -1;
}

void onNoteOn(byte channel, byte note, byte velocity) {
  if (MIDI_CHANNEL != 0 && channel != MIDI_CHANNEL) return;
  if (velocity == 0) {
    onNoteOff(channel, note, velocity);
    return;
  }

  int idx = note - MIDI_NOTE_MODULE_1;
  if (idx < 0 || idx >= NUM_MODULES) return;

  // Velocity escala a cor RGB já definida nos CCs
  applyModuleColorScaled(idx, midiToByte(velocity));
  showAll();
}

void onNoteOff(byte channel, byte note, byte velocity) {
  if (MIDI_CHANNEL != 0 && channel != MIDI_CHANNEL) return;

  int idx = note - MIDI_NOTE_MODULE_1;
  if (idx < 0 || idx >= NUM_MODULES) return;

  modules[idx] = CRGB::Black;
  showAll();
}

void onControlChange(byte channel, byte cc, byte value) {
  if (MIDI_CHANNEL != 0 && channel != MIDI_CHANNEL) return;

  if (cc == 7) {
    masterBrightness = midiToByte(value);
    FastLED.setBrightness(masterBrightness);
    for (int i = 0; i < NUM_MODULES; i++) {
      applyModuleColor(i);
    }
    showAll();
    return;
  }

  int rgbCh;
  int mod = ccToModuleChannel(cc, &rgbCh);
  if (mod >= 0) {
    uint8_t v = midiToByte(value);
    if (rgbCh == 0) moduleR[mod] = v;
    else if (rgbCh == 1) moduleG[mod] = v;
    else moduleB[mod] = v;
    applyModuleColor(mod);
    showAll();
  }
}

void onProgramChange(byte channel, byte program) {
  if (MIDI_CHANNEL != 0 && channel != MIDI_CHANNEL) return;

  switch (program) {
    case 0:
      blackout();
      break;
    case 1:
      // Warm white
      for (int i = 0; i < NUM_MODULES; i++) {
        setModuleRgb(i, 255, 180, 80);
      }
      break;
    case 2:
      // Vermelho
      for (int i = 0; i < NUM_MODULES; i++) {
        setModuleRgb(i, 255, 0, 0);
      }
      break;
    case 3:
      // Verde
      for (int i = 0; i < NUM_MODULES; i++) {
        setModuleRgb(i, 0, 255, 0);
      }
      break;
    case 4:
      // Azul
      for (int i = 0; i < NUM_MODULES; i++) {
        setModuleRgb(i, 0, 0, 255);
      }
      break;
    case 5:
      // Magenta
      for (int i = 0; i < NUM_MODULES; i++) {
        setModuleRgb(i, 255, 0, 255);
      }
      break;
    case 6:
      // Branco
      for (int i = 0; i < NUM_MODULES; i++) {
        setModuleRgb(i, 255, 255, 255);
      }
      break;
    default:
      break;
  }
}

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(modules, NUM_MODULES);
  FastLED.setBrightness(masterBrightness);
  FastLED.clear(true);

  // Boot: demonstra RGB em cada módulo
  const CRGB bootColors[] = { CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::White };
  for (int i = 0; i < NUM_MODULES; i++) {
    modules[i] = bootColors[i];
    showAll();
    delay(200);
    modules[i] = CRGB::Black;
  }

  if (MIDI_CHANNEL == 0) {
    MIDI.begin(MIDI_CHANNEL_OMNI);
  } else {
    MIDI.begin(MIDI_CHANNEL);
  }

  MIDI.setHandleNoteOn(onNoteOn);
  MIDI.setHandleNoteOff(onNoteOff);
  MIDI.setHandleControlChange(onControlChange);
  MIDI.setHandleProgramChange(onProgramChange);
}

void loop() {
  MIDI.read();
}

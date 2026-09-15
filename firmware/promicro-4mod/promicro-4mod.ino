/*
 * StageMod — Protótipo v0
 * Pro Micro (ATmega32U4) + 4× WS2812B em cadeia (1 LED por módulo)
 * MIDI USB → cor/brilho por módulo
 *
 * Bibliotecas (Arduino Library Manager):
 *   - MIDI Library by FortySevenEffects
 *   - FastLED by Daniel Garcia
 *
 * Placa: Arduino Leonardo ou SparkFun Pro Micro (5V, 16MHz)
 * LED data: pin 6 (mudar LED_PIN se necessário)
 */

#include <MIDI.h>
#include <FastLED.h>

// --- Configuração hardware ---
#define LED_PIN     6
#define NUM_MODULES 4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

#define MIDI_NOTE_MODULE_1  60   // C3
#define MIDI_CHANNEL        1    // 0 = omni (aceita todos os canais)

CRGB modules[NUM_MODULES];

MIDI_CREATE_DEFAULT_INSTANCE();

// Cores por módulo (HSV) — usadas em modo nota
const uint8_t MODULE_HUE[NUM_MODULES] = { 0, 32, 64, 96 }; // matizes distintos

uint8_t masterBrightness = 255;

// --- MIDI handlers ---

void applyModule(int index, CRGB color) {
  if (index < 0 || index >= NUM_MODULES) return;
  modules[index] = color;
  FastLED.show();
}

void blackout() {
  fill_solid(modules, NUM_MODULES, CRGB::Black);
  FastLED.show();
}

void onNoteOn(byte channel, byte note, byte velocity) {
  if (MIDI_CHANNEL != 0 && channel != MIDI_CHANNEL) return;
  if (velocity == 0) {
    onNoteOff(channel, note, velocity);
    return;
  }

  int idx = note - MIDI_NOTE_MODULE_1;
  if (idx < 0 || idx >= NUM_MODULES) return;

  uint8_t bri = map(velocity, 1, 127, 10, 255);
  modules[idx] = CHSV(MODULE_HUE[idx], 255, bri);
  FastLED.show();
}

void onNoteOff(byte channel, byte note, byte velocity) {
  if (MIDI_CHANNEL != 0 && channel != MIDI_CHANNEL) return;

  int idx = note - MIDI_NOTE_MODULE_1;
  if (idx < 0 || idx >= NUM_MODULES) return;

  modules[idx] = CRGB::Black;
  FastLED.show();
}

// CC 7 = master dimmer
void onControlChange(byte channel, byte cc, byte value) {
  if (MIDI_CHANNEL != 0 && channel != MIDI_CHANNEL) return;

  if (cc == 7) {
    masterBrightness = value;
    FastLED.setBrightness(masterBrightness);
    FastLED.show();
  }

  // CC 20 = selecionar módulo 1-4, CC 21/22/23 = R/G/B (modo técnico)
  // Implementação mínima: usar notas por agora
}

void onProgramChange(byte channel, byte program) {
  if (MIDI_CHANNEL != 0 && channel != MIDI_CHANNEL) return;

  switch (program) {
    case 0:
      blackout();
      break;
    case 1:
      // Warm wash — tons quentes
      for (int i = 0; i < NUM_MODULES; i++) {
        modules[i] = CHSV(32, 180, 200);
      }
      FastLED.show();
      break;
    case 2:
      // Red mood
      for (int i = 0; i < NUM_MODULES; i++) {
        modules[i] = CHSV(0, 255, 220);
      }
      FastLED.show();
      break;
    default:
      break;
  }
}

// --- Setup / loop ---

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(modules, NUM_MODULES);
  FastLED.setBrightness(masterBrightness);
  FastLED.clear(true);

  // Boot test: flash sequencial nos 4 módulos
  for (int i = 0; i < NUM_MODULES; i++) {
    modules[i] = CRGB::White;
    FastLED.show();
    delay(120);
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

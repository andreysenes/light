/*
 * StageMod v0 — Pro Micro
 * - 4× WS2812B (módulos spot, pin 6)
 * - Tubo D15-Woven Magic WS2811 (gradiente / chase, pin 5)
 *
 * Bibliotecas: MIDI Library (FortySevenEffects), FastLED
 *
 * MIDI: USB (padrão) + opcional Serial1 (ESP-01 / bridge sem fio) — ver docs/18-WIRELESS-MIDI.md
 */

#include <MIDI.h>
#include <SerialMIDI.h>
#include <FastLED.h>

// 1 = MIDI USB (programação / cabo). 0 = só serial (show sem USB).
#define ENABLE_USB_MIDI     1
// 1 = MIDI na UART (ESP-01, ZS-040 com firmware serial). Ligação: RX/TX Serial1.
#define ENABLE_SERIAL_MIDI  1
// 115200 = bridge ESP UDP; 31250 = MIDI serial clássico
#define SERIAL_MIDI_BAUD    115200

// --- Módulos spot (4× LED individuais) ---
#define MODULE_PIN    6
#define NUM_MODULES   4

// --- Tubo D15-Woven Magic (manual: IC WS2811, 50 LED/m, corte 20 mm) ---
#define TUBE_PIN      5
#define NUM_TUBE_LEDS 200   // 4 m × 50 LED/m

#define MODULE_LED_TYPE   WS2812B
#define MODULE_COLOR_ORDER GRB
#define TUBE_LED_TYPE     WS2811
#define TUBE_COLOR_ORDER  RGB   // se cores invertidas, trocar para GRB

#define MIDI_NOTE_MODULE_1  60
#define MIDI_CHANNEL        1

CRGB modules[NUM_MODULES];
CRGB tube[NUM_TUBE_LEDS];

uint8_t moduleR[NUM_MODULES];
uint8_t moduleG[NUM_MODULES];
uint8_t moduleB[NUM_MODULES];

#if ENABLE_USB_MIDI
MIDI_CREATE_DEFAULT_INSTANCE();
#endif

#if ENABLE_SERIAL_MIDI
MIDI_CREATE_INSTANCE(SerialMIDI<Serial1>, MIDI_Serial);
#endif

uint8_t masterBrightness = 255;

// --- Tubo: estado e efeitos ---
enum TubeEffect : uint8_t {
  TUBE_OFF = 0,
  TUBE_CHASE = 1,          // cometa com rastro
  TUBE_GRADIENT_WAVE = 2,  // ondas de luz de larguras variadas ( ---  --  - )
  TUBE_RAINBOW = 3,        // gradiente arco-íris estático no tubo
  TUBE_SOLID = 4,
};

TubeEffect tubeEffect = TUBE_OFF;
uint8_t tubeHue = 160;
uint8_t tubeSpeed = 80;       // 0–255
uint8_t tubeDensity = 64;     // comprimento das “manchas” de luz
uint8_t tubeSolidBrightness = 200;

uint16_t tubeAnimOffset = 0;
uint8_t chaseHead = 0;
unsigned long lastAnimMs = 0;

static const uint8_t CC_RGB_MAP[][3] = {
  { 1,  2,  3  },
  { 4,  5,  6  },
  { 9,  10, 11 },
  { 12, 13, 14 },
};

// Tubo: CC 15=efeito 16=matiz 17=velocidade 18=densidade 19=brilho sólido
#define CC_TUBE_EFFECT   15
#define CC_TUBE_HUE      16
#define CC_TUBE_SPEED    17
#define CC_TUBE_DENSITY  18
#define CC_TUBE_SOLID_BRI 19

uint8_t midiToByte(byte value) {
  return (uint8_t)map(value, 0, 127, 0, 255);
}

void showAll() {
  FastLED.show();
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

void tubeBlackout() {
  fill_solid(tube, NUM_TUBE_LEDS, CRGB::Black);
}

// Cometa: cabeça brilhante + rastro que apaga
void renderTubeChase() {
  tubeBlackout();
  uint8_t tailLen = map(tubeDensity, 0, 255, 2, 12);

  for (uint8_t t = 0; t < tailLen; t++) {
    int pos = (int)chaseHead - t;
    if (pos < 0) pos += NUM_TUBE_LEDS;
    if (pos >= NUM_TUBE_LEDS) pos -= NUM_TUBE_LEDS;

    uint8_t bri = 255 - (uint8_t)((uint16_t)t * 255 / tailLen);
    tube[pos] = CHSV(tubeHue, 255, bri);
  }
}

// Ondas de brilho — cria manchas de tamanhos diferentes que se movem:
// visual:  ------    --   ---   -     -----
void renderTubeGradientWave() {
  uint8_t freq = map(tubeDensity, 0, 255, 8, 48);

  for (int i = 0; i < NUM_TUBE_LEDS; i++) {
    uint16_t phase = (uint16_t)i * freq + tubeAnimOffset;
    uint8_t wave = sin8((uint8_t)(phase & 0xFF));
    // Segunda harmônica para variar largura dos “traços”
    uint8_t wave2 = sin8((uint8_t)((phase * 2) & 0xFF));
    uint8_t bri = (uint8_t)((uint16_t)wave * wave2 / 255);
    tube[i] = CHSV(tubeHue, 220, bri);
  }
}

void renderTubeRainbow() {
  for (int i = 0; i < NUM_TUBE_LEDS; i++) {
    uint8_t hue = (uint8_t)((uint16_t)i * 255 / NUM_TUBE_LEDS + tubeHue);
    tube[i] = CHSV(hue, 255, 200);
  }
}

void renderTubeSolid() {
  fill_solid(tube, NUM_TUBE_LEDS, CHSV(tubeHue, 255, tubeSolidBrightness));
}

void renderTube() {
  switch (tubeEffect) {
    case TUBE_OFF:
      tubeBlackout();
      break;
    case TUBE_CHASE:
      renderTubeChase();
      break;
    case TUBE_GRADIENT_WAVE:
      renderTubeGradientWave();
      break;
    case TUBE_RAINBOW:
      renderTubeRainbow();
      break;
    case TUBE_SOLID:
      renderTubeSolid();
      break;
  }
}

void animateTube() {
  if (tubeEffect == TUBE_OFF) return;

  unsigned long now = millis();
  uint16_t interval = map(tubeSpeed, 0, 255, 80, 8);
  if (now - lastAnimMs < interval) return;
  lastAnimMs = now;

  if (tubeEffect == TUBE_CHASE) {
    chaseHead = (chaseHead + 1) % NUM_TUBE_LEDS;
  } else if (tubeEffect == TUBE_GRADIENT_WAVE) {
    tubeAnimOffset = (tubeAnimOffset + map(tubeSpeed, 0, 255, 1, 12)) & 0xFF;
  }

  renderTube();
  showAll();
}

void blackoutAll() {
  fill_solid(modules, NUM_MODULES, CRGB::Black);
  tubeEffect = TUBE_OFF;
  tubeBlackout();
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
    for (int i = 0; i < NUM_MODULES; i++) applyModuleColor(i);
    renderTube();
    showAll();
    return;
  }

  if (cc == CC_TUBE_EFFECT) {
    tubeEffect = (TubeEffect)map(value, 0, 127, 0, TUBE_SOLID);
    renderTube();
    showAll();
    return;
  }
  if (cc == CC_TUBE_HUE) {
    tubeHue = midiToByte(value);
    renderTube();
    showAll();
    return;
  }
  if (cc == CC_TUBE_SPEED) {
    tubeSpeed = midiToByte(value);
    return;
  }
  if (cc == CC_TUBE_DENSITY) {
    tubeDensity = midiToByte(value);
    renderTube();
    showAll();
    return;
  }
  if (cc == CC_TUBE_SOLID_BRI) {
    tubeSolidBrightness = midiToByte(value);
    if (tubeEffect == TUBE_SOLID) {
      renderTube();
      showAll();
    }
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
      blackoutAll();
      break;
    case 1:
      for (int i = 0; i < NUM_MODULES; i++) setModuleRgb(i, 255, 180, 80);
      break;
    case 2:
      for (int i = 0; i < NUM_MODULES; i++) setModuleRgb(i, 255, 0, 0);
      break;
    case 3:
      for (int i = 0; i < NUM_MODULES; i++) setModuleRgb(i, 0, 255, 0);
      break;
    case 4:
      for (int i = 0; i < NUM_MODULES; i++) setModuleRgb(i, 0, 0, 255);
      break;
    case 5:
      for (int i = 0; i < NUM_MODULES; i++) setModuleRgb(i, 255, 0, 255);
      break;
    case 6:
      for (int i = 0; i < NUM_MODULES; i++) setModuleRgb(i, 255, 255, 255);
      break;
    // --- Presets tubo ---
    case 7:
      tubeEffect = TUBE_GRADIENT_WAVE;
      tubeHue = 160;
      tubeSpeed = 120;
      tubeDensity = 80;
      renderTube();
      showAll();
      break;
    case 8:
      tubeEffect = TUBE_CHASE;
      tubeHue = 0;
      tubeSpeed = 150;
      tubeDensity = 100;
      renderTube();
      showAll();
      break;
    case 9:
      tubeEffect = TUBE_RAINBOW;
      renderTube();
      showAll();
      break;
    case 10:
      tubeEffect = TUBE_OFF;
      tubeBlackout();
      showAll();
      break;
    default:
      break;
  }
}

void bootTestTube() {
  tubeEffect = TUBE_GRADIENT_WAVE;
  tubeHue = 96;
  tubeSpeed = 200;
  tubeDensity = 70;

  for (int step = 0; step < NUM_TUBE_LEDS + 16; step++) {
    tubeAnimOffset = (tubeAnimOffset + 14) & 0xFF;
    renderTubeGradientWave();
    showAll();
    delay(35);
  }

  tubeEffect = TUBE_OFF;
  tubeBlackout();
  showAll();
}

void setup() {
  FastLED.addLeds<MODULE_LED_TYPE, MODULE_PIN, MODULE_COLOR_ORDER>(modules, NUM_MODULES);
  FastLED.addLeds<TUBE_LED_TYPE, TUBE_PIN, TUBE_COLOR_ORDER>(tube, NUM_TUBE_LEDS);
  FastLED.setBrightness(masterBrightness);
  FastLED.clear(true);

  const CRGB bootColors[] = { CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::White };
  for (int i = 0; i < NUM_MODULES; i++) {
    modules[i] = bootColors[i];
    showAll();
    delay(150);
    modules[i] = CRGB::Black;
  }

  bootTestTube();

#if ENABLE_SERIAL_MIDI
  Serial1.begin(SERIAL_MIDI_BAUD);
#endif

#if ENABLE_USB_MIDI
  if (MIDI_CHANNEL == 0) {
    MIDI.begin(MIDI_CHANNEL_OMNI);
  } else {
    MIDI.begin(MIDI_CHANNEL);
  }
  MIDI.setHandleNoteOn(onNoteOn);
  MIDI.setHandleNoteOff(onNoteOff);
  MIDI.setHandleControlChange(onControlChange);
  MIDI.setHandleProgramChange(onProgramChange);
#endif

#if ENABLE_SERIAL_MIDI
  if (MIDI_CHANNEL == 0) {
    MIDI_Serial.begin(MIDI_CHANNEL_OMNI);
  } else {
    MIDI_Serial.begin(MIDI_CHANNEL);
  }
  MIDI_Serial.setHandleNoteOn(onNoteOn);
  MIDI_Serial.setHandleNoteOff(onNoteOff);
  MIDI_Serial.setHandleControlChange(onControlChange);
  MIDI_Serial.setHandleProgramChange(onProgramChange);
#endif
}

void loop() {
#if ENABLE_USB_MIDI
  MIDI.read();
#endif
#if ENABLE_SERIAL_MIDI
  MIDI_Serial.read();
#endif
  animateTube();
}

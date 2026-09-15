# Tubo flexível LED — gradiente e chase (v0)

Além dos **4 módulos spot** (1 WS2812B cada), o protótipo v0 suporta um **tubo flexível** com dezenas de LEDs endereçáveis — ideal para efeitos de **gradiente**, **ondas** e **chase** ao longo do comprimento.

## Visual do efeito

O efeito **Gradient Wave** move manchas de luz de larguras diferentes pelo tubo:

```
tempo →
██████          ██    ███   █         █████
  (longo)      (curto)(médio)(ponto)   (longo)
```

Equivalente ao padrão que você descreveu: traços acesos de tamanhos variados deslizando pelo tubo.

## Hardware

| Item | Especificação |
|------|----------------|
| LED | **Fita WS2812B** (60 LED/m ou 30 LED/m) dentro de **tubo silicone** difuso |
| Tensão | **5 V** (mesma fonte dos módulos) |
| Data | **Pin 5** do Pro Micro (separado dos módulos no pin 6) |
| Quantidade | `NUM_TUBE_LEDS` no firmware (padrão **30**) |

### Onde comprar / montar

| Opção | Busca |
|-------|-------|
| Fita + tubo | `WS2812B LED strip` + `silicone diffuser tube 10mm` |
| Pronto | `WS2812B neon flex` / `LED neon tube addressable` |

### Ligação

```
[Fonte 5V] ──┬── módulos (pin 6) + tubo (pin 5)
             └── GND comum

Pro Micro D6 ──► módulos 1–4 (cadeia)
Pro Micro D5 ──► DIN da fita no tubo
```

| Pino Pro Micro | Destino |
|----------------|---------|
| **D6** | 4× módulos spot |
| **D5** | Tubo flexível (fita WS2812B) |

Resistor **470Ω** em cada linha de data (D5 e D6). Capacitor **1000µF** no início de cada alimentação 5V.

### Corrente

| LEDs no tubo | Corrente max ~ |
|--------------|----------------|
| 30 | ~1,8 A |
| 60 | ~3,6 A |

Com 4 módulos + 30 LEDs no tubo: fonte **5V / 3A** recomendada.

## Efeitos no firmware

| ID | Nome | Descrição |
|----|------|-----------|
| 0 | Off | Tubo apagado |
| 1 | **Chase** | Cometa com rastro que corre o tubo |
| 2 | **Gradient Wave** | Ondas de luz de larguras variadas (padrão `--- -- -`) |
| 3 | Rainbow | Arco-íris estático ao longo do tubo |
| 4 | Solid | Cor única em todo o tubo |

## MIDI — controle do tubo

| CC | Função | Valores |
|----|--------|---------|
| **15** | Efeito | 0=off · baixo=chase · médio=wave · alto=rainbow/solid |
| **16** | Matiz (hue) | Cor base do efeito |
| **17** | Velocidade | Animação chase / wave |
| **18** | Densidade | Largura das manchas / tamanho do rastro |
| **19** | Brilho | Modo sólido |

| PC | Preset |
|----|--------|
| **7** | Gradient wave (azul, velocidade média) |
| **8** | Chase vermelho |
| **9** | Rainbow |
| **10** | Tubo off |
| **0** | Blackout (módulos + tubo) |

**CC 7** (master dimmer) afeta módulos e tubo.

## Configurar quantidade de LEDs

Em `promicro-4mod.ino`:

```cpp
#define NUM_TUBE_LEDS 30   // ex: 0,5 m @ 60 LED/m = 30
```

| Comprimento | 60 LED/m | 30 LED/m |
|-------------|----------|----------|
| 0,5 m | 30 | 15 |
| 1 m | 60 | 30 |
| 2 m | 120 | 60 |

## Boot

Após os 4 módulos piscarem R/G/B/W, o tubo executa um **gradient wave** de teste. Se o tubo não estiver ligado, comentar `bootTestTube();` no `setup()`.

## Sem tubo ainda?

- Deixar `NUM_TUBE_LEDS` como está ou definir **0** (requer remover `addLeds` do tubo no código)
- Ou simplesmente não ligar o fio no D5 — módulos spot funcionam normalmente

## v1

Tubo pode evoluir para perfil de palco maior ou segundo barramento RS-485 — por ora é saída direta do Pro Micro.

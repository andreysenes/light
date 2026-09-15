# Resumo das decisões — leitura rápida

## LEDs: sua ideia está certa

Use **um LED por cor** (3× 3 W vermelho, verde, azul), não um RGB 10 W caro.

| | 3× LED mono 3 W | RGB 10 W integrado |
|---|----------------|-------------------|
| Preço | ~US$ 1,50/módulo | ~US$ 5–8 |
| Controle | 3 MOSFETs (simples) | 3 MOSFETs (igual) |
| Branco | RGB mix + WW opcional | RGB mix |
| Onde comprar | AliExpress / LCSC | Difícil com fios separados |

**Star RGB 3 W** (ânodo comum, 3 catodos) é um meio-termo barato para protótipo — elétrico igual a 3 mono no mesmo heatsink.

## Eletrônica: como o vídeo, mas com fonte externa

```
DAW ──USB MIDI──► ESP32 ──GPIO──► MOSFET ──► LED 3W
                                      ▲
                                 Fonte 24V (NÃO o ESP)
```

O vídeo [ESP + MOSFET](https://www.youtube.com/watch?v=HSeckw3VLy8) ensina o **chaveamento**; para palco a **energia vem de fonte 24 V** e corrente limitada por **PT4115** ou resistor calculado.

## Módulos acopláveis

Cada módulo: **IN** e **OUT** com 4 fios:

1. V+ 24 V  
2. GND  
3. RS-485 A  
4. RS-485 B  

```
Fonte ─ M1 ─ M2 ─ M3 ─ M4 ──┬─ M5
                             ├─ M6
                             └─ M9 ─ M10 ─ ...
```

Splits = cabo T ou segunda saída na distro.

## Alimentação barata e segura

- **1 fonte** 24 V central (ex. 10 A para ~8 módulos).
- **Fusível** na entrada + polyfuse em cada módulo.
- **Injeção** de V+ no meio do ramo se > 4 módulos ou cabo longo.
- Nunca alimentar LED de palco pelo 5 V do ESP.

## MIDI / DAW

- Master **ESP32-S3** com USB MIDI.
- Mapear notas ou CC para RGB por módulo.
- Satélites só escutam RS-485 (sem USB).

## Primeira compra (mínimo)

| Item | Qtd |
|------|-----|
| ESP32-S3 DevKit | 1 |
| LED 3 W R, G, B (ou 1 star RGB) | 1 set |
| IRLB8721 | 3 |
| Módulo PT4115 | 3 |
| Fonte 24 V 3 A | 1 |
| Heatsink pequeno | 1 |

Custo ~**US$ 30** para validar antes de comprar 12 módulos.

## Próximo passo

Montar **1 módulo** em breadboard → ver [08-ROADMAP.md](08-ROADMAP.md).

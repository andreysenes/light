# BOM — Lista de materiais

Preços aproximados em **USD** (AliExpress/LCSC) para planejamento. Ajustar para fornecedor local (Brasil: FilipeFlop, Usinainfo, Mouser BR).

## Kit protótipo — 1 módulo (validação)

| Qty | Item | Ref / busca | ~US$ | Notas |
|-----|------|-------------|------|-------|
| 1 | ESP32-S3 DevKit USB | ESP32-S3-WROOM-1 | 6 | Master + primeiro módulo |
| 3 | LED 3 W vermelho star | 620 nm 3W red star | 0,45 | |
| 3 | LED 3 W verde star | 520 nm | 0,45 | |
| 3 | LED 3 W azul star | 460 nm | 0,45 | *Ou 1× star RGB 3 W* |
| 3 | MOSFET N logic-level | **IRLB8721** TO-220 | 1,50 | |
| 3 | Resistor gate | 100 Ω 1/4 W | 0,10 | |
| 3 | Resistor pull-down | 10 kΩ | 0,10 | |
| 3 | Módulo PT4115 CC | 350 mA buck LED driver | 1,00 | Ajustar corrente |
| 1 | Buck 24→5 V | Mini560 ou LM2596 | 0,80 | ESP |
| 1 | Fonte 24 V 3 A | Mean Well ou genérica | 12 | Bancada |
| 1 | Heatsink + pasta térmica | 40×40 mm | 2 | |
| — | Fios, breadboard | — | 5 | |
| | **Subtotal 1 módulo** | | **~30** | Sem cabo de acoplamento |

## Módulo satélite (produção DIY, por unidade)

| Qty | Item | Ref | ~US$ |
|-----|------|-----|------|
| 1 | ESP32-C3 SuperMini | ou C3-MINI-1 | 2,50 |
| 1 | MAX485 ou SP3485 | SO-8 | 0,50 |
| 3–4 | IRLB8721 ou AO3400A | conforme PCB | 1,50 |
| 3–4 | PT4115 module | 1 por canal | 1,00 |
| 1 | Buck 24→5 V | | 0,80 |
| 1 | Polyfuse 1,5 A | | 0,10 |
| 1 | TVS SMBJ24A | proteção entrada | 0,15 |
| 3 | LED 3 W RGB mono set | ver doc LEDs | 1,50 |
| 1 | Heatsink perfil | 50 mm | 1,50 |
| 2 | Conector 4 pin GX16 | IN + OUT | 3,00 |
| 1 | DIP-3 endereço | opcional | 0,20 |
| 1 | PCB custom | JLCPCB 5 pcs | 2,00* |
| | **Por módulo** | | **~15–18** |

\* PCB amortizada em lote de 5–10 placas.

## Master adicional (se separado do primeiro spot)

| Qty | Item | ~US$ |
|-----|------|------|
| 1 | ESP32-S3 DevKit | 6 |
| 1 | MAX485 | 0,50 |
| 1 | Buck 24→5 V | 0,80 |
| 1 | Caixa ABS | 3 |
| | **Total** | **~10** |

## Sistema 12 módulos + alimentação

| Categoria | Itens | ~US$ |
|-----------|-------|------|
| Módulos luz | 12× satélite @ 16 | 192 |
| Master | 1× (pode ser Mód 1) | 0–10 |
| Fonte | 24 V 15 A | 30 |
| Distribuição | caixa, fusíveis, cabos | 25 |
| Cabos acoplamento | 11× 1 m 4 condutores + XT30 | 35 |
| Reserva LEDs/MOSFET | 20 % | 40 |
| | **Total estimado** | **~320–350** |

Comparável a 2–3 PAR LED comerciais, com vantagem de layout modular customizado.

## Onde comprar (sugestão)

| Região | Loja |
|--------|------|
| Brasil | FilipeFlop, Usinainfo, Baú da Eletrônica |
| Global | LCSC, Mouser, DigiKey |
| Barato lote | AliExpress (LEDs, MOSFET, PT4115) |

## Alternativas de custo

| Peça premium | Alternativa barata | Trade-off |
|--------------|-------------------|-----------|
| Mean Well 24 V | Fonte genérica 24 V 10 A | Ripple, vida útil |
| GX16 | XT30 + cabo RJ45 só RS-485 | Menos integrado |
| ESP32-C3 por módulo | 1 master + ATtiny PWM slaves | Menos modular, firmware complexo |
| PT4115 | Resistor + MOSFET @ 12 V | Calor, ineficiência |

## Ferragens mecânicas

| Item | Uso |
|------|-----|
| Parafuso M3 + espaçador | Fixar PCB no heatsink |
| Perfil alumínio 20×20 | Montagem em truss DIY |
| Abraçadeira nylon | Cabos |
| Grade plástica | Proteção LED |

## Checklist antes de comprar em lote

- [ ] 1 módulo protótipo estável 2 h contínuas
- [ ] Temperatura heatsink < 60 °C ao toque
- [ ] MIDI mapeado no DAW usado
- [ ] RS-485 com 3 módulos em cadeia sem erro CRC
- [ ] Queda de tensão no último módulo < 1 V

# Lista de compras — itens restantes

**Já em mãos (não comprar de novo):** Pro Micro, ZS-040, fonte 5 V 10 A, 4 módulos WS2812B (8 LEDs cada), tubo 4 m (200 LED).

---

## Obrigatório — Medusa (cabeça)

| # | Qty | Item | Busca AliExpress / loja |
|---|-----|------|-------------------------|
| 1 | 1 | Caixa ABS grande | `ABS project box 150x100` (cabe C14 + fonte + placas) |
| 2 | 1 | **C14** painel IEC | `IEC320 C14 power inlet panel mount` |
| 3 | 1 | Cabo **C13** → tomada | `C13 power cord` (ou reaproveitar de PC) |
| 4 | 1 | Suporte fusível **5×20 mm** | `fuse holder 5x20mm panel` |
| 5 | 1 | Fusível **2 A** retardado | `5x20 fuse 2A slow blow` |
| 6 | 2 | XLR **fêmea** painel | `XLR female 3 pin panel mount` — **MOD** + **TUBO** |
| 7 | 1 | USB **micro** painel | `micro USB panel mount socket` |
| 8 | 2 | Resistor **470 Ω** 1/4 W | `470 ohm resistor kit` (Medusa D5 + D6) |
| 9 | 1 | Capacitor **1000 µF** 16 V | `1000uf 16V electrolytic` (barramento 5 V Medusa) |
| 10 | 1 | Par **1 kΩ + 2 kΩ** | Divisor TX Pro Micro → RX ZS-040 (se precisar) |
| 11 | — | Fio **AWG 18** verm./preto | Barramento 5 V / GND na caixa |
| 12 | — | Fio **AWG 22** verde/branco | D5, D6 → XLR |

## Obrigatório — cada módulo spot (×4)

| # | Qty total | Item | Onde |
|---|-----------|------|------|
| 13 | **4** | Resistor **470 Ω** | DATA IN → DIN (1 por módulo) |
| 14 | **4** | Cap **470 µF–1000 µF** ≥6,3 V | 5 V/GND no LED (1 por módulo) |
| 15 | **4** | XLR **fêmea** painel (IN) | Entrada do módulo |
| 16 | **4** | XLR **macho** painel (OUT) | Saída para o próximo módulo |

**Resumo passivos:** kit **470 Ω** (mín. **6** un.) + **5** capacitores eletrolíticos.

## Cabos palco (tentáculos)

| # | Qty | Item | Notas |
|---|-----|------|--------|
| 17 | 1 | Cabo XLR **Medusa → Mod1** | 1–2 m, 3 condutores + malha GND |
| 18 | 1 | Cabo XLR **Medusa → tubo** | 3–5 m |
| 19 | 3 | Cabo XLR **Mod → Mod** | 0,3–1 m (ou montar com `microphone cable`) |
| 20 | 0–1 | Cabo só **5 V/GND** (opc.) | Injeção no **meio** do tubo 4 m |

Montar cabo: `microphone cable 2 core shield` — vermelho=5 V, preto=GND, verde=DATA, malha=GND.

## Opcional (recomendado)

| # | Item | Motivo |
|---|------|--------|
| 21 | XLR fêmea extra (**INJ**) | Só 5 V/GND para reforço no tubo |
| 22 | **AMS1117-3.3** | Só se o ZS-040 **não** aceitar 5 V no VCC |
| 23 | LED indicador 5 V + resistor | “Power ON” na Medusa |
| 24 | Chave **rocker** na entrada AC | Desligar rig sem puxar C13 |
| 25 | Terminais **spade** / olhal | C14 → fios da fonte (mais seguro que solda solta) |
| 26 | Espaçador **M3** + parafusos | Fixar Pro Micro e fonte na caixa |

---

## Checklist rápido antes de pedir

- [ ] **6×** 470 Ω (4 módulos + 2 Medusa) — comprar kit 100
- [ ] **5×** cap eletrolítico (4 módulos + 1 Medusa)
- [ ] **8×** XLR painel nos módulos (4 IN + 4 OUT) + **2×** na Medusa (MOD, TUBO)
- [ ] Caixa + C14 + fusível + USB painel
- [ ] Cabos ou material para **5** cabos XLR

## Estimativa de custo (referência)

| Grupo | ~US$ |
|-------|------|
| Caixa + C14 + fusível + USB | 15–25 |
| XLR painel (10 peças) | 10–20 |
| Resistores + caps + fios | 5–10 |
| Cabos prontos (ou DIY) | 15–40 |
| **Total** | **~45–95** |

Envio Brasil: variável (Choice / Standard).

## Referências

- Montagem: [17-CABECA-MEDUSA.md](17-CABECA-MEDUSA.md)
- Inventário: [20-INVENTARIO-HARDWARE.md](20-INVENTARIO-HARDWARE.md)
- AliExpress detalhado: [15-ALIEXPRESS-BOM.md](15-ALIEXPRESS-BOM.md)

# MIDI sem fio — Medusa (ZS-040 + Pro Micro)

Na **Medusa** o rádio é o **ZS-040** (BLE UART). O **Pro Micro** aceita **dois caminhos ao mesmo tempo**:

| Modo | Quando | Latência típica |
|------|--------|-----------------|
| **USB** no Pro Micro | Cabeça **perto** do PC (ensaio, gravação) | ~1–3 ms |
| **ZS-040** (Bluetooth) | Cabeça **no palco**, sem cabo USB | ~15–40 ms |

Para **luz com música**, **15–40 ms** costuma ser aceitável: em **120 BPM**, uma semínima ≈ **125 ms** — o atraso do BT fica **abaixo de um 16º** perceptível na maioria das cenas. Hits muito secos no beat podem preferir **USB** naquele dia.

Firmware lê **USB e Serial1 em paralelo** — não precisa recompilar ao trocar; só **não envie MIDI duplicado** da DAW para as duas portas ao mesmo tempo.

## Arquitetura

```
                    ┌─ USB MIDI (opcional, cabo curto)
DAW ──► [PC] ───────┤
        │           │
        └── BT serial ──► ZS-040 ── UART ──► Pro Micro Serial1 ──► LEDs
                              ▲
                         VCC (5V breakout comum)
```

| Camada | Função |
|--------|--------|
| PC | Parear BT; porta **COM** serial; bridge **MIDI → serial** (Hairless, etc.) |
| ZS-040 | BLE transparente UART |
| Pro Micro | `MIDI.read()` (USB) + `MIDI_Serial.read()` (ZS) |

## Por que ZS-040 na Medusa

| Vantagem | Detalhe |
|----------|---------|
| **Alimentação simples** | Muitos breakouts **ZS-040/HM-10** aceitam **5 V** no VCC (regulador onboard) — mesmo barramento da Medusa, sem ESP + AMS1117 |
| **PC** | Bluetooth nativo no notebook — sem script UDP |
| **Montagem** | UART + 4 fios; sem firmware no módulo BT |

**Alternativa** (não usada na Medusa v0): [ESP-01 + UDP](../firmware/esp01-midi-bridge/) — menor latência, mais eletrônica.

## Ligação na Medusa

### Alimentação

| Módulo | Alimentação |
|--------|-------------|
| Pro Micro | **5 V** do barramento |
| ZS-040 | **5 V** no breakout **se** o vendedor indicar 3,3–6 V / “5V tolerant”; senão **3,3 V** do mesmo 5 V via AMS1117 |

Confirme no seu módulo: pinos **VCC / GND / TX / RX** — não inverter.

### UART (Serial1)

| Pro Micro | ZS-040 |
|-----------|--------|
| **RX (D0)** | **TX** do módulo |
| **TX (D1)** | **RX** do módulo (divisor 5 V→3,3 V se lógica 3,3 V) |
| **GND** | **GND** |

Se o breakout já nivelar TX para o Arduino, o divisor no RX do ZS-040 pode ser opcional.

### Painel

```
[USB micro]  ← Pro Micro: programação + MIDI com cabo
[MOD][TUBO][INJ]  ← XLR
ZS-040 dentro da caixa (antena para fora do metal)
```

## Configurar baud do ZS-040

Padrão de fábrica costuma ser **9600**. Recomendado subir para **115200** (menos atraso em fila serial).

1. Ligue o ZS-040 num adaptador USB-UART (3,3 V ou 5 V conforme o módulo).
2. Terminal serial **9600**, sem newline ou com `\r\n` conforme o clone.
3. Comandos AT (HM-10 / ZS-040 compatível):

```
AT
AT+BAUD4
```

`BAUD4` ≈ **115200** na tabela HM-10. Reinicie o módulo.

4. No `promicro-4mod.ino`:

```cpp
#define ENABLE_USB_MIDI     1
#define ENABLE_SERIAL_MIDI  1
#define SERIAL_MIDI_BAUD    115200   // ou 9600 se não alterou o AT
```

## PC — Bluetooth → MIDI

1. **Parear** o ZS-040 no sistema (nome tipo `HMSoft`, `BT04`, etc.).
2. Anotar a porta **COM** (Windows) ou `/dev/cu.*` (macOS).
3. Usar um bridge **MIDI ↔ serial** na mesma baud do módulo, por exemplo:
   - [Hairless MIDI](https://projectgus.github.io/hairless-midiserial/) (Win/mac/Linux)
   - Ou equivalente que envie bytes MIDI crus na COM

4. Na DAW: saída MIDI → porta virtual do bridge → **COM do ZS-040**.

Não use phantom power nem entrada de microfone — é **UART digital**.

## USB direto (cabeça perto)

1. Cabo **USB micro** no Pro Micro.
2. DAW: dispositivo MIDI **Arduino / Pro Micro** (nativo USB MIDI).
3. Pode **desligar** o bridge Bluetooth na DAW para evitar mensagens duplicadas.
4. Firmware: manter `ENABLE_USB_MIDI 1` (já é o padrão).

## Latência — expectativa honesta

| Caminho | Ordem de grandeza | Uso |
|---------|-------------------|-----|
| USB | 1–3 ms | Ensaio, cabeça ao lado do notebook |
| ZS-040 BLE | 15–40 ms | Show, rig longe do PC |
| Jitter BT | Ocasional pico | Evitar flood de CC; preferir mudanças de cor em blocos |

Iluminação de palco raramente precisa de sub-5 ms; **sincronizar com música** em BPM humanos costuma funcionar bem com BT se a DAW já compensa latência de áudio (não a de luz).

## Checklist

- [ ] ZS-040 pareado; COM abre sem erro
- [ ] Baud **igual** no AT, no bridge e em `SERIAL_MIDI_BAUD`
- [ ] `MIDI_CHANNEL` = canal da DAW (padrão **1**)
- [ ] Teste **CC1** antes do rig completo
- [ ] Com USB ligado: **uma** fonte MIDI ativa na DAW

## Referências

- [17-CABECA-MEDUSA.md](17-CABECA-MEDUSA.md)
- [05-MIDI-DAW.md](05-MIDI-DAW.md)
- Firmware Pro Micro: [promicro-4mod.ino](../firmware/promicro-4mod/promicro-4mod.ino)
- Alternativa Wi‑Fi: [esp01-midi-bridge](../firmware/esp01-midi-bridge/) (opcional)

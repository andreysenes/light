# Cablagem — energia P4 + cabo de dados separado

Para **baratear**, o StageMod **não** usa cabo especial 5 vias. São **dois chicotes independentes** em cada ligação:

| Chicote | Função | Conector | Cabo comum |
|---------|--------|----------|------------|
| **Energia** | 24 V + GND | **P4** (DC barrel) | Fio 2× AWG18 + plug P4 macho/fêmea |
| **Dados** | RS-485 A / B | **RJ45** | Patch **Cat5e** (um par trançado) |

O **GND de dados** é o mesmo GND da alimentação — ligado na PCB do módulo (não precisa de fio extra no cabo de rede se o par RS-485 referencia o GND da fonte via módulo).

## Por que separar

| Cabo único GX16-5 | P4 + RJ45 |
|-------------------|-----------|
| Conector aviação ~US$ 2/par | P4 ~US$ 0,15 + RJ45 ~US$ 0,20 |
| Cabo 5 condutores especial | Sobra de **Cat5e** + fio silicone 2× |
| Um erro mistura V+ com dados | Energia e dados fisicamente separados |
| Difícil de repor em campo | **P4 e RJ45 em qualquer loja** |

## Energia — plug P4

### Padrão adotado

| Item | Especificação |
|------|----------------|
| Conector | **DC barrel 5,5 mm × 2,1 mm** (P4 comum) |
| Polaridade | **Centro = V+** · Externo = GND |
| Proteção anti-reverso | **Só na Cabeça (P4 OUT)** — única fonte do rig — ver [03-ELETRONICA.md](03-ELETRONICA.md) |
| Tensão | 24 V DC |
| Corrente por ligação P4 | ≤ **2 A** contínuo (patch entre 2 módulos) |

> P4 de CCTV/fonte notebook aguenta bem ~1,2 A por módulo. **Não** passar 10 A do rig inteiro por uma cadeia longa só de P4 — usar **distro** com fio grosso e várias derivações P4.

### Por módulo (pass-through)

```
[P4 IN centro] ── V+ ── polyfuse 2A ──┬── drivers
[P4 IN casco]  ── GND ───────────────┤
[P4 OUT]       ── (pass-through) ────┘
```

Anti-reverso **não** vai no módulo — apenas **polyfuse 2 A** no IN.

Entre módulos: cabo **P4 macho → macho** (extensão DC barata) ou **macho → fêmea** conforme o que estiver no módulo.

```
Cabeça/Fonte ──P4──► Mód1 IN ── (bus interno) ── Mód1 OUT ──P4──► Mód2 IN ── ...
```

### Cabo de energia DIY

| Trecho | Condutor | Conector |
|--------|----------|----------|
| Patch módulo→módulo | 2× **AWG18** silicone 30–50 cm | P4 macho nos dois lados |
| Fonte → distro | AWG16 | P4 ou borne |
| Distro → primeiro módulo | AWG18 | P4 |

**Custo patch energia:** ~US$ 0,50–1,00 (fio + 2 plugs P4).

## Dados — cabo de rede simples

### Padrão adotado

| Item | Especificação |
|------|----------------|
| Cabo | **Cat5e** (patch ou sobra) |
| Conector | **RJ45** 8P8C |
| Protocolo | RS-485 half-duplex |
| Par usado | **Pin 4 + 5** (par azul) = D+ / D− *ou* pin 1 + 2 (par laranja) — **fixar no projeto e não mudar** |

### Pinagem RJ45 StageMod (T568B — par azul = RS-485)

| Pin | Cor T568B | Sinal |
|-----|-----------|-------|
| 4 | Azul | **D+** (RS-485 A) |
| 5 | Azul/branco | **D−** (RS-485 B) |
| Outros | — | NC (reserva futura) |

GND da RS-485 = **GND do P4** no módulo (ligação na PCB, não no RJ45).

### Pass-through no módulo

```
[RJ45 IN]  pin4 ──────────────── pin4  [RJ45 OUT]
           pin5 ──────────────── pin5
           (ligação direta, sem MAX485 no caminho dos fios)
           
MAX485 do módulo: A/B ligados ao par 4-5 do IN (stub curto na PCB)
```

Cabo entre módulos: **patch Cat5e** qualquer (0,3–1 m).

**Custo patch dados:** ~US$ 0,30–0,80 (cabo + 2 RJ45 se crimpado em casa).

## Ligação completa entre dois módulos

```
Módulo 1                          Módulo 2
┌─────────────────┐              ┌─────────────────┐
│ P4 IN    P4 OUT │── cabo P4 ──►│ P4 IN    P4 OUT │
│ RJ45 IN RJ45 OUT│── Cat5e ────►│ RJ45 IN RJ45 OUT│
└─────────────────┘              └─────────────────┘
```

Dois cabos por salto — ainda **muito mais barato** que GX16-5 + cabo 5 vias.

## Cabeça (Head Unit) — única fonte + proteção

| Conector | Função |
|----------|--------|
| **P4 IN** | Fonte 24 V (centro +) |
| **P4 OUT** | **Saída protegida** → toda a cadeia de módulos |
| **RJ45** | RS-485 → M1 |
| **USB** | MIDI / DAW |

```
Fonte ──► P4 IN [Cabeça: P-MOS anti-reverso] ──► P4 OUT ──► M1 ──► M2 ──► ...
```

| Item na Cabeça | Especificação |
|----------------|---------------|
| Anti-reverso | **P-MOS IRF9540N** (TO-220) no tronco de saída |
| Após proteção | Polyfuse **10 A** + TVS SMBJ24A |
| Buck ESP | Alimentado do barramento **já protegido** |

Detalhe do circuito: [03-ELETRONICA.md](03-ELETRONICA.md).

**Teste:** inverter cabo na fonte ou no P4 OUT → corrente ≈ 0 em todo o rig.

## Split em T

Dois adaptadores baratos:

| Adaptador | Tipo | Função |
|-----------|------|--------|
| **T-P4** | 1 P4 fêmea → 2 P4 fêmea | Ramo de energia |
| **T-RJ45** | 1 RJ45 → 2 RJ45 (pin 4-5 em paralelo) | Ramo de dados |

DIY: soquete RJ45 triplo ou cabo Y Cat5e. Para palco ≤ 12 módulos costuma bastar.

## Terminação RS-485

Resistor **120 Ω** entre D+ e D− no **último** módulo de cada ramo longo (jumper na PCB, no par 4-5).

## Identificação

| Etiqueta | Significado |
|----------|-------------|
| Fita **vermelha** no P4 | Lado que vem da fonte / V+ |
| Cabo **azul** ou curto | Dados (RJ45) |
| Cabo **preto** grosso | Energia (P4) |

## Limites e cuidados

| Risco | Mitigação |
|-------|-----------|
| P4 invertido na fonte/OUT | **Anti-reverso na Cabeça** bloqueia; etiqueta vermelha no centro + |
| P4 invertido entre módulos | Evitar com cabos certificados; módulos não têm anti-reverso |
| Corrente alta num P4 só | Máx. ~2 A por patch; distro com AWG16 |
| Ruído RS-485 | Par trançado Cat5e; não enrolar dados junto do P4 por metros |
| GND flutuante | GND P4 = GND MAX485 em cada módulo |

## Checklist montagem

- [ ] P4: centro = +24 V em todos os cabos
- [ ] Cabeça: cabo invertido na fonte/OUT → corrente **≈ 0 A** em todo o rig
- [ ] RJ45: pin 4-5 contínuo IN→OUT em cada módulo
- [ ] Sem curto V+ ↔ GND na entrada P4
- [ ] Terminação 120 Ω só no fim do ramo dados
- [ ] Cabo Cat5e não precisa ser blindado para < 15 m

## Comparativo de custo (1 salto módulo→módulo)

| Item | GX16-5 (antigo) | P4 + RJ45 |
|------|-----------------|-----------|
| Conectores | ~US$ 4 | ~US$ 0,35 |
| Cabo | ~US$ 3 | ~US$ 0,40 |
| **Total / salto** | **~US$ 7** | **~US$ 0,75** |

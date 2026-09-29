# Módulo spot StageMod v0 — impressão 3D

Coluna em **U** com **difusor frontal recuado** e **tampa inferior** para dois XLR (IN fêmea / OUT macho), alinhado ao visual de referência do projeto.

## Arquivos

| Arquivo | Descrição |
|---------|-----------|
| `stagemod_spot_v0.scad` | Modelo paramétrico (OpenSCAD) |
| `stl/spot_body.stl` | Corpo (U + pés + calço LED) |
| `stl/spot_diffuser.stl` | Painel difusor |
| `stl/spot_bottom_plate.stl` | Tampa inferior (XLR) |
| `stl/spot_led_clip.stl` | Clipe opcional para fita |

Documentação de montagem elétrica: [docs/22-MANUAL-MONTAGEM.md](../../docs/22-MANUAL-MONTAGEM.md).  
Guia completo CAD: [docs/23-MODULO-SPOT-3D.md](../../docs/23-MODULO-SPOT-3D.md).

## Regenerar STL

```bash
./export-stl.sh
```

Requer [OpenSCAD](https://openscad.org/) 2021+.

## Ajuste rápido

No topo de `stagemod_spot_v0.scad`:

- `led_pitch` / `led_count` — deve bater com o seu PCB de 8× WS2812B  
- `xlr_hole_d` — medir o furo do conector XLR painel que você comprou  
- `outer_w`, `total_h` — escala estética

## Impressão sugerida

| Peça | Material | Notas |
|------|----------|--------|
| Corpo + tampa | PETG ou ABS | 0,2 mm, 3 perímetros, 20% infill |
| Difusor | PETG branco natural ou PLA branco | 0,12–0,2 mm; 2–4 perímetros; **100% infill** ou 4–6 paredes para difundir |
| Clipe | PETG | Opcional |

Orientação: corpo **deitado** (frente para cima ou costas na mesa) para boa resistência dos pés.

## Montagem (resumo)

1. Soldar LEDs e XLR conforme manual (sem caps/resistores).  
2. Encaixar PCB no calço interno; fios pela canaleta até a tampa.  
3. Parafusar XLR na `bottom_plate`; parafusar tampa no corpo (M3 × 10).  
4. Encaixar difusor na frente; 4× M3 × 8 (laterais do painel, opcional os da coluna lateral).  
5. Etiquetar **MOD 1…4**.

// StageMod v0 — módulo spot (corpo impresso 3D)
// Design: coluna em U, difusor frontal recuado, pés laterais, tampa inferior (XLR).
// Exportar: ./export-stl.sh  ou  openscad -D PART="body" -o stl/spot_body.stl stagemod_spot_v0.scad

PART = "preview"; // preview | body | diffuser | bottom_plate | led_clip

// --- Dimensões gerais (mm) ---
outer_w        = 48;      // largura frontal
outer_d        = 34;      // profundidade (frente → fundo)
total_h        = 300;     // altura total incluindo pés
wall           = 2.4;     // parede (FDM 0,4 mm × 6)
foot_h         = 10;      // altura dos pés
foot_w         = 12;      // largura de cada pé (parede lateral)
foot_front_gap = 6;       // pé não chega à frente (estética da referência)

// Difusor
diffuser_thick    = 2.5;
diffuser_recess   = 4.5;  // recuo em relação à borda frontal
diffuser_clear    = 0.35; // folga lateral

// LEDs (ajuste ao seu PCB / fita)
led_count      = 8;
led_pitch      = 10.0;    // centro a centro (mm) — fita 100 LED/m ≈ 10 mm
led_pcb_w      = 10.0;    // largura do breakout / fita
led_pcb_thick  = 2.0;

// Fixação
m3_hole_d      = 3.2;
m3_boss_od     = 6.5;
m3_boss_h      = 8;

// XLR painel (furo circular simplificado; ajuste ao conector real)
xlr_hole_d     = 23.0;
xlr_inset_y    = 10;      // do fundo da peça para o centro do furo

$fn = 48;

inner_w = outer_w - 2 * wall;
inner_d = outer_d - wall - diffuser_recess - diffuser_thick - 0.5;

led_strip_len = (led_count - 1) * led_pitch + led_pcb_w;
diffuser_h = led_strip_len + 50; // margem acima/abaixo do LED
diffuser_y0 = (total_h - foot_h - diffuser_h) / 2; // centrado na área útil

function screw_boss() =
  cylinder(h = m3_boss_h, d = m3_boss_od, $fn = 24);

module spot_feet() {
  for (x = [0, outer_w - foot_w])
    translate([x, foot_front_gap, 0])
      cube([foot_w, outer_d - foot_front_gap, foot_h], center = false);
}

module spot_shell_solid() {
  translate([0, 0, foot_h])
    cube([outer_w, outer_d, total_h - foot_h], center = false);
  spot_feet();
}

module inner_cavity() {
  // câmara interna (atrás do difusor)
  translate([wall, diffuser_recess + diffuser_thick + 0.2, foot_h + wall])
    cube([
      inner_w,
      inner_d,
      total_h - foot_h - 2 * wall - 3
    ], center = false);

  // slot frontal para o difusor
  translate([
    wall + diffuser_clear,
    wall * 0.5,
    foot_h + diffuser_y0
  ])
    cube([
      inner_w - 2 * diffuser_clear,
      diffuser_recess + diffuser_thick + 1,
      diffuser_h
    ], center = false);
}

module diffuser_screw_holes() {
  // dois parafusos na base do difusor (como na referência)
  for (z = [foot_h + diffuser_y0 + 8, foot_h + diffuser_y0 + diffuser_h - 8]) {
    for (x = [outer_w * 0.28, outer_w * 0.72]) {
      translate([x, outer_d / 2, z])
        rotate([90, 0, 0])
          cylinder(h = outer_d + 2, d = m3_hole_d, center = true);
    }
  }
}

module side_boss_holes() {
  // coluna de parafusos na lateral (decorativo / opcional reforço)
  for (z = [foot_h + 40, foot_h + 70, foot_h + 100, foot_h + 130]) {
    translate([outer_w - wall / 2, outer_d * 0.35, z])
      rotate([0, 90, 0])
        cylinder(h = wall + 4, d = m3_hole_d, center = true);
  }
  translate([outer_w - wall / 2, outer_d * 0.35, total_h - 18])
    rotate([0, 90, 0])
      cylinder(h = wall + 4, d = m3_hole_d, center = true);
}

module cable_exit() {
  translate([outer_w / 2, outer_d - wall - 1, foot_h + 6])
    rotate([90, 0, 0])
      cylinder(h = wall + 6, d = 7, center = true);
}

module body() {
  difference() {
    spot_shell_solid();
    inner_cavity();
    diffuser_screw_holes();
    side_boss_holes();
    cable_exit();
    // abertura para tampa inferior
    translate([wall + 2, wall + 2, foot_h - 0.01])
      cube([outer_w - 2 * wall - 4, outer_d - 2 * wall - 4, 3.5], center = false);
  }

  // calço interno para PCB de LEDs (centralizado na largura)
  led_x = outer_w / 2 - led_pcb_w / 2;
  led_z0 = foot_h + diffuser_y0 + (diffuser_h - led_strip_len) / 2;
  translate([led_x, diffuser_recess + diffuser_thick + 1.2, led_z0])
    cube([led_pcb_w, 4, led_strip_len], center = false);

  // canaleta de fios até a base
  translate([outer_w / 2 - 3, diffuser_recess + diffuser_thick + 1, foot_h])
    cube([6, inner_d * 0.6, led_z0 - foot_h + 5], center = false);
}

module diffuser_panel() {
  w = inner_w - 2 * diffuser_clear;
  translate([wall + diffuser_clear, 0, 0])
    cube([w, diffuser_thick, diffuser_h], center = false);
}

module bottom_plate() {
  plate_h = 3;
  difference() {
    translate([-2, -2, 0])
      cube([outer_w + 4, outer_d + 4, plate_h], center = false);
    // encaixe no corpo
    translate([wall, wall, -0.01])
      cube([outer_w - 2 * wall, outer_d - 2 * wall, plate_h + 0.5], center = false);
    // XLR IN (esquerda) e OUT (direita) — vista de baixo, frente = +Y
    for (x = [outer_w * 0.25, outer_w * 0.75]) {
      translate([x, outer_d - xlr_inset_y, -0.01])
        cylinder(h = plate_h + 2, d = xlr_hole_d, $fn = 64);
    }
    // furos M3 na tampa → corpo
    for (xy = [[8, 8], [outer_w - 8, 8], [8, outer_d - 8], [outer_w - 8, outer_d - 8]]) {
      translate([xy[0], xy[1], -0.01])
        cylinder(h = plate_h + 2, d = m3_hole_d, $fn = 24);
    }
    translate([outer_w / 2, outer_d / 2, -0.01])
      cylinder(h = plate_h + 2, d = 8, $fn = 32); // passagem cabos
  }
}

module led_clip() {
  // Clipe opcional (2×) para prender fita LED — imprimir se não usar calço integrado
  difference() {
    cube([led_pcb_w + 4, 8, 12], center = false);
    translate([2, 2, 2])
      cube([led_pcb_w, 6, 10], center = false);
    translate([led_pcb_w / 2 + 2, 4, -0.01])
      cylinder(h = 3, d = m3_hole_d, $fn = 24);
  }
}

module preview() {
  color("Gainsboro") body();
  translate([wall + diffuser_clear, -diffuser_recess - diffuser_thick, foot_h + diffuser_y0])
    color("White", 0.85) diffuser_panel();
  translate([0, 0, -3])
    color("DimGray") bottom_plate();
}

if (PART == "body") body();
else if (PART == "diffuser") diffuser_panel();
else if (PART == "bottom_plate") bottom_plate();
else if (PART == "led_clip") led_clip();
else preview();

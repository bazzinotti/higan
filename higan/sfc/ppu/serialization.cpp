auto PPUcounter::serialize(serializer& s) -> void {
  s.integer(status.interlace);
  s.integer(status.field);
  s.integer(status.vcounter);
  s.integer(status.hcounter);

  s.array(history.field);
  s.array(history.vcounter);
  s.array(history.hcounter);
  s.integer(history.index);
}

auto PPU::serialize(serializer& s) -> void {
  Thread::serialize(s);
  PPUcounter::serialize(s);

  s.array(vram);
  s.array(oam);
  s.array(cgram);

  s.integer(ppu1_version);
  s.integer(ppu2_version);

  s.integer(display.interlace);
  s.integer(display.overscan);

  s.integer(regs.ppu1_mdr);
  s.integer(regs.ppu2_mdr);

  s.integer(regs.vram_readbuffer);
  s.integer(regs.oam_latchdata);
  s.integer(regs.cgram_latchdata);
  s.integer(regs.bgofs_latchdata);
  s.integer(regs.mode7_latchdata);
  s.integer(regs.counters_latched);
  s.integer(regs.latch_hcounter);
  s.integer(regs.latch_vcounter);

  s.integer(regs.oam_iaddr);
  s.integer(regs.cgram_iaddr);

  s.integer(regs.display_disable);
  s.integer(regs.display_brightness);

  s.integer(regs.oam_baseaddr);
  s.integer(regs.oam_addr);
  s.integer(regs.oam_priority);

  s.integer(regs.bg3_priority);
  s.integer(regs.bgmode);

  s.integer(regs.mode7_hoffset);
  s.integer(regs.mode7_voffset);

  s.integer(regs.vram_incmode);
  s.integer(regs.vram_mapping);
  s.integer(regs.vram_incsize);

  s.integer(regs.vram_addr);

  s.integer(regs.mode7_repeat);
  s.integer(regs.mode7_vflip);
  s.integer(regs.mode7_hflip);

  s.integer(regs.m7a);
  s.integer(regs.m7b);
  s.integer(regs.m7c);
  s.integer(regs.m7d);
  s.integer(regs.m7x);
  s.integer(regs.m7y);

  s.integer(regs.cgram_addr);

  s.integer(regs.mode7_extbg);
  s.integer(regs.pseudo_hires);
  s.integer(regs.overscan);
  s.integer(regs.interlace);

  s.integer(regs.hcounter);
  s.integer(regs.vcounter);

  bg1.serialize(s);
  bg2.serialize(s);
  bg3.serialize(s);
  bg4.serialize(s);
  sprite.serialize(s);
  window.serialize(s);
  screen.serialize(s);
}

auto PPU::Background::serialize(serializer& s) -> void {
  s.integer(regs.tiledata_addr);
  s.integer(regs.screen_addr);
  s.integer(regs.screen_size);
  s.integer(regs.mosaic);
  s.integer(regs.tile_size);

  s.integer(regs.mode);
  s.integer(regs.priority0);
  s.integer(regs.priority1);

  s.integer(regs.main_enable);
  s.integer(regs.sub_enable);

  s.integer(regs.hoffset);
  s.integer(regs.voffset);

  s.integer(cache.hoffset);
  s.integer(cache.voffset);

  s.integer(output.main.priority);
  s.integer(output.main.palette);
  s.integer(output.main.tile);

  s.integer(output.sub.priority);
  s.integer(output.sub.palette);
  s.integer(output.sub.tile);

  s.integer(x);
  s.integer(y);

  s.integer(mosaic.priority);
  s.integer(mosaic.palette);
  s.integer(mosaic.tile);

  s.integer(mosaic.vcounter);
  s.integer(mosaic.voffset);
  s.integer(mosaic.hcounter);
  s.integer(mosaic.hoffset);

  s.integer(tile_counter);
  s.integer(tile);
  s.integer(priority);
  s.integer(palette_number);
  s.integer(palette_index);
  s.array(data);
}

auto PPU::Sprite::serialize(serializer& s) -> void {
  for(auto n : range(128)) {
    s.integer(list[n].x);
    s.integer(list[n].y);
    s.integer(list[n].character);
    s.integer(list[n].nameselect);
    s.integer(list[n].vflip);
    s.integer(list[n].hflip);
    s.integer(list[n].priority);
    s.integer(list[n].palette);
    s.integer(list[n].size);
  }

  s.integer(t.x);
  s.integer(t.y);

  s.integer(t.item_count);
  s.integer(t.tile_count);

  s.integer(t.active);
  for(auto p : range(2)) {
    for(auto n : range(32)) {
      s.integer(t.item[p][n].valid);
      s.integer(t.item[p][n].index);
    }
    for(auto n : range(34)) {
      s.integer(t.tile[p][n].valid);
      s.integer(t.tile[p][n].x);
      s.integer(t.tile[p][n].priority);
      s.integer(t.tile[p][n].palette);
      s.integer(t.tile[p][n].hflip);
      s.integer(t.tile[p][n].d0);
      s.integer(t.tile[p][n].d1);
      s.integer(t.tile[p][n].d2);
      s.integer(t.tile[p][n].d3);
    }
  }

  s.integer(regs.main_enable);
  s.integer(regs.sub_enable);
  s.integer(regs.interlace);

  s.integer(regs.base_size);
  s.integer(regs.nameselect);
  s.integer(regs.tiledata_addr);
  s.integer(regs.first_sprite);

  s.integer(regs.priority0);
  s.integer(regs.priority1);
  s.integer(regs.priority2);
  s.integer(regs.priority3);

  s.integer(regs.time_over);
  s.integer(regs.range_over);

  s.integer(output.main.priority);
  s.integer(output.main.palette);

  s.integer(output.sub.priority);
  s.integer(output.sub.palette);
}

auto PPU::Window::serialize(serializer& s) -> void {
  s.integer(regs.bg1_one_enable);
  s.integer(regs.bg1_one_invert);
  s.integer(regs.bg1_two_enable);
  s.integer(regs.bg1_two_invert);

  s.integer(regs.bg2_one_enable);
  s.integer(regs.bg2_one_invert);
  s.integer(regs.bg2_two_enable);
  s.integer(regs.bg2_two_invert);

  s.integer(regs.bg3_one_enable);
  s.integer(regs.bg3_one_invert);
  s.integer(regs.bg3_two_enable);
  s.integer(regs.bg3_two_invert);

  s.integer(regs.bg4_one_enable);
  s.integer(regs.bg4_one_invert);
  s.integer(regs.bg4_two_enable);
  s.integer(regs.bg4_two_invert);

  s.integer(regs.oam_one_enable);
  s.integer(regs.oam_one_invert);
  s.integer(regs.oam_two_enable);
  s.integer(regs.oam_two_invert);

  s.integer(regs.col_one_enable);
  s.integer(regs.col_one_invert);
  s.integer(regs.col_two_enable);
  s.integer(regs.col_two_invert);

  s.integer(regs.one_left);
  s.integer(regs.one_right);
  s.integer(regs.two_left);
  s.integer(regs.two_right);

  s.integer(regs.bg1_mask);
  s.integer(regs.bg2_mask);
  s.integer(regs.bg3_mask);
  s.integer(regs.bg4_mask);
  s.integer(regs.oam_mask);
  s.integer(regs.col_mask);

  s.integer(regs.bg1_main_enable);
  s.integer(regs.bg1_sub_enable);
  s.integer(regs.bg2_main_enable);
  s.integer(regs.bg2_sub_enable);
  s.integer(regs.bg3_main_enable);
  s.integer(regs.bg3_sub_enable);
  s.integer(regs.bg4_main_enable);
  s.integer(regs.bg4_sub_enable);
  s.integer(regs.oam_main_enable);
  s.integer(regs.oam_sub_enable);

  s.integer(regs.col_main_mask);
  s.integer(regs.col_sub_mask);

  s.integer(output.main.color_enable);
  s.integer(output.sub.color_enable);

  s.integer(x);
  s.integer(one);
  s.integer(two);
}

auto PPU::Screen::serialize(serializer& s) -> void {
  s.integer(regs.addsub_mode);
  s.integer(regs.direct_color);

  s.integer(regs.color_mode);
  s.integer(regs.color_halve);
  s.integer(regs.bg1_color_enable);
  s.integer(regs.bg2_color_enable);
  s.integer(regs.bg3_color_enable);
  s.integer(regs.bg4_color_enable);
  s.integer(regs.oam_color_enable);
  s.integer(regs.back_color_enable);

  s.integer(regs.color_b);
  s.integer(regs.color_g);
  s.integer(regs.color_r);

  s.integer(math.main.color);
  s.integer(math.main.color_enable);
  s.integer(math.sub.color);
  s.integer(math.sub.color_enable);
  s.integer(math.transparent);
  s.integer(math.addsub_mode);
  s.integer(math.color_halve);
}

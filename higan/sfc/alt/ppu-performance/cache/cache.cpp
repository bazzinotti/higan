PPU::Cache::Cache(PPU& self) : self(self) {
  tiledata[0] = new buint8[262144]();
  tiledata[1] = new buint8[131072]();
  tiledata[2] = new buint8[ 65536]();
  tilevalid[0] = new buint8[ 4096]();
  tilevalid[1] = new buint8[ 2048]();
  tilevalid[2] = new buint8[ 1024]();
}

auto PPU::Cache::tile_2bpp(uint tile) -> buint8* {
  if(tilevalid[0][tile] == 0) {
    tilevalid[0][tile] = 1;
    buint8* output = (buint8*)tiledata[0] + (tile << 6);
    uint offset = tile << 4;
    uint y = 8;
    uint color, d0, d1;
    while(y--) {
      d0 = ppu.vram[offset +  0];
      d1 = ppu.vram[offset +  1];
      #define render_line(mask) \
        color  = !!(d0 & mask) << 0; \
        color |= !!(d1 & mask) << 1; \
        *output++ = color
      render_line(0x80);
      render_line(0x40);
      render_line(0x20);
      render_line(0x10);
      render_line(0x08);
      render_line(0x04);
      render_line(0x02);
      render_line(0x01);
      #undef render_line
      offset += 2;
    }
  }
  return tiledata[0] + (tile << 6);
}

auto PPU::Cache::tile_4bpp(uint tile) -> buint8* {
  if(tilevalid[1][tile] == 0) {
    tilevalid[1][tile] = 1;
    buint8* output = (buint8*)tiledata[1] + (tile << 6);
    uint offset = tile << 5;
    uint y = 8;
    uint color, d0, d1, d2, d3;
    while(y--) {
      d0 = ppu.vram[offset +  0];
      d1 = ppu.vram[offset +  1];
      d2 = ppu.vram[offset + 16];
      d3 = ppu.vram[offset + 17];
      #define render_line(mask) \
        color  = !!(d0 & mask) << 0; \
        color |= !!(d1 & mask) << 1; \
        color |= !!(d2 & mask) << 2; \
        color |= !!(d3 & mask) << 3; \
        *output++ = color
      render_line(0x80);
      render_line(0x40);
      render_line(0x20);
      render_line(0x10);
      render_line(0x08);
      render_line(0x04);
      render_line(0x02);
      render_line(0x01);
      #undef render_line
      offset += 2;
    }
  }
  return tiledata[1] + (tile << 6);
}

auto PPU::Cache::tile_8bpp(uint tile) -> buint8* {
  if(tilevalid[2][tile] == 0) {
    tilevalid[2][tile] = 1;
    buint8* output = (buint8*)tiledata[2] + (tile << 6);
    uint offset = tile << 6;
    uint y = 8;
    uint color, d0, d1, d2, d3, d4, d5, d6, d7;
    while(y--) {
      d0 = ppu.vram[offset +  0];
      d1 = ppu.vram[offset +  1];
      d2 = ppu.vram[offset + 16];
      d3 = ppu.vram[offset + 17];
      d4 = ppu.vram[offset + 32];
      d5 = ppu.vram[offset + 33];
      d6 = ppu.vram[offset + 48];
      d7 = ppu.vram[offset + 49];
      #define render_line(mask) \
        color  = !!(d0 & mask) << 0; \
        color |= !!(d1 & mask) << 1; \
        color |= !!(d2 & mask) << 2; \
        color |= !!(d3 & mask) << 3; \
        color |= !!(d4 & mask) << 4; \
        color |= !!(d5 & mask) << 5; \
        color |= !!(d6 & mask) << 6; \
        color |= !!(d7 & mask) << 7; \
        *output++ = color
      render_line(0x80);
      render_line(0x40);
      render_line(0x20);
      render_line(0x10);
      render_line(0x08);
      render_line(0x04);
      render_line(0x02);
      render_line(0x01);
      #undef render_line
      offset += 2;
    }
  }
  return tiledata[2] + (tile << 6);
}

auto PPU::Cache::tile(uint bpp, uint tile) -> buint8* {
  switch(bpp) {
  case 0: return tile_2bpp(tile);
  case 1: return tile_4bpp(tile);
  case 2: return tile_8bpp(tile);
  }
}

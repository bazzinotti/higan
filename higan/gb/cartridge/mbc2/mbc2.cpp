auto Cartridge::MBC2::mmio_read(buint16 addr) -> buint8 {
  if((addr & 0xc000) == 0x0000) {  //$0000-3fff
    return cartridge.rom_read(addr);
  }

  if((addr & 0xc000) == 0x4000) {  //$4000-7fff
    return cartridge.rom_read((rom_select << 14) | (addr & 0x3fff));
  }

  if((addr & 0xee00) == 0xa000) {  //$a000-a1ff
    if(ram_enable) return cartridge.ram_read(addr & 0x1ff);
    return 0xff;
  }

  return 0xff;
}

auto Cartridge::MBC2::mmio_write(buint16 addr, buint8 data) -> void {
  if((addr & 0xe000) == 0x0000) {  //$0000-1fff
    if(!(addr & 0x0100)) ram_enable = (data & 0x0f) == 0x0a;
    return;
  }

  if((addr & 0xe000) == 0x2000) {  //$2000-3fff
    if( (addr & 0x0100)) rom_select = (data & 0x0f) + ((data & 0x0f) == 0);
    return;
  }

  if((addr & 0xee00) == 0xa000) {  //$a000-a1ff
    if(ram_enable) cartridge.ram_write(addr & 0x1ff, data & 0x0f);
    return;
  }
}

auto Cartridge::MBC2::power() -> void {
  ram_enable = false;
  rom_select = 0x01;
}

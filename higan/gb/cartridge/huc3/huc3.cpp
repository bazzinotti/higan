auto Cartridge::HuC3::mmio_read(buint16 addr) -> buint8 {
  if((addr & 0xc000) == 0x0000) {  //$0000-3fff
    return cartridge.rom_read(addr);
  }

  if((addr & 0xc000) == 0x4000) {  //$4000-7fff
    return cartridge.rom_read((rom_select << 14) | (addr & 0x3fff));
  }

  if((addr & 0xe000) == 0xa000) {  //$a000-bfff
    if(ram_enable) return cartridge.ram_read((ram_select << 13) | (addr & 0x1fff));
    return 0xff;
  }

  return 0xff;
}

auto Cartridge::HuC3::mmio_write(buint16 addr, buint8 data) -> void {
  if((addr & 0xe000) == 0x0000) {  //$0000-1fff
    ram_enable = (data & 0x0f) == 0x0a;
    return;
  }

  if((addr & 0xe000) == 0x2000) {  //$2000-3fff
    rom_select = data;
    return;
  }

  if((addr & 0xe000) == 0x4000) {  //$4000-5fff
    ram_select = data;
    return;
  }

  if((addr & 0xe000) == 0x6000) {  //$6000-7fff
    //unknown purpose
    return;
  }

  if((addr & 0xe000) == 0xa000) {  //$a000-bfff
    if(ram_enable) cartridge.ram_write((ram_select << 13) | (addr & 0x1fff), data);
    return;
  }
}

auto Cartridge::HuC3::power() -> void {
  ram_enable = false;
  rom_select = 0x01;
  ram_select = 0x00;
}

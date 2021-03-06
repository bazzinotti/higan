auto Cartridge::MROM::read(uint mode, buint32 addr) -> buint32 {
  if(mode & Word) {
    buint32 word = 0;
    word |= read(mode & ~Word | Half, (addr & ~3) + 0) <<  0;
    word |= read(mode & ~Word | Half, (addr & ~3) + 2) << 16;
    return word;
  }

  addr &= 0x01ff'ffff;
  if(addr >= size) return (buint16)(addr >> 1);

  if(mode & Half) addr &= ~1;
  auto p = data + addr;
  if(mode & Half) return p[0] << 0 | p[1] << 8;
  if(mode & Byte) return p[0] << 0;
  return 0;  //should never occur
}

auto Cartridge::MROM::write(uint mode, buint32 addr, buint32 word) -> void {
}

auto Cartridge::MROM::serialize(serializer& s) -> void {
}

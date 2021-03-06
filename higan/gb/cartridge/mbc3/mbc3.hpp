struct MBC3 : MMIO {
  auto second() -> void;
  auto mmio_read(buint16 addr) -> buint8;
  auto mmio_write(buint16 addr, buint8 data) -> void;
  auto power() -> void;

  bool  ram_enable;  //$0000-1fff
  buint8 rom_select;  //$2000-3fff
  buint8 ram_select;  //$4000-5fff
  bool rtc_latch;    //$6000-7fff

  bool rtc_halt;
  uint rtc_second;
  uint rtc_minute;
  uint rtc_hour;
  uint rtc_day;
  bool rtc_day_carry;

  uint rtc_latch_second;
  uint rtc_latch_minute;
  uint rtc_latch_hour;
  uint rtc_latch_day;
  uint rtc_latch_day_carry;
} mbc3;

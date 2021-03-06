#pragma once

namespace Processor {

struct SPC700 {
  virtual auto op_io() -> void = 0;
  virtual auto op_read(buint16 addr) -> buint8 = 0;
  virtual auto op_write(buint16 addr, buint8 data) -> void = 0;
  virtual auto disassembler_read(buint16 addr) -> buint8 = 0;

  auto op_step() -> void;

  auto serialize(serializer&) -> void;

  auto disassemble(buint16 addr, bool p) -> string;

  #include "registers.hpp"
  #include "memory.hpp"

  Regs regs;
  Word dp, sp, rd, wr, bit, ya;
  buint8 opcode;

protected:
  auto op_adc(buint8, buint8) -> buint8;
  auto op_and(buint8, buint8) -> buint8;
  auto op_asl(buint8) -> buint8;
  auto op_cmp(buint8, buint8) -> buint8;
  auto op_dec(buint8) -> buint8;
  auto op_eor(buint8, buint8) -> buint8;
  auto op_inc(buint8) -> buint8;
  auto op_ld (buint8, buint8) -> buint8;
  auto op_lsr(buint8) -> buint8;
  auto op_or (buint8, buint8) -> buint8;
  auto op_rol(buint8) -> buint8;
  auto op_ror(buint8) -> buint8;
  auto op_sbc(buint8, buint8) -> buint8;
  auto op_st (buint8, buint8) -> buint8;
  auto op_adw(buint16, buint16) -> buint16;
  auto op_cpw(buint16, buint16) -> buint16;
  auto op_ldw(buint16, buint16) -> buint16;
  auto op_sbw(buint16, buint16) -> buint16;

  template<auto (SPC700::*op)(buint8) -> buint8> auto op_adjust(uint8_t&) -> void;
  template<auto (SPC700::*op)(buint8) -> buint8> auto op_adjust_addr() -> void;
  template<auto (SPC700::*op)(buint8) -> buint8> auto op_adjust_dp() -> void;
  auto op_adjust_dpw(int) -> void;
  template<auto (SPC700::*op)(buint8) -> buint8> auto op_adjust_dpx() -> void;
  auto op_branch(bool) -> void;
  auto op_branch_bit() -> void;
  auto op_pull(uint8_t&) -> void;
  auto op_push(buint8) -> void;
  template<auto (SPC700::*op)(buint8, buint8) -> buint8> auto op_read_addr(uint8_t&) -> void;
  template<auto (SPC700::*op)(buint8, buint8) -> buint8> auto op_read_addri(uint8_t&) -> void;
  template<auto (SPC700::*op)(buint8, buint8) -> buint8> auto op_read_const(uint8_t&) -> void;
  template<auto (SPC700::*op)(buint8, buint8) -> buint8> auto op_read_dp(uint8_t&) -> void;
  template<auto (SPC700::*op)(buint8, buint8) -> buint8> auto op_read_dpi(uint8_t&, uint8_t&) -> void;
  template<auto (SPC700::*op)(buint16, buint16) -> buint16> auto op_read_dpw() -> void;
  template<auto (SPC700::*op)(buint8, buint8) -> buint8> auto op_read_idpx() -> void;
  template<auto (SPC700::*op)(buint8, buint8) -> buint8> auto op_read_idpy() -> void;
  template<auto (SPC700::*op)(buint8, buint8) -> buint8> auto op_read_ix() -> void;
  auto op_set_addr_bit() -> void;
  auto op_set_bit() -> void;
  auto op_set_flag(bool&, bool) -> void;
  auto op_test_addr(bool) -> void;
  auto op_transfer(uint8_t&, uint8_t&) -> void;
  auto op_write_addr(uint8_t&) -> void;
  auto op_write_addri(uint8_t&) -> void;
  auto op_write_dp(uint8_t&) -> void;
  auto op_write_dpi(uint8_t&, uint8_t&) -> void;
  template<auto (SPC700::*op)(buint8, buint8) -> buint8> auto op_write_dp_const() -> void;
  template<auto (SPC700::*op)(buint8, buint8) -> buint8> auto op_write_dp_dp() -> void;
  template<auto (SPC700::*op)(buint8, buint8) -> buint8> auto op_write_ix_iy() -> void;

  auto op_bne_dp() -> void;
  auto op_bne_dpdec() -> void;
  auto op_bne_dpx() -> void;
  auto op_bne_ydec() -> void;
  auto op_brk() -> void;
  auto op_clv() -> void;
  auto op_cmc() -> void;
  auto op_daa() -> void;
  auto op_das() -> void;
  auto op_div_ya_x() -> void;
  auto op_jmp_addr() -> void;
  auto op_jmp_iaddrx() -> void;
  auto op_jsp_dp() -> void;
  auto op_jsr_addr() -> void;
  auto op_jst() -> void;
  auto op_lda_ixinc() -> void;
  auto op_mul_ya() -> void;
  auto op_nop() -> void;
  auto op_plp() -> void;
  auto op_rti() -> void;
  auto op_rts() -> void;
  auto op_sta_idpx() -> void;
  auto op_sta_idpy() -> void;
  auto op_sta_ix() -> void;
  auto op_sta_ixinc() -> void;
  auto op_stw_dp() -> void;
  auto op_wait() -> void;
  auto op_xcn() -> void;
};

}

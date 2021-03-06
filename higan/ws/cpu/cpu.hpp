struct CPU : Processor::V30MZ, Thread, IO {
  enum class Interrupt : uint {
    SerialSend,
    Input,
    Cartridge,
    SerialReceive,
    LineCompare,
    VblankTimer,
    Vblank,
    HblankTimer,
  };

  static auto Enter() -> void;
  auto main() -> void;
  auto step(uint clocks) -> void;

  auto wait(uint clocks = 1) -> void override;
  auto read(uint20 addr) -> buint8 override;
  auto write(uint20 addr, buint8 data) -> void override;
  auto in(buint16 port) -> buint8 override;
  auto out(buint16 port, buint8 data) -> void override;

  auto power() -> void;

  //io.cpp
  auto keypadRead() -> uint4;
  auto portRead(buint16 addr) -> buint8 override;
  auto portWrite(buint16 addr, buint8 data) -> void override;

  //interrupt.cpp
  auto poll() -> void;
  auto raise(Interrupt) -> void;
  auto lower(Interrupt) -> void;

  //dma.cpp
  auto dmaTransfer() -> void;

  //serialization.cpp
  auto serialize(serializer&) -> void;

  struct Registers {
    //$0040-0042  DMA_SRC
    uint20 dmaSource;

    //$0044-0045  DMA_DST
    buint16 dmaTarget;

    //$0046-0047  DMA_LEN
    buint16 dmaLength;

    //$0048  DMA_CTRL
    uint1 dmaEnable;
    uint1 dmaMode;  //0 = increment; 1 = decrement

    //$00b0  INT_BASE
    buint8 interruptBase;

    //$00b1  SER_DATA
    buint8 serialData;

    //$00b2  INT_ENABLE
    buint8 interruptEnable;

    //$00b3  SER_STATUS
    uint1 serialBaudRate;  //0 = 9600; 1 = 38400
    uint1 serialEnable;

    //$00b4  INT_STATUS
    buint8 interruptStatus;

    //$00b5  KEYPAD
    uint1 ypadEnable;
    uint1 xpadEnable;
    uint1 buttonEnable;
  } r;
};

extern CPU cpu;

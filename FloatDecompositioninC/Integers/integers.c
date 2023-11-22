#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#define MIN_SIGN_MAG - 2147483647
#define MAX_SIGN_MAG 2147483647

#define MIN_ONES - 2147483647
#define MAX_ONES 2147483647

#define MIN_TWOS - 2147483648
#define MAX_TWOS 2147483647

#define MAX_BCD 999999
#define MIN_BCD - 999999

int OneComplementtoDecimal(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  if (signBit == 0) {
    return repr;
  } else if (signBit == 1) {
    return (~repr) * -1;
  }
  return 0;
}
int TwosComplementtoDecimal(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  if (signBit == 0) {
    return repr;
  } else if (signBit == 1) {
    return (-1) * ((~repr) + 0x1);
  }
  return 0;
}
int SignMagtoDecimal(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  if (signBit == 0) {
    return repr;
  } else if (signBit == 1) {
    return ((repr << 1) >> 1) * -1;
  }
  return 0;
}
int BCDtoDecimal(unsigned int repr) {
  unsigned int byte1 = repr & 0x001F;
  unsigned int byte2 = (repr >> 5) & 0x001F;
  unsigned int byte3 = (repr >> 10) & 0x001F;
  unsigned int byte4 = (repr >> 15) & 0x001F;
  unsigned int byte5 = (repr >> 20) & 0x001F;
  unsigned int byte6 = (repr >> 25) & 0x001F;
  unsigned int byte7 = (repr >> 30);

  if (byte1 > 9 || byte2 > 9 || byte3 > 9 || byte4 > 9 || byte5 > 9 || byte6 > 9) {
    printf("error\n");
    exit(1);
  }

  int finalAnswer = (byte6 * 100000) + (byte5 * 10000) + (byte4 * 1000) + (byte3 * 100) + (byte2 * 10) + (byte1 * 1);
  if (byte7 == 0) {
    // printf("%8d", finalAnswer);
    return finalAnswer;
  } else if (byte7 == 3) {
    // printf("%8d", finalAnswer*-1);
    return finalAnswer * -1;
  } else {
    printf("error\n");
    return -100000;
  }
}

int OnestoTwos(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  if (signBit == 0) {
    return repr;
  } else if (signBit == 1) {
    return repr + 0x1;
  } else {
    exit(1);
  }
}

int OnestoSignMag(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  if (signBit == 0) {
    return repr;
  } else if (signBit == 1) {
    return (~repr) + 0x80000000;
  }
  return 0;
}
int OnestoOnes(unsigned int repr) {
  return repr;
}
int OnestoBCD(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  int value = OneComplementtoDecimal(repr);

  if (value > MAX_BCD || value < MIN_BCD) {
    printf("undefined\n");
    exit(1);
  }

  int bit1, bit2, bit3, bit4, bit5, bit6;

  if (signBit == 1) {
    value = value * -1;
    bit1 = value % 10;
    value /= 10;
    bit2 = value % 10;
    value /= 10;
    bit3 = value % 10;
    value /= 10;
    bit4 = value % 10;
    value /= 10;
    bit5 = value % 10;
    value /= 10;
    bit6 = value % 10;
  } else {
    bit1 = value % 10;
    value /= 10;
    bit2 = value % 10;
    value /= 10;
    bit3 = value % 10;
    value /= 10;
    bit4 = value % 10;
    value /= 10;
    bit5 = value % 10;
    value /= 10;
    bit6 = value % 10;
  }

  unsigned int finalValue = 0x0000;

  if (bit1 > 9 || bit2 > 9 || bit3 > 9 || bit4 > 9 || bit5 > 9 || bit6 > 9) {
    printf("error\n");
    return;
  }

  finalValue |= bit1;
  finalValue |= bit2 << 5;
  finalValue |= bit3 << 10;
  finalValue |= bit4 << 15;
  finalValue |= bit5 << 20;
  finalValue |= bit6 << 25;

  if (signBit == 1) {
    finalValue |= 1 << 30;
    finalValue |= 1 << 31;
  }
  return finalValue;
}

int TwostoOnes(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  if (signBit == 0) {
    return repr;
  } else if (signBit == 1) {
    return ~((~repr) + 0x000001);
  }
  return 0;
}

int TwostoTwos(unsigned int repr) {
  return repr;
}
int TwostoSignMag(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  if (signBit == 0) {
    return repr;
  } else if (signBit == 1) {
    return ((~repr) + 0x80000001);
  }
  return 0;
}
int TwostoBCD(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  int value = TwosComplementtoDecimal(repr);

  if (value > MAX_BCD || value < MIN_BCD) {
    printf("undefined\n");
    exit(1);
  }

  int bit1, bit2, bit3, bit4, bit5, bit6;

  if (signBit == 1) {
    value = value * -1;
    bit1 = value % 10;
    value /= 10;
    bit2 = value % 10;
    value /= 10;
    bit3 = value % 10;
    value /= 10;
    bit4 = value % 10;
    value /= 10;
    bit5 = value % 10;
    value /= 10;
    bit6 = value % 10;
  } else {
    bit1 = value % 10;
    value /= 10;
    bit2 = value % 10;
    value /= 10;
    bit3 = value % 10;
    value /= 10;
    bit4 = value % 10;
    value /= 10;
    bit5 = value % 10;
    value /= 10;
    bit6 = value % 10;
  }

  unsigned int finalValue = 0x0000;

  if (bit1 > 9 || bit2 > 9 || bit3 > 9 || bit4 > 9 || bit5 > 9 || bit6 > 9) {
    printf("error\n");
    return;
  }

  finalValue |= bit1;
  finalValue |= bit2 << 5;
  finalValue |= bit3 << 10;
  finalValue |= bit4 << 15;
  finalValue |= bit5 << 20;
  finalValue |= bit6 << 25;

  if (signBit == 1) {
    finalValue |= 1 << 30;
    finalValue |= 1 << 31;
  }
  return finalValue;
}

int BCDtoOnes(unsigned int repr) {
  return TwostoOnes(BCDtoDecimal(repr));
}
int BCDtoTwos(unsigned int repr) {
  return TwostoTwos(BCDtoDecimal(repr));
}
int BCDtoSignMag(unsigned int repr) {
  return (TwostoSignMag(BCDtoDecimal(repr)));
}
int BCDtoBCD(unsigned int repr) {
  return repr;
}

int SignMagtoBCD(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  int value = SignMagtoDecimal(repr);
  if (SignMagtoDecimal(repr) > MAX_BCD + 1 || SignMagtoDecimal(repr) < MIN_BCD - 1) {
    printf("undefined\n");
    exit(1);
  }

  int bit1, bit2, bit3, bit4, bit5, bit6;

  if (signBit == 1) {
    value = value * -1;
    bit1 = value % 10;
    value /= 10;
    bit2 = value % 10;
    value /= 10;
    bit3 = value % 10;
    value /= 10;
    bit4 = value % 10;
    value /= 10;
    bit5 = value % 10;
    value /= 10;
    bit6 = value % 10;
  } else {
    bit1 = value % 10;
    value /= 10;
    bit2 = value % 10;
    value /= 10;
    bit3 = value % 10;
    value /= 10;
    bit4 = value % 10;
    value /= 10;
    bit5 = value % 10;
    value /= 10;
    bit6 = value % 10;
  }

  unsigned int finalValue = 0x0000;

  if (bit1 > 9 || bit2 > 9 || bit3 > 9 || bit4 > 9 || bit5 > 9 || bit6 > 9) {
    printf("error\n");
    return;
  }

  finalValue |= bit1;
  finalValue |= bit2 << 5;
  finalValue |= bit3 << 10;
  finalValue |= bit4 << 15;
  finalValue |= bit5 << 20;
  finalValue |= bit6 << 25;

  if (signBit == 1) {
    finalValue |= 1 << 30;
    finalValue |= 1 << 31;
  }
  return finalValue;
}
int SignMagtoOnes(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  if (signBit == 0) {
    return repr;
  } else if (signBit == 1) {
    return (~repr) + 0x80000000;
  }
  return 0;
}
int SignMagtoTwos(unsigned int repr) {
  unsigned int signBit = repr >> 31;
  if (signBit == 0) {
    return repr;
  } else if (signBit == 1) {
    return (~repr) + 0x80000001;
  }
  return 0;
}
int SignMagtoSignMag(unsigned int repr) {
  return repr;
}

void repr_convert(char source_repr, char target_repr, unsigned int repr) {
  if (source_repr == '1') {
    if (target_repr == '1') {
      if (OnestoOnes(repr) == 0xffffffff) {
        printf("%08x\n", 0x0);
      } else if (OneComplementtoDecimal(OnestoOnes(repr)) > MAX_ONES || OneComplementtoDecimal(OnestoOnes(repr)) < MIN_ONES) {
        printf("undefined\n");
      }
        else {
        printf("%08x\n", OnestoOnes(repr));
      }
    } else if (target_repr == '2') {
      if (TwosComplementtoDecimal(OnestoTwos(repr)) > MAX_TWOS || TwosComplementtoDecimal(OnestoTwos(repr)) < MIN_TWOS) {
        printf("undefined\n");
      }
        else {
        printf("%08x\n", OnestoTwos(repr));
      }
    } else if (target_repr == 'S') {
      if (OnestoSignMag(repr) == 0x80000000) {
        printf("%08x\n", 0x0);
      } else if (SignMagtoDecimal(OnestoSignMag(repr)) > MAX_SIGN_MAG || SignMagtoDecimal(OnestoSignMag(repr)) < MIN_SIGN_MAG ){
        printf("undefined\n");
      } else {
        printf("%08x\n", OnestoSignMag(repr));
      }
    } else if (target_repr == 'D') {
      if (OnestoBCD(repr) == 0xC0000000) {
        printf("%08x\n", 0x0);
      } else {
        printf("%08x\n", OnestoBCD(repr));
      }

    } else {
      printf("error\n");
      return;
    }
  } else if (source_repr == '2') {
    if (target_repr == '1') {
      if (TwostoOnes == 0xffffffff) {
        printf("%08x\n", 0x0);
      } else if (OneComplementtoDecimal(TwostoOnes(repr)) >= MAX_ONES || OneComplementtoDecimal(TwostoOnes(repr)) <= MIN_ONES) {
        printf("undefined\n");
      } else {
        printf("%08x\n", TwostoOnes(repr));
      }
    } else if (target_repr == '2') {
      if (TwosComplementtoDecimal(TwostoTwos(repr)) > MAX_TWOS || TwosComplementtoDecimal(TwostoTwos(repr)) < MIN_TWOS) {
        printf("undefined\n");
      }
        else {
        printf("%08x\n", TwostoTwos(repr));
      }
    } else if (target_repr == 'S') {
      if (TwostoSignMag(repr) == 0x80000000) {
        printf("%08x\n", 0x0);
      } else if (SignMagtoDecimal(TwostoSignMag(repr)) > MAX_SIGN_MAG || SignMagtoDecimal(TwostoSignMag(repr)) < MIN_SIGN_MAG ){
        printf("undefined\n");
      } 
      else {
        printf("%08x\n", TwostoSignMag(repr));
      }
    } else if (target_repr == 'D') {
      if (TwostoBCD(repr) == 0xC0000000) {
        printf("%08x\n", 0x0);
      } else {
        printf("%08x\n", TwostoBCD(repr));
      }
    } else {
      printf("error\n");
      return;
    }
  } else if (source_repr == 'S') {
    if (target_repr == '1') {
      if (SignMagtoOnes(repr) == 0xffffffff) {
        printf("%08x\n", 0x0);
      } else if (OneComplementtoDecimal(SignMagtoOnes(repr)) > MAX_ONES || OneComplementtoDecimal(SignMagtoOnes(repr)) < MIN_ONES) {
        printf("undefined\n");
      }
      else {
        printf("%08x\n", SignMagtoOnes(repr));
      }
    } else if (target_repr == '2') {
      printf("%08x\n", SignMagtoTwos(repr));
    } else if (target_repr == 'S') {
      if (SignMagtoSignMag(repr) == 0x80000000) {
        printf("%08x\n", 0x0);
      } else if (TwosComplementtoDecimal(SignMagtoTwos(repr)) > MAX_TWOS || TwosComplementtoDecimal(SignMagtoTwos(repr)) < MIN_TWOS) {
        printf("undefined\n");
      }
    else {
        printf("%08x\n", SignMagtoSignMag(repr));
      }

    } else if (target_repr == 'D') {
      if (SignMagtoBCD(repr) == 0xC0000000) {
        printf("%08x\n", 0x0);
      } else if (SignMagtoDecimal(SignMagtoSignMag(repr)) >= MAX_SIGN_MAG || SignMagtoDecimal(SignMagtoSignMag(repr)) <= MIN_SIGN_MAG ){
        printf("undefined\n");
      } 
    else {
        printf("%08x\n", SignMagtoBCD(repr));
      }
    } else {
      printf("error\n");
      return;
    }
  } else if (source_repr == 'D') {
    if (target_repr == '1') {
      if (BCDtoOnes(repr) == 0xffffffff) {
        printf("%08x\n", 0x0);
      } else if (OneComplementtoDecimal(BCDtoOnes(repr)) > MAX_ONES || OneComplementtoDecimal(BCDtoOnes(repr)) < MIN_ONES) {
        printf("undefined\n");
      }else {
        printf("%08x\n", BCDtoOnes(repr));
      }
    } else if (target_repr == '2') {
       if (TwosComplementtoDecimal(BCDtoTwos(repr)) > MAX_TWOS || TwosComplementtoDecimal(BCDtoTwos(repr)) < MIN_TWOS) {
        printf("undefined\n");
      }else{
        printf("%08x\n", BCDtoTwos(repr));
    } }else if (target_repr == 'S') {
      if (BCDtoSignMag(repr) == 0x80000000) {
        printf("%08x\n", 0x0);
      } else if (SignMagtoDecimal(BCDtoSignMag(repr)) > MAX_SIGN_MAG || SignMagtoDecimal(BCDtoSignMag(repr)) < MIN_SIGN_MAG ){
        printf("undefined\n");
      } 
      else {
        printf("%08x\n", BCDtoSignMag(repr));
      }
    } else if (target_repr == 'D') {
      if (BCDtoBCD(repr) == 0xC0000000) {
        printf("%08x\n", 0x0);
      } 
    else {
        printf("%08x\n", BCDtoBCD(repr));
      }
    } else {
      printf("error\n");
      return;
    }
  } else {
    printf("error\n");
    return;
  }
}

// DO NOT CHANGE ANY CODE BELOW THIS LINE
int main(int argc, char * argv[]) {
  (void) argc; // Suppress compiler warning
  repr_convert(argv[1][0], argv[2][0], (int) strtol(argv[3], NULL, 16));
  // unsigned int i = 0b11111111111111100111110000000100;
  //printf("Mangoes: %x", SignMagtoBCD(0x8098967f));
  return 0;
}
#include <bacon.h>
 // Add other #includes here if you want.

static int count = 0;

char * bacon_code_translation[64][64] = {
  {
    "000000",
    "A"
  },
  {
    "000001",
    "B"
  },
  {
    "000010",
    "C"
  },
  {
    "000011",
    "D"
  },
  {
    "000100",
    "E"
  },
  {
    "000101",
    "F"
  },
  {
    "000110",
    "G"
  },
  {
    "000111",
    "H"
  },
  {
    "001000",
    "I"
  },
  {
    "001001",
    "J"
  },
  {
    "001010",
    "K"
  },
  {
    "001011",
    "L"
  },
  {
    "001100",
    "M"
  },
  {
    "001101",
    "N"
  },
  {
    "001110",
    "O"
  },
  {
    "001111",
    "P"
  },
  {
    "010000",
    "Q"
  },
  {
    "010001",
    "R"
  },
  {
    "010010",
    "S"
  },
  {
    "010011",
    "T"
  },
  {
    "010100",
    "U"
  },
  {
    "010101",
    "V"
  },
  {
    "010110",
    "W"
  },
  {
    "010111",
    "X"
  },
  {
    "011000",
    "Y"
  },
  {
    "011001",
    "Z"
  }, //26 (index 25)
  {
    "011010",
    " "
  },
  {
    "011011",
    "!"
  },
  {
    "011100",
    "\""
  },
  {
    "011101",
    "#"
  },
  {
    "011110",
    "$"
  }, //30 (index 29)
  {
    "011111",
    "%"
  },
  {
    "100000",
    "&"
  },
  {
    "100001",
    "'"
  },
  {
    "100010",
    "("
  },
  {
    "100011",
    ")"
  },
  {
    "100100",
    ","
  },
  {
    "100101",
    "-"
  },
  {
    "100110",
    "."
  },
  {
    "100111",
    "/"
  },
  {
    "101000",
    "0"
  }, //40
  {
    "101001",
    "1"
  },
  {
    "101010",
    "2"
  },
  {
    "101011",
    "3"
  },
  {
    "101100",
    "4"
  },
  {
    "101101",
    "5"
  },
  {
    "101110",
    "6"
  },
  {
    "101111",
    "7"
  },
  {
    "110000",
    "8"
  },
  {
    "110001",
    "9"
  },
  {
    "110010",
    ":"
  },
  {
    "110011",
    ";"
  },
  {
    "110100",
    "?"
  },
  {
    "110101",
    ""
  },
  {
    "110110",
    ""
  },
  {
    "110111",
    ""
  },
  {
    "111000",
    ""
  },
  {
    "111001",
    ""
  },
  {
    "111010",
    ""
  },
  {
    "111011",
    ""
  },
  {
    "111100",
    ""
  },
  {
    "111101",
    ""
  },
  {
    "111110",
    ""
  },
  {
    "111111",
    "\0"
  }, //end of message marker
};

int cipherIt(char * ciphertext, int value) {

  int bit0 = (value & (1 << 0)) >> 0;
  int bit1 = (value & (1 << 1)) >> 1;
  int bit2 = (value & (1 << 2)) >> 2;
  int bit3 = (value & (1 << 3)) >> 3;
  int bit4 = (value & (1 << 4)) >> 4;
  int bit5 = (value & (1 << 5)) >> 5;
  int bitarr[] = {
    bit5,
    bit4,
    bit3,
    bit2,
    bit1,
    bit0
  };

  for (int i = count, j = 0; i < ((int) strlen(ciphertext)), j < 6; j++, i++) {
    count++;
    if (isalpha(ciphertext[i]) != 0) {
      if (bitarr[j] == 1) {
        ciphertext[i] = toupper(ciphertext[i]);

      } else if (bitarr[j] == 0) {
        ciphertext[i] = tolower(ciphertext[i]);
      }
    } else if (isalpha(ciphertext[i]) == 0) {
      j--;
    }

  }
  return 0;
}
int encrypt(const char * plaintext, char * ciphertext) {

  int calculateEncodableSpace = 0;
  for (int i = 0; i < ((int) strlen(ciphertext)); i++) {
    if ((ciphertext[i] >= 65 && ciphertext[i] <= 90) || (ciphertext[i] >= 97 && ciphertext[i] <= 122)) {
      calculateEncodableSpace++;
    }
  }
  if (calculateEncodableSpace < 6) {
    return -1;
  }
  if (calculateEncodableSpace == 6) {
    return cipherIt(ciphertext, 63);
  }

  int maxHold = (calculateEncodableSpace - 6) / 6;
  //printf("maxHold: %d\n", maxHold);
  int holdingCharacters = 0;

  for (int j = 0; j < ((int) strlen(plaintext)) && j < maxHold; j++) {
    //uppercase letters
    if (((plaintext[j] >= 65 && plaintext[j] <= 90))) {
      cipherIt(ciphertext, ((plaintext[j]) - 65));
      holdingCharacters++;

    }
    //lowercase letters
    else if (((plaintext[j] >= 97 && plaintext[j] <= 122))) {
      cipherIt(ciphertext, plaintext[j] - 97);
      holdingCharacters++;

    }
    //bacon codes 26-39
    else if (((plaintext[j] >= 32 && plaintext[j] <= 41))) {
      cipherIt(ciphertext, plaintext[j] - 6);
      holdingCharacters++;

    }
    //bacon codes 26-39
    else if (((plaintext[j] >= 44 && plaintext[j] <= 47))) {
      cipherIt(ciphertext, plaintext[j] - 8);
      holdingCharacters++;

    }
    //0-9
    else if (((plaintext[j] >= 48 && plaintext[j] <= 57))) {
      cipherIt(ciphertext, plaintext[j] - 8);
      holdingCharacters++;

    }
    //:;
    else if (((plaintext[j] >= 58 && plaintext[j] <= 59))) {
      cipherIt(ciphertext, plaintext[j] - 8);
      holdingCharacters++;

    }
    //?
    else if (plaintext[j] == 63) {
      cipherIt(ciphertext, plaintext[j] - 11);
      holdingCharacters++;

    } else if (plaintext[j] == 0) {
      break;
    }
  }
  cipherIt(ciphertext, 63);
  return holdingCharacters;
}

int decrypt(const char * ciphertext, char * plaintext) {
  if (strlen(plaintext) == 0) {
    return -1;
  }
  int partialMessage = (int) strlen(plaintext);
  int sourceLength = strlen(ciphertext);
  int whileLoopCounter = 0;
  int calculateEncodableSpace = 0;
  //printf("Cipher Length: %d\n", sourceLength);
  int cipherTextLength = strlen(ciphertext);
  for (int i = 0; i < cipherTextLength; i++) {
    if ((ciphertext[i] >= 65 && ciphertext[i] <= 90) || (ciphertext[i] >= 97 && ciphertext[i] <= 122)) {
      calculateEncodableSpace++;
    }
  }
  //printf("Encodeable Length: %d\n", calculateEncodableSpace);

  char baconCodes[calculateEncodableSpace + 1];

  int inc = 0;
  while (sourceLength != 0) {
    if (ciphertext[whileLoopCounter] >= 65 && ciphertext[whileLoopCounter] <= 90) {
      baconCodes[inc] = 49;
      //printf("Length: %d\n", (inc));
      inc++;
    } else if (ciphertext[whileLoopCounter] >= 97 && ciphertext[whileLoopCounter] <= 122) {
      baconCodes[inc] = 48;
      //printf("Length: %d\n", (inc));
      inc++;
    }
    sourceLength = sourceLength - 1;
    whileLoopCounter++;
  }
  baconCodes[calculateEncodableSpace] = 0;

  //printf("Bacon Codes: %s\n", baconCodes);

  int baconCodeLength = strlen(baconCodes);

  //printf("BaconCode Length: %d\n", baconCodeLength);

  int possibleGroups = baconCodeLength / 6;
  //printf("Possible Groups Length: %d\n", possibleGroups);

  char groups[possibleGroups][7];

  for (int i = 0; i < possibleGroups; i++) {
    strncpy(groups[i], baconCodes + (i * 6), 6);
    groups[i][6] = '\0';
    // printf("%s\n", groups[i]);
  }

  int EOMMarker = 0;
  for (int i = 0; i < possibleGroups; i++) {
    if (strcmp(groups[i], "111111") == 0) {
      EOMMarker++;
    }
  }
  if (EOMMarker == 0) {
    return -2;
  }

  int outofBoundsBaconCodes = 0;

  if (partialMessage < possibleGroups) {
    for (int i = 0; i < partialMessage; i++) {
      for (int j = 0; j < 63; j++) {
        if (strcmp(groups[i], "111111") == 0) {
          plaintext[i] = * bacon_code_translation[63][1];
          break;
        } else if (strcmp(groups[i], bacon_code_translation[j][0]) == 0) {
          plaintext[i] = * bacon_code_translation[j][1];
        }
      }
    }
  } else {
    for (int i = 0; i < possibleGroups; i++) {
      for (int j = 0; j < 63; j++) {
        if (strcmp(groups[i], "111111") == 0) {
          plaintext[i] = * bacon_code_translation[63][1];
          break;
        } else if (strcmp(groups[i], bacon_code_translation[j][0]) == 0) {
          plaintext[i] = * bacon_code_translation[j][1];
        }
      }
    }
  }

  return strlen(plaintext);
}
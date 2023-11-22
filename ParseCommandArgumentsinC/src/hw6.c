#include "hw6.h"

int main(int argc, char * argv[]) {
  // Print Out Every Argument in Command current_line_holder - Testing Purposes Only
  // printf("ARGC Length: %d\n", argc);
  // printf("ARGV Values: \n");
  //   for (int i = 1; i < argc; i++) {
  //     printf("%s\n", argv[i]);
  //   }

  //--------------------------------------------------------ERROR CHECKING ------------------------------------------------------------------------------------------------------------//
  if (argc < 7) {
    return MISSING_ARGUMENT;
  }

  int opt = 0;
  char * searching_text = NULL;
  char * replacing_text = NULL;
  bool has_wildcard = false;
  char * start_str = NULL;
  char * end_str = NULL;
  int s_dup = 0;
  int r_dup = 0;
  int l_dup = 0;
  int w_dup = 0;

  while ((opt = getopt(argc, argv, "s:r:l:w")) != -1) {
    switch (opt) {
    case 's':
      s_dup++;
      if ((s_dup > 1) | (r_dup > 1) | (l_dup > 1) | (w_dup > 1)) {
        return DUPLICATE_ARGUMENT;
      }
      if (optarg[0] == '-') {
        return S_ARGUMENT_MISSING;
      }
      searching_text = optarg;
      //printf("Searching Text: %s\n", searching_text);
      break;
    case 'r':
      r_dup++;
      if ((s_dup > 1) | (r_dup > 1) | (l_dup > 1) | (w_dup > 1)) {
        return DUPLICATE_ARGUMENT;
      }
      if (optarg[0] == '-') {
        return R_ARGUMENT_MISSING;
      }
      replacing_text = optarg;
      // printf("Replacing Text: %s\n", replacing_text);
      break;
    case 'w':
      w_dup++;
      if ((s_dup > 1) | (r_dup > 1) | (l_dup > 1) | (w_dup > 1)) {
        return DUPLICATE_ARGUMENT;
      }
      has_wildcard = true;

      // printf("Wild Card is %d\n", has_wildcard);
      break;
    case 'l':
      l_dup++;
      if ((s_dup > 1) | (r_dup > 1) | (l_dup > 1) | (w_dup > 1)) {
        return DUPLICATE_ARGUMENT;
      }
      if (optarg[0] == '-') {
        return L_ARGUMENT_INVALID;
      }
      start_str = strtok(optarg, ",");
      end_str = strtok(NULL, ",");
      if ((start_str == NULL) | (end_str == NULL)) {
        return L_ARGUMENT_INVALID;
      }
      int startline = atoi(start_str);
      int endline = atoi(end_str);
      if ((startline > endline)) {
        return L_ARGUMENT_INVALID;
      }
      //   printf("Start_STR: %s\n", start_str);
      //   printf("END_STR: %s\n", end_str);
      break;
    default:
      continue;
    }
  }

  char * input_file = NULL;
  char * output_file = NULL;
  input_file = argv[argc - 2];
  output_file = argv[argc - 1];

  // Input File Check
  FILE * input_check = fopen(input_file, "r");
  if (input_check == NULL) {
    return INPUT_FILE_MISSING;
  }
  fclose(input_check);

  // Output File Check
  FILE * output_check = fopen(output_file, "w");
  if (output_check == NULL) {
    return OUTPUT_FILE_UNWRITABLE;
  }
  fclose(output_check);

  int s_count = 0;
  int r_count = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-s") == 0) {
      s_count++;
    }
    if (strcmp(argv[i], "-r") == 0) {
      r_count++;
    }
  }

  if (s_count != 1) {
    return S_ARGUMENT_MISSING;
  }
  if (r_count != 1) {
    return R_ARGUMENT_MISSING;
  }

  int wildcard_in_between = 0;
  int wildcard_present = 0;
  bool prefix = false;
  bool suffix = false;

  if (has_wildcard == true) {
    for (unsigned int i = 1; i < (strlen(searching_text) - 1); i++) {
      if (strcmp( & searching_text[i], "*") == 0) {
        wildcard_in_between++;
      }
    }

    if (searching_text != NULL && searching_text[0] == '*') {
      wildcard_present++;
      suffix = true;
      // printf("true at begin \n");
    }

    if (searching_text != NULL && searching_text[strlen(searching_text) - 1] == '*') {
      wildcard_present++;
      prefix = true;
      // printf("true at end \n");
    }

    if ((wildcard_present > 1) | (wildcard_present == 0)) {
      return WILDCARD_INVALID;
    }
    if (wildcard_in_between > 0) {
      return WILDCARD_INVALID;
    }

  }
  //----------------------------------------------------ERROR CHECKING STOPS HERE --------------------------------------------------------------------------------------------//

 // printf("Entering Loops:\n");
  //-------------------------------------------------------------------------Part 2 starts here --------------------------------------------------------------------------------------
  if (has_wildcard == false) {
    // printf("Into the Non wildcard section - part 2 of hw assignment");
    FILE * input = fopen(input_file, "r");
    FILE * output = fopen(output_file, "w");
    char current_line_holder[MAX_LINE];

    //No Line Bounds
    if (l_dup == 0) {
      while (fgets(current_line_holder, MAX_LINE, input)) {
        unsigned int line_len = strlen(current_line_holder);
        char copy_array[MAX_LINE];
        unsigned int new_line_len = 0;
        for (unsigned int i = 0; i < line_len; i++) {
          if (strncmp( & current_line_holder[i], searching_text, strlen(searching_text)) == 0) {
            strncpy( & copy_array[new_line_len], replacing_text, strlen(replacing_text));
            new_line_len += strlen(replacing_text);
            i += strlen(searching_text) - 1;
          } else {
            copy_array[new_line_len++] = current_line_holder[i];
          }
        }
        copy_array[new_line_len] = '\0';
        fputs(copy_array, output);
      }
    }
    //Line Bounds Present on Code
    else if (l_dup == 1) {
      int start_line = atoi(start_str);
      int end_line = atoi(end_str);
      int current_line = 1;

      // get to the start line - put everything before that on output file
      while ((current_line != start_line) && (fgets(current_line_holder, MAX_LINE, input))) {
        current_line++;
        // printf("%d\n", current_line);
        fputs(current_line_holder, output);
      }

      // Keep end line bound in check
      for (; current_line <= end_line; current_line++) {
        // printf("Current current_line_holder: %d\n", current_line);

        // empty line check
        if (fgets(current_line_holder, MAX_LINE, input) == NULL) {
          break;
        }

        // same syntax as above for no restriction
        unsigned int line_len = strlen(current_line_holder);
        char copy_array[MAX_LINE];
        unsigned int new_line_len = 0;
        // printf("%s", current_line_holder);
        for (unsigned int i = 0; i < line_len; i++) {
          if (strncmp( & current_line_holder[i], searching_text, strlen(searching_text)) == 0) {
            strncpy( & copy_array[new_line_len], replacing_text, strlen(replacing_text));
            new_line_len += strlen(replacing_text);
            i += strlen(searching_text) - 1;
          } else {
            copy_array[new_line_len++] = current_line_holder[i];
          }
        }
        copy_array[new_line_len] = '\0';
        fputs(copy_array, output);
      }

      // copy the rest of the file
      while ((fgets(current_line_holder, MAX_LINE, input))) {
        // printf("%d\n", current_line);
        fputs(current_line_holder, output);
      }
    }
  }
  //---------------------------------------------------------------------------Part 2 ends here --------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------Part 3 starts here --------------------------------------------------------------------------------------
  else if (has_wildcard == true) {
    //printf("Wild Card True\n");

    FILE * input = fopen(input_file, "r");
    FILE * output = fopen(output_file, "w");
    // printf("Hereertaasdf\n");
    // printf("l_dup: %d \n", l_dup);
    // printf("Suffix Value: %d\n", suffix);
    // printf("Prefix Value: %d\n", prefix);

    //syntax to remove wildcard operator + copy everything into prefixer and replacer arrays

    int search_text_len = strlen(searching_text);
    int replace_text_len = strlen(replacing_text);

    //code specific to prefixer
    char prefixer[MAX_SEARCH_LEN];
    strncpy(prefixer, searching_text, search_text_len - 1);
    prefixer[search_text_len - 1] = '\0';

    //common code
    char replacer[MAX_SEARCH_LEN];
    strncpy(replacer, replacing_text, replace_text_len + 1);
    char current_line_holder[MAX_LINE];
    char word[MAX_LINE];
    char copying_arr[MAX_LINE];

    int prefixer_length = strlen(prefixer);

    int replacer_length = strlen(replacer);

    if (l_dup == 0) {
      //no line bounds and check if prefix or suffix are true
      if (prefix == true) {
        printf("In prefix true and ldup equals 0\n");
        while (fgets(current_line_holder, MAX_LINE, input) != NULL) {
          //REMEMBER TO CLEAR COPPYING ARRAY EACH TIME or VALGRIND ISSUES COME UP
          memset(copying_arr, 0, sizeof(copying_arr));
          int index = 0;
          for (unsigned int i = 0; i < strlen(current_line_holder); i++) {
            if (isspace(current_line_holder[i]) || ispunct(current_line_holder[i])) {
              copying_arr[index] = current_line_holder[i];
              index++;
            } else {
              int j = 0;
              while (i + j < strlen(current_line_holder) && !isspace(current_line_holder[i + j]) && !ispunct(current_line_holder[i + j])) {
                //get the word from line holder into word array for analysis below
                word[j] = current_line_holder[i + j];
                j++;
              }
              //word[j] = '\0';
              if (strncmp(word, prefixer, prefixer_length) == 0) {
                strcpy(copying_arr + index, replacer);
                index += replacer_length;
                i += j - 1;
              } else {
                memcpy(copying_arr + index, word, j);
                index += j;
                i += j - 1;
              }
            }
          }
          fputs(copying_arr, output);
        }
        fclose(input);
        fclose(output);
      } else if (suffix == true) {
        // printf("In suffix and no line bounds and wildcard true\n");
        //code specific to suffixer
        char suffixer[MAX_SEARCH_LEN];
        for (int i = 0; i <= replace_text_len; i++) {
          suffixer[i] = searching_text[i + 1];
        }
        suffixer[search_text_len] = '\0';
        unsigned int suffixer_length = strlen(suffixer);

        // printf("Suffixer String: %s\n", suffixer);
        // printf("Suffixer Length: %d\n", suffixer_length);

        while (fgets(current_line_holder, MAX_LINE, input) != NULL) {
          memset(copying_arr, 0, sizeof(copying_arr));
          int index = 0;
          for (unsigned int i = 0; i < strlen(current_line_holder); i++) {
            if (isspace(current_line_holder[i]) || ispunct(current_line_holder[i])) {
              copying_arr[index++] = current_line_holder[i];
            } else {
              int j = 0;
              while (i + j < strlen(current_line_holder) && !isspace(current_line_holder[i + j]) && !ispunct(current_line_holder[i + j])) {
                word[j] = current_line_holder[i + j];
                j++;
              }
              word[j] = '\0';
              unsigned int word_len = strlen(word);
              //printf("Word Len: %d", word_len); //nowhere is it null
              if ((word_len >= suffixer_length) && (strncmp((word + (word_len - suffixer_length)), suffixer, suffixer_length) == 0)) {

                strcpy(copying_arr + index, replacer);
                index += replacer_length;
                i += j - 1;
              } else {
                memcpy(copying_arr + index, word, j);
                index += j;
                i += j - 1;
              }
            }
          }
          fputs(copying_arr, output);
        }
        fclose(input);
        fclose(output);
      }

    } else if (l_dup == 1) {

      int start_line = atoi(start_str);
      int end_line = atoi(end_str);
      int current_line = 1;

      //line bounds and then check if prefix/suffix are true
      if (prefix == true) {

        // printf("In prefix true and ldup equals 1\n");
        // printf("Start Line: %d\n", start_line);
        // printf("End Line: %d\n", end_line);
        // printf("prefixer text: %s\n", prefixer);
        // printf("replacer text: %s\n", replacer);

        //get to the start line - put everything before that on output file
        while ((current_line < start_line) && (fgets(current_line_holder, MAX_LINE, input))) {
          current_line++;
          //printf("%d\n", current_line);
          fputs(current_line_holder, output);
        }

        //do the middle part between the range
        while ((current_line <= end_line) && (fgets(current_line_holder, MAX_LINE, input) != NULL)) {
       //   printf("Current Line: %s\n", current_line_holder);
          //REMEMBER TO CLEAR COPPYING ARRAY EACH TIME or VALGRIND ISSUES COME UP
          memset(copying_arr, 0, sizeof(copying_arr));
          int index = 0;
          for (unsigned int i = 0; i < strlen(current_line_holder); i++) {
            if (isspace(current_line_holder[i]) || ispunct(current_line_holder[i])) {
              copying_arr[index] = current_line_holder[i];
              index++;
            } else {
              int j = 0;
              while (i + j < strlen(current_line_holder) && !isspace(current_line_holder[i + j]) && !ispunct(current_line_holder[i + j])) {

                //get the word from line holder into word array for analysis below

                word[j] = current_line_holder[i + j];
                j++;
              }
              if (strncmp(word, prefixer, prefixer_length) == 0) {
                strcpy(copying_arr + index, replacer);
                index += replacer_length;
                i += j - 1;
              } else {
                //memcpy syntax
                //memcpy(destination, source, size);
                memcpy(copying_arr + index, word, j);
                index += j;
                i += j - 1;
              }

            }
          }
          fputs(copying_arr, output);
          current_line++;
        }

        // copy the rest of the file
        while ((fgets(current_line_holder, MAX_LINE, input))) {
          // printf("%d\n", current_line);
          fputs(current_line_holder, output);
        }
        fclose(input);
        fclose(output);
      } else if (suffix == true) {

        char suffixer[MAX_SEARCH_LEN];
        for (int i = 0; i <= replace_text_len; i++) {
          suffixer[i] = searching_text[i + 1];
        }
        suffixer[search_text_len] = '\0';
        unsigned int suffixer_length = strlen(suffixer);

        // printf("Suffixer String: %s\n", suffixer);
        // printf("Suffixer Length: %d\n", suffixer_length);
        // printf("In prefix true and ldup equals 1\n");
        // printf("Start Line: %d\n", start_line);
        // printf("End Line: %d\n", end_line);
        // printf("suffixer text: %s\n", suffixer);
        // printf("replacer text: %s\n", replacer);

        //get to the start line - put everything before that on output file
        while ((current_line < start_line) && (fgets(current_line_holder, MAX_LINE, input))) {
          current_line++;
          //printf("%d\n", current_line);
          fputs(current_line_holder, output);
        }

        while ((current_line <= end_line) && fgets(current_line_holder, MAX_LINE, input) != NULL) {

          //printf("Current Line: %s", current_line_holder);
          memset(copying_arr, 0, sizeof(copying_arr));
          int index = 0;
          for (unsigned int i = 0; i < strlen(current_line_holder); i++) {
            if (isspace(current_line_holder[i]) || ispunct(current_line_holder[i])) {
              copying_arr[index++] = current_line_holder[i];
            } else {
              int j = 0;
              while (i + j < strlen(current_line_holder) && !isspace(current_line_holder[i + j]) && !ispunct(current_line_holder[i + j])) {
                word[j] = current_line_holder[i + j];
                j++;
              }
              word[j] = '\0';
              unsigned int word_len = strlen(word);
              //printf("Word Len: %d", word_len); //nowhere is it null
              if ((word_len >= suffixer_length) && (strncmp((word + (word_len - suffixer_length)), suffixer, suffixer_length) == 0)) {

                strcpy(copying_arr + index, replacer);
                index += replacer_length;
                i += j - 1;
              } else {
                memcpy(copying_arr + index, word, j);
                index += j;
                i += j - 1;
              }
            }
          }
          fputs(copying_arr, output);
          current_line++;
        }

        // copy the rest of the file
        while ((fgets(current_line_holder, MAX_LINE, input))) {
          // printf("%d\n", current_line);
          fputs(current_line_holder, output);
        }

        fclose(input);
        fclose(output);
      }
    }
  }
  //---------------------------------------------------------------------------Part 3 ends here --------------------------------------------------------------------------------------

  return 0;
}
#include "unit_tests.h"

TestSuite(student_suite, .timeout=TEST_TIMEOUT);

/*
Test(student_suite, decrypt_, .description="description of test") {
    // Steps of unit test go here
}
*/

Test(student_suite, decrypt_0, .description="description of test") {
    char plaintext_act[] = "*******************";
    for (unsigned int i = 0; i < strlen(plaintext_act); i++)
        plaintext_act[i] = (char)(rand() % 200 + 33);
    char *ciphertext = "BBaaaB BBaaaB BaBBBBB BBBBBB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "997";
    int count_exp = 3;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_1, .description="description of test") {
    char plaintext_act[] = "**";
    for (unsigned int i = 0; i < strlen(plaintext_act); i++)
        plaintext_act[i] = (char)(rand() % 200 + 33);
    char *ciphertext = "BBaaaB BBaaaB BaBBBBB BBBBBB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "99";
    int count_exp = 2;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_2, .description="description of test") {
    char plaintext_act[] = "";
    for (unsigned int i = 0; i < strlen(plaintext_act); i++)
        plaintext_act[i] = (char)(rand() % 200 + 33);
    char *ciphertext = "BBaaaB BBaaaB BaBBBBB BBBBBB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "";
    int count_exp = -1;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_3, .description="description of test") {
    char plaintext_act[] = "****";
    for (unsigned int i = 0; i < strlen(plaintext_act); i++)
        plaintext_act[i] = (char)(rand() % 200 + 33);
    char *ciphertext = "aaaaaBaaaaaaaBaaBBaBaaBaBBBBBBaBaaBBaBaaBa";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "BATS";
    int count_exp = 4;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_4, .description="description of test") {
    char plaintext_act[] = "*****";
    for (unsigned int i = 0; i < strlen(plaintext_act); i++)
        plaintext_act[i] = (char)(rand() % 200 + 33);
    char *ciphertext = "aaB aBB aBBaBaa aaaa aaB BaBaa aaaBBBBB BBB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "L A D";
    int count_exp = 5;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_5, .description="description of test") {
    char plaintext_act[] = "**************";
    for (unsigned int i = 0; i < strlen(plaintext_act); i++)
        plaintext_act[i] = (char)(rand() % 200 + 33);
    char *ciphertext = "aBaa BaaB aaB BaB aaB BaBaaBB aB BaB aaaaaaBaa aaa Baaa aaBa aaaa BaaBBaaBB BBBB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "STTT BBBBM";
    int count_exp = 10;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_6, .description="description of test") {
    char plaintext_act[] = "";
    char *ciphertext = "aBaa BaaB aaB BaB aaB BaBaaBB aB BaB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "";
    int count_exp = -1;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_7, .description="description of test") {
    char plaintext_act[] = "sa";
    char *ciphertext = "aBaa BaaB aaB BaB aaB BaBaaBB aB BaB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "sa";
    int count_exp = -2;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_8, .description="description of test") {
    char plaintext_act[] = "***";
    char *ciphertext = "aBa a Ba aaaaaaaa a aB BB BB BB B";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "SAD";
    int count_exp = 3;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_9, .description="description of test") {
    char plaintext_act[] = "***";
    char *ciphertext = "aaB a BBaa BBaaaaB BaBaaB BBaaaB BBBB BBBBB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "LMN";
    int count_exp = 3;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_10, .description="description of test") {
    char plaintext_act[] = "*****";
    char *ciphertext = "aaB a BBaa BBaaaaB BaBaaB BBaaaB BBBB BBBBB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "LMNOP";
    int count_exp = 5;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_11, .description="description of test") {
    char plaintext_act[] = "*****";
    char *ciphertext = "aaB a BBaa BBaaaaB BaBaaB BBaaaB BBB BBBBB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "*****";
    int count_exp = -2;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_12, .description="description of test") {
   char plaintext_act[] = "*";
    char *ciphertext = "aaB a BBaa BBaaaaB BaBaaB BBaaaB BBBB BBBBB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "L";
    int count_exp = 1;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_13, .description="description of test") {
   char plaintext_act[] = "**********";
    char *ciphertext = "BaaBaB BBBBBB";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "-";
    int count_exp = 1;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_14, .description="description of test") {
   char plaintext_act[] = "**********";
    char *ciphertext = "BaBaa aBaBaaB BaBaBaBaBaBBBaB BaaBaBBaBBaBBBaBaBBBB BBaaaaBB aaaBBBaaBa ";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "**********";
    int count_exp = -2;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_15, .description="description of test") {
   char plaintext_act[] = "***********";
    char *ciphertext = "BaBaa aBaBaaB BaBaBaBaBaBBBaB BaaBaBBaBBaBBBaBaBBBB BBaaaaBB aaaBBBaaBa BBBBBB aaa";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "0123456789:";
    int count_exp = 11;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_16, .description="description of test") {
   char plaintext_act[] = "***********";
    char *ciphertext = "aaaaaaBBBBBBBaBaa aBaBaaB BaBaBaBaBaBBBaB BaaBaBBaBBaBBBaBaBBBB BBaaaaBB aaaBBBaaBa";
    int count_act = decrypt(ciphertext, plaintext_act);  
    char *plaintext_exp = "A";
    int count_exp = 1;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}



Test(base_output, encrypt_1, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "In ancient Pompeii";
    char *plaintext = "R";
    encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    char *ciphertext_exp = "iN ancIENT POMpeii";
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
}
Test(base_return, encrypt_1, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "In ancient Pompeii";
    char *plaintext = "R";
    int count_act = encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    int count_exp = 1;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(base_output, encrypt_2, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "In ancient Pompeii are cools.";
    char *plaintext = "R .";
    encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    char *ciphertext_exp = "iN ancIeNT pOmPeiI ArE COOLS.";
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
}
Test(base_return, encrypt_2, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "In ancient Pompeii are cools.";
    char *plaintext = "R .";
    int count_act = encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    int count_exp = 3;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(base_output, encrypt_3, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "In ancient Pompeii, bakers made bread that has lasted until the present day.";
    char *plaintext = "Riddle.";
    encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    char *ciphertext_exp = "iN ancIenT pompeii, BAkers MAde BrEAd thAt hAs lAStED UNTIl the present day.";
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
}
Test(base_return, encrypt_3, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "In ancient Pompeii, bakers made bread that has lasted until the present day.";
    char *plaintext = "Riddle.";
    int count_act = encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    int count_exp = 7;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}



Test(base_output, encrypt_4, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "Foaming in disgust. Helllllo.";
    char *plaintext = "2-U.";
    encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    char *ciphertext_exp = "FoAmInG in DiSgUsT. heLLLLLO.";
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    
}
/*
Test(base_return, encrypt_4, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "Foaming in disgust. Hellllo.";
    char *plaintext = "2-U";
    int count_act = encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    int count_exp = 3;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}
*/


Test(base_output, encrypt_5, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "In ancient Pompeii, bakers made bread that hed unti.";
    char *plaintext = "Riddle";
    encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    char *ciphertext_exp = "iN ancIenT pompeii, BAkers MAde BrEAd thAt hED UNTI.";
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
}

Test(base_output, encrypt_6, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "In anci";
    char *plaintext = "Riddle";
    encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    char *ciphertext_exp = "IN ANCI";
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
}

Test(base_return, encrypt_6, .description="Ciphertext string has room only for three characters.") {
   char ciphertext_act[] = "In anci";
    char *plaintext = "Riddle";
    int count_act = encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    int count_exp = 0;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}


Test(base_output, encrypt_7, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "In anci inANCI";
    char *plaintext = "Riddle";
    encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    char *ciphertext_exp = "iN ancI INANCI";
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
}

Test(base_return, encrypt_7, .description="Ciphertext string has room only for three characters.") {
    char ciphertext_act[] = "In anci inANCI";
    char *plaintext = "Riddle";
    int count_act = encrypt(plaintext, ciphertext_act);  // s = 010010, t = 010011, o = 001110
    int count_exp = 1;
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}






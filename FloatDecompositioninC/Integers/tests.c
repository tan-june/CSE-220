#include <stdio.h>
#include "criterion/criterion.h"

#define TEST_TIMEOUT 3 
#define TEST_INPUT_DIR "tests.in"
#define TEST_OUTPUT_DIR "tests.out"

static char test_log_outfile[100];

int run_using_system(char *test_name, char *args) {
    sprintf(test_log_outfile, "%s/%s.log", TEST_OUTPUT_DIR, test_name);
    char cmd[500];
    sprintf(cmd, "mkdir -p %s", TEST_OUTPUT_DIR);
    system(cmd);
    sprintf(cmd, "./integers %s > %s 2>&1", args, test_log_outfile);
    return system(cmd);
}

void assert_outfile_matches(char *name) {
    char cmd[500];
    sprintf(cmd, "diff --strip-trailing-cr %s/%s.txt %s ", TEST_INPUT_DIR, name, test_log_outfile);
    int err = system(cmd);
    cr_assert_eq(err, 0, "The output was not what was expected (diff exited with status %d).\n", WEXITSTATUS(err));
}

TestSuite(base_suite, .timeout=TEST_TIMEOUT);

Test(base_suite, test_output01) {
    //passed
    char *test_name = "test_output01";
    run_using_system(test_name, "1 2 0xfffffffa");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output02) {
    //passed
    char *test_name = "test_output02";
    run_using_system(test_name, "2 1 0x00000020");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output03) {
    //passed
    char *test_name = "test_output03";
    run_using_system(test_name, "S 2 0x80000001");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output04) {
    //passed
    char *test_name = "test_output04";
    run_using_system(test_name, "1 S 0xfffffff0");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output05) {
    //passed
    char *test_name = "test_output05";
    run_using_system(test_name, "S 2 0x80000000");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output06) {
    //passed
    char *test_name = "test_output06";
    run_using_system(test_name, "1 1 0x59f2ca50");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output07) {
    //passed
    char *test_name = "test_output07";
    run_using_system(test_name, "F 1 0x00394812");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output08) {
    //should be undefined
    char *test_name = "test_output08";
    run_using_system(test_name, "2 1 0x80000000");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output09) {
    //passed
    char *test_name = "test_output09";
    run_using_system(test_name, "D 2 0x00411d01");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output10) {
    //passed - issue with return
    char *test_name = "test_output10";
    run_using_system(test_name, "D 2 0xa02837fa");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output11) {
    char *test_name = "test_output11";
    run_using_system(test_name, "1 D 0xfffff075");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output12) {
    char *test_name = "test_output12";
    run_using_system(test_name, "2 D 0x000000ff");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output13) {
    char *test_name = "test_output13";
    run_using_system(test_name, "S D 0x801252eb");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output14) {
    char *test_name = "test_output14";
    run_using_system(test_name, "1 2 0xffecc8a6");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output15) {
    char *test_name = "test_output15";
    run_using_system(test_name, "2 1 0xffff7912");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output16) {
    char *test_name = "test_output16";
    run_using_system(test_name, "S 1 0x86EE");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output17) {
    char *test_name = "test_output17";
    run_using_system(test_name, "1 S 0x86EE");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output18) {
    char *test_name = "test_output18";
    run_using_system(test_name, "2 1 0x86EE");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output19) {
    //should be undefined
    char *test_name = "test_output19";
    run_using_system(test_name, "1 2 0x80000001");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output20) {
    //should be undefined
    char *test_name = "test_output20";
    run_using_system(test_name, "2 D 0x80000001");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output21) {
    //should be undefined
    char *test_name = "test_output21";
    run_using_system(test_name, "2 D 0xfffd0c4f");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output22) {
    //should be undefined
    char *test_name = "test_output22";
    run_using_system(test_name, "S D 0xF423F");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output23) {
    //should be undefined
    char *test_name = "test_output23";
    run_using_system(test_name, "2 D 0xfff0bdc1");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output24) {
    char *test_name = "test_output24";
    run_using_system(test_name, "1 2 0x80000000");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output25) {
    char *test_name = "test_output25";
    run_using_system(test_name, "D 1 0x340045");
    assert_outfile_matches(test_name);
}

//BCD to 1's 2's and signMag's with Positive and Negative Numbers
Test(base_suite, test_output26) {
    char *test_name = "test_output26";
    run_using_system(test_name, "D 2 0x340045");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output27) {
    char *test_name = "test_output27";
    run_using_system(test_name, "D S 0x340045");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output28) {
    char *test_name = "test_output28";
    run_using_system(test_name, "D 2 0xC0340045");
    assert_outfile_matches(test_name);
}


Test(base_suite, test_output29) {
    char *test_name = "test_output29";
    run_using_system(test_name, "D 1 0xC0340045");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output30) {
    char *test_name = "test_output30";
    run_using_system(test_name, "D S 0xC0340045");
    assert_outfile_matches(test_name);
}

//1's to 2's, SignMag, BCD with Positive and Negative Numbers

Test(base_suite, test_output31) {
    char *test_name = "test_output31";
    run_using_system(test_name, "1 S 0xF4240");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output32) {
    char *test_name = "test_output32";
    run_using_system(test_name, "1 2 0xF4240");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output33) {
    char *test_name = "test_output33";
    run_using_system(test_name, "1 D 0xF4240");
    assert_outfile_matches(test_name);
}

//-1mil
Test(base_suite, test_output34) {
    //8000f4240
    char *test_name = "test_output34";
    run_using_system(test_name, "1 S 0xFFF0BDBF");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output35) {
    //fff0bdc0
    char *test_name = "test_output35";
    run_using_system(test_name, "1 2 0xFFF0BDBF");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output36) {

    char *test_name = "test_output36";
    run_using_system(test_name, "1 D 0xFFF0BDBF");
    assert_outfile_matches(test_name);
}

//2s to All (Positive and Negative)


Test(base_suite, test_output37) {
    char *test_name = "test_output37";
    run_using_system(test_name, "2 S 0x37E");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output38) {
    char *test_name = "test_output38";
    run_using_system(test_name, "2 1 0x37E");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output39) {
    char *test_name = "test_output39";
    run_using_system(test_name, "2 D 0x37E");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output40) {
    char *test_name = "test_output40";
    run_using_system(test_name, "2 2 0x37E");
    assert_outfile_matches(test_name);
}

//negative
Test(base_suite, test_output41) {
    //8000037e
    char *test_name = "test_output41";
    run_using_system(test_name, "2 S 0xFFFFFC82");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output42) {
    //fffffc82
    char *test_name = "test_output42";
    run_using_system(test_name, "2 2 0xFFFFFC82");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output43) {
    //fffffc81
    char *test_name = "test_output43";
    run_using_system(test_name, "2 1 0xFFFFFC82");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output44) {
    //06002124
    char *test_name = "test_output44";
    run_using_system(test_name, "2 D 0xFFFFFC82");
    assert_outfile_matches(test_name);
}

//SignMag to All (Positive and Negative)

Test(base_suite, test_output45) {
    //8000037e
    char *test_name = "test_output45";
    run_using_system(test_name, "S S 0x5A5E");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output46) {
    //fffffc82
    char *test_name = "test_output46";
    run_using_system(test_name, "S 2 0x5A5E");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output47) {
    //fffffc81
    char *test_name = "test_output47";
    run_using_system(test_name, "S 1 0x5A5E");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output48) {
    //06002124
    char *test_name = "test_output48";
    run_using_system(test_name, "S D 0x5A5E");
    assert_outfile_matches(test_name);
}

//negative
Test(base_suite, test_output49) {
    //0x80005a5e
    char *test_name = "test_output49";
    run_using_system(test_name, "S S 0x80005A5E");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output50) {
    //ffffa5a2
    char *test_name = "test_output50";
    run_using_system(test_name, "S 2 0x80005A5E");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output51) {
    //ffffa5a1
    char *test_name = "test_output51";
    run_using_system(test_name, "S 1 0x80005A5E");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output52) {
    //6218464
    char *test_name = "test_output52";
    run_using_system(test_name, "S D 0x80005A5E");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output53) {
    //6218464
    char *test_name = "test_output53";
    run_using_system(test_name, "1 S 0xffffffff");
    assert_outfile_matches(test_name);
}


Test(base_suite, test_output54) {
    //6218464
    char *test_name = "test_output54";
    run_using_system(test_name, "S 1 0x80000000");
    assert_outfile_matches(test_name);
}


Test(base_suite, test_output55) {
    //twos zeroes test
    char *test_name = "test_output55";
    run_using_system(test_name, "D 1 0xC0000000");
    assert_outfile_matches(test_name);
}


//checking bounds

Test(base_suite, test_output56) {
    //twos zeroes test
    char *test_name = "test_output56";
    run_using_system(test_name, "S 1 0xFFFFFFFF");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output57) {
    //twos zeroes test
    char *test_name = "test_output57";
    run_using_system(test_name, "1 S 0x80000000");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output58) {
    //c0000824
    char *test_name = "test_output58";
    run_using_system(test_name, "S D 0x800000D6");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output59) {
    //fffff29
    char *test_name = "test_output59";
    run_using_system(test_name, "S 1 0x800000D6");
    assert_outfile_matches(test_name);
}

Test(base_suite, test_output60) {
    //fffff2a
    char *test_name = "test_output60";
    run_using_system(test_name, "S 2 0x800000D6");
    assert_outfile_matches(test_name);
}
#include "testLab.h"
#include <stdio.h>
#include <string.h>

static int testN = 0;
static const struct {const char *const in, *const out;} testInOut[] = {
    {"(((((\n", "syntax error"},
    {"1/0\n", "division by zero"},
    {"2*2\n", "4"},
    {"bad input\n", "syntax error"},
    {"2.0*2.0\n", "syntax error"},
    {"123()\n", "syntax error"},
    {"()123\n", "syntax error"},
    {"1*2+3/4\n", "2"},
    {"1*(2+3)/4\n", "1"},
    {"1/2/3/4\n", "0"},
    {"1*2*3/4\n", "1"},
    {"1*2+3*4\n", "14"},
    {"1+2*3+4\n", "11"},
    {"1+3*2/(3-1-2)\n", "division by zero"},
    {"1--\n", "syntax error"},
    {"1-*\n", "syntax error"},
    {"1-1-*1\n", "syntax error"},
    {"--1\n", "syntax error"},
    {"11-\n", "syntax error"},
    {"()\n", "syntax error"},
    {"(-)\n", "syntax error"},
    {"\n", "syntax error"},
    {")\n", "syntax error"},
    {"1+1)(\n", "syntax error"},
    {"1 1\n", "syntax error"},
    {"1)+(2\n", "syntax error"},
    {"(1+2))+(3\n", "syntax error"},
    {"1234567890\n", "1234567890"},
    {"(1234567890)\n", "1234567890"},
    {"((1234567890))\n", "1234567890"},
    {"1+23+456+7890\n", "8370"},
    {"1-23-456-7890\n", "-8368"},
    {"(1)-(23)-(456)-(7890)\n", "-8368"},
    {"(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "((((((((((((((((((((((((((((((((((((((((\n", "syntax error"},
    {"((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
    "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((99"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1"
    ")+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)\n", "348"},
    {"1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
    "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1"
    "+1+1+1+1+1+1+1+1+1+1+1+99\n", "598"}
};

static int FeedFromArray(void) {
    FILE* const in = fopen("in.txt", "w+");
    if (in == NULL) {
        printf("can't create in.txt. No space on disk?\n");
        return -1;
    }
    fprintf(in, "%s", testInOut[testN].in);
    fclose(in);
    return 0;
}

static int CheckFromArray(void) {
    FILE* const out = fopen("out.txt", "r");
    if (out == NULL) {
        printf("can't open out.txt\n");
        testN++;
        return -1;
    }
    char buf[128] = {0};
    const char* status = ScanChars(out, sizeof(buf), buf);
    fclose(out);
    if (status == Pass && _strnicmp(testInOut[testN].out, buf, strlen(testInOut[testN].out)) != 0) {
        status = Fail;
    }
    if (status == Pass && HaveGarbageAtTheEnd(out)) {
        status = Fail;
    }
    printf("%s\n", status);
    ++testN;
    return status == Fail;
}

TLabTest GetLabTest(int testIdx) {
    (void)testIdx;
    TLabTest labTest = {FeedFromArray, CheckFromArray};
    return labTest;
}

int GetTestCount(void) {
    return sizeof(testInOut)/sizeof(testInOut[0]);
}

const char* GetTesterName(void) {
    return "Lab 4 Calc";
}

int GetTestTimeout(void) {
    return 3000;
}

size_t GetTestMemoryLimit(void) {
    return MIN_PROCESS_RSS_BYTES;
}

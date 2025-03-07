//
// Created by elito on 9/2/2024.
//

#pragma once


struct TestResult {
    TestResult(bool passed, unsigned int cycleCount) {
        Passed = passed;
        CycleCount = cycleCount;
    }

    bool Passed;
    unsigned int CycleCount;
};

class TestBase {


};

#define TEST_DECLARATION(test_name) \
const TestResult test_name();

#define RUN_TEST(test_name) \


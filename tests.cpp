#include "create_hand.h"
#include <string>

struct Test {
    ll hand;
    ll profit;
    ll hand_rank;
};


void print_bit_to_hand(ll bits) {
    std::vector<std::string> suits = {"C", "D", "H", "S"};
    std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};

    for (int i = 0; i < COLOR_COUNT; i++) {
        ll cur = bits & SET_FIRST_SUIT;
        for (int j = 0; j < 13; j++) {
            if (1ll << j & cur) cout << suits[i] << ranks[j] << " ";
        }
        bits >>= 13;
    }
}


void run_tests(std::vector<Test> tests, std::string name_of_test) {
    bool flag = true;
    for (auto el: tests) {
        Hand res = create_hand(el.hand);
        if (res.hand_rank != el.hand_rank || res.profit != el.profit) {
            if (flag) cout << "\n-------------------------------------------------\nError occured in " << name_of_test << endl;
            flag = false;
            cout << "*******************\nWrong test Case Hand: ";
            print_bit_to_hand(el.hand);
            if (res.hand_rank != el.hand_rank) cout << " hand_ranks are not equal " << " result: " << res.hand_rank << " should be: " << el.hand_rank << endl;
            if (res.profit    != el.profit) cout << "profits are not equal result: " << res.profit << " should be: " << el.profit << endl;
        }
    }
    if (flag) cout << name_of_test << " is successfully completed" << endl;
}


void royalFlush_straightFlush_test() {
    std::vector<Test> tests = {
        {CA | CK | CQ | CJ | CT | C9, 300, max_rank_bit},
        {DA | DK | DQ | DJ | DT | D9, 300, max_rank_bit},
        {HA | HK | HQ | HJ | HT | H9, 300, max_rank_bit},
        {SA | SK | SQ | SJ | ST | S9, 300, max_rank_bit},
    };
    run_tests(tests, "RoyalFlush_straightFlush Tests");
}

void straight_tests() {
    std::vector<Test> tests = {
        {C2 | C3 | D4 | D5 | H6, 8, straight_rank_bit | C6},
        {H3 | C4 | D5 | H6 | C7, 8, straight_rank_bit | C7},
        {D4 | C5 | H6 | S7 | S8, 8, straight_rank_bit | C8},
        {S5 | C6 | D7 | S8 | H9, 8, straight_rank_bit | C9},
        {S6 | C7 | D8 | C9 | HT, 8, straight_rank_bit | CT},
        {S7 | H8 | C9 | HT | DJ, 8, straight_rank_bit | CJ},
        {D8 | C9 | HT | SJ | CQ, 8, straight_rank_bit | CQ},
        {H9 | DT | CJ | DQ | SK, 8, straight_rank_bit | CK},
        {DT | DJ | DQ | DK | SA, 8, straight_rank_bit | CA},
        {HT | HJ | HQ | HK | CA, 8, straight_rank_bit | CA},
        {CT | CJ | CQ | CK | HA, 8, straight_rank_bit | CA},
        {ST | SJ | SQ | SK | CA, 8, straight_rank_bit | CA},
        {S6 | S7 | S8 | S9 | CT, 8, straight_rank_bit | CT},
        {C6 | S7 | S8 | S9 | CT, 8, straight_rank_bit | CT},
        {C6 | C7 | C8 | C9 | HT, 8, straight_rank_bit | CT},
        {D6 | D7 | D8 | D9 | ST, 8, straight_rank_bit | CT},
        {SA | D2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
        {HA | D2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
        {CA | D2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
        {DA | D2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
        {SA | C2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
        {HA | C2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
        {CA | C2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
        {DA | C2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
        {SA | H2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
        {HA | H2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
        {CA | H2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
        {DA | H2 | D3 | D4 | C5, 8, straight_rank_bit | C5},
    };
    run_tests(tests, "Straight Tests");
}

void straight_straight_tests() {
    std::vector<Test> tests = {
        {C2 | C3 | D4 | D5 | H6 | H7, 16, straight_rank_bit | C7},
        {H3 | C4 | D5 | H6 | C7 | H8, 16, straight_rank_bit | C8},
        {D4 | C5 | H6 | S7 | S8 | C9, 16, straight_rank_bit | C9},
        {S5 | C6 | D7 | S8 | H9 | DT, 16, straight_rank_bit | CT},
        {S6 | C7 | D8 | C9 | HT | DJ, 16, straight_rank_bit | CJ},
        {S7 | H8 | C9 | HT | DJ | SQ, 16, straight_rank_bit | CQ},
        {D8 | C9 | HT | SJ | CQ | CK, 16, straight_rank_bit | CK},
        {H9 | DT | CJ | DQ | SK | DA, 16, straight_rank_bit | CA},
        {S6 | S7 | S8 | S9 | CT | CJ, 16, straight_rank_bit | CJ},
        {C6 | S7 | S8 | S9 | CT | DJ, 16, straight_rank_bit | CJ},
        {C6 | C7 | C8 | C9 | HT | DJ, 16, straight_rank_bit | CJ},
        {D6 | D7 | D8 | D9 | ST | HJ, 16, straight_rank_bit | CJ},
        {SA | D2 | D3 | D4 | C5 | S6, 16, straight_rank_bit | C6},
        {HA | D2 | D3 | D4 | C5 | S6, 16, straight_rank_bit | C6},
        {CA | D2 | D3 | D4 | C5 | H6, 16, straight_rank_bit | C6},
        {DA | D2 | D3 | D4 | C5 | C6, 16, straight_rank_bit | C6},
        {SA | C2 | D3 | D4 | C5 | H6, 16, straight_rank_bit | C6},
        {HA | C2 | D3 | D4 | C5 | S6, 16, straight_rank_bit | C6},
        {CA | C2 | D3 | D4 | C5 | H6, 16, straight_rank_bit | C6},
        {DA | C2 | D3 | D4 | C5 | C6, 16, straight_rank_bit | C6},
        {SA | H2 | D3 | D4 | C5 | D6, 16, straight_rank_bit | C6},
        {HA | H2 | D3 | D4 | C5 | C6, 16, straight_rank_bit | C6},
        {CA | H2 | D3 | D4 | C5 | H6, 16, straight_rank_bit | C6},
        {DA | H2 | D3 | D4 | C5 | S6, 16, straight_rank_bit | C6},
    };
    run_tests(tests, "Straight_Straight tests");
}

void flush_tests() {
    std::vector<Test> tests = {
        {CA | CK | CQ | CJ | C9, 10, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {DA | DK | DQ | DJ | D9, 10, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {HA | HK | HQ | HJ | H9, 10, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {SA | SK | SQ | SJ | S9, 10, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {HT | H6 | H4 | H3 | H2, 10, flush_rank_bit | CT | C6 | C4 | C3 | C2},
        {D9 | D7 | D5 | D3 | D2, 10, flush_rank_bit | C9 | C7 | C5 | C3 | C2},
        {SQ | S9 | S7 | S5 | S2, 10, flush_rank_bit | CQ | C9 | C7 | C5 | C2},
        {CK | CJ | C8 | C5 | C4, 10, flush_rank_bit | CK | CJ | C8 | C5 | C4},
        {DJ | DT | D9 | D8 | D2, 10, flush_rank_bit | CJ | CT | C9 | C8 | C2},
        {HK | H5 | H4 | H3 | H2, 10, flush_rank_bit | CK | C5 | C4 | C3 | C2},
        {ST | S9 | S7 | S6 | S5, 10, flush_rank_bit | CT | C9 | C7 | C6 | C5},
        {DK | D8 | D7 | D6 | D5, 10, flush_rank_bit | CK | C8 | C7 | C6 | C5},
        {CQ | CJ | CT | C9 | C6, 10, flush_rank_bit | CQ | CJ | CT | C9 | C6},
        {D9 | D8 | D7 | D6 | D4, 10, flush_rank_bit | C9 | C8 | C7 | C6 | C4},
        {HT | H8 | H6 | H4 | H2, 10, flush_rank_bit | CT | C8 | C6 | C4 | C2},
        {ST | S9 | S8 | S7 | S5, 10, flush_rank_bit | CT | C9 | C8 | C7 | C5},
        {ST | S8 | S7 | S5 | S4, 10, flush_rank_bit | CT | C8 | C7 | C5 | C4},
        {ST | S9 | S6 | S5 | S4, 10, flush_rank_bit | CT | C9 | C6 | C5 | C4},
        {HT | H9 | H5 | H4 | H2, 10, flush_rank_bit | CT | C9 | C5 | C4 | C2},
    };
    run_tests(tests, "Flush tests");
}

void flush_flush_tests() {
    std::vector<Test> tests = {
        {CA | CK | CQ | CJ | C9 | C8, 20, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {DA | DK | DQ | DJ | D9 | D6, 20, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {HA | HK | HQ | HJ | H9 | H2, 20, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {SA | SK | SQ | SJ | S9 | S5, 20, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {CK | CJ | C8 | C5 | C4 | C3, 20, flush_rank_bit | CK | CJ | C8 | C5 | C4},
        {ST | S9 | S7 | S6 | S5 | S2, 20, flush_rank_bit | CT | C9 | C7 | C6 | C5},
        {DK | D8 | D7 | D6 | D5 | D2, 20, flush_rank_bit | CK | C8 | C7 | C6 | C5},
        {CQ | CJ | CT | C9 | C6 | C3, 20, flush_rank_bit | CQ | CJ | CT | C9 | C6},
        {D9 | D8 | D7 | D6 | D4 | D3, 20, flush_rank_bit | C9 | C8 | C7 | C6 | C4},
        {ST | S9 | S8 | S7 | S5 | S2, 20, flush_rank_bit | CT | C9 | C8 | C7 | C5},
        {ST | S8 | S7 | S5 | S4 | S3, 20, flush_rank_bit | CT | C8 | C7 | C5 | C4},
        {ST | S9 | S6 | S5 | S4 | S2, 20, flush_rank_bit | CT | C9 | C6 | C5 | C4},
        {SA | SK | SQ | SJ | S9 | S8, 20, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {HK | HQ | HJ | HT | H8 | H6, 20, flush_rank_bit | CK | CQ | CJ | CT | C8},
        {DQ | DJ | DT | D9 | D5 | D2, 20, flush_rank_bit | CQ | CJ | CT | C9 | C5},
        {CQ | CT | C9 | C8 | C6 | C5, 20, flush_rank_bit | CQ | CT | C9 | C8 | C6},
        {CA | CK | CQ | CJ | C9 | C8, 20, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {HJ | H9 | H8 | H7 | H6 | H4, 20, flush_rank_bit | CJ | C9 | C8 | C7 | C6},
    };
    run_tests(tests, "Flush_Flush tests");
}

void royalFlush_flush_tests() {
    std::vector<Test> tests = {
        {CA | CK | CQ | CJ | CT | C8, 210, max_rank_bit},
        {CA | CK | CQ | CJ | CT | C7, 210, max_rank_bit},
        {CA | CK | CQ | CJ | CT | C6, 210, max_rank_bit},
        {CA | CK | CQ | CJ | CT | C5, 210, max_rank_bit},
        {CA | CK | CQ | CJ | CT | C3, 210, max_rank_bit},
        {CA | CK | CQ | CJ | CT | C2, 210, max_rank_bit},
        {DA | DK | DQ | DJ | DT | D8, 210, max_rank_bit},
        {DA | DK | DQ | DJ | DT | D7, 210, max_rank_bit},
        {DA | DK | DQ | DJ | DT | D6, 210, max_rank_bit},
        {DA | DK | DQ | DJ | DT | D5, 210, max_rank_bit},
        {DA | DK | DQ | DJ | DT | D4, 210, max_rank_bit},
        {DA | DK | DQ | DJ | DT | D3, 210, max_rank_bit},
        {DA | DK | DQ | DJ | DT | D2, 210, max_rank_bit},
        {HA | HK | HQ | HJ | HT | H8, 210, max_rank_bit},
        {HA | HK | HQ | HJ | HT | H7, 210, max_rank_bit},
        {HA | HK | HQ | HJ | HT | H6, 210, max_rank_bit},
        {HA | HK | HQ | HJ | HT | H5, 210, max_rank_bit},
        {HA | HK | HQ | HJ | HT | H4, 210, max_rank_bit},
        {HA | HK | HQ | HJ | HT | H3, 210, max_rank_bit},
        {HA | HK | HQ | HJ | HT | H2, 210, max_rank_bit},
        {SA | SK | SQ | SJ | ST | S8, 210, max_rank_bit},
        {SA | SK | SQ | SJ | ST | S7, 210, max_rank_bit},
        {SA | SK | SQ | SJ | ST | S6, 210, max_rank_bit},
        {SA | SK | SQ | SJ | ST | S4, 210, max_rank_bit},
        {SA | SK | SQ | SJ | ST | S3, 210, max_rank_bit},
        {SA | SK | SQ | SJ | ST | S2, 210, max_rank_bit},
    };
    run_tests(tests, "RoyalFlush_flush Tests");
}

void royalFlush_straight_test() {
    std::vector<Test> tests = {
        {CA | CK | CQ | CJ | CT | D9, 208, max_rank_bit},
        {CA | CK | CQ | CJ | CT | H9, 208, max_rank_bit},
        {CA | CK | CQ | CJ | CT | S9, 208, max_rank_bit},
        {DA | DK | DQ | DJ | DT | C9, 208, max_rank_bit},
        {DA | DK | DQ | DJ | DT | H9, 208, max_rank_bit},
        {DA | DK | DQ | DJ | DT | S9, 208, max_rank_bit},
        {HA | HK | HQ | HJ | HT | C9, 208, max_rank_bit},
        {HA | HK | HQ | HJ | HT | D9, 208, max_rank_bit},
        {HA | HK | HQ | HJ | HT | S9, 208, max_rank_bit},
        {SA | SK | SQ | SJ | ST | C9, 208, max_rank_bit},
        {SA | SK | SQ | SJ | ST | D9, 208, max_rank_bit},
        {SA | SK | SQ | SJ | ST | H9, 208, max_rank_bit},
    };
    run_tests(tests, "RoyalFlush_straight Tests");
}

void straightFlush_straightFlush_tests() {
    std::vector<Test> tests = {
        {CK | CQ | CJ | CT | C9 | C8, 200, max_rank_bit},
        {CQ | CJ | CT | C9 | C8 | C7, 200, max_rank_bit},
        {CJ | CT | C9 | C8 | C7 | C6, 200, max_rank_bit},
        {DT | D9 | D8 | D7 | D6 | D5, 200, max_rank_bit},
        {D9 | D8 | D7 | D6 | D5 | D4, 200, max_rank_bit},
        {D8 | D7 | D6 | D5 | D4 | D3, 200, max_rank_bit},
        {H7 | H6 | H5 | H4 | H3 | H2, 200, max_rank_bit},
        {H6 | H5 | H4 | H3 | H2 | HA, 200, max_rank_bit},
        {HK | HQ | HJ | HT | H9 | H8, 200, max_rank_bit},
        {SQ | SJ | ST | S9 | S8 | S7, 200, max_rank_bit},
        {SJ | ST | S9 | S8 | S7 | S6, 200, max_rank_bit},
        {ST | S9 | S8 | S7 | S6 | S5, 200, max_rank_bit},
        {S6 | S5 | S4 | S3 | S2 | SA, 200, max_rank_bit},
        {H6 | H5 | H4 | H3 | H2 | HA, 200, max_rank_bit},
        {C6 | C5 | C4 | C3 | C2 | CA, 200, max_rank_bit},
        {D6 | D5 | D4 | D3 | D2 | DA, 200, max_rank_bit},
    };
    run_tests(tests, "StraightFlush_straightFlush Tests");
}

void straightFlush_flush_tests() {
    std::vector<Test> tests = {
        {CK | CQ | CJ | CT | C9 | C4, 110, max_rank_bit},
        {CQ | CJ | CT | C9 | C8 | C3, 110, max_rank_bit},
        {CJ | CT | C9 | C8 | C7 | C2, 110, max_rank_bit},
        {DT | D9 | D8 | D7 | D6 | D3, 110, max_rank_bit},
        {D9 | D8 | D7 | D6 | D5 | D2, 110, max_rank_bit},
        {D8 | D7 | D6 | D5 | D4 | D2, 110, max_rank_bit},
        {H7 | H6 | H5 | H4 | H3 | HA, 110, max_rank_bit},
        {H7 | H5 | H4 | H3 | H2 | HA, 110, max_rank_bit},
        {HK | HQ | HJ | HT | H9 | H6, 110, max_rank_bit},
        {SQ | SJ | ST | S9 | S8 | S6, 110, max_rank_bit},
        {SJ | ST | S9 | S8 | S7 | S3, 110, max_rank_bit},
        {SQ | S9 | S8 | S7 | S6 | S5, 110, max_rank_bit},
        {S9 | S5 | S4 | S3 | S2 | SA, 110, max_rank_bit},
        {HK | H5 | H4 | H3 | H2 | HA, 110, max_rank_bit},
        {C9 | C5 | C4 | C3 | C2 | CA, 110, max_rank_bit},
        {DJ | D5 | D4 | D3 | D2 | DA, 110, max_rank_bit},
    };
    run_tests(tests, "StraightFlush_flush Tests");
}

void straightFlush_straight_tests() {
    std::vector<Test> tests = {
        {CK | CQ | CJ | CT | C9 | D8, 108, max_rank_bit},
        {CQ | CJ | CT | C9 | C8 | H7, 108, max_rank_bit},
        {CJ | CT | C9 | C8 | C7 | S6, 108, max_rank_bit},
        {DT | D9 | D8 | D7 | D6 | H5, 108, max_rank_bit},
        {D9 | D8 | D7 | D6 | D5 | C4, 108, max_rank_bit},
        {D8 | D7 | D6 | D5 | D4 | C3, 108, max_rank_bit},
        {H7 | H6 | H5 | H4 | H3 | S2, 108, max_rank_bit},
        {H6 | H5 | H4 | H3 | H2 | CA, 108, max_rank_bit},
        {HK | HQ | HJ | HT | H9 | C8, 108, max_rank_bit},
        {SQ | SJ | ST | S9 | S8 | H7, 108, max_rank_bit},
        {SJ | ST | S9 | S8 | S7 | H6, 108, max_rank_bit},
        {CT | S9 | S8 | S7 | S6 | S5, 108, max_rank_bit},
        {C6 | S5 | S4 | S3 | S2 | SA, 108, max_rank_bit},
        {S6 | H5 | H4 | H3 | H2 | HA, 108, max_rank_bit},
        {D6 | C5 | C4 | C3 | C2 | CA, 108, max_rank_bit},
        {C6 | D5 | D4 | D3 | D2 | DA, 108, max_rank_bit},
    };
    run_tests(tests, "StraightFlush_straight Tests");
}

void quads_full_tests() {
    std::vector<Test> tests = {
        {CT | DT | ST | HT | CK | DK, 54, quad_rank_bit | CT},
        {CQ | DQ | HQ | SQ | C8 | S8, 54, quad_rank_bit | CQ},
        {CJ | DJ | HJ | SJ | H5 | S5, 54, quad_rank_bit | CJ},
        {CA | SA | HA | DA | C2 | H2, 54, quad_rank_bit | CA},
        {CA | SA | HA | DA | CK | HK, 54, quad_rank_bit | CA},
        {CA | SA | HA | DA | HQ | SQ, 54, quad_rank_bit | CA},
        {CK | SK | HK | DK | CJ | SJ, 54, quad_rank_bit | CK},
        {H6 | C6 | D6 | S6 | H5 | C5, 54, quad_rank_bit | C6},
        {C5 | D5 | H5 | S5 | H4 | C4, 54, quad_rank_bit | C5},
        {S4 | H4 | C4 | D4 | SA | HA, 54, quad_rank_bit | C4},
        {S4 | H4 | C4 | D4 | HA | CA, 54, quad_rank_bit | C4},
        {C3 | S3 | H3 | D3 | ST | HT, 54, quad_rank_bit | C3},
        {C2 | S2 | H2 | D2 | SA | HA, 54, quad_rank_bit | C2},
        {C2 | H2 | S2 | D2 | HK | SK, 54, quad_rank_bit | C2},
        {D2 | C2 | H2 | S2 | C3 | H3, 54, quad_rank_bit | C2},
    };
    run_tests(tests, "Quads_Full Tests");
}

void quads_aceKing_test() {
    std::vector<Test> tests = {
        {CA | DA | SA | HA | CA | DK, 42, quad_rank_bit | CA},
        {CA | DA | HA | SA | CA | SK, 42, quad_rank_bit | CA},
        {CA | DA | HA | SA | CA | HK, 42, quad_rank_bit | CA},
        {CA | DA | HA | SA | CA | CK, 42, quad_rank_bit | CA},
        {CK | DK | SK | HK | CK | DA, 42, quad_rank_bit | CK},
        {CK | DK | HK | SK | CK | SA, 42, quad_rank_bit | CK},
        {CK | DK | HK | SK | CK | HA, 42, quad_rank_bit | CK},
        {CK | DK | HK | SK | CK | CA, 42, quad_rank_bit | CK},
    };
    run_tests(tests, "Quads_aceKing Tests");
}

void full_full_tests() {
    std::vector<Test> tests = {
        {CA | DA | HA | SK | CK | DK, 28, full_rank_bit | CA | CK},
        {CA | DA | HA | SQ | CQ | DQ, 28, full_rank_bit | CA | CQ},
        {SA | HA | CA | SK | CK | DK, 28, full_rank_bit | CA | CK},
        {CA | DA | HA | SK | CK | DK, 28, full_rank_bit | CA | CK},
        {CA | DA | HA | SK | CK | DK, 28, full_rank_bit | CA | CK},
        {SA | HA | CA | S2 | C2 | D2, 28, full_rank_bit | CA | C2},
        {CA | DA | HA | S2 | C2 | D2, 28, full_rank_bit | CA | C2},
        {CQ | DQ | HQ | SJ | CJ | DJ, 28, full_rank_bit | CQ | CJ},
        {CJ | DJ | HJ | S2 | C2 | D2, 28, full_rank_bit | CJ | C2},
        {C9 | D9 | H9 | S6 | C6 | D6, 28, full_rank_bit | C9 | C6},
        {C7 | D7 | H7 | S5 | C5 | D5, 28, full_rank_bit | C7 | C5},
        {C4 | D4 | H4 | S2 | C2 | D2, 28, full_rank_bit | C4 | C2},
        {C3 | D3 | H3 | S2 | C2 | D2, 28, full_rank_bit | C3 | C2},
    };
    run_tests(tests, "Full_full Tests");
}

void full_aceKing_tests() {
    std::vector<Test> tests = {
        {CA | DK | HK | S7 | C7 | D7, 16, full_rank_bit | C7},
        {CA | DK | HK | SQ | CQ | DQ, 16, full_rank_bit | CQ},
        {SA | HK | CK | SK | C7 | D7, 16, full_rank_bit | CK},
        {CA | DK | HK | SK | C9 | D9, 16, full_rank_bit | CK},
        {CA | DA | HA | SK | C8 | D8, 16, full_rank_bit | CA},
        {SA | HA | CA | SK | C2 | D2, 16, full_rank_bit | CA},
        {CA | DA | HA | SK | C5 | D5, 16, full_rank_bit | CA},
        {CA | DA | HK | S5 | C5 | D5, 16, full_rank_bit | C5},
        {CA | DA | HK | SQ | CQ | DQ, 16, full_rank_bit | CQ},
        {CA | DA | HK | ST | CT | DT, 16, full_rank_bit | CT},
        {CA | DK | HK | SK | C2 | D2, 16, full_rank_bit | CK},
        {CA | DA | HA | SK | C2 | D2, 16, full_rank_bit | CA},
        {CA | DK | HK | SK | C2 | D2, 16, full_rank_bit | CK},
    };
    run_tests(tests, "Full_aceKing Tests");
}

void flush_straight_tests() {
    std::vector<Test> tests = {
        {CA | C2 | D3 | C4 | C5 | C6, 18, flush_rank_bit | C6 | C5 | C4 | C2 | CA},
        {CA | D2 | C3 | C4 | C5 | C9, 18, flush_rank_bit | C9 | C5 | C4 | C3 | CA},
        {DA | D2 | D3 | D4 | S5 | DK, 18, flush_rank_bit | CK | C4 | C3 | C2 | CA},
        {HK | DQ | HJ | HT | H9 | H3, 18, flush_rank_bit | CK | CJ | CT | C9 | C3},
        {SJ | S9 | S8 | H7 | S6 | S5, 18, flush_rank_bit | CJ | C9 | C8 | C6 | C5},
        {S9 | S8 | S7 | S6 | C5 | S2, 18, flush_rank_bit | C9 | C8 | C7 | C6 | C2},
        {D8 | D7 | H6 | D5 | D4 | D3, 18, flush_rank_bit | C8 | C7 | C5 | C4 | C3},
        {H7 | H5 | H4 | H3 | H2 | CA, 18, flush_rank_bit | C7 | C5 | C4 | C3 | C2},
        {DK | D5 | D4 | D3 | H2 | DA, 18, flush_rank_bit | CA | CK | C5 | C4 | C3},
        {CA | DQ | CJ | CT | C9 | C8, 18, flush_rank_bit | CA | CJ | CT | C9 | C8},
        {ST | S9 | S8 | C7 | S6 | S2, 18, flush_rank_bit | CT | C9 | C8 | C6 | C2},
        {CQ | HJ | HT | H9 | H8 | HA, 18, flush_rank_bit | CA | CJ | CT | C9 | C8},
        {DA | H2 | H3 | H4 | H5 | H9, 18, flush_rank_bit | C9 | C5 | C4 | C3 | C2},
    };
    run_tests(tests, "Flush_straight Tests");
}

void flush_pair_tests() {
    std::vector<Test> tests = {
        {CA | C2 | D2 | C4 | C5 | C6, 12, flush_rank_bit | C6 | C5 | C4 | C2 | CA},
        {CA | D9 | C3 | C4 | C5 | C9, 12, flush_rank_bit | C9 | C5 | C4 | C3 | CA},
        {DA | D2 | D3 | D4 | SK | DK, 12, flush_rank_bit | CK | C4 | C3 | C2 | CA},
        {HK | DT | HJ | HT | H9 | H3, 12, flush_rank_bit | CK | CJ | CT | C9 | C3},
        {SJ | S9 | S8 | HJ | S6 | S5, 12, flush_rank_bit | CJ | C9 | C8 | C6 | C5},
        {S9 | S8 | S7 | S6 | C2 | S2, 12, flush_rank_bit | C9 | C8 | C7 | C6 | C2},
        {D8 | D7 | H8 | D5 | D4 | D3, 12, flush_rank_bit | C8 | C7 | C5 | C4 | C3},
        {H7 | H5 | H4 | H3 | H2 | C7, 12, flush_rank_bit | C7 | C5 | C4 | C3 | C2},
        {DK | D5 | D4 | D3 | HA | DA, 12, flush_rank_bit | CA | CK | C5 | C4 | C3},
        {CA | DA | CJ | CT | C9 | C8, 12, flush_rank_bit | CA | CJ | CT | C9 | C8},
        {ST | S9 | S8 | C8 | S6 | S2, 12, flush_rank_bit | CT | C9 | C8 | C6 | C2},
        {CA | HJ | HT | H9 | H8 | HA, 12, flush_rank_bit | CA | CJ | CT | C9 | C8},
        {D2 | H2 | H3 | H4 | H5 | H9, 12, flush_rank_bit | C9 | C5 | C4 | C3 | C2},
    };
    run_tests(tests, "Flush_pair Tests");
}

void flush_aceKing_tests() {
    std::vector<Test> tests = {
        {CA | C2 | DK | C4 | C5 | C6, 12, flush_rank_bit | C6 | C5 | C4 | C2 | CA},
        {CA | DK | C3 | C4 | C5 | C9, 12, flush_rank_bit | C9 | C5 | C4 | C3 | CA},
        {DA | D2 | D3 | D4 | SK | DK, 12, flush_rank_bit | CK | C4 | C3 | C2 | CA},
        {HK | DA | HJ | HT | H9 | H3, 12, flush_rank_bit | CK | CJ | CT | C9 | C3},
        {CA | DK | CJ | CT | C9 | C8, 12, flush_rank_bit | CA | CJ | CT | C9 | C8},
        {CK | HJ | HT | H9 | H8 | HA, 12, flush_rank_bit | CA | CJ | CT | C9 | C8},
    };
    run_tests(tests, "Flush_aceKing Tests");
}

void straight_pair_tests() {
        std::vector<Test> tests = {
        {C2 | C3 | D4 | D5 | H6 | C6, 10, straight_rank_bit | C6},
        {H3 | C4 | D5 | H6 | C7 | C3, 10, straight_rank_bit | C7},
        {D4 | C5 | H6 | S7 | S8 | C8, 10, straight_rank_bit | C8},
        {S5 | C6 | D7 | S8 | H9 | C9, 10, straight_rank_bit | C9},
        {S6 | C7 | D8 | C9 | HT | CT, 10, straight_rank_bit | CT},
        {S7 | H8 | C9 | HT | DJ | CJ, 10, straight_rank_bit | CJ},
        {D8 | C9 | HT | SJ | CQ | DQ, 10, straight_rank_bit | CQ},
        {H9 | DT | CJ | DQ | SK | DK, 10, straight_rank_bit | CK},
        {HT | HJ | HQ | HK | CA | DA, 10, straight_rank_bit | CA},
        {CT | CJ | CQ | CK | HA | DJ, 10, straight_rank_bit | CA},
        {ST | SJ | SQ | SK | CA | DT, 10, straight_rank_bit | CA},
        {S6 | S7 | S8 | S9 | CT | D9, 10, straight_rank_bit | CT},
        {C6 | S7 | S8 | S9 | CT | HT, 10, straight_rank_bit | CT},
        {C6 | C7 | C8 | C9 | HT | H9, 10, straight_rank_bit | CT},
        {D6 | D7 | D8 | D9 | ST | H8, 10, straight_rank_bit | CT},
        {SA | D2 | D3 | D4 | C5 | H3, 10, straight_rank_bit | C5},
        {HA | D2 | D3 | D4 | C5 | H2, 10, straight_rank_bit | C5},
        {CA | D2 | D3 | D4 | C5 | HA, 10, straight_rank_bit | C5},
        {DA | D2 | D3 | D4 | C5 | SA, 10, straight_rank_bit | C5},
        {SA | C2 | D3 | D4 | C5 | HA, 10, straight_rank_bit | C5},
        {HA | C2 | D3 | D4 | C5 | CA, 10, straight_rank_bit | C5},
        {CA | C2 | D3 | D4 | C5 | S5, 10, straight_rank_bit | C5},
        {DA | C2 | D3 | D4 | C5 | S4, 10, straight_rank_bit | C5},
        {SA | H2 | D3 | D4 | C5 | S2, 10, straight_rank_bit | C5},
        {HA | H2 | D3 | D4 | C5 | D2, 10, straight_rank_bit | C5},
        {CA | H2 | D3 | D4 | C5 | C2, 10, straight_rank_bit | C5},
        {DA | H2 | D3 | D4 | C5 | D2, 10, straight_rank_bit | C5},
    };
    run_tests(tests, "Straight_pair Tests");
}

void straight_aceKing_tests() {
    std::vector<Test> tests = {
        {SA | D2 | D3 | D4 | C5 | HK, 10, straight_rank_bit | C5},
        {HA | D2 | D3 | D4 | C5 | HK, 10, straight_rank_bit | C5},
        {CA | D2 | D3 | D4 | C5 | HK, 10, straight_rank_bit | C5},
        {DA | D2 | D3 | D4 | C5 | SK, 10, straight_rank_bit | C5},
        {SA | C2 | D3 | D4 | C5 | HK, 10, straight_rank_bit | C5},
        {HA | C2 | D3 | D4 | C5 | CK, 10, straight_rank_bit | C5},
        {HA | C2 | D3 | D4 | C5 | DK, 10, straight_rank_bit | C5},
        {CA | C2 | D3 | D4 | C5 | DK, 10, straight_rank_bit | C5},
        {DA | C2 | D3 | D4 | C5 | DK, 10, straight_rank_bit | C5},
        {CA | C2 | D3 | D4 | C5 | SK, 10, straight_rank_bit | C5},
        {DA | C2 | D3 | D4 | C5 | SK, 10, straight_rank_bit | C5},
        {SA | H2 | D3 | D4 | C5 | SK, 10, straight_rank_bit | C5},
        {HA | H2 | D3 | D4 | C5 | DK, 10, straight_rank_bit | C5},
        {CA | H2 | D3 | D4 | C5 | CK, 10, straight_rank_bit | C5},
        {DA | H2 | D3 | D4 | C5 | DK, 10, straight_rank_bit | C5},
    };
    run_tests(tests, "Straight_aceKing Tests");
}

void threeOfKind_aceKing_tests() {
    std::vector<Test> tests = {
        {S9 | D9 | H9 | DA | C5 | HK, 8, threeOfKind_rank_bit | C9},
        {H2 | D2 | S2 | H4 | CA | HK, 8, threeOfKind_rank_bit | C2},
        {C3 | D3 | H3 | C4 | SA | HK, 8, threeOfKind_rank_bit | C3},
        {H8 | S8 | D8 | S4 | CA | SK, 8, threeOfKind_rank_bit | C8},
        {SQ | CQ | DQ | S2 | DA | HK, 8, threeOfKind_rank_bit | CQ},
        {HJ | CJ | DJ | S9 | CA | CK, 8, threeOfKind_rank_bit | CJ},
        {H2 | C2 | D2 | CQ | DA | DK, 8, threeOfKind_rank_bit | C2},
        {C3 | H3 | S3 | CJ | HA | DK, 8, threeOfKind_rank_bit | C3},
        {D4 | C4 | H4 | CT | HA | DK, 8, threeOfKind_rank_bit | C4},
        {C5 | S5 | D5 | C8 | DA | SK, 8, threeOfKind_rank_bit | C5},
        {D6 | C6 | H6 | H7 | SA | SK, 8, threeOfKind_rank_bit | C6},
        {S9 | H9 | D9 | DT | SA | SK, 8, threeOfKind_rank_bit | C9},
        {HT | CT | DT | DJ | CA | DK, 8, threeOfKind_rank_bit | CT},
        {CJ | HJ | DJ | HQ | DA | CK, 8, threeOfKind_rank_bit | CJ},
        {CJ | HJ | DJ | D2 | HA | DK, 8, threeOfKind_rank_bit | CJ},
    };
    run_tests(tests, "ThreeOfKind_aceKing Tests");
}


void twoPair_twoPair_tests() {
    std::vector<Test> tests = {
        {SQ | DQ | H6 | D6 | C3 | H3, 6, twoPair_rank_bit | DQ | D6 | C3 },
        {HA | DA | SK | HK | C5 | H5, 6, twoPair_rank_bit | DA | DK | C5 },
        {CK | DK | HQ | CQ | SJ | HJ, 6, twoPair_rank_bit | DK | DQ | CJ },
        {CA | SA | DK | SK | CQ | SQ, 6, twoPair_rank_bit | DA | DK | CQ },
        {SA | CA | D2 | S2 | D3 | H3, 6, twoPair_rank_bit | DA | D3 | C2 },
        {HJ | CJ | D9 | S9 | C5 | D5, 6, twoPair_rank_bit | DJ | D9 | C5 },
        {HT | CT | D8 | C8 | D4 | H4, 6, twoPair_rank_bit | DT | D8 | C4 },
        {C9 | H9 | S7 | C7 | H5 | D5, 6, twoPair_rank_bit | D9 | D7 | C5 },
        {D8 | C8 | H6 | C6 | H4 | D4, 6, twoPair_rank_bit | D8 | D6 | C4 },
        {C5 | S5 | D4 | C4 | D3 | S3, 6, twoPair_rank_bit | D5 | D4 | C3 },
        {D4 | C4 | H3 | C3 | H2 | S2, 6, twoPair_rank_bit | D4 | D3 | C2 },
        {SA | HA | D3 | C3 | S2 | D2, 6, twoPair_rank_bit | DA | D3 | C2 },
        {HK | CK | D3 | H3 | C2 | D2, 6, twoPair_rank_bit | DK | D3 | C2 },
        {CQ | HQ | D5 | H5 | D2 | C2, 6, twoPair_rank_bit | DQ | D5 | C2 },
        {C8 | H8 | D5 | H5 | H3 | D3, 6, twoPair_rank_bit | D8 | D5 | C3 },
    };
    run_tests(tests, "twoPair_twoPair Tests");
}

void twoPair_aceKing_tests() {
    std::vector<Test> tests = {
        {SQ | DQ | H6 | D6 | CA | HK, 6, twoPair_rank_bit | DQ | D6 | CA },
        {CK | DK | HQ | CQ | SA | H5, 6, twoPair_rank_bit | DK | DQ | CA },
        {SA | CA | D2 | S2 | DK | H4, 6, twoPair_rank_bit | DA | D2 | CK },
        {HJ | CJ | D9 | S9 | CA | DK, 6, twoPair_rank_bit | DJ | D9 | CA },
        {HT | CT | D8 | C8 | DA | HK, 6, twoPair_rank_bit | DT | D8 | CA },
        {C9 | H9 | S7 | C7 | HA | DK, 6, twoPair_rank_bit | D9 | D7 | CA },
        {D8 | C8 | H6 | C6 | HA | DK, 6, twoPair_rank_bit | D8 | D6 | CA },
        {C5 | S5 | D4 | C4 | DA | SK, 6, twoPair_rank_bit | D5 | D4 | CA },
        {D4 | C4 | H3 | C3 | HA | SK, 6, twoPair_rank_bit | D4 | D3 | CA },
        {SA | HA | D3 | C3 | SK | D5, 6, twoPair_rank_bit | DA | D3 | CK },
        {HK | CK | D3 | H3 | CA | D2, 6, twoPair_rank_bit | DK | D3 | CA },
        {CQ | HQ | D5 | H5 | DA | CK, 6, twoPair_rank_bit | DQ | D5 | CA },
        {C8 | H8 | D5 | H5 | HA | DK, 6, twoPair_rank_bit | D8 | D5 | CA },
        {HK | CK | D3 | H3 | CA, 6, twoPair_rank_bit | DK | D3 | CA },
        {CK | HK | D5 | H5 | DA, 6, twoPair_rank_bit | DK | D5 | CA },
        {CK | HK | D5 | H5 | HA, 6, twoPair_rank_bit | DK | D5 | CA },
        {HK | C3 | D3 | HA | CA, 6, twoPair_rank_bit | DA | D3 | CK },
        {CK | H5 | D5 | HA | DA, 6, twoPair_rank_bit | DA | D5 | CK },
        {CK | H5 | D5 | CA | HA, 6, twoPair_rank_bit | DA | D5 | CK },
    };
    run_tests(tests, "twoPair_Aceking Tests");
}

void pair_aceKing_tests() {
    std::vector<Test> tests = {
        {SQ | DQ | C6 | D4 | DA | HK, 4, onePair_rank_bit | DQ | CA | CK | C6},
        {HQ | SQ | S2 | S3 | CA | DK, 4, onePair_rank_bit | DQ | CA | CK | C3},
        {SQ | CQ | H9 | D4 | SA | SK, 4, onePair_rank_bit | DQ | CA | CK | C9},
        {CT | DT | SJ | C9 | CA | HK, 4, onePair_rank_bit | DT | CA | CK | CJ},
        {D8 | H8 | DQ | H3 | HA | DK, 4, onePair_rank_bit | D8 | CA | CK | CQ},
        {SK | DK | DQ | CJ | DA | H9, 4, onePair_rank_bit | DK | CA | CQ | CJ},
        {CK | HK | HT | D3 | HA | D2, 4, onePair_rank_bit | DK | CA | CT | C3},
        {HK | DK | SJ | ST | DA | S9, 4, onePair_rank_bit | DK | CA | CJ | CT},
        {DK | CK | H2 | C3 | CA | H4, 4, onePair_rank_bit | DK | CA | C4 | C3},
        {CK | DK | C5 | H6 | SA | S7, 4, onePair_rank_bit | DK | CA | C7 | C6},
        {SK | HK | HQ | HT | DA | C2, 4, onePair_rank_bit | DK | CA | CQ | CT},
        {SA | DA | HK | DT | D9 | C8, 4, onePair_rank_bit | DA | CK | CT | C9},
        {CA | SA | DK | C2 | H3 | H4, 4, onePair_rank_bit | DA | CK | C4 | C3},
        {HA | DA | CK | DQ | CJ | S9, 4, onePair_rank_bit | DA | CK | CQ | CJ},
        {SA | CA | SK | H4 | S3 | H2, 4, onePair_rank_bit | DA | CK | C4 | C3},
        {SA | HA | HK | S5 | C3 | D2, 4, onePair_rank_bit | DA | CK | C5 | C3},
        {HA | DA | CK | D8 | S3 | H2, 4, onePair_rank_bit | DA | CK | C8 | C3},
    };
    run_tests(tests, "PairAceKing Tests");
}



int main() {
    // perft testi oluşturduğun filter fonksiyonu ile yapman çok daha basit olur ve matematik kullanarak

    royalFlush_straightFlush_test();
    royalFlush_flush_tests();
    royalFlush_straight_test();
    straightFlush_straightFlush_tests();
    straightFlush_flush_tests();
    quads_full_tests();
    quads_aceKing_test();
    full_full_tests();
    full_aceKing_tests();
    flush_flush_tests();
    flush_straight_tests();
    flush_pair_tests();
    flush_aceKing_tests();
    straight_straight_tests();
    straight_pair_tests();
    straight_aceKing_tests();
    threeOfKind_aceKing_tests();
    twoPair_twoPair_tests();
    twoPair_aceKing_tests();
    pair_aceKing_tests();
    
    straight_tests();
    flush_tests();
}
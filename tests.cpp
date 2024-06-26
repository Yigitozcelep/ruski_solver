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

    for (int i = 0; i < 4; i++) {
        ll cur = bits & ((1 << 14) - 1);
        for (int j = 1; j < 14; j++) {
            if (1ll << j & cur) cout << suits[i] << ranks[j - 1] << " ";
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
        {D6 | D7 | D8 | D9 | DT | HJ, 16, straight_rank_bit | CJ},
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
        {DK | D8 | D7 | D6 | D5 | D4, 20, flush_rank_bit | CK | C8 | C7 | C6 | C5},
        {CQ | CJ | CT | C9 | C6 | C3, 20, flush_rank_bit | CQ | CJ | CT | C9 | C6},
        {D9 | D8 | D7 | D6 | D4 | D3, 20, flush_rank_bit | C9 | C8 | C7 | C6 | C4},
        {ST | S9 | S8 | S7 | S5 | S2, 20, flush_rank_bit | CT | C9 | C8 | C7 | C5},
        {ST | S8 | S7 | S5 | S4 | S3, 20, flush_rank_bit | CT | C8 | C7 | C5 | C4},
        {ST | S9 | S6 | S5 | S4 | S2, 20, flush_rank_bit | CT | C9 | C6 | C5 | C4},
        {SA | SK | SQ | SJ | S9 | S8, 20, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {HK | HQ | HJ | HT | H8 | H6, 20, flush_rank_bit | CK | CQ | CJ | CT | C8},
        {DQ | DJ | DT | D9 | D8 | D7, 20, flush_rank_bit | CQ | CJ | CT | C9 | C8},
        {CQ | CT | C9 | C8 | C6 | C5, 20, flush_rank_bit | CQ | CT | C9 | C8 | C6},
        {CA | CK | CQ | CJ | C9 | C8, 20, flush_rank_bit | CA | CK | CQ | CJ | C9},
        {HJ | H9 | H8 | H7 | H6 | H4, 20, flush_rank_bit | CJ | C9 | C8 | C7 | C6},
    };
    run_tests(tests, "Flush_Flush tests");
}

int main() {
    straight_tests();
    straight_straight_tests();
    flush_tests();
    flush_flush_tests();
    royalFlush_straightFlush_test();
}
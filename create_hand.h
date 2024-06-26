#ifndef CREATE_HAND_H
#define CREATE_HAND_H

#include <iostream>
#include <bitset>
#include <algorithm>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

#define ll long long
#define ull unsigned long long
#define bit_count __builtin_popcountll



const ll C2 = 1ll << 1;
const ll C3 = 1ll << 2;
const ll C4 = 1ll << 3;
const ll C5 = 1ll << 4;
const ll C6 = 1ll << 5;
const ll C7 = 1ll << 6;
const ll C8 = 1ll << 7;
const ll C9 = 1ll << 8;
const ll CT = 1ll << 9;
const ll CJ = 1ll << 10;
const ll CQ = 1ll << 11;
const ll CK = 1ll << 12;
const ll CA = 1ll << 13;

const ll D2 = 1ll << 14;
const ll D3 = 1ll << 15;
const ll D4 = 1ll << 16;
const ll D5 = 1ll << 17;
const ll D6 = 1ll << 18;
const ll D7 = 1ll << 19;
const ll D8 = 1ll << 20;
const ll D9 = 1ll << 21;
const ll DT = 1ll << 22;
const ll DJ = 1ll << 23;
const ll DQ = 1ll << 24;
const ll DK = 1ll << 25;
const ll DA = 1ll << 26;

const ll H2 = 1ll << 27;
const ll H3 = 1ll << 28;
const ll H4 = 1ll << 29;
const ll H5 = 1ll << 30;
const ll H6 = 1ll << 31;
const ll H7 = 1ll << 32;
const ll H8 = 1ll << 33;
const ll H9 = 1ll << 34;
const ll HT = 1ll << 35;
const ll HJ = 1ll << 36;
const ll HQ = 1ll << 37;
const ll HK = 1ll << 38;
const ll HA = 1ll << 39;

const ll S2 = 1ll << 40;
const ll S3 = 1ll << 41;
const ll S4 = 1ll << 42;
const ll S5 = 1ll << 43;
const ll S6 = 1ll << 44;
const ll S7 = 1ll << 45;
const ll S8 = 1ll << 46;
const ll S9 = 1ll << 47;
const ll ST = 1ll << 48;
const ll SJ = 1ll << 49;
const ll SQ = 1ll << 50;
const ll SK = 1ll << 51;
const ll SA = 1ll << 52;

struct Hand {
    ll bits;
    ll hand_rank;
    int profit;
};

std::ostream& operator<<(std::ostream& os, const Hand& x) {
    os << x.bits << "," << x.hand_rank << "," << x.profit;
    return os;
}

const ll max_rank_bit           = 1ll << 63;
const ll quad_rank_bit          = 1ll << 62;
const ll full_rank_bit          = 1ll << 61;
const ll flush_rank_bit         = 1ll << 60;
const ll straight_rank_bit      = 1ll << 59;
const ll threeOfKind_rank_bit   = 1ll << 58;
const ll twoPair_rank_bit       = 1ll << 57;
const ll onePair_rank_bit       = 1ll << 56;
const ll aceKing_rank_bit       = 1ll << 55;

std::vector<ll> create_bits() {
    std::vector<ll> nums;
    ll limit = 1ll << 52;
    for (ll i = 1ll; i < limit; i <<= 1) {
        for (ll j = i << 1; j < limit; j <<= 1) {
            for (ll k = j << 1; k < limit; k <<= 1) {
                for (ll l = k << 1; l < limit; l <<= 1) {
                    for (ll m = l << 1; m < limit; m <<= 1) {
                        nums.push_back(i | j | k | l | m);
                        for (ll n = m << 1; n < limit; n <<= 1) {
                           nums.push_back(i | j | k | l | m | n);
                        }
                    }
                }
            }
        }
    }
    return nums;
}

ll _get_straight_with_count(ll bits, int count) {
    for (ll i = 1ll << 13; i > count; i >>= 1) {
        if ((bits & (i | i << 13 | i << 26 | i << 39 | i << 52)) == 0) continue;
        for (ll j = i >> 1; bits & (j | (j << 13) | (j << 26) | (j << 39) | (j << 52)); j >>= 1) {
            if (j == i >> (count - 1)) return i | straight_rank_bit;
        }
    }
    return 0;
}


ll aceKing(ll bits) {
    return bit_count(bits & (CA | DA | HA | SA)) == 1 && bit_count(bits & (CK | DK | HK | SK)) == 1;
}

ll straight_straight(ll bits) {
    return _get_straight_with_count(bits, 6);
}

ll flush_flush(ll bits) {
    for (int i = 0; i < 4; i++) {
        ll cur = bits & ((1ll << 14) - 1);
        if (bit_count(cur) == 6) return flush_rank_bit | (cur & (cur - 1));
        bits >>= 13;
    }
    return 0;
}

ll straight(ll bits) {
    return _get_straight_with_count(bits, 5);
}


bool royalFlush_flush(ll bits) {
    return aceKing(bits) && straight(bits) && flush_flush(bits);
}

bool royalFlush_straight(ll bits) {
    return aceKing(bits) && straight_straight(bits) && flush_flush(bits);
}

bool straightFlush_straightFlush(ll bits) {
    return false;
}

bool straightFlush_flush(ll bits) {
    return false;
}

bool straightFlush_straight(ll bits) {
    return false;
}

bool straightFlush_ace_king(ll bits) {
    return false;
}

bool quads_full(ll bits){
    return false;
}

bool quads_aceKing(ll bits) {
    return false;
}

ll full_full(ll bits) {
    return false;
}

ll full_aceKing(ll bits) {
    return false;
}


ll flush_straight(ll bits) {
    return false;
}

ll flush_pair(ll bits) {
    return false;
}

ll flush_aceKing(ll bits) {
    return false;
}

ll straight_aceKing(ll bits) {
    return false;
}

ll threeOfKind_aceKing(ll bits) {
    return false;
}

ll twoPair_twoPair(ll bits) {
    return false;
}

ll twoPair_aceKing(ll bits) {
    return false;
}

ll onePair_aceKing(ll bits) {
    return false;
}

bool royalFlush(ll bits) {
    return false;
}

bool straightFlush(ll bits) {
    return false;
}

ll quads(ll bits) {
    return false;
}

ll full(ll bits) {
    return false;
}

ll flush(ll bits) {
    for (int i = 0; i < 4; i++) {
        ll cur = bits & ((1ll << 14) - 1);
        if (bit_count(cur) == 5) return flush_rank_bit | cur;
        bits >>= 13;
    }
    return 0;
}

ll threeOfKind(ll bits) {
    return false;
}

ll twoPair(ll bits) {
    return false;
}

ll onePair(ll bits) {
    return false;
}

bool royalFlush_straightFlush(ll bits) {
    return (straight_straight(bits) && flush_flush(bits) && aceKing(bits));
}


Hand create_hand(ll bits) {
    Hand current_hand;
    current_hand.bits      = bits;
    current_hand.hand_rank = 0;
    if (royalFlush_straightFlush(bits)) {
        current_hand.hand_rank |= max_rank_bit;
        current_hand.profit     = 150 * 2;
        return current_hand;
    }
    if (royalFlush_flush(bits)) {
        current_hand.hand_rank |= max_rank_bit;
        current_hand.profit     = 105 * 2;
        return current_hand;
    }

    if (royalFlush_straight(bits)) {
        current_hand.hand_rank |= max_rank_bit;
        current_hand.profit     = 104 * 2;
        return current_hand;
    }

    if (straightFlush_straightFlush(bits)) {
        current_hand.hand_rank |= max_rank_bit;
        current_hand.profit     = 100 * 2;
        return current_hand;
    }

    if (straightFlush_flush(bits)) {
        current_hand.hand_rank |= max_rank_bit;
        current_hand.profit     = 55 * 2;
        return current_hand;
    }

    if (straightFlush_straight(bits)) {
        current_hand.hand_rank |= max_rank_bit;
        current_hand.profit     = 54 * 2;
        return current_hand;
    }

    if (straightFlush_ace_king(bits)) {
        current_hand.hand_rank |= max_rank_bit;
        current_hand.profit     = 51 * 2;
        return current_hand;
    }

    if (quads_full(bits)) {
        current_hand.hand_rank  = quads(bits);
        current_hand.profit     = 27 * 2;
        return current_hand;
    }

    if (quads_aceKing(bits)) {
        current_hand.hand_rank  = quads(bits);
        current_hand.profit     = 21 * 2;
        return current_hand;
    }

    if (ll hand_rank = full_full(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 14 * 2;
        return current_hand;
    }

    if (ll hand_rank = full_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    =  8 * 2;
        return current_hand;
    }

    if (ll hand_rank = flush_flush(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 10 * 2;
        return current_hand;
    }

    if (ll hand_rank = flush_straight(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 9 * 2;
        return current_hand;
    }

    if (ll hand_rank = flush_pair(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 6 * 2;
        return current_hand;
    }

    if (ll hand_rank = flush_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 6 * 2;
        return current_hand;
    }

    if (ll hand_rank = straight_straight(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 8 * 2;
        return current_hand;
    }

    if (ll hand_rank = straight_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 5 * 2;
        return current_hand;
    }

    if (ll hand_rank = threeOfKind_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 4 * 2;
        return current_hand;
    }

    if (ll hand_rank = twoPair_twoPair(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 4 * 2;
        return current_hand;
    }

    if (ll hand_rank = twoPair_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 3 * 2;
        return current_hand;
    }

    if (ll hand_rank = onePair_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 2 * 2;
        return current_hand;
    }

    if (royalFlush(bits)) {
        current_hand.hand_rank = max_rank_bit;
        current_hand.profit    = 100 * 2;
        return current_hand;
    }

    if (straightFlush(bits)) {
        current_hand.hand_rank = max_rank_bit;
        current_hand.profit    = 50 * 2;
        return current_hand;
    }

    if (ll hand_rank = quads(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 20 * 2;
        return current_hand;
    }

    if (ll hand_rank = full(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 7 * 2;
        return current_hand;
    }

    if (ll hand_rank = flush(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 5 * 2;
        return current_hand;
    }

    
    if (ll hand_rank = straight(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 4 * 2;
        return current_hand;
    }

    if (ll hand_rank = threeOfKind(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 3 * 2;
        return current_hand;
    }

    if (ll hand_rank = twoPair(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 2 * 2;
        return current_hand;
    }

    if (ll hand_rank = onePair(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 1 * 2;
    }

    if (ll hand_rank = aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 1 * 2;
        return current_hand;
    }
    
    current_hand.hand_rank = 0;
    current_hand.profit    = 0;
    return current_hand;
}

std::vector<Hand> get_every_hand() {
    std::vector<ll> bits = create_bits();
    std::vector<Hand> hands;
    for (auto el: bits) hands.push_back(create_hand(el));
    return hands;
}

#endif
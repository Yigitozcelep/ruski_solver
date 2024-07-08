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



const ll C2 = 1ll << 0;
const ll C3 = 1ll << 1;
const ll C4 = 1ll << 2;
const ll C5 = 1ll << 3;
const ll C6 = 1ll << 4;
const ll C7 = 1ll << 5;
const ll C8 = 1ll << 6;
const ll C9 = 1ll << 7;
const ll CT = 1ll << 8;
const ll CJ = 1ll << 9;
const ll CQ = 1ll << 10;
const ll CK = 1ll << 11;
const ll CA = 1ll << 12;

const ll D2 = 1ll << 13;
const ll D3 = 1ll << 14;
const ll D4 = 1ll << 15;
const ll D5 = 1ll << 16;
const ll D6 = 1ll << 17;
const ll D7 = 1ll << 18;
const ll D8 = 1ll << 19;
const ll D9 = 1ll << 20;
const ll DT = 1ll << 21;
const ll DJ = 1ll << 22;
const ll DQ = 1ll << 23;
const ll DK = 1ll << 24;
const ll DA = 1ll << 25;

const ll H2 = 1ll << 26;
const ll H3 = 1ll << 27;
const ll H4 = 1ll << 28;
const ll H5 = 1ll << 29;
const ll H6 = 1ll << 30;
const ll H7 = 1ll << 31;
const ll H8 = 1ll << 32;
const ll H9 = 1ll << 33;
const ll HT = 1ll << 34;
const ll HJ = 1ll << 35;
const ll HQ = 1ll << 36;
const ll HK = 1ll << 37;
const ll HA = 1ll << 38;

const ll S2 = 1ll << 39;
const ll S3 = 1ll << 40;
const ll S4 = 1ll << 41;
const ll S5 = 1ll << 42;
const ll S6 = 1ll << 43;
const ll S7 = 1ll << 44;
const ll S8 = 1ll << 45;
const ll S9 = 1ll << 46;
const ll ST = 1ll << 47;
const ll SJ = 1ll << 48;
const ll SQ = 1ll << 49;
const ll SK = 1ll << 50;
const ll SA = 1ll << 51;

const ll ACE = CA;
const ll KING = CK;
const ll TWO = C2;
const ll LAST_CARD = SA; 
const ll COLOR_COUNT = 4;
const ll SET_FIRST_SUIT = (ACE << 1) - 1;
const ll KINGS = HK | DK | CK | SK;
const ll ACES  = DA | CA | HA | SA;
const ll QUENS = DQ | CQ | HQ | SQ;
const ll TWOS  = C2 | H2 | D2 | S2;
const ll CLUBS = (1ll << 13) - 1;
const ll DIAMONDS = (1ll << 26) - 1 ^ CLUBS;
const ll HEARTS = (1ll << 39) - 1 ^ DIAMONDS ^ CLUBS;
const ll SPADES = (1ll << 52) - 1 ^ HEARTS ^ DIAMONDS ^ CLUBS;

struct Hand {
    ll bits;
    ll hand_rank;
    int profit;
};

std::ostream& operator<<(std::ostream& os, const Hand& x) {
    os << x.bits << "," << x.hand_rank << "," << x.profit;
    return os;
}
    
const ll HEART_ROYAL   = HA | HK | HQ | HJ | HT;
const ll SPADE_ROYAL   = SA | SK | SQ | SJ | ST;
const ll CLUB_ROYAL    = CA | CK | CQ | CJ | CT;
const ll DIAMOND_ROYAL = DA | DK | DQ | DJ | DT;

const ll max_rank_bit           = 1ll << 62;
const ll quad_rank_bit          = 1ll << 61;
const ll full_rank_bit          = 1ll << 60;
const ll flush_rank_bit         = 1ll << 59;
const ll straight_rank_bit      = 1ll << 58;
const ll threeOfKind_rank_bit   = 1ll << 57;
const ll twoPair_rank_bit       = 1ll << 56;
const ll onePair_rank_bit       = 1ll << 55;
const ll aceKing_rank_bit       = 1ll << 54;

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


std::vector<ll> create_bits() {
    std::vector<ll> nums;
    ll limit = LAST_CARD << 1;
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

ll _convert_hand_to_just_ranks(ll bits) {
    return (bits & SPADES) >> 39 | (bits & HEARTS) >> 26 | (bits & DIAMONDS) >> 13 | (bits & CLUBS);
}

bool has_one_aceKing(ll bits) {
   return bit_count(bits & ACES) == 1 && bit_count(bits & KINGS) == 1;
}

ll _get_straight_with_count(ll bits, int count) {
    for (ll i = ACE; i > (1ll << (count - 3)); i >>= 1) {
        if ((bits & (i | i << 13 | i << 26 | i << 39)) == 0) continue;
        for (ll j = i >> 1; bits & (j | (j << 13) | (j << 26) | (j << 39)); j >>= 1) {
            if (j == i >> (count - 1)) return i | straight_rank_bit;
            if (j == TWO && bits & ACES) return i | straight_rank_bit;
        }
    }
    return 0;
}

ll _get_same_cards(ll bits, int count, int times, ll rank_bit) {
    ll res = 0;
    for (ll i = TWO; i <= ACE; i <<= 1) {
        ll cur = bits & (i | (i << 13) | (i << 26) | (i << 39));
        if (bit_count(cur) == count) {
            times--;
            res |= i;
        }
    }
    if (times == 0) return res | rank_bit;
    return 0;
}

ll flush(ll bits) {
    for (int i = 0; i < COLOR_COUNT; i++) {
        ll cur = bits & SET_FIRST_SUIT;
        if (bit_count(cur) == 5) return flush_rank_bit | cur;
        bits >>= 13;
    }
    return 0;
}


ll straight_pair(ll bits) {
    ll r1 = _get_straight_with_count(bits, 5), r2 = _get_same_cards(bits, 2, 1, 0);
    if (r1 && r2) return r1;
    return 0;
}


bool royalFlush(ll bits) {
    return ((bits & HEART_ROYAL) == HEART_ROYAL || (bits & SPADE_ROYAL) == SPADE_ROYAL || (bits & CLUB_ROYAL) == CLUB_ROYAL || (bits & DIAMOND_ROYAL) == DIAMOND_ROYAL);
}

bool straightFlush(ll bits) {
    ll res = _get_straight_with_count(bits, 5);
    if (!res) return 0;
    res ^= straight_rank_bit;
    if (res == C5) res += C4 + C3 + C2 + CA;
    else res += (res >> 1) + (res >> 2) + (res >> 3) + (res >> 4);
    return bit_count(res & bits) == 5 || bit_count((res << 13) & bits) == 5 || bit_count((res << 26) & bits) == 5 || bit_count((res << 39) & bits) == 5;
}


ll aceKing(ll bits) {
    if (!has_one_aceKing(bits)) return 0;
    ll ranks = _convert_hand_to_just_ranks(bits);
    while (bit_count(ranks) != 5) ranks = ranks & (ranks - 1);
    return ranks | aceKing_rank_bit;
}

ll straight_straight(ll bits) {
    return _get_straight_with_count(bits, 6);
}

ll flush_flush(ll bits) {
    for (int i = 0; i < 4; i++) {
        ll cur = bits & SET_FIRST_SUIT;
        if (bit_count(cur) == 6) return flush_rank_bit | (cur & (cur - 1));
        bits >>= 13;
    }
    return 0;
}

ll straight(ll bits) {
    return _get_straight_with_count(bits, 5);
}


bool royalFlush_flush(ll bits) {
    return royalFlush(bits) && flush_flush(bits);
}

bool royalFlush_straight(ll bits) {
    return royalFlush(bits) && straight_straight(bits);
}

bool straightFlush_straightFlush(ll bits) {
    return straight_straight(bits) && flush_flush(bits);
}

bool straightFlush_flush(ll bits) {
    return straight(bits) && flush_flush(bits);
}

bool straightFlush_straight(ll bits) {
    return straight_straight(bits) && straightFlush(bits);
}

bool straightFlush_aceKing(ll bits) {
    ll res = straightFlush(bits);
    if (!res || (bits & TWOS) == 0 || (bits & ACES) == 0) return 0;
    if (bits & KINGS) return true;
    return false;
}

ll quads_full(ll bits){
    ll r1 = _get_same_cards(bits, 4, 1, quad_rank_bit), r2 = _get_same_cards(bits, 2, 1, 0);
    if (!r1 || !r2) return false;
    return r1;
}

ll quads_aceKing(ll bits) {
    ll res = _get_same_cards(bits, 4, 1, quad_rank_bit);
    if (!res) return 0;
    if (bit_count(bits & ACES) && bit_count(bits & KINGS)) return res;
    return 0;
}

ll full_full(ll bits) {
    return _get_same_cards(bits, 3, 2, full_rank_bit);

}

ll full_aceKing(ll bits) {
    ll r1 = _get_same_cards(bits, 3, 1, full_rank_bit), r2 = _get_same_cards(bits, 2, 1, 0);
    if (!r1 || !r2) return 0;
    ll tot = bit_count(bits & ACES) + bit_count(bits & KINGS);
    ll ace_count = bit_count(bits & ACES), king_count = bit_count(bits & KINGS);
    tot = ace_count + king_count;
    if ((tot == 3 && ace_count && king_count) || tot == 4) return r1;
    return 0;
}


ll flush_straight(ll bits) {
    ll r1 = flush(bits), r2 = straight(bits);
    if (r1 && r2) return r1;
    return 0;
}

ll flush_pair(ll bits) {
    ll r1 = flush(bits), r2 = _get_same_cards(bits, 2, 1, 0);
    if (r1 && r2) return r1;
    return 0;
}

ll flush_aceKing(ll bits) {
    ll r1 = flush(bits), r2 = has_one_aceKing(bits);
    if (r1 && r2 && bit_count(bits & (HA | HK)) != 2 && bit_count(bits & (CA | CK)) != 2 && bit_count(bits & (SA | SK)) != 2 && bit_count(bits & (DA | DK)) != 2) return r1;
    return 0;
}

ll straight_aceKing(ll bits) {
    ll r1 = straight(bits), r2 = has_one_aceKing(bits);
    if (r1 && r2 && bit_count(bits) == 6) return r1;
    return 0;
}

ll threeOfKind_aceKing(ll bits) {
    ll r1 = _get_same_cards(bits, 3, 1, threeOfKind_rank_bit);
    if (r1 && bit_count(bits & (ACES | KINGS)) == 2) return r1;
    return false;
}

ll twoPair_twoPair(ll bits) {
    ll res = _get_same_cards(bits, 2, 3, twoPair_rank_bit);
    if (!res) return 0;
    ll last = res & -res;
    return twoPair_rank_bit | last | ((res & SET_FIRST_SUIT) ^ last) << 13;
}

ll twoPair_aceKing(ll bits) {
    ll res = _get_same_cards(bits, 2, 2, 0);
    if (!res) return 0;
    res = twoPair_rank_bit | res << 13;
    if (has_one_aceKing(bits) || (bit_count(bits & KINGS) == 2 && bit_count(bits & ACES) == 1)) return res | ACE;
    if (bit_count(bits & KINGS) == 1 && bit_count(bits & ACES) == 2) return res | KING;
    return 0;
}

ll onePair_aceKing(ll bits) {
    ll res = _get_same_cards(bits, 2, 1, 0);
    if (!res) return 0;
    if (has_one_aceKing(bits) || (bit_count(bits & KINGS) == 2 && bit_count(bits & ACES) == 1) || (bit_count(bits & KINGS) == 1 && bit_count(bits & ACES) == 2)) {
        ll ranks = _convert_hand_to_just_ranks(bits) ^ res;
        if (bit_count(ranks) == 4) {
            return (ranks & (ranks - 1)) | res << 13 | onePair_rank_bit;
        }
        return ranks | res << 13 | onePair_rank_bit;
    }
    return 0;
}

ll quads(ll bits) {
    return _get_same_cards(bits, 4, 1, quad_rank_bit);
}

ll full(ll bits) {
    ll r1 = _get_same_cards(bits, 3, 1, full_rank_bit), r2 = _get_same_cards(bits, 2, 1, full_rank_bit);
    if (!r1 || !r2) return 0;
    return r1 | r2;
}

ll threeOfKind(ll bits) {
    return _get_same_cards(bits, 3, 1, threeOfKind_rank_bit);
}

ll twoPair(ll bits) {
    ll res = _get_same_cards(bits, 2, 2, 0);
    if (!res) return 0;
    ll ranks = _convert_hand_to_just_ranks(bits) ^ res;
    while (bit_count(ranks) != 1) ranks = ranks & (ranks - 1);
    
    return res << 13 | twoPair_rank_bit | ranks;
}

ll onePair(ll bits) {
    ll res = _get_same_cards(bits, 2, 1, 0);
    if (!res) return 0;
    
    ll ranks = _convert_hand_to_just_ranks(bits) ^ res;
    while (bit_count(ranks) != 3) ranks = ranks & (ranks - 1);
    
    return res << 13 | onePair_rank_bit | ranks;
}

bool royalFlush_straightFlush(ll bits) {
    return (straight_straight(bits) && flush_flush(bits) && has_one_aceKing(bits));
}


Hand create_hand(ll bits) {
    Hand current_hand;
    current_hand.bits      = bits;
    current_hand.hand_rank = 0;
    if (royalFlush_straightFlush(bits)) {
        current_hand.hand_rank  = max_rank_bit;
        current_hand.profit     = 150 * 2;
        return current_hand;
    }
    else if (royalFlush_flush(bits)) {
        current_hand.hand_rank  = max_rank_bit;
        current_hand.profit     = 105 * 2;
        return current_hand;
    }

    else if (royalFlush_straight(bits)) {
        current_hand.hand_rank  = max_rank_bit;
        current_hand.profit     = 104 * 2;
        return current_hand;
    }

    else if (straightFlush_straightFlush(bits)) {
        current_hand.hand_rank  = max_rank_bit;
        current_hand.profit     = 100 * 2;
        return current_hand;
    }

    else if (royalFlush(bits)) {
        current_hand.hand_rank = max_rank_bit;
        current_hand.profit    = 100 * 2;
        return current_hand;
    }

    else if (straightFlush_flush(bits)) {
        current_hand.hand_rank  = max_rank_bit;
        current_hand.profit     = 55 * 2;
        return current_hand;
    }
    
    else if (straightFlush_straight(bits)) {
        current_hand.hand_rank  = max_rank_bit;
        current_hand.profit     = 54 * 2;
        return current_hand;
    }

    else if (straightFlush_aceKing(bits)) {
        current_hand.hand_rank  = max_rank_bit;
        current_hand.profit     = 51 * 2;
        return current_hand;
    }

    else if (straightFlush(bits)) {
        current_hand.hand_rank = max_rank_bit;
        current_hand.profit    = 50 * 2;
        return current_hand;
    }
    
    else if (ll hand_rank = quads_full(bits)) {
        current_hand.hand_rank  = hand_rank;
        current_hand.profit     = 27 * 2;
        return current_hand;
    }

    else if (ll hand_rank = quads_aceKing(bits)) {
        current_hand.hand_rank  = hand_rank;
        current_hand.profit     = 21 * 2;
        return current_hand;
    }

    else if (ll hand_rank = quads(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 20 * 2;
        return current_hand;
    }

    else if (ll hand_rank = full_full(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 14 * 2;
        return current_hand;
    }

    else if (ll hand_rank = full_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    =  8 * 2;
        return current_hand;
    }

    else if (ll hand_rank = flush_flush(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 10 * 2;
        return current_hand;
    }

    else if (ll hand_rank = flush_straight(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 9 * 2;
        return current_hand;
    }

    else if (ll hand_rank = full(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 7 * 2;
        return current_hand;
    }

    else if (ll hand_rank = flush_pair(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 6 * 2;
        return current_hand;
    }

    else if (ll hand_rank = flush_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 6 * 2;
        return current_hand;
    }

    else if (ll hand_rank = straight_straight(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 8 * 2;
        return current_hand;
    }

    else if (ll hand_rank = straight_pair(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 5 * 2;
        return current_hand;
    }

    else if (ll hand_rank = straight_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 5 * 2;
        return current_hand;
    }

    else if (ll hand_rank = threeOfKind_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 4 * 2;
        return current_hand;
    }

    else if (ll hand_rank = twoPair_twoPair(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 3 * 2;
        return current_hand;
    }

    else if (ll hand_rank = threeOfKind(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 3 * 2;
        return current_hand;
    }

    else if (ll hand_rank = twoPair_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 3 * 2;
        return current_hand;
    }

    else if (ll hand_rank = onePair_aceKing(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 2 * 2;
        return current_hand;
    }

    else if (ll hand_rank = flush(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 5 * 2;
        return current_hand;
    }
    
    else if (ll hand_rank = straight(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 4 * 2;
        return current_hand;
    }

    else if (ll hand_rank = twoPair(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 2 * 2;
        return current_hand;
    }

    else if (ll hand_rank = onePair(bits)) {
        current_hand.hand_rank = hand_rank;
        current_hand.profit    = 1 * 2;
        return current_hand;
    }

    else if (ll hand_rank = aceKing(bits)) {
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
    for (auto el: bits) {
        hands.push_back(create_hand(el));
    }
    return hands;
}

#endif
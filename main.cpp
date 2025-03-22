#include "create_hand.h"
#include <random>
#include <algorithm>


// MASA limiti muhabbeti ve sigorta ekle straight flush over straight flush a da baksın
// NUMERIC test te yap işte toplam straight sayısı bukadar olmalı falan filan diye
// örnek toplam 2280123 straight olmalı ama benimkinde 228015 tane var ozaman benimki yanlış
// eğer yavaş ise multi threading ekle
// HAND COMPERSION TESTS LERIDE LAZIM
// MEMORY SİZELARI DÜŞÜR

#define ull unsigned long long
using namespace std;
vector<Hand> hands5, hands6;

ll rotl(ll x, ll k) {
    return (x << k) | (x >> (64 - k));
}

struct RandomGenerator {
    ll data[2];
    RandomGenerator() {
        random_device rd;
        data[0] = rd();
        data[1] = rd();
    }

    ull gen_num() {
        ll s0 = data[0];
        ll s1 = data[1];
        ll res = s0 + s1;
        s1 ^= s0;
        data[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16);
        data[1] = rotl(s1, 37);
        return res;
    }
    
    ull gen_hand(int count, ll res) {
        while (count) {
            int i = gen_num() % 52;
            count -= !((res >> i) & 1);
            res |= (1ll << i);
        }
        return res;
    }
};

float get_profit(Hand player_hand, vector<Hand>& banks) {
    ll res = 0;
    for (auto el: banks) {
        if (el.hand_rank == 0) res += 1;
        else if (el.hand_rank > player_hand.hand_rank) res -= 3;
        else res += player_hand.profit;
    }
    return (float)res / (float)banks.size();
}

ll get_includes(int i, ll bits) {
    ll res = 0;
    for (int j = 0; j < 52; j++) {
        if ((bits >> j) & 1) {
            if (i & 1) res |= 1ll << j;
            i >>= 1;
        }
    }
    return res;
}

void print_hand_info(vector<Hand> hands) {
    ll empty = 0, aceKing = 0, onePair = 0, twoPair = 0, threeOfKind = 0, straight = 0, flush = 0, full = 0, quads = 0, straightFlush = 0, royalFlush = 0;
    for (auto el: hands) {
        if (el.hand_rank & royalFlush_rank_bit) royalFlush++;
        else if (el.hand_rank & straightFlush_rank_bit) straightFlush++;
        else if (el.hand_rank & quad_rank_bit) quads++;
        else if (el.hand_rank & full_rank_bit) full++;
        else if (el.hand_rank & flush_rank_bit) flush++;
        else if (el.hand_rank & straight_rank_bit) straight++;
        else if (el.hand_rank & threeOfKind_rank_bit) threeOfKind++;
        else if (el.hand_rank & twoPair_rank_bit) twoPair++;
        else if (el.hand_rank & onePair_rank_bit) onePair++;
        else if (el.hand_rank & aceKing_rank_bit) aceKing++;
        else empty++;
    }
    cout << "\n***************************\n";
    cout << "empty: " << (float)empty / hands.size() << "\n";
    cout << "aceKing: " << (float)aceKing / hands.size() << "\n";
    cout << "onePair: " << (float)onePair / hands.size() << "\n";
    cout << "twoPair: " << (float)twoPair / hands.size() << "\n";
    cout << "threeOfKind: " << (float)threeOfKind / hands.size() << "\n";
    cout << "staright: " << (float)straight / hands.size() << "\n";
    cout << "flush: " << (float)flush / hands.size() << "\n";
    cout << "full: " << (float)full / hands.size() << "\n";
    cout << "quads: " << (float)quads / hands.size() << "\n";
    cout << "straightFlush: " << (float)straightFlush / hands.size() << "\n";
    cout << "royalFlush: " << (float)quads/ hands.size() << "\n";
}   

struct Game {
    vector<Hand> h5, h6, banks;
    RandomGenerator rand;
    Hand player_hand;
    ull excludes, bank_card;

    float run_game() {
        reset_vars();
        filter_hands();
        chose_player_hand();
        filter_banks();
        return get_result();
    }
    float get_result() {
        ll chosen_cards = 0;
        float max_res = get_profit(player_hand, banks);
        cout << "\n----------------------------------\n";
        cout << "hand: " << player_hand << "\n";
        cout << "bank_card: " << print_bit_to_hand(bank_card) << "\n";
        cout << "excludes: " << print_bit_to_hand(excludes ^ bank_card) << "\n";
        cout << "res: " << max_res << "\n";
        print_hand_info(banks);
        for (int i = 1; i < 32; i++) {
            ll includes = get_includes(i, player_hand.bits);
            ll bits = player_hand.bits;
            ll cur_res = 0;
            vector<Hand> new_bank;
            for (auto el: banks) {
                if ((el.bits & includes) == 0) new_bank.push_back(el);
            }
            ll count = 0;
            float res = 0;
            for (auto el: h5) {
                if ((el.bits & includes) != includes) continue;
                count++;
                res += get_profit(el, new_bank);
            }
            res = (res / count) - 1;
            if (res > max_res) {
                max_res = res;
                chosen_cards = includes;
            }
            cout << "\n------------------------------\n";
            cout << "i: " << i << "\n";
            cout << "res: " << res << "\n";
            cout << print_bit_to_hand(includes) << "\n";
        }

        cout << "\n------------------------------\n";
        cout << "max_res: " << max_res << "\n";
        if (chosen_cards) {
            cout << "chosen_cards: " << print_bit_to_hand(chosen_cards) << "\n";
        }
        if (max_res < -1) max_res = -1;
        return max_res;
    }

    void filter_banks() {
        excludes = (bank_card ^ excludes) | player_hand.bits;
        for (auto el: hands5){
            if ((el.bits & excludes) == 0 && el.bits & bank_card) { banks.push_back(el); }
        }
    }

    void chose_player_hand() {
        ll index = rand.gen_num() % h5.size();
        while (h5[index].hand_rank < threeOfKind_rank_bit) index = rand.gen_num() % h5.size();
        player_hand = h5[index];
        swap(h5[index], h5[h5.size() -1]);
        h5.pop_back();
    }

    void filter_hands() {
        for (auto el: hands5){
            if ((el.bits & excludes) == 0) h5.push_back(el);
        }
        for (auto el: hands6){
            if ((el.bits & excludes) == 0) h6.push_back(el);
        }
    }

    void reset_vars() { 
        bank_card = rand.gen_hand(1, 0);
        excludes  = rand.gen_hand(10, bank_card);
        h5.clear();
        h6.clear();
        banks.clear();
    }
};


void writeToFile(const std::vector<Hand>& vec, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to open file for writing.\n";
        return;
    }

    size_t size = vec.size();
    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
    outFile.write(reinterpret_cast<const char*>(vec.data()), size * sizeof(Hand));
    outFile.close();
}

std::vector<Hand> readFromFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    size_t size;
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::vector<Hand> vec(size);
    vec.resize(size);
    inFile.read(reinterpret_cast<char*>(vec.data()), size * sizeof(Hand));
    inFile.close();
    return vec;

}


std::pair<std::vector<Hand>, std::vector<Hand>> get_hands() {
    if (!std::filesystem::exists("hands5.txt")) {
        auto [bits5, bits6] = create_bits();

        std::vector<Hand> hands5, hands6;
        for (auto el: bits5) hands5.push_back(create_hand(el));
        for (auto el: bits6) hands6.push_back(create_hand(el));
        
        
        std::sort(std::begin(hands5), std::end(hands5), &hand_sorter);
        std::sort(std::begin(hands6), std::end(hands6), &hand_sorter);
        writeToFile(hands5, "hands5.txt");
        writeToFile(hands6, "hands6.txt");
    }
    return {readFromFile("hands5.txt"), readFromFile("hands6.txt")};
}

int main() {
    auto data = get_hands();
    hands5 = data.first;
    hands6 = data.second;
    Game game;
    float res = 0;
    for (int i = 0; i < 100; i++) {
        res += game.run_game();
    }
    cout << "res: " << res / 100 << "\n";
}
#include "create_hand.h"

// MASA limiti muhabbeti ve sigorta ekle straight flush over straight flush a da baksın
// NUMERIC test te yap işte toplam straight sayısı bukadar olmalı falan filan diye
// örnek toplam 2280123 straight olmalı ama benimkinde 228015 tane var ozaman benimki yanlış
// eğer yavaş ise multi threading ekle
// HAND COMPERSION TESTS LERIDE LAZIM
int main() {
    //std::vector<Hand> hands = get_every_hand();
    create_hand(CK | CQ | CJ | CT | C9 | D5);
}

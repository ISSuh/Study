#include <iostream>
#include <list>

using namespace std;

struct Item{
        Item(int itemCd, int buyMoney){
                ItemCd = itemCd;
                BuyMoney = buyMoney;
        }
        int ItemCd;     // 아이템코드
        int BuyMoney;   // 판매금액
};

int main(){
        list<Item> Itemlist;

        Item item1(1,2000);
        Itemlist.push_front(item1);
        Item item2(2,1000);
        Itemlist.push_front(item2);

        Item item3(3,3000);
        Itemlist.push_back(item3);
        Item item4(4,6000);
        Itemlist.push_back(item4);

        list<Item>::iterator itEnd = Itemlist.end();
        for(list<Item>::iterator iterPos=Itemlist.begin() ; iterPos != Itemlist.end() ; iterPos++){
                cout << "아이템 코드 : " << iterPos->ItemCd << endl;
        }

        Itemlist.pop_front();

        Item front_item = Itemlist.front();
        cout << "아이템 코드 : " << front_item.ItemCd << endl;

        Itemlist.pop_back();

        Item back_Item = Itemlist.back();
        cout << "아이템 코드 : " << back_Item.ItemCd << endl;

        if(Itemlist.empty() == false){
                list<Item>::size_type count = Itemlist.size();
                cout << "남아있는 아이템 개수 : " << count << endl;
        }

        Itemlist.clear();
        list<Item>::size_type count = Itemlist.size();
        cout << "남아있는 아이템 개수 : " << count << endl;
}
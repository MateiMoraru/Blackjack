#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int nrand(int a, int b)
{
	return (rand() % (b + 1)) + a;
}

int calculate_cards(string cards[], int len)
{
	int sum = 0;
	for(int i = 0; i < len; i++)
	{
		string card = cards[i];
		char card_num = card[0];
		if(card[1] == '0')
			sum += 10;
		else if(card_num == 'A' || card_num == 'K' || card_num == 'Q' || card_num == 'J')
			sum += 10;
		else
			sum += card_num - '0';
	}
	return sum;
}

string get_card(string cards[])
{

	int index = nrand(0, 51);
	string card = cards[index];
	while(card == "EMPTY")
	{
		index = nrand(0, 51);
		card = cards[index];
	}

	cards[index] = "EMPTY";
	return card;
}

int loop()
{
	int bet;
	cout << "How much would you like to bet?" << endl;
	cin >> bet;
	if(bet == -1)
		return 0;

}

void generate_cards(string cards[])
{
	string card_names[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
	string card_colors[] = {"H", "S", "C", "D"};
	int idx = 0;

	for(int i = 0; i < 13; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			//cout << i << ' ' << j << ' ' << idx << endl;
			cards[idx] = card_names[i] + card_colors[j];
			idx++;
		}
	}
}

void shuffle_cards(string cards[])
{
	for(int i = 0; i < 52; i++)
	{
		string temp = cards[i];
		int new_index = nrand(0, 51);
		cards[i] = cards[new_index];
		cards[new_index] = temp;
	}
}

void print_cards(string cards[], int len)
{
	for(int i = 0; i < len; i++)
	{
		cout << cards[i] << ' ';
	}
	cout << endl;
}

int main()
{
	srand(time(0));
	bool playing = true;
	string cards[52];
	string player[10];
	string dealer[10];
	
	cout << "Hello there" << endl;

	generate_cards(cards);
	shuffle_cards(cards);

	player[0] = get_card(cards);
	player[1] = get_card(cards);

	print_cards(player, 2);

	int event = -1;
	while(playing)
	{
		event = loop();
		if(event == 0)
			playing = false;
	}
}


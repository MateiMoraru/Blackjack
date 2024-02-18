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

void generate_cards(string cards[])
{
	string card_names[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
	string card_colors[] = {"H", "S", "C", "D"};
	int idx = 0;

	for(int i = 0; i < 13; i++)
	{
		for(int j = 0; j < 4; j++)
		{
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


int loop(string cards[], string player[], int p_len, string dealer[], int d_len, int& balance)
{
    cout << "\n\n\n";
	int bet, move;
    int p_sum = calculate_cards(player, p_len);
    int d_sum = calculate_cards(dealer, d_len);
          
    cout << "Balance: " << *balance << endl;
    cout << "How much would you like to bet?" << endl;
    cin >> bet;
    while(bet > balance)
    {
        cout << "Your current balance is only: " << balance << endl;
        cin >> bet;
    }
    *balance -= bet;
    cout << "Dealers's cards:" << endl;
    print_cards(dealer, d_len);
    cout << "Dealer sum: " << d_sum;
    cout << endl;
   
   cout << "Here are your cards:" << endl;
    print_cards(player, p_len);
    cout << "Cards sum: " << p_sum << endl;
    cout << endl;

    while(move != 0)
    {
        cout << "Stand(0) or Hit(1)?" << endl;
        cin >> move;
        if(move == 1)
        {
            player[p_len] = get_card(cards);
            p_len++;
            p_sum = calculate_cards(player, p_len);
        }
        cout << "Cards: ";
        print_cards(player, p_len);
        cout << "Sum: ";
        cout << p_sum;
        cout << endl;
        if(p_sum > 21)
        {
            cout << "You lost!" << endl;
            return 0;
        }
    }

    while(d_sum <= 16)
    {
        dealer[d_len] = get_card(cards);
        d_len++;
        d_sum = calculate_cards(dealer, d_len);
        cout << "Dealer cards: "; 
        print_cards(dealer, d_len);
        cout << "Dealer sum: " << d_sum << endl;
        if(d_sum > 21)
        {
            cout << "Dealer's busted!" << endl;
            balance += bet;
            return 0;
        }   
    }

    if(p_sum > d_sum)
    {
        cout << "You win!" << endl;
        cout << "Prize: " << bet * 2 << endl;
        balance += bet * 2;
    }
    else if(d_sum > p_sum)
    {
        cout << "You lost! :(" << endl;
    }
    else if(d_sum == p_sum)
    {
        cout << "Draw!" << endl;
        if(p_sum == 21)
            balance += bet;
        balance += bet;
    }
    return 0;
}

int main()
{
	srand(time(0));
	bool playing = true;
	string cards[52];
	string player[10];
	string dealer[10];
    int p_len = 2, d_len = 2;
	int balance = 100;
	cout << "Hello there" << endl;

	generate_cards(cards);
	shuffle_cards(cards);

	player[0] = get_card(cards);
	player[1] = get_card(cards);
    dealer[0] = get_card(cards);
    dealer[1] = get_card(cards);

	int event = -1;
	while(playing)
	{
		event = loop(cards, player, p_len, dealer, d_len, &balance);
		cout << balance;
        if(event == -1)
			playing = false;
	    
	    player[0] = get_card(cards);
	    player[1] = get_card(cards);
        dealer[0] = get_card(cards);
        dealer[1] = get_card(cards);
        p_len = 2;
        d_len = 2;
    }
}


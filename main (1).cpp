// Name: Hailey Clark
// Class (CECS 325-01)
// Project Name (Prog 2 – More War Vectors)
// Due Date (10/01/2024)
// I certify that this program is my own original work. I did not copy any part
// of this program from any other source. I further certify that I typed each
// and every line of code in this program.

// war.cpp

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

class Card {
private:
  char suit;
  char rank;

public:
  // Constructor
  Card(char r, char s) : suit(s), rank(r) {}

  // Print function for the cards
  void print() {

    // If the card is a 10, print a 10 instead of a T
    if (rank == 'T') {
      std::cout << "10" << suit;
    }

    // otherwise, print the rank and suit normally
    else {
      std::cout << rank << suit;
    }
  }

  // Function to compare two cards
  int compare(Card c) {

    // Establishing the order of rank for the cards
    const char ranks[] = "A23456789TJQK";
    int this_rank = -1, other_rank = -1;

    // Finding the rank of the cards
    for (int i = 0; i < 13; ++i) {
      if (ranks[i] == rank)
        this_rank = i;
      if (ranks[i] == c.rank)
        other_rank = i;
    }

    // Return number based on which card ranks higher
    if (this_rank > other_rank)
      return 1;
    if (this_rank < other_rank)
      return -1;
    return 0;
  }
};

class Deck {
private:
  std::vector<Card> cards;
  int currentCard;

public:
  Deck() : currentCard(0) {
    // Clubs, Spades, Diamonds, and Hearts
    char suits[] = {'C', 'S', 'D', 'H'};
    // Ranks of cards
    char ranks[] = {'A', '2', '3', '4', '5', '6', '7',
                    '8', '9', 'T', 'J', 'Q', 'K'};

    // Creating the deck unshuffled
    for (char suit : suits) {
      for (char rank : ranks) {
        cards.push_back(Card(rank, suit));
      }
    }
  }

  // Method to shuffle the deck
  void shuffle() {
    // Shuffling the deck by randomly swapping cards repeatedly
    srand(time(0));
    for (int i = 0; i < 52; ++i) {
      int j = rand() % 52;
      std::swap(cards[i], cards[j]);
    }
    currentCard = 0;
  }

  // Method to deal the next card
  Card deal() {
    if (isEmpty())
      throw std::out_of_range("Out of cards");
    return cards[currentCard++];
  }

  // Print method
  void print() {
    for (int i = 0; i < 52; ++i) {
      cards[i].print();
      std::cout << " ";
      if ((i + 1) % 13 == 0)
        std::cout << std::endl; // Print 13 cards per line
    }
  }

  // Return true if deck is empty
  bool isEmpty() { return currentCard >= cards.size(); }
};

int main() {
  std::string player1, player2;

  // Getting player names
  std::cout << "Enter Player 1 name: ";
  std::cin >> player1;
  std::cout << "Enter Player 2 name: ";
  std::cin >> player2;

  // Creating the deck
  Deck deck;

  // Printing unshuffled deck
  std::cout << "\nUnshuffled deck:\n";
  deck.print();

  // Shuffling the deck
  deck.shuffle();

  // Printing shuffled deck
  std::cout << "\nShuffled deck:\n";
  deck.print();

  // Initializing scores
  int player1Wins = 0, player2Wins = 0, ties = 0;

  int games;
  std::cout << "How many games do you want to play? ";
  std::cin >> games;

  // Repeat the game 26 times
  for (int i = 0; i < games; ++i) {

    // Printing the number of the round and dealing a card to each player
    try{
      std::cout << "\nRound " << (i + 1) << ":\n";
      Card card1 = deck.deal();
      Card card2 = deck.deal();

      // Printing the cards
      std::cout << player1 << " plays ";
      card1.print();
      std::cout << "\n" << player2 << " plays ";
      card2.print();
      std::cout << "\n";

      // Comparing the cards and printing the result
      int result = card1.compare(card2);
      if (result == 1) {
        std::cout << player1 << " wins this round!\n";
        player1Wins++;
      } else if (result == -1) {
        std::cout << player2 << " wins this round!\n";
        player2Wins++;
      } else {
        std::cout << "It's a tie!\n";
        ties++;
      }
    }

    catch (const std::out_of_range &e){
      std::cout << "Error: " << e.what() << "\n";
      break;
    }
  }

  // Print final scores
  std::cout << "\nGame Over! Final Statistics:\n";
  std::cout << player1 << " Wins: " << player1Wins << "\n";
  std::cout << player2 << " Wins: " << player2Wins << "\n";
  std::cout << "Ties: " << ties << "\n";

  return 0;
}

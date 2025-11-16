//card_operations.h
#ifndef CARD_OPERATIONS_H
#define CARD_OPERATIONS_H

#include <string>
using namespace std;
struct Card;

Card* createCards(int n);
void destroyCards(Card* p);
void inputCards(Card* arr, int n);
void deposit(Card& c, double amount, double fee = 0.02);
bool spend(Card& c, double cost);
bool spend(Card& c, double cost, const string& item);
void showBalance(const Card& c);
void viewStudentID(const Card* p);
int toCent(double amount);
void printReport(const Card* arr, int n);

#endif

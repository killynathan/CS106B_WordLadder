/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include <string>
using namespace std;

void getInputFromUser(string& startWord, string& destWord);

void initialize(string startWord, Queue<Vector<string> >& ladderDatabase, Lexicon& usedWords);

void outputLadder(Vector<string>& ladder);

bool runProgram(Queue<Vector<string> >& ladderDatabase, Lexicon& engWords, Lexicon& usedWords, string destWord);

void enqueueNewLadders(Queue<Vector<string> >& ladderDatabase, Lexicon& engWords, Lexicon& usedWords, Vector<string>& currentLadder);

Vector<string> findSimilarWords(Lexicon& engWords, Lexicon& usedWords, string currentWord);

bool oneLetterOff(string str, string str2);

int main() {
	Queue<Vector<string> > ladderDatabase;
	Lexicon engWords("EnglishWords.dat");
	Lexicon usedWords;
	string startWord;
	string destWord;

	cout << "Welcome to the word ladder program." << endl;
	cout << "Enter a starting word and destination word and we will generate a word ladder." << endl;

	while (true) {
		string quit = getLine("Enter 'q' to quit and anything else to continue: ");
		if (quit == "q") break;
		cout << endl;

		getInputFromUser(startWord, destWord);

		initialize(startWord, ladderDatabase, usedWords);
	
		if (!runProgram(ladderDatabase, engWords, usedWords, destWord)) {
			cout << "Sorry, we could not generate a ladder for " << startWord << "." << endl;
		}

		cout << endl;
	}

	return 0;
}

void getInputFromUser(string& startWord, string& destWord) {
	startWord = getLine("Please enter the starting word: ");
	destWord = getLine("Please enter the destination word: ");
}


void initialize(string startWord, Queue<Vector<string> >& ladderDatabase, Lexicon& usedWords) {
	Vector<string> startingLadder(1, startWord);
	ladderDatabase.enqueue(startingLadder);
	usedWords.add(startWord);
}



bool runProgram(Queue<Vector<string> >& ladderDatabase, Lexicon& engWords, Lexicon& usedWords, string destWord) {
	while (!ladderDatabase.isEmpty()) {
		Vector<string> currentLadder = ladderDatabase.dequeue();
		string currentWord = currentLadder[currentLadder.size() - 1];

		if (currentWord == destWord) {
			outputLadder(currentLadder);
			return true;
		}

		enqueueNewLadders(ladderDatabase, engWords, usedWords, currentLadder);
		
	}
	return false;
}

void outputLadder(Vector<string>& ladder) {
	for (int i = 0; i < ladder.size(); i++) {
		if (i == ladder.size() - 1) {
			cout << ladder[i] << endl;
		} else {
			cout << ladder[i] << " --> ";
		}
	}
}

void enqueueNewLadders(Queue<Vector<string> >& ladderDatabase, Lexicon& engWords, Lexicon& usedWords, Vector<string>& currentLadder) {
	string currentWord = currentLadder[currentLadder.size() - 1];

	Vector<string> similarWords = findSimilarWords(engWords, usedWords, currentWord);
	for (int i = 0; i < similarWords.size(); i++) {
		Vector<string> newLadder = currentLadder;
		newLadder.add(similarWords[i]);
		ladderDatabase.enqueue(newLadder);
	}
}

Vector<string> findSimilarWords(Lexicon& engWords, Lexicon& usedWords, string currentWord) {
	Vector<string> similarWords;

	for (int i = 0; i < currentWord.length(); i++) {
		for (int j = 0; j < 26; j++) {
			string newWord = currentWord;
			newWord[i] = 'a' + j;
			if (engWords.contains(newWord) && !usedWords.contains(newWord)){
				similarWords.add(newWord);
				usedWords.add(newWord);
			}
		}
	}

	return similarWords;
}

bool oneLetterOff(string str, string str2) {
	int count = 0;
	if (str.length() != str2.length()) {
		return false;
	} 

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == str2[i]) {
			count++;
		}
	}

	if (count >= (str.length() - 1)) {
		return true;
	} else {
		return false;
	}
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;
vector<string> loadWords() {
    vector<string> words;
    ifstream file("words.txt");
    string word;

    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    return words;
}
string chooseWord(vector<string>& words, int difficulty) {
    vector<string> filtered;

    for (string w : words) {
        if (difficulty == 1 && w.length() <= 5)
            filtered.push_back(w);
        else if (difficulty == 2 && w.length() <= 8)
            filtered.push_back(w);
        else if (difficulty == 3)
            filtered.push_back(w);
    }

    return filtered[rand() % filtered.size()];
}
int main() {
    srand(time(0));
    vector<string> words = loadWords();
    if (words.empty()) {
        cout << "Word file not found!\n";
        return 0;
    }
    int difficulty;
    cout << "🎮 HANGMAN GAME\n";
    cout << "1. Easy\n2. Medium\n3. Hard\nChoose difficulty: ";
    cin >> difficulty;
    string secret = chooseWord(words, difficulty);
    string guessed(secret.length(), '_');
    int attempts = (difficulty == 1) ? 8 : (difficulty == 2) ? 6 : 4;
    vector<char> usedLetters;
    while (attempts > 0 && guessed != secret) {
        cout << "\nWord: ";
        for (char c : guessed) cout << c << " ";
        cout << "\nAttempts left: " << attempts;
        cout << "\nUsed letters: ";
        for (char c : usedLetters) cout << c << " ";
        char guess;
        cout << "\nEnter a letter: ";
        cin >> guess;
        bool alreadyUsed = false;
        for (char c : usedLetters)
            if (c == guess) alreadyUsed = true;
        if (alreadyUsed) {
            cout << "⚠ Letter already used!\n";
            continue;
        }
        usedLetters.push_back(guess);
        bool correct = false;
        for (int i = 0; i < secret.length(); i++) {
            if (secret[i] == guess) {
                guessed[i] = guess;
                correct = true;
            }
        }
        if (!correct) {
            attempts--;
            cout << "❌ Wrong guess!\n";
        } else {
            cout << "✅ Correct!\n";
        }
    }

    if (guessed == secret)
        cout << "\n🎉 You Won! The word was: " << secret << endl;
    else
        cout << "\n💀 You Lost! The word was: " << secret << endl;

    return 0;
}

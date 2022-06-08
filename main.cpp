#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
    enum charState {
        normal,
        incorrect,
        wrongSpot,
        correct
    };

    string colors[] = {
            "0",
            "31",
            "33",
            "32"
    };

    map<char, int> alphabet = {
            { 'a', 0 },
            { 'b', 0 },
            { 'c', 0 },
            { 'd', 0 },
            { 'e', 0 },
            { 'f', 0 },
            { 'g', 0 },
            { 'h', 0 },
            { 'i', 0 },
            { 'j', 0 },
            { 'k', 0 },
            { 'l', 0 },
            { 'm', 0 },
            { 'n', 0 },
            { 'o', 0 },
            { 'p', 0 },
            { 'q', 0 },
            { 'r', 0 },
            { 's', 0 },
            { 't', 0 },
            { 'u', 0 },
            { 'v', 0 },
            { 'w', 0 },
            { 'x', 0 },
            { 'y', 0 },
            { 'z', 0 },
    };

    auto printGuessWord = [&alphabet, &colors](string guess, string word) {
        for (string::size_type i = 0; i < guess.size(); ++i) {
            bool isCorrect = alphabet.at(guess[i]) == correct;

            int thing = word.find(guess[i]);
            if (thing < guess.length()) {
                if (thing == i) {
                    alphabet.at(guess[i]) = correct;
                }
                else {
                    alphabet.at(guess[i]) = wrongSpot;
                }
            }
            else {
                alphabet.at(guess[i]) = incorrect;
            }

            cout << "\x1b[" << colors[alphabet.at(guess[i])] << "m" << guess[i];

            if (isCorrect)
                alphabet.at(guess[i]) = correct;
        }
        cout << "\x1b[0m" << endl;
    };

    vector<string> words;
    std::ifstream file("words.txt");
    std::string str;
    while (std::getline(file, str)) {
        words.push_back(str);
    }

    srand(time(NULL));
    string word = words[rand() % words.size()];

    system("clear");

    vector<string> guesses;
    string guess;
    for (int guessNr = 0; guessNr < 6; ++guessNr) {
        string error;
        bool validGuess = false;

        while (!validGuess) {
            system("clear");

            cout << "Btech WORDLE!" << endl;

            cout << "\x1b[31m" << error << "\x1b[0m" << endl;

            for (int i = 0; i < guesses.size(); ++i) {
                printGuessWord(guesses[i], word);
            }

            string alphabetString = "abcdefghijklmnopqrstuvwxyz";
            cout << endl;
            for (string::size_type i = 0; i < alphabetString.size(); ++i) {
                cout << "\x1b[" << colors[alphabet.at(alphabetString[i])] << "m" << alphabetString[i] << " \x1b[0m";
            }
            cout << endl;


            cout << "Enter guess: ";
            cin >> guess;


            error = "Guess not valid";
            for (int i = 0; i < words.size(); ++i) {
                string w = words[i];

                if (w == guess) {
                    error = "";

                    validGuess = true;
                    for (int i = 0; i < guesses.size(); ++i) {
                        string g = guesses[i];

                        if (g == guess) {
                            error = "You can't use the same word multiple times";
                            validGuess = false;
                            break;
                        }
                    }

                    if (validGuess)
                        guesses.push_back(guess);
                    break;
                }
            }
        }

        if (guess == word)
            break;
    }

    system("clear");

    cout << "Btech WORDLE!" << endl << endl;

    for (int i = 0; i < guesses.size(); ++i) {
        printGuessWord(guesses[i], word);
    }
    cout << endl;

    if (guess == word)
        cout << "\x1b[33mCorrect! The word was " << word << "\x1b[0m" << endl;
    else
        cout << "\x1b[31mYou Lost! The word was " << word << "\x1b[0m" << endl;

    return 0;
}
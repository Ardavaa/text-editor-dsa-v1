#include <iostream>
#include <conio.h>  // Untuk _kbhit() dan _getch() buat display text editornya
#include "header.h"

bool breakStatement = false;

void createList(List &L) {
    L.first = nullptr;
    L.last = nullptr;
    L.cursor = nullptr;
}

address alokasi(infotype x) {
    address P = new elmList;
    P->info = x;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

void insertChar(List &L, infotype x) {
    address P = alokasi(x);

    // insert first
    if (L.cursor == nullptr) {
        L.first = L.last = P;
        L.cursor = P;
    } else {
        // insert after (insert karakter setelah cursor)
        P->next = L.cursor->next;
        P->prev = L.cursor;

        if (L.cursor->next != nullptr) {
            L.cursor->next->prev = P;
        }
        L.cursor->next = P;

        // insert last (jika kursor berada di elemen terakhir)
        if (L.cursor == L.last) {
            L.last = P;
        }

        L.cursor = P;  // P dijadiin posisi baru dari cursor setelah di-insert
    }
}


void removeChar(List &L) {
    if (L.cursor != nullptr) {
        address temp = L.cursor;
        if (L.cursor->prev != nullptr) {
            L.cursor->prev->next = L.cursor->next;
        }
        if (L.cursor->next != nullptr) {
            L.cursor->next->prev = L.cursor->prev;
        }

        if (L.cursor == L.first) {
            L.first = L.cursor->next;
        }
        if (L.cursor == L.last) {
            L.last = L.cursor->prev;
        }

        L.cursor = L.cursor->prev;
        delete temp;
    }
}

int count_words(List L) {
    address head = L.first;
    int word_count = 0;
    bool in_word = false;

    while (head != nullptr) {
        if (head->info == ' ' || head->info == '\t' || head->info == '\n') {
            // kalaua ada spasi, tab, atau newline, kita anggap sebagai pemisah kata
            if (in_word) {
                word_count++;  // increment satu kata
                in_word = false;  // keluar dari kata
            }
        } else {
            // kalau karakter bukan spasi, kita masih dalam kata
            in_word = true;
        }
        head = head->next;
    }

    // increment kalau kata terakhir tidak diikuti spasi
    if (in_word) {
        word_count++;
    }

    return word_count;
}


void displayText(List L) {
    address temp = L.first;

    while (temp != nullptr) {
        if (temp == L.cursor) {
            cout << temp->info << "|";  // display teks dengan si kursor
        } else {
            cout << temp->info;
        }
        temp = temp->next;
    }
    cout << endl;
}

void displayFinalText(List L) {
    address temp = L.first;

    while (temp != nullptr) {
        cout << temp->info;  // cetak karakter biasa tanpa tanda si kursor
        temp = temp->next;
    }
    cout << endl;
}

void moveCursorLeft(List &L) {
    if (L.cursor != nullptr && L.cursor->prev != nullptr) {
        L.cursor = L.cursor->prev;
    }
}


void moveCursorRight(List &L) {
    if (L.cursor != nullptr && L.cursor->next != nullptr) {
        L.cursor = L.cursor->next;
    }
}

void handleInput(List &L) {
    char c;
    cout << "Text Editor Controls:" << endl;
    cout << "[Left Arrow]: Move Cursor Left" << endl;
    cout << "[Right Arrow]: Move Cursor Right" << endl;
    cout << "[Backspace]: Remove Character" << endl;
    cout << "[ESC]: Exit Editor" << endl;
    cout << "Start typing..." << endl;

    while (true && breakStatement == false) {
        if (_kbhit()) {  // meng-cath input dari si keyboard
            c = _getch();

            // navigasi kursor
            if (c == 27) {  // ESC key untuk keluar
                breakStatement = true;
            } else if (c == -32) {  // arrow keys
                c = _getch();
                if (c == 75) {  // left arrow
                    moveCursorLeft(L);
                } else if (c == 77) {  // right arrow
                    moveCursorRight(L);
                }
            } else if (c == 8) {  // backspace
                removeChar(L);
            } else {
                insertChar(L, c);  // memasukkan karakter
            }

            system("cls");  // membersihkan layar untuk refresh tampilan
            cout << "Text Editor:" << endl;
            displayText(L);


            cout << endl;
            // display jumlah karakter
            int length_words = count_words(L);

            cout << "Words: " << length_words  << endl;
        }
    }
}

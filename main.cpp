#include <iostream>
#include <conio.h>  // Untuk _kbhit() dan _getch() buat display text editornya
using namespace std;

typedef char infotype;
typedef struct elmList *address;

struct elmList {
    infotype info;
    address next;
    address prev;
};

struct List {
    address first;
    address last;
    address cursor;
};

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

        L.cursor = P;  //  P dijadiin posisi baru dari cursor setelah di-insert
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

// Display the text in the editor
void displayText(List &L) {
    address current = L.first;
    while (current != nullptr) {
        cout << current->info;
        current = current->next;
    }
   cout << "\r" << flush;  // Update text in place
}

int main() {
    List editor;
    createList(editor);

    cout << "Ketik teks (tekan 'Backspace' untuk menghapus, 'ESC' untuk keluar):\n";

    while (true) {
        if (_kbhit()) {  // cek kalau a key is pressed
            char ch = _getch();  // dapetin info "pressed key" nya

            if (ch == 27) {  // ESC key => exit
                break;
            } else if (ch == 8) {  // Backspace key => remove character
                removeChar(editor);
            } else {
                insertChar(editor, ch);
            }

            displayText(editor);
        }
    }

    cout << "\nProgram selesai.\n";
    return 0;
}

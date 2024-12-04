#include <iostream>
#include <conio.h>  // Untuk _kbhit() dan _getch() buat display text editornya
#include "header.h"

int main() {
    List editor;
    createList(editor);

    handleInput(editor);

    cout << "\nFinal Text:" << endl;
    displayFinalText(editor);  // menampilkan teks tanpa kursor setelah keluar dari loop

    return 0;
}

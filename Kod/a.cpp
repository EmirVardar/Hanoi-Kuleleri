#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAX_DISKS = 20;  // Maksimum disk sayisi

// Rekursif Hanoi cozumu
void hanoiRecursive(int n, char source, char auxiliary, char destination, int& steps) {
    if (n == 1) {
        steps++;
        return;
    }
    hanoiRecursive(n - 1, source, destination, auxiliary, steps);
    steps++;
    hanoiRecursive(n - 1, auxiliary, source, destination, steps);
}

// Iteratif Hanoi cozumu
void hanoiIterative(int n, int& steps) {
    int towers[3][MAX_DISKS] = {0};
    int tops[3] = {0};

    for (int i = n; i > 0; i--) {
        towers[0][tops[0]++] = i;
    }

    int totalMoves = pow(2, n) - 1;
    int src = 0, aux = 1, dst = 2;

    if (n % 2 == 0) {
        swap(aux, dst);
    }

    for (int move = 1; move <= totalMoves; move++) {
        int from, to;

        if (move % 3 == 1) {
            from = src;
            to = dst;
        } else if (move % 3 == 2) {
            from = src;
            to = aux;
        } else {
            from = aux;
            to = dst;
        }

        if (tops[from] == 0 || (tops[to] != 0 && towers[to][tops[to] - 1] < towers[from][tops[from] - 1])) {
            swap(from, to);
        }

        towers[to][tops[to]++] = towers[from][--tops[from]];
        steps++;
    }
}

// Grafik gosterimi
void printTowers(int towers[3][MAX_DISKS], int tops[3], int maxDisk) {
    int towerWidth = maxDisk * 2 - 1;
    int spacing = 5;  // Kuleler arası boşluk
    for (int height = maxDisk; height >= 0; height--) {
        for (int t = 0; t < 3; t++) {
            if (height == 0) {
                cout << string(towerWidth, '=') << string(spacing, ' ');
            } else if (height <= tops[t]) {
                int diskSize = towers[t][height - 1] * 2 - 1;
                int spaces = (towerWidth - diskSize) / 2;
                cout << string(spaces, ' ') << string(diskSize, '*') << string(spaces, ' ') << string(spacing, ' ');
            } else {
                cout << string((towerWidth - 1) / 2, ' ') << "|" << string((towerWidth - 1) / 2, ' ') << string(spacing, ' ');
            }
        }
        cout << endl;
    }
    for (int t = 0; t < 3; t++) {
        cout << "  " << char('A' + t) << string(towerWidth + spacing - 3, ' ');
    }
    cout << endl << endl;
}

void hanoiGraphic(int n) {
    int towers[3][MAX_DISKS] = {0};
    int tops[3] = {0};
    for (int i = n; i > 0; i--) {
        towers[0][tops[0]++] = i;
    }

    int totalMoves = pow(2, n) - 1;
    int src = 0, aux = 1, dst = 2;

    if (n % 2 == 0) {
        swap(aux, dst);
    }

    cout << "Baslangic durumu:" << endl;
    printTowers(towers, tops, n);

    for (int move = 1; move <= totalMoves; move++) {
        int from, to;

        if (move % 3 == 1) {
            from = src;
            to = dst;
        } else if (move % 3 == 2) {
            from = src;
            to = aux;
        } else {
            from = aux;
            to = dst;
        }

        if (tops[from] == 0 || (tops[to] != 0 && towers[to][tops[to] - 1] < towers[from][tops[from] - 1])) {
            swap(from, to);
        }

        towers[to][tops[to]++] = towers[from][--tops[from]];

        cout << "Adim " << move << ": Disk " << towers[to][tops[to] - 1] << "'i "
             << char('A' + from) << "'dan " << char('A' + to) << "'ye tasi" << endl;
        printTowers(towers, tops, n);
    }
}

int main() {
    int diskSayisi;
    cout << "Disk sayisini giriniz (maksimum " << MAX_DISKS << "): ";
    cin >> diskSayisi;

    if (diskSayisi > MAX_DISKS) {
        cout << "Disk sayisi cok yuksek. Maksimum " << MAX_DISKS << " disk kullanabilirsiniz." << endl;
        return 1;
    }

    // Rekursif cozum
    cout << "------Rekusif Cozum------" << endl;
    int recursiveSteps = 0;
    auto recursiveStart = chrono::high_resolution_clock::now();
    hanoiRecursive(diskSayisi, 'A', 'B', 'C', recursiveSteps);
    hanoiGraphic(min(diskSayisi, 6));
    auto recursiveEnd = chrono::high_resolution_clock::now();
    auto recursiveDuration = chrono::duration_cast<chrono::microseconds>(recursiveEnd - recursiveStart);

    // Iteratif cozum
    cout << "------Iteratif Cozum------" << endl;
    int iterativeSteps = 0;
    auto iterativeStart = chrono::high_resolution_clock::now();
    hanoiIterative(diskSayisi, iterativeSteps);
    hanoiGraphic(min(diskSayisi, 6));
    auto iterativeEnd = chrono::high_resolution_clock::now();
    auto iterativeDuration = chrono::duration_cast<chrono::microseconds>(iterativeEnd - iterativeStart);

    // Sonuclari karsilastir ve goster
    cout << "\n--- Karsilastirma Sonuclari ---" << endl;
    cout << "Disk sayisi: " << diskSayisi << endl;
    cout << "Teorik adim sayisi: 2^n - 1 = " << (pow(2, diskSayisi) - 1);
    cout << "\nZaman karmasikligi: O(2^n)" << endl;
    cout << "\nRekursif Cozum:" << endl;
    cout << "Adim sayisi: " << recursiveSteps << endl;
    cout << "Cozum suresi: " << recursiveDuration.count() << " mikrosaniye" << endl;
    cout << "\nIteratif Cozum:" << endl;
    cout << "Adim sayisi: " << iterativeSteps << endl;
    cout << "Cozum suresi: " << iterativeDuration.count() << " mikrosaniye" << endl;

    return 0;
}

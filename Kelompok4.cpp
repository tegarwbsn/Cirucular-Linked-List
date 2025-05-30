#include <iostream>
#include <string>
using namespace std;

struct Penjaga {
    string nama;
    string nim;
    int shift;
    Penjaga* next;
};

class CircularLinkedList {
private:
    Penjaga* head;
    int shiftCounter;

    void updateShiftNumbers() {
        if (head == nullptr) return;
        Penjaga* current = head;
        int shiftNum = 1;
        do {
            current->shift = shiftNum++;
            current = current->next;
        } while (current != head);
        shiftCounter = shiftNum;
    }

public:
    CircularLinkedList() {
        head = nullptr;
        shiftCounter = 1;
    }

    void tambahPenjaga(string nama, string nim) {
        Penjaga* baru = new Penjaga{nama, nim, shiftCounter++, nullptr};

        if (head == nullptr) {
            head = baru;
            head->next = head;
        } else {
            Penjaga* temp = head;
            while (temp->next != head)
                temp = temp->next;
            temp->next = baru;
            baru->next = head;
        }
        cout << "Penjaga berhasil ditambahkan.\n";
    }

    void hapusPenjaga(string nim) {
        if (head == nullptr) {
            cout << "Daftar penjaga kosong.\n";
            return;
        }

        Penjaga *current = head, *prev = nullptr;

        do {
            if (current->nim == nim) {
                if (current == head) {
                    if (head->next == head) {
                        delete head;
                        head = nullptr;
                        cout << "Penjaga berhasil dihapus.\n";
                        return;
                    }
                    Penjaga* tail = head;
                    while (tail->next != head)
                        tail = tail->next;
                    head = head->next;
                    tail->next = head;
                    delete current;
                } else {
                    prev->next = current->next;
                    delete current;
                }
                updateShiftNumbers();
                cout << "Penjaga berhasil dihapus.\n";
                return;
            }
            prev = current;
            current = current->next;
        } while (current != head);

        cout << "Penjaga dengan NIM tersebut tidak ditemukan.\n";
    }

    void tampilkanRotasi() {
        if (head == nullptr) {
            cout << "Tidak ada penjaga.\n";
            return;
        }

        Penjaga* current = head;
        cout << "=== Urutan Rotasi Penjaga ===\n";
        do {
            cout << "Shift " << current->shift
                 << ": " << current->nama
                 << " (NIM: " << current->nim << ")\n";
            current = current->next;
        } while (current != head);
    }

    void simulasiRotasi(string nama, int x) {
        if (head == nullptr) {
            cout << "Tidak ada data penjaga.\n";
            return;
        }

        Penjaga* current = head;
        bool ditemukan = false;

        do {
            if (current->nama == nama) {
                ditemukan = true;
                break;
            }
            current = current->next;
        } while (current != head);

        if (!ditemukan) {
            cout << "Penjaga tidak ditemukan.\n";
            return;
        }

        for (int i = 0; i < x; ++i) {
            current = current->next;
        }

        cout << x << " shift setelah " << nama << " adalah:\n";
        cout << "Shift " << current->shift << ": "
             << current->nama << " (NIM: " << current->nim << ")\n";
    }
};

int main() {
    CircularLinkedList rotasi;
    int pilihan;
    string nama, nim;
    int shiftKe;

    do {
        cout << "\n=== MENU ROTASI PENJAGA ===\n";
        cout << "1. Tambah Penjaga\n";
        cout << "2. Hapus Penjaga\n";
        cout << "3. Tampilkan Urutan Rotasi\n";
        cout << "4. Simulasi Rotasi (X shift dari nama tertentu)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore(); // membersihkan buffer

        switch (pilihan) {
            case 1:
                cout << "Masukkan nama penjaga: ";
                getline(cin, nama);
                cout << "Masukkan NIM penjaga: ";
                getline(cin, nim);
                rotasi.tambahPenjaga(nama, nim);
                break;

            case 2:
                cout << "Masukkan NIM yang akan dihapus: ";
                getline(cin, nim);
                rotasi.hapusPenjaga(nim);
                break;

            case 3:
                rotasi.tampilkanRotasi();
                break;

            case 4:
                cout << "Masukkan nama penjaga sebagai titik awal: ";
                getline(cin, nama);
                cout << "Berapa shift ke depan? ";
                cin >> shiftKe;
                cin.ignore();
                rotasi.simulasiRotasi(nama, shiftKe);
                break;

            case 0:
                cout << "Terima kasih!\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}

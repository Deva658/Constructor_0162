#include <iostream>
#include <string>
using namespace std;

class Petugas;
class Admin;

class Buku {
private:
    string judul;
    string penulis;
    bool dipinjam;

public:
    Buku(string j, string p) : judul(j), penulis(p), dipinjam(false) {}

    void infoBuku() const {
        cout << "Judul: " << judul << ", Penulis: " << penulis 
             << ", Status: " << (dipinjam ? "Dipinjam" : "Tersedia") << endl;
    }

    friend class Petugas;
    friend void aksesTerbatas(Admin* a, Buku* b); // hanya untuk melihat info
};

class Peminjam {
private:
    string nama;
    int id;
    int totalPinjaman;

public:
    Peminjam(string n, int i) : nama(n), id(i), totalPinjaman(0) {}

    void infoPeminjam() const {
        cout << "Nama: " << nama << ", ID: " << id 
             << ", Total Pinjaman: " << totalPinjaman << endl;
    }

    friend class Petugas;
    friend void aksesTerbatas(Admin* a, Peminjam* p); // hanya untuk melihat info
};

class Petugas {
private:
    string nama;
    int id;
    string levelAkses;

public:
    Petugas(string n, int i, string la) : nama(n), id(i), levelAkses(la) {}

    void prosesPinjam(Buku* b, Peminjam* p) {
        if (!b->dipinjam) {
            b->dipinjam = true;
            p->totalPinjaman++;
            cout << "Buku berhasil dipinjam.\n";
        } else {
            cout << "Buku sudah dipinjam.\n";
        }
    }

    void prosesKembali(Buku* b) {
        if (b->dipinjam) {
            b->dipinjam = false;
            cout << "Buku berhasil dikembalikan.\n";
        } else {
            cout << "Buku belum dipinjam.\n";
        }
    }

    friend class Admin;
};

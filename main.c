#include <stdio.h>
#include <stdlib.h>

// Struktur utama pohon. Tanpa typedef, panggil dengan 'struct Node'
struct Node {
    int value;           // Data yang disimpan
    struct Node* left;   // Pointer ke anak kiri
    struct Node* right;  // Pointer ke anak kanan
    int height;          // Level ketinggian node (penting untuk AVL)
};

// --- FUNGSI PEMBANTU (Utility) ---

// Ambil tinggi node. Kalau NULL (kosong), tingginya 0. 
// Ini mencegah program crash kalau ngecek node yang belum ada.
int getHeight(struct Node* n) {
    if (n == NULL) return 0;
    return n->height;
}

// Cari nilai mana yang lebih besar. Dipakai buat nentuin tinggi tree.
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Bikin node baru di memori heap
struct Node* createNode(int value) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // Node baru dianggap punya tinggi 1 (daun/leaf)
    return newNode;
}

// Cek selisih tinggi kiri vs kanan.
// Kalau hasilnya > 1 (berat kiri) atau < -1 (berat kanan), berarti harus dirotasi.
int getBalance(struct Node* n) {
    if (n == NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// --- FUNGSI ROTASI (Jantungnya AVL) ---

/* Right Rotate: Dipakai kalau tree berat ke Kiri (LL Case).
   Analogi: Node 'x' naik pangkat jadi root, 'y' turun jadi anak kanannya.
*/
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Proses pindah jabatan
    x->right = y;
    y->left = T2;

    // Update tinggi node yang berubah posisinya (y dulu baru x)
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // Return root baru
}



/* Left Rotate: Dipakai kalau tree berat ke Kanan (RR Case).
   Analogi: Node 'y' naik pangkat jadi root, 'x' turun jadi anak kirinya.
*/
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Proses pindah jabatan
    y->left = x;
    x->right = T2;

    // Update tinggi node yang berubah posisinya (x dulu baru y)
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // Return root baru
}



// --- OPERASI UTAMA ---

/* Insert: Gabungan logika BST dan AVL.
   BST: Nentuin arah kiri/kanan.
   AVL: Nentuin perlu rotasi atau enggak setelah data masuk.
*/
struct Node* insert(struct Node* node, int value) {
    // 1. LOGIKA BST (Cari posisi kosong)
    if (node == NULL) return createNode(value);

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else
        return node; // Balikin node apa adanya kalau nilainya sama (ga boleh duplikat)

    // 2. UPDATE HEIGHT (Setelah balik dari rekursi, tinggi diupdate satu-satu)
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3. LOGIKA AVL (Cek apakah jadi miring/tidak seimbang)
    int balance = getBalance(node);

    // KASUS LL: Berat kiri, data baru ada di kirinya anak kiri. Cukup Right Rotate.
    if (balance > 1 && value < node->left->value)
        return rightRotate(node);

    // KASUS RR: Berat kanan, data baru ada di kanannya anak kanan. Cukup Left Rotate.
    if (balance < -1 && value > node->right->value)
        return leftRotate(node);

    // KASUS LR: Berat kiri, tapi data baru masuk ke kanan. Left dulu baru Right Rotate.
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // KASUS RL: Berat kanan, tapi data baru masuk ke kiri. Right dulu baru Left Rotate.
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Balikin node (bisa jadi alamatnya berubah kalau habis rotasi)
}



// Fungsi Cari: Standar BST (Cepat karena buang setengah kemungkinan setiap langkah)
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->value == key)
        return root;
    
    if (key < root->value)
        return search(root->left, key);
    
    return search(root->right, key);
}

// Cetak In-order: Hasilnya pasti urut dari kecil ke besar
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d (h:%d) ", root->value, root->height);
        inOrder(root->right);
    }
}

void displayAVL(struct Node* root, char* prefix, bool isLeft) {
    if (root == NULL) return;

    printf("%s", prefix);
    printf("%s", (isLeft ? "├── " : "└── "));
    printf("[%d]\n", root->value);

    // Siapkan prefix untuk level selanjutnya
    char newPrefix[255];
    sprintf(newPrefix, "%s%s", prefix, (isLeft ? "│   " : "    "));

    // Rekursi ke anak-anaknya
    if (root->left || root->right) {
        if (root->left) displayAVL(root->left, newPrefix, true);
        else {
            printf("%s├── [NULL]\n", newPrefix);
        }
        
        if (root->right) displayAVL(root->right, newPrefix, false);
        else {
            printf("%s└── [NULL]\n", newPrefix);
        }
    }
}

int main() {
    struct Node* root = NULL;

    // Contoh Input yang bikin Tree harus muter-muter (Self Balancing)
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30); // Otomatis rotasi karena miring kanan (RR)
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25); // Masuk ke tengah, memicu rotasi kompleks

    printf("Tampilan AVL (In-order traversal):\n");
    inOrder(root);
    printf("\n");

    printf("\n=== STRUKTUR VISUAL AVL TREE ===\n");
    printf("Root\n");
    displayAVL(root, "", false);
    printf("================================\n");
}
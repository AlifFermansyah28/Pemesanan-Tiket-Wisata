#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
int isExistFile(char *fileName)
{
	FILE *fp;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{

		return 0;
	}
	else
	{
		fclose(fp);
		return 1;
	}
}

void makeFile(char *fileName)
{
	FILE *fp;
	fp = fopen(fileName, "w");
	fclose(fp);
}

char *readFileText(char *fileName)
{
	FILE *fp;
	char *text;
	int size;
	fp = fopen(fileName, "r");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	if (size == 0)
	{
		fclose(fp);
		return NULL;
	}
	else
	{
		fseek(fp, 0, SEEK_SET);
		text = (char *)malloc(sizeof(char) * size);
		fread(text, sizeof(char), size, fp);
		fclose(fp);
		return text;
	}
}

char FILE_ANTRIAN[] = "antrian.txt";
char FILE_TERVERIFIKASI[] = "verifikasi.txt";
char enter[] = "\n";
struct node
{ // BUAT KESELURUHAN
	int data, tanggal, nomor;
	char wisata[30], judul[30];
	struct node *next;
	struct node *right;
	struct node *left;
};
typedef struct node node;

struct queue
{ // BUAT QUEUE SAJA
	int count;
	node *front;
	node *rear;
};
typedef struct queue queue;

void insert(node **root, node *newNode);
void loadDataQueqe(queue *myQueue)
{
	if (isExistFile(FILE_ANTRIAN))
	{
		// Masukkan data file ke dalam memories
		char *data = readFileText(FILE_ANTRIAN);
		if (data != NULL)
		{
			char *a, *c;
			node temp;
			for (a = strtok_r(data, enter, &c); a != NULL; a = strtok_r(NULL, enter, &c))
			{
				node *newNode = (node *)malloc(sizeof(node));
				strcpy(newNode->wisata, a);
				a = strtok_r(NULL, enter, &c);
				if (a == NULL)
				{
					break;
				}
				newNode->data = atoi(a);

				newNode->next = NULL;
				newNode->right = NULL;
				newNode->left = NULL;
				if (myQueue->count == 0)
				{
					myQueue->front = newNode;
					myQueue->rear = newNode;
				}
				else
				{
					myQueue->rear->next = newNode;
					myQueue->rear = newNode;
				}
				myQueue->count++;

				// Masukkan data ke setiap nodes
			}
		}
		// Masukkan data ke dalam queue
	}
	else
	{
		// Buat file jika file tidak ada
		makeFile(FILE_ANTRIAN);
	}
}

void loadDataVerif(node **root)
{
	if (isExistFile(FILE_TERVERIFIKASI))
	{
		// Masukkan data file ke dalam memories
		char *data = readFileText(FILE_TERVERIFIKASI);
		if (data != NULL)
		{
			char *a, *c;
			node temp;
			for (a = strtok_r(data, enter, &c); a != NULL; a = strtok_r(NULL, enter, &c))
			{
				node *newNode = (node *)malloc(sizeof(node));
				strcpy(newNode->judul, a);
				a = strtok_r(NULL, enter, &c);
				if (a == NULL)
				{
					break;
				}
				newNode->nomor = atoi(a);
				newNode->left = NULL;
				newNode->right = NULL;
				// dequeue
				insert(root, newNode);
				// Masukkan data ke setiap nodes
			}
		}
		// Masukkan data ke dalam queue
	}
	else
	{
		// Buat file jika file tidak ada
		makeFile(FILE_TERVERIFIKASI);
	}
}

void rewriteQueqe(queue myQueue)
{

	node *temp;
	temp = myQueue.front;
	FILE *fp;
	fp = fopen(FILE_ANTRIAN, "w");
	if (temp != NULL)

	{

		while (temp)
		{
			if (temp == NULL)
			{
				break;
			}
			fprintf(fp, "%s", temp->wisata);
			fprintf(fp, "%s", enter);
			fprintf(fp, "%d", temp->data);
			fprintf(fp, "%s", enter);
			temp = temp->next;
		}
	}
	else
	{
		fprintf(fp, "%s", "");
	}

	fflush(fp);
	fclose(fp);
}

queue createQueue(void)
{ // BUAT QUEUE
	queue myQueue;
	myQueue.count = 0;
	myQueue.front = NULL;
	myQueue.rear = NULL;
	return (myQueue);
}

int enqueue(int data, char wisata[30], queue *myQueue)
{ // MASUKKAN NILAI KE QUEUE
	int success;

	if (myQueue->count >= 99)
		success = 0;

	else
	{
		node *newPtr;
		newPtr = (node *)malloc(sizeof(node));

		newPtr->data = data;
		strcpy(newPtr->wisata, wisata);

		newPtr->next = NULL;

		if (myQueue->front == NULL)
			myQueue->front = newPtr;
		else
			myQueue->rear->next = newPtr;

		myQueue->rear = newPtr;
		myQueue->count++;
		success = 1;

		// Simpan Data pada file para
		FILE *fp;
		fp = fopen(FILE_ANTRIAN, "a");
		if (fp == NULL)
		{
			makeFile(FILE_ANTRIAN);
			fp = fopen(FILE_ANTRIAN, "a");
		}

		fprintf(fp, "%s", newPtr->wisata);
		fprintf(fp, "%s", enter);
		fprintf(fp, "%d", newPtr->data);
		fprintf(fp, "%s", enter);
		fflush(fp);
		fclose(fp);
	}
	return success;
}

node *createNode(void)
{ // NODE BUAT QUEUE
	node *newPtr;
	newPtr = (node *)malloc(sizeof(newPtr));
	return (newPtr);
}

void destroy(queue *myQueue)
{ // DESTROY QUEUE
	node *temp;

	while (myQueue->count != 0)
	{
		temp = myQueue->front;
		myQueue->front = myQueue->front->next;
		myQueue->count--;
		free(temp);
	}
	myQueue->count = 0;
	myQueue->front = NULL;
	myQueue->rear = NULL;
}

void display(queue myQueue)
{ // TAMPILKAN ANTRIAN
	node *temp;
	temp = myQueue.front;

	if (temp == NULL)
		printf("Kosong");

	else
	{
		printf("Antrian :\n");
		while (temp)
		{
			printf("\nJudul wisata      %s\n", temp->wisata);
			printf("Nomor tanggal     %d\n", temp->data);
			temp = temp->next;
		}
	}
}
// =============================================================================================================================================================

node *createnOde(int bil)
{ // NODE BUAT SINGLE LINKED LIST
	node *ptr;
	ptr = (node *)malloc(sizeof(node));

	if (ptr != NULL)
	{
		ptr->tanggal = bil;
		ptr->next = NULL;
	}
	return (ptr);
}

void insertNode(node **head, node *pPre, node *pNew)
{ // MASUKKAN DATA KE NODE
	if (pPre == NULL)
	{
		pNew->next = *head;
		*head = pNew;
	}
	else
	{
		pNew->next = pPre->next;
		pPre->next = pNew;
	}
}

void deleteNode(node **head, node *pPre, node *pCur)
{ // HAPUS DATA KE NODE
	if (pPre == NULL)
		*head = pCur->next;
	else
		pPre->next = pCur->next;
	free(pCur);
}

void tranverse(node *head)
{ // TAMPILKAN DATA-DATA
	node *pWalker;
	pWalker = head;
	system("cls");

	if (pWalker == NULL)
		printf("NULL");

	printf("Judul wisata berserta tanggal yang tersisa :\n\n");
	printf("1. PULAU KARIMUNJAWA\n");
	while (pWalker != NULL)
	{

		if (pWalker->tanggal < 10)
		{ // JIKA NILAI KURANG DARI 10
			printf("|0%d| ", pWalker->tanggal);
			goto w;
		}

		printf("|%d| ", pWalker->tanggal);
	w:
		pWalker = pWalker->next;

		if (pWalker->tanggal == 31)
		{
			pWalker = pWalker->next;
			break;
		}

		if (pWalker->tanggal >= 31)
		{
			system("cls");
			printf("DESTINASI WISATA berserta tanggal yang tersisa :\n\n");
			printf("1. PULAU KARIMUNJAWA\n");
			printf("SEMUA tanggal SUDAH DIPESAN!");
			break;
		}
	}

	printf("\n\n2. GUNUNG BROMO\n");
	while (pWalker != NULL)
	{

		if (pWalker->tanggal - 31 < 10)
		{ // JIKA NILAI KURANG DARI 10
			printf("|0%d| ", pWalker->tanggal - 31);
			goto q;
		}

		if (pWalker->tanggal >= 31 && pWalker->tanggal >= 62)
		{
			printf("SEMUA tanggal SUDAH DIPESAN!");
			pWalker = pWalker->next;
			break;
		}

		printf("|%d| ", pWalker->tanggal - 31);
	q: //-1
		pWalker = pWalker->next;

		if (pWalker->tanggal == 62)
		{
			pWalker = pWalker->next;
			break;
		}
	}

	printf("\n\n3. RAJA AMPAT\n");
	while (pWalker != NULL)
	{

		if (pWalker->tanggal - 62 < 10)
		{ // JIKA NILAI KURANG DARI 10
			printf("|0%d| ", pWalker->tanggal - 62);
			goto e;
		}

		if (pWalker->tanggal == 93)
		{
			printf("SEMUA tanggal SUDAH DIPESAN!");
			break;
		}

		printf("|%d| ", pWalker->tanggal - 62);
	e: //-1
		pWalker = pWalker->next;

		if (pWalker->tanggal == 93)
		{
			pWalker = pWalker->next;
			break;
		}

		if (pWalker->tanggal >= 31 && pWalker->tanggal >= 62 && pWalker->tanggal >= 93)
		{
			printf("SEMUA tanggal SUDAH DIPESAN!");
			break;
		}
	}
}

void deleteList(node *head)
{ // DESTROY SINGLE LINKED LIST
	node *pTemp;

	while (head != NULL)
	{
		pTemp = head;
		head = head->next;
		free(pTemp);
	}
}

void hapusData(node **head, int tanggal)
{ // MENGHAPUS DATA
	node *pCur, *pPre;
	int pos;

	if (tanggal >= 31 && tanggal <= 60)
	{
		tanggal = tanggal + 1;
	}
	else if (tanggal >= 61 && tanggal < 93)
	{
		tanggal = tanggal + 2;
	}

	pPre = NULL;
	pCur = *head;

	while (pCur != NULL && pCur->tanggal != tanggal)
	{
		pPre = pCur;
		pCur = pCur->next;
	}

	if (pCur != NULL)
		deleteNode(head, pPre, pCur);
	else
	{
		printf("\ntanggal itu sudah terpesan!");
		getch();
	}
}

// =============================================================================================================================================================

node *creatEnode(int bil, char judul[30])
{ // BIKIN NODE BUAT BST
	node *pNew;

	pNew = (node *)malloc(sizeof(node));
	if (pNew != NULL)
	{
		pNew->nomor = bil;
		strcpy(pNew->judul, judul);
		pNew->left = NULL;
		pNew->right = NULL;
	}
	return (pNew);
}

void insert(node **root, node *newNode)
{ // MASUKKAN DATA KE NODE
	if (*root == NULL)
	{

		*root = newNode;
	}
	else if (newNode->nomor < (*root)->nomor)
		insert(&((**root).left), newNode);

	else
	{

		insert(&((**root).right), newNode);
	}
	// printf("");
}

void inorder(node *root, int *a, int *b, int *c)
{ // TAMPILKAN DATA

	if (root != NULL)
	{
		inorder(root->left, a, b, c);
		if (strcmp(root->judul, "GUNUNG BROMO") == 0)
			*b = *b + 1600000;
		else if (strcmp(root->judul, "RAJA AMPAT") == 0)
			*c = *c + 15000000;
		else
			*a = *a + 3000000;
		printf("%d\n", root->nomor);
		printf("%s\n\n", root->judul);
		inorder(root->right, a, b, c);
	}
}

node *findLargestBST(node *root)
{
	if (root->right == NULL)
		return (root);
	else
		return (findLargestBST(root->right));
}

bool deletenOde(node **root, int key)
{
	node *pDel;
	node *pReplace;

	if (*root == NULL)
		return (false);

	else if (key < (*root)->nomor)
		return (deletenOde(&((**root).left), key));

	else if (key > (*root)->nomor)
		return (deletenOde(&((**root).right), key));

	else
	{
		if ((*root)->left == NULL && (*root)->right == NULL)
		{
			pDel = *root;
			*root = NULL;
			free(pDel);
			return (true);
		}

		else if ((*root)->left == NULL)
		{
			pDel = *root;
			*root = (*root)->right;
			free(pDel);
			return (true);
		}

		else if ((*root)->right == NULL)
		{
			pDel = *root;
			*root = (*root)->left;
			free(pDel);
			return (true);
		}

		else
		{
			pDel = *root;
			pReplace = findLargestBST((*root)->left);
			pDel->nomor = pReplace->nomor;
			return (deletenOde(&((**root).left), pReplace->nomor));
		}
	}
}

void deleteBST(node **root)
{
	while (*root != NULL)
		deletenOde(root, (*root)->nomor);
}

int cekcoy(node *root, int num, char judul[30], int cpksgd)
{ // TAMPILKAN DATA
	if (root != NULL)
	{
		cpksgd = cekcoy(root->left, num, judul, cpksgd);

		if (num == root->nomor && strcmp(root->judul, judul) == 0)
		{
			cpksgd = 0;
		}

		cpksgd = cekcoy(root->right, num, judul, cpksgd);
	}
	return (cpksgd);
}

// =============================================================================================================================================================

void dequeue(queue *myQueue, node **root, node **tanggal)
{
	node *pNew;

	int dequeue;
	char wisata[30];
	if (myQueue->count == 0)
		printf("\nTidak ada antrian");

	else
	{
		node *dltPtr;

		dltPtr = myQueue->front;
		dequeue = dltPtr->data;
		strcpy(wisata, dltPtr->wisata);

		myQueue->front = myQueue->front->next;
		free(dltPtr);
		myQueue->count--;
		printf("\ntanggal nomor %d dari wisata %s terpesan!", dequeue, wisata);

		if (strcmp(wisata, "GUNUNG BROMO") == 0)
		{
			hapusData(tanggal, dequeue + 30);
		}
		else if (strcmp(wisata, "RAJA AMPAT") == 0)
		{
			hapusData(tanggal, dequeue + 60);
		}
		else
		{
			hapusData(tanggal, dequeue);
		}

		pNew = creatEnode(dequeue, wisata);

		if (pNew == NULL)
		{
			printf("insert gagal");
			getch();
		}
		else
		{

			insert(root, pNew);
			FILE *fp;
			fp = fopen(FILE_TERVERIFIKASI, "a");
			if (fp == NULL)
			{
				makeFile(FILE_TERVERIFIKASI);
				fp = fopen(FILE_TERVERIFIKASI, "a");
			}

			fprintf(fp, "%s", pNew->judul);
			fprintf(fp, "%s", enter);
			fprintf(fp, "%d", pNew->nomor);
			fprintf(fp, "%s", enter);
			fflush(fp);
			fclose(fp);
		}
		rewriteQueqe(*myQueue);
	}
}

void tampil()
{
	printf("         > > > TANGGAL PELAYANAN < < <            ||\n");
	printf("                                                  ||\n");
	printf("                                                  ||\n");
	printf("|01| |02| |03| |04| |05| |06| |07| |08| |09| |10| ||\n");
	printf("                                                  ||\n");
	printf("|11| |12| |13| |14| |15| |16| |17| |18| |19| |20| ||\n");
	printf("                                                  ||\n");
	printf("|21| |22| |23| |24| |25| |26| |27| |28| |29| |30| ||\n");
	printf("                                                  ||\n");
	printf("                  ^ ^ ^ ^ ^ ^                     ||\n");
	printf("                                                  ||\n");
	printf("====================================================\n\n");
}

//==============================================================================================================================================================

int main()
{
	int choice, pilwisata, num, success, a, b, c;
	char wisata[30];
	queue myQueue;
	int p;
	myQueue = createQueue();
	system("color 70");

	node *head, *ptr, *root;
	root = NULL;
	int bil, tanggal;
	head = NULL;
	loadDataVerif(&root);

	for (tanggal = 99; tanggal > 0; tanggal--)
	{
		bil = tanggal - 1;
		ptr = createnOde(bil + 1);
		if (ptr == NULL)
		{
			printf("insert gagal");
			getch();
		}
		else
			insertNode(&head, NULL, ptr);
	}
	// Load data dari file

	loadDataQueqe(&myQueue);

	do
	{
	z:
		printf("============================================\n");
		printf("=>         PEMESANAN TIKET TRAVEL        <=\n"); // TAMPILAN UTAMA PROGRAM KITA
		printf("============================================\n");
		printf("                                          ||\n");
		printf("Lanjutkan sebagai :                       ||\n");
		printf("                                          ||\n");
		printf("1. Pengunjung                             ||\n");
		printf("2. Admin                                  ||\n");
		printf("3. Keluar program                         ||\n");
		printf("                                          ||\n");
		printf("============================================\n\n");
		printf("Masukkan pilihan : ");
		scanf("%d", &p);

		//=========================================================================================================================================================

		if (p == 1)
		{ // PANEL PENGUNJUNG
			int pil;

			do
			{
				system("cls");
				printf("============================================\n");
				printf("=>            PANEL PENGUNJUNG            <=\n");
				printf("============================================\n");
				printf("                                          ||\n");
				printf("1. Pilih Tempat Wisata                            ||\n");
				printf("2. Lihat Jadwal Terbang                   ||\n");
				printf("3. Keluar                                 ||\n");
				printf("                                          ||\n");
				printf("============================================\n\n");
				printf("Masukkan pilihan : ");
				scanf("%d", &pil);

				if (pil == 1)
				{ // INPUT DATA PENGUNJUNG - ENQUEUE
					system("cls");
					printf("===================================================\n");
					printf("=>                JADWAL  TAYANG                <=\n"); // TAMPILAN UTAMA PROGRAM KITA
					printf("===================================================\n");
					printf("                                                 ||\n");
					printf("   TEMPAT WISATA       ||   ESTIMASI WAKTU   ||      HARGA  TIKET    ||\n");
					printf("-------------------------------------------------||\n");
					printf("1. PULAU KARIMUNJAWA   ||  2 Hari 3 Malam    || Rp 3.000.000,00/org  ||\n");
					printf("2. GUNUNG BROMO        ||  1 Hari 1 Malam    || Rp 1.600.000,00/org  ||\n");
					printf("3. RAJA AMPAT          ||  3 Hari 3 Malam    || Rp 15.000.000,00/org ||\n");
					printf("                                                                     ||\n");
					printf("=====================================================================\n\n");
					printf("Pilih Wisata        : ");
					scanf("%d", &pilwisata);

					if (pilwisata == 1)
						strcpy(wisata, "PULAU KARIMUNJAWA");
					else if (pilwisata == 2)
						strcpy(wisata, "GUNUNG BROMO");
					else if (pilwisata == 3)
						strcpy(wisata, "RAJA AMPAT");
					else
					{
						printf("wisata itu tidak ada!");
						getch();
						system("cls");
						goto z;
					}

					printf("Tanggal Pemesanan : ");
					scanf("%d", &num);
					if (num < 1 || num > 30)
					{
						printf("\n	Untuk tgl 31 Diliburkan!");
						getch();
						system("cls");
						goto z;
					}
					node *temp = myQueue.front;
					while (temp != NULL)
					{
						if (num == temp->data && strcmp(wisata, temp->wisata) == 0)
						{
							break;
						}
						temp = temp->next;
					}
					if (temp == NULL && cekcoy(root, num, wisata, 1))
						success = enqueue(num, wisata, &myQueue);
					else
					{
						printf("Sudah terpesan/masuk daftar antrian\nTidak dapat dipesan");
						getch();
					}

					if (success == 0)
					{
						printf("operasi enqueue gagal");
						getch();
					}
				}

				else if (pil == 2)
				{ // LIHAT DENAH TEMPAT DUDUK
					system("cls");
					tampil();
					getch();
				}

				else if (pil > 3 || pil < 1)
				{ // APABILA PENGUNJUNG MEMBERI MASUKKAN SELAIN 1-3
					printf("pilihan invalid!");
					getch();
				}
				system("cls");

			} while (pil != 3); // KEMBALI KE TAMPILAN UTAMA PROGRAM
		}

		//=========================================================================================================================================================

		else if (p == 2)
		{ // PANEL ADMIN
			int pil;
			char name[6], pass[6];

			do
			{
				printf("\nusername : ");
				scanf("%s", &name);
				printf("password : ");
				scanf("%s", &pass);

				if (strcmp("admin", name) == 0 && strcmp("admin", pass) == 0)
				{ // PROSES AUTENTIKASI

					do
					{
						system("cls");

						printf("============================================\n");
						printf("=>              PANEL ADMIN               <=\n");
						printf("============================================\n");
						printf("                                          ||\n");
						printf("1. Tampilkan antrian                      ||\n");
						printf("2. Verifikasi                             ||\n");
						printf("3. Tanggal Pelayanan                      ||\n");
						printf("4. Laporan hari ini                       ||\n");
						printf("5. Kembali ke menu utama                  ||\n");
						printf("                                          ||\n");
						printf("============================================\n\n");
						printf("Masukkan pilihan : ");
						scanf("%d", &pil);

						if (pil == 1)
						{ // TAMPILKAN ANTRIAN - SHOW QUEUE
							system("cls");
							display(myQueue);
							getch();
						}

						else if (pil == 2)
						{ // HAPUS ANTRIAN - DEQUEUE
							dequeue(&myQueue, &root, &head);
							getch();
						}

						else if (pil == 3)
						{ // LIHAT tanggal KOSONG - SINGLE LINKED LIST
							tranverse(head);
							getch();
						}

						else if (pil == 4)
						{ // LIHAT LAPORAN - BINARY SEARCH TREE
							a = 0;
							b = 0;
							c = 0;
							inorder(root, &a, &b, &c);

							if (a + b + c == 0)
							{
								printf("Belum ada pemesanan!");
							}

							if (a + b + c != 0)
							{
								printf("Laba dari PULAU KARIMUNJAWA adalah : Rp %d\n", a);
								printf("Laba dari GUNUNG BROMO adalah      : Rp %d\n", b);
								printf("Laba dari RAJA AMPAT adalah        : Rp %d\n", c);
								printf("Laba total                         : Rp %d", a + b + c);
							}
							getch();
						}

						else if (pil < 1 || pil > 5)
						{ // APABILA PENGUNJUNG MEMBERI MASUKKAN SELAIN 1-6
							printf("Pilihan invalid!");
							getch();
							system("cls");
						}

					} while (pil != 5); // KEMBALI KE TAMPILAN UTAMA PROGRAM
				}

				else
				{ // PROSES AUTENTIKASI GAGAL
					printf("nama pengguna dan kata sandi salah!");
					getch();
					system("cls");
					goto z;
				}
				system("cls");

			} while (pil != 5); // KEMBALI KE TAMPILAN UTAMA PROGRAM
		}

		else if (p < 1 || p > 3)
		{ // APABILA MEMBERI MASUKAN SELAIN 1 SAMPAI 3
			printf("pilihan invalid!");
			getch();
			system("cls");
		}

	} while (p != 3);
	destroy(&myQueue);
	deleteList(head);
	deleteBST(&root); // KELUAR PROGRAM
}

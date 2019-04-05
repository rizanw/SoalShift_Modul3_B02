# SoalShift_Modul3_B02

## 1. soal1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
##### Contoh
##### ./faktorial 5 3 4
##### 3!=6
##### 4!=24
##### 5!=120
### Jawaban:
> Check : [Full SourceCode](https://github.com/sherlyrosa/SoalShift_Modul3_B02/blob/master/SoalNo1/no1.c)
### Penjelasan :
1. Karena input-an pada file yang diminta ialah dalam bentuk argumen maka menggunakan `argc` dan `argv`.
2. Untuk menghitung `factorial` nya 
```sh
void *factorial(void *args) {
  int fac=1;
  for(int a=1; a<=num[j];a++){
    fac=fac*a;
  }
  printf("%d! = %d \n",num[j],fac);
  j++;
  status=1;

```
3. Untuk merubah dari `string` menjadi `integer` dengan menggunakan fungsi `atoi`
```sh
while(argv[i] != NULL){
  num[i]=atoi(argv[i]);
  i++;}
```
4. Karena yang diminta sorting 
```sh
for(k=1;k<argc;k++){
  for(j=k+1;j<argc;j++){
    int angka1=atoi(argv[k]);
    int angka2=atoi(argv[j]);
    if(angka2<angka1){
      char *temp = argv[j];
      int temp2 = num[j];
      num[j] = num[k];
      num[k] = temp2;
      argv[j] = argv[k];
      argv[k] = temp;
    }
  }
```
## 2. soal2
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi  sebagai berikut:  

a. Terdapat 2 server: server penjual dan server pembeli

b. 1 server hanya bisa terkoneksi dengan 1 client

c. Server penjual dan server pembeli memiliki stok barang yang selalu sama

d. Client yang terkoneksi ke server penjual hanya bisa menambah stok
 	
        Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1

e. Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
	
        Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1

f. Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
	
        Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
	
        Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”

g. Server penjual akan mencetak stok saat ini setiap 5 detik sekali

h. Menggunakan thread, socket, shared memory
### Jawaban :
> Check : [Full SourceCode](https://github.com/sherlyrosa/SoalShift_Modul3_B02/tree/master/SoalNo2)
### Penjelasan :
#### Client Pembeli
1. Membuat deskriptor file socket

```sh
if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	printf("\n Socket creation error \n");
        return -1;
    }
    
 ```
 
 2. Tetapkan alamat IP di `servaddr` ke `127.0.0.1` karena server juga berada di mesin yang sama. Alamat dalam `servaddr` harus dalam format integer, karenanya menggunakan fungsi `inet_pton`

```sh
 if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
```

3. Hubungkan ke perangkat yang `address` dan nomor `port`nya ditentukan di `servaddr`.

```sh
if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
```

4. Client pembeli melakukan apa yang diperintahkan

```sh
while(1) {
        char perintah[10];
        scanf("%s", perintah);
        send(sock , perintah , strlen(perintah) , 0 );
        valread = read(sock, temp, 1024);
        printf("%s\n", temp);
        memset(temp, 0, sizeof(temp));
    }
```

#### Client Penjual
1. Untuk proses socketnya sama dengan `Client Pembeli`

2. Client penjual melakukan apa yang diperintahkan

```sh
while(1) {
        char perintah[10];
        scanf("%s", perintah);
        send(sock, perintah, strlen(perintah), 0);
    }
```
#### Server Pembeli

1. Memaksa melampirkan socket ke `port`

```sh
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
   
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
```

2. Melaksanakan yang diperintahkan, `sizeof()` untuk mengembalikan jumlah memori.

```sh
 while((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))>0) {
        memset(buffer, 0, sizeof(buffer));
        while(valread = read( new_socket , buffer, 1024) > 0) {
            if(strcmp(buffer, "beli") == 0) {
                if(*value == 0)
                    send(new_socket, "Transaksi Gagal", strlen("Transaksi Gagal"), 0);
                else {
                    *value -= 1;
                    send(new_socket, "Transaksi Berhasil", strlen("Transaksi Berhasil"), 0);
                }
            }
            memset(buffer, 0, sizeof(buffer));
        }
    }
 ```
 
#### Server Penjual
1. Socket memiliki perintah yang sama dengan server pembeli

2. Melaksanakan yang diperintahkan, `sizeof()` untuk mengembalikan jumlah memori.

```sh
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))>0) {
        memset(buffer, 0, sizeof(buffer));
        while(valread = read( new_socket , buffer, 1024) > 0) {
            if(strcmp(buffer, "tambah") == 0) {
                *value += 1;
            }
            memset(buffer, 0, sizeof(buffer));
        }
    }
```

3. Untuk mengeluarkan jumlah stok yang tersedia di penjual

```sh
void *print_value(void *ptr) {
    while(1) {
        printf("Stok saat ini : %d\n", *value);
        sleep(5);
    }
```
## 3. soal3
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:

a. Terdapat 2 karakter Agmal dan Iraj
b. Kedua karakter memiliki status yang unik
	-Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
	
	-Iraj memiliki Spirit_Status, di awal program memiliki status 100
	
	-Terdapat 3 Fitur utama
		
		All Status, yaitu menampilkan status kedua sahabat
		
		Ex: Agmal WakeUp_Status = 75 
      		    
		    Iraj Spirit_Status = 30
		
		“Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
		
		“Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
	
	-Terdapat Kasus yang unik dimana:
		
		Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
		
		Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
	
	-Program akan berhenti jika Salah Satu :
		
		WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
		
		Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)

#### Syarat Menggunakan Lebih dari 1 Thread
### Jawaban:
> Check : [Full SourceCode](https://github.com/sherlyrosa/SoalShift_Modul3_B02/blob/master/SoalNo3/no3.c)
### Penjelasan :
1. pertama-tama buat karakter agmal dan iraj dalam bentuk fungsi, dan langsung dalam bentuk thread, karena akan dijalankan secara pararel.
```c
void *agmal(void *argv);
void *iraj(void *argv);
```
2. Buat variable untuk menampung WakeUp status Agmal dan Spirit Status Iraj sebagai variable global.
```c
int WakeUp_Status = 0;
int Spirit_Status = 100;
```
3. Buat fungsi agmal dan iraj bekerja sebagai thread.
```c
... 
    pthread_t tid_a, tid_i, tid_s;
    pthread_create(&tid_a, NULL, agmal, NULL);
    pthread_create(&tid_i, NULL, iraj, NULL);
...
    pthread_join(tid_a, NULL);
    pthread_join(tid_i, NULL);
...
```
4. Buat menu main aplikasi menggunakan command.
```c
    char *cmd = malloc(100);
    char *s1 = "All Status";
    char *s2 = "Agmal Ayo Bangun";
    char *s3 = "Iraj Ayo Tidur";
...
    while(1){
        gets(cmd);
        if(strcasecmp(cmd, s1) == 0){
            printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }else if(strcasecmp(cmd, s2) == 0){
            printf("agmal ayo bangun\n");
        }else if(strcasecmp(cmd, s3) == 0){
            printf("iraj ayo tidur\n");
        }
    }
...
```
5. Karena antara command dan fungsi yang menjalankan perubahan status agmal dan iraj diberbeda tempat namun berjalan seirama, dapat digunakan variable untuk memanipulasi keadan mereka. Pertama buat varible untuk menunjuk keadaan dimana user memberikan command ke fungsi agmal dan iraj.
```c
int i_ptr = 0;
int a_ptr = 0;
```
6. dan karena di kondisi dimana kita tidak dapat memberikan command sebabanyak tiga kali maka dapat ditambahkan variable global:
```c
int i_stat = 0;
int a_stat = 0;
```
7. Sekarang proses utama di fungsi main() dapat dilengkapi menjadi :
```c
    while(1){
        gets(cmd);
        if(strcasecmp(cmd, s1) == 0){
            printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }else if(strcasecmp(cmd, s2) == 0){
            // printf("agmal ayo bangun\n");
            if(a_stat != 3)
                a_ptr = 1;
        }else if(strcasecmp(cmd, s3) == 0){
            // printf("iraj ayo tidur\n");
            if(i_stat != 3)
                i_ptr = 1;
        }
    }
```
8. Setelah itu, lengkapi fungsi agmal, dimana setelah variable a_stat berisikan 3 makan fungsi ini akan di-disable selama 10 detik, dan jika tidak maka value WakeUp_Status ditambah 15 dan i_stat bertambah 1.
```c
void *agmal(void *argv){
    while (1) {
        if(a_stat == 3){            
            printf("Agmal Ayo Bangun disabled 10 s\n");
            sleep(10);
            // printf("\tagmal sleep selesai\n");
            a_stat = 0;
        }else if(a_ptr == 1 && a_stat != 3){
            a_ptr = 0;
            WakeUp_Status += 15;
            i_stat++;
            // printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            // printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }
    }
    
}
```
9. Begitu juga dengan fungsi iraj, namun sebaliknya.
```c
void *iraj(void *argv){
    while (1) {
        if(i_stat == 3){
            printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
            sleep(10);
            // printf("\tiraj sleep selesai\n");
            i_stat = 0;
        }else if(i_ptr == 1 && i_stat != 3){
            i_ptr = 0;
            Spirit_Status -= 20;
            a_stat++;
            // printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            // printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }
    }
}
```
10. Terakhir tambahkan thread untuk memeriksa dimana WakeUp_Status agmal >= 100 dan juga Spirit_Status iraj <= 0 maka hentikan program.
```c
...
    pthread_t tid_a, tid_i, tid_s;
...
    pthread_create(&tid_s, NULL, checker, NULL);
...
    pthread_join(tid_s, NULL);
...
```
Untuk fungsinya:
```c
void *checker(void *argv){
    while(1){
        if(WakeUp_Status >= 100){
            printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
            exit(0);
        }
        if(Spirit_Status <= 0){
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            exit(0);
        }
    }
}
```
## 4 Soal 4
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip  

####Dengan Syarat :  
- Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
- Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
- Ketika Mengekstrak file .zip juga harus secara bersama-sama
- Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
- Wajib Menggunakan Multithreading
- Boleh menggunakan system  

### Jawaban:
> Check : [Full SourceCode](https://github.com/sherlyrosa/SoalShift_Modul3_B02/blob/master/SoalNo4/no4.c)
### Penjelasan :
1. Buat tiga fungsi utama yaitu :
```c
void bikinFile();
void kompresFile();
void ekstrakFile();
```
2. Fungsi `bikinFile()` akan membuat file dari `ps -aux` ke sebuah teks file.
```c
void bikinFile(int x){
    char filename[50];
    char dir[30];
    sprintf(dir, "~/Documents/FolderProses%d", x);
    char cmd1[50];
    sprintf(cmd1,"mkdir -p %s", dir);
    system(cmd1);
    sprintf(filename, "%s/SimpanProses%d.txt", dir, x);
    char cmd2[70];
    sprintf(cmd2, "ps -aux | head -10 > %s", filename);
    system(cmd2);
}
```
3. Fungsi `kompresFile()` akan mengkompres file teks ke zip file.
```c
void kompresFile(int x){
    char dir[30];
    sprintf(dir, "~/Documents/FolderProses%d", x);
    char filename[50];
    sprintf(filename, "%s/SimpanProses%d.txt", dir, x);
    char cmd[120];
    sprintf(cmd, "zip -r %s/KompresProses%d.zip %s",dir, x, filename);
    system(cmd);
    char del[80];
    sprintf(del, "rm %s", filename);
    system(del);
}
```
4. Fungsi `ekstrakFile()` akan mengekstrak kembali filenya.
```c
void ekstrakFile(int x){
    char dir[30];
    sprintf(dir, "~/Documents/FolderProses%d", x);
    char filename[50];
    sprintf(filename, "%s/SimpanProses%d.txt", dir, x);
    char cmd[180];
    sprintf(cmd, "unzip -j %s/KompresProses%d.zip -d %s", dir, x, dir);
    system(cmd);
}
```
5. untuk menjalankannya secara pararel maka buat sebuah fungsi thread yang dinamik. Dalam kasus ini kita dapat memanfaatkan array.
```c
    int num_t = 2, i;
    pthread_t tid[num_t];
    
    for (i=0; i<num_t; i++) {
        pthread_create(&tid[i], NULL, thread, &i);
    }
    for (i=0; i<num_t; i++) {
        pthread_join(tid[i], NULL);
    }
```
6. Lengkapi fungsi `thread()` yang dibuat degan fungsi-fungsi yang telah dibuat sebelumnya.
```c
void *thread(void *argv){
    int *ptr = (int *) argv;
    int id = *ptr + 1;
    
    bikinFile(id);
    sleep(3);
    kompresFile(id);
    printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    sleep(5);
    ekstrakFile(id);
    
    return 0;
}
```
## 5 Soal5
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta.  
a. Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.  
b. Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.  
c. Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).  
d. Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.  
e. Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian.
f. Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
- Pembeli (terintegrasi dengan game)
	- Dapat mengecek stok makanan yang ada di toko.
	- Jika stok ada, pembeli dapat membeli makanan.
- Penjual (terpisah)
	- Bisa mengecek stok makanan yang ada di toko
	- Penjual dapat menambah stok makanan.  
#### Spesifikasi program:
A. Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)  
B. Program terdiri dari 3 scene yaitu standby, battle, dan shop.  
C. Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :  
Standby Mode  
Health : [health status]  
Hunger : [hunger status]  
Hygiene : [hygiene status]  
Food left : [your food stock]  
Bath will be ready in [cooldown]s  
1 Choices  
2 Eat  
3 Bath  
4 Battle  
5 Shop  
6 Exit  
D. Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :  
Battle Mode  
Monster’s Health : [health status]  
Enemy’s Health : [enemy health status]  
Choices  
1 Attack  
2 Run  
E. Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :  
Shop Mode  
Shop food stock : [shop food stock]  
Your food stock : [your food stock]  
Choices  
1 Buy  
2 Back  
F. Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :  
Shop  
Food stock : [shop food stock]  
Choices  
1 Restock  
2 Exit  
G. Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))  

### Jawaban:
> Check : [Full SourceCode](https://github.com/sherlyrosa/SoalShift_Modul3_B02/blob/master/SoalNo5)
### Penjelasan :
1. Pertama buat program utamanya dulu. Kumpulkan variable utamanya.
```c
char petname[77];
int hunger_stat = 200;
int food_strg = 0;
int *food_stock; 
int hygiene_stat = 100; 
int bath_time = 0;
int health_stat = 300;
int health_enemy = 100; 
int pet_stat = 0; 
int NPC_health = 100; 
```
2. Buat fitur utamanya dan jadikan fungsi thread.
```c
void *Hunger(void *argv);
void *Hygiene(void *argv);
void *Bathing(void *argv);
void *Regenerating(void *argv);
```
3. Lalu panggil fungsi sebagai thread.
```c
  pthread_t tid1, tid2, tid3, tid4, tid5, tid6, tid7;
  pthread_create(&tid1, NULL, Hunger, NULL);
  pthread_create(&tid2, NULL, Hygiene, NULL);
  pthread_create(&tid3, NULL, Bathing, NULL);
  pthread_create(&tid4, NULL, Regenerating, NULL);
  pthread_create(&tid5, NULL, menu0, NULL);
  pthread_create(&tid6, NULL, menu1, NULL);
  pthread_create(&tid7, NULL, menu2, NULL);
...
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  pthread_join(tid4, NULL);
  pthread_join(tid5, NULL);
  pthread_join(tid6, NULL);
```
4. beri nama monster peliharan.
```c
  printf("Kasih Nama: ");
  scanf("%s", petname);
```
5. Buat menu utama di dalam `while(1)` di `main()`. dan gunakan `system("clear")` untuk merefresh menu tiap detik `sleep(1)`.
```c
  while (1) {
    if(pet_stat == 0){
      printf("Standby Mode\n");
      printf("Health\t\t: %d\n", health_stat);
      printf("Hunger\t\t: %d\n", hunger_stat);
      printf("Hygiene\t\t: %d\n", hygiene_stat);
      printf("Food left\t: %d\n", food_strg);
      if(bath_time == 0)
        printf("Bath is ready\n");
      else
        printf("Bath will be ready in %ds\n", bath_time);
      printf("Choices\n");
      printf("1. Eat\n");
      printf("2. Bath\n");
      printf("3. Battle\n");
      printf("4. Shop\n");
      printf("5. Exit\n");
    }else if (pet_stat == 1){
      printf("Battle Mode\n");
      printf("Monster's Health: %d\n", health_stat);
      printf("Enemy's Health\t: %d\n", health_enemy);
      printf("Choices\n");
      printf("1. Attack\n");
      printf("2. Run\n");
    }else if(pet_stat == 2){
      printf("Shop Mode\n");
      printf("Shop food stock\t: %d\n", *food_stock);
      printf("Your food stock\t: %d\n", food_strg);
      printf("Choices\n");
      printf("1. Buy\n");
      printf("2. Back\n");
    }
    sleep(1);
    system("clear");
  }
```
6. Lengkapi fungsi-fungsi utama yang telah dibuat:
	- untuk memanipulasi status hungry monster:
	```c
	void *Hunger(void *argv){
	  while (pet_stat != 1) {
	    if(hunger_stat > 200) hunger_stat = 200;

	    sleep(10);
	    hunger_stat-=5;
	    printf("hunger_stat: %d\n", hunger_stat);
	    if(hunger_stat <= 0){
	      printf("Lapar - Game Over\n");
	      exit(0);
	    }
	  }
	}
	```
	- untuk memanipulasi status hygiene monster:
	```c
	void *Hygiene(void *argv){
	  while (pet_stat != 1) {
	    sleep(10);
	    hygiene_stat-=10;

	    if(hygiene_stat <= 0){
	      printf("Kotor - Game Over\n");
	      exit(0);
	    }
	  }
	}
	```
	- untuk memandikan monster:
	```c
	void *Bathing(void *argv){
	  while (1) {
	    if (bath_time != 0) {
	      hygiene_stat+=30;
	      while(bath_time != 0) {
	        sleep(1);
	        bath_time-=1;
	      }
	    }
	  }
	}
	```
	- untuk meregenerasi health monster:
	```c
	void *Regenerating(void *argv) {
	  while (pet_stat != 1) {
	    if(pet_stat == 0 && health_stat < 30){
	      health_stat+=5;
	      sleep(10);
	    }
	  }
	}
	```
6. game ini memiliki tiga mode yaitu standby, battle, dan shop. dan dalam mode tersebut memiliki menu masing-masing, maka buat ketiga fungsi tersebut dalam bentuk thread. namun sebelum itu. karena di Linux tidak ada library untuk menerima input tanpa memencet tombol enter. maka buat fungsi tersebut sendiri:
```c
char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
```
7. Setelah fungsi yang dibutuhkan dibuat. Buat ketiga menu tersebut:
	- menu ketika game standby :
	```c
	void *menu0(void *argv) {
	  char in;
	  while (1) {
	    if(pet_stat == 0){
	      in = getch();
	      if(in == '1'){
	        //Mode makan
	        if(food_strg != 0){
	          food_strg-=1;
	          printf("%s is eating\n", petname);
	          hunger_stat+= 15;
	          sleep(1);
	        }else{
	          printf("food needed. restock please\n");
	          sleep(1);
	        }
	      }else if(in == '2'){
	        //Mode mandi
	        printf("mandi dulu\n");
	        if(bath_time == 0) bath_time = 20;
	      }else if(in == '3'){
	        //Mode tarung
	        printf("3\n");
	        pet_stat = 1;
	      }else if(in == '4'){
	        //Mode pasar
	        pet_stat = 2;
	      }else if(in == '5'){
	        //keluar game
	        printf("exit . . .\n");
	        exit(0);
	      }
	    }
	  }
	}
	```
	- menu ketika game battle:
	```c
	void *menu1(void *argv){
	  //menu tarung
	  char in;
	  while (1) {
	    if(pet_stat == 1){
	      in = getch();
	      if(in == '1'){
	        printf("%s is attacking\n", petname);
	        sleep(1);
	        health_enemy -= 20;
	        printf("Enemy is attacking\n");
	        sleep(1);
	        health_stat -= 20;
	        if(health_enemy == 0){
	          printf("%s wins\n", petname);
	          sleep(2);
	          pet_stat = 0;
	        }
	      }else if(in == '2'){
	        //Mode kabur
	        printf("%s is running\n", petname);
	        health_enemy = 100;
	        pet_stat = 0;
	      }
	    }
	  }
	}
	```
	- menu ketika shop:
	```c
	void *menu2(void *argv){
	  //menu pasar
	  char in;
	  while (1) {
	    if(pet_stat == 2){
	      in = getch();
	      if(in == '1'){
	        //buy
	        if (*food_stock > 0) {
	          *food_stock-=1;
	          food_strg+=1;
	        }
	      }else if(in == '2'){
	        //back
	        pet_stat = 0;
	      }
	    }
	  }
	}
	```
8. Game selesai namun tidak dapat berfungsi sepenuhnya, karena belum shop untuk membeli makanan. maka buat file baru untuk membuat shop. dalam kasus ini kita akan menggunakan shared memory.
```c
int *food_stock;

int main(){
  key_t key = 1234;

  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  food_stock = shmat(shmid, NULL, 0);

  *food_stock = 0;

  while (1) {
    printf("Shop\n");
    printf("Food stock : %d\n", *food_stock);
    printf("Choices\n");
    printf("1. Restock\n");
    printf("2. Exit\n");
    sleep(1);
    system("clear");
  }
}
9. Tambahkan fungsi menu untuk memasukkan command. namun sebelum itu tambahkan fungsi untuk melakukan input tanpa press Enter.
```c
char getch() {
  char buf = 0;
  struct termios old = {0};
  if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0)
    perror ("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror ("tcsetattr ~ICANON");
  return (buf);
}
```
10. Setelah itu buat fungsi sekaligus thread nya.
```c
void *menu(void * argv){
  int in;
  while (1) {
    in = getch();
    if (in == '1') {
      printf("tambah 1\n");
      *food_stock+=1;
    }else if(in == '2'){
      exit(0);
    }
  }
}
```
dan di dalam fungsi `main()`:
```c
...
  pthread_t tid;
  pthread_create(&tid, NULL, menu, NULL);
...
```
11. Setelah program shop bekerja, panggil juga fungsi untuk mengambil data dari memori yang sama oleh program shop. Tambahkan di `main()`:
```c
  key_t key = 1234;
  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  food_stock = shmat(shmid, NULL, 0);
```
12. Game berjalan dengan lancar. enjoy.
# SoalShift_Modul3_B02

## 1. soal1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
##### Contoh
##### ./faktorial 5 3 4
##### 3!=6
##### 4!=24
##### 5!=120
### Jawaban:
> Check : [Full SourceCode]
### Penjelasan :
1. Karena input-an pada file yang diminta ialah dalam bentuk argumen maka menggunakan `argc` dan `argv`.
2. Untuk menghitung `factorial` nya 
```sh
void *factorial(void *args) {
	int fac=1;
	char* temp = (char*)args;
	int argc = temp[0] - '0';
	for(int a=1; a<=argc;a++){
		fac=fac*a;
	}
	printf("Factorial of Given Number is = %d\n",fac);
}
```
3. Menghitung banyaknya argumen yang di inputkan dengan menggunakan `argc`. Jika lebih dari sama dengan 2, maka di print kan inputan argumennya. Mengapa lebih dari sama dengan 2 karena nama file dihitung 1
```sh
if( argc >= 2 )
    {
        printf("The arguments supplied are:\n");
        for(i = 1; i < argc; i++)
        {
            printf("%s\t", argv[i]);
        }
    }
    else
    {
        printf("argument list is empty.\n");
    }
```
4. Karena yang diminta sorting 
```sh
for(k = 1; k < argc; k++) {
	for(j = k + 1; j < argc; j++) {
		int angka1 = argv[k][0] - '0';
		int angka2 = argv[j][0] - '0';
		if(angka2 < angka1){
			char *temp = argv[j];
			argv[j] = argv[k];
			argv[k] = temp;
		}
	}
```

	

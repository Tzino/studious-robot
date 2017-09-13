#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TESTCASES 100000000 // 100 million
#define WRITETOFILE
#define BETTERCHANCES

void emptyintarray(int* arr, int size);
void printintarray(int* arr, int size);
void graphintarray(int* arr, int size);

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    short int att, def, stam;
    double iv;
    FILE* f;
    FILE* f2;

    f = fopen("myfile.dat","w+");
    f2 = fopen("script.sc","w+");
    fprintf(f2,
    "set term png size 1750,900;\
    set output \'output.png\';\
    set title \'Number of Pokemon per IV%% (out of 100mil Pokemon caught)\';\
    set xlabel \'IV percentage\';\
    set ylabel \'Pokemon at that IV%%\';\
    set xtics font \", 8\";\
    set ytics font \", 10\";\
    set grid xtics lw 1 lt 0;\
    set grid ytics lw 1 lt 0;\
    set format x \"%%.1f\"; set xtics 100.0/45.0 rotate by 30 right;\
    set ytics 500000;\
    unset key;\
    set boxwidth 0.75;\
    set style fill solid;\
    plot \'myfile.dat\' using 2:xtic(1) with boxes;");
    int i = 0;

    // array[i] - how many (i/0.45)% IVs have been seen
    int array[46];
    emptyintarray(array, 46);

    while (i < 100000000) {
        #ifndef BETTERCHANCES
        att = rand()%16;
        def = rand()%16;
        stam = rand()%16;
        #endif

        #ifdef BETTERCHANCES
        att = rand()%6+10;
        def = rand()%6+10;
        stam = rand()%6+10;
        #endif // BETTERCHANCES

        iv = (att + def + stam)/0.45;
        array[(int)(iv*0.45)] += 1;
        i++;
    }

    #ifdef WRITETOFILE
    for (i = 0; i < 46; i++) {
        fprintf(f, "%.2f\t%.2f\n", i/0.45, (float)array[i]);
    }
    #endif // WRITETOFILE

    // printf("Testcases: %d\n", TESTCASES);
    // printf("%%IV\t- Number of results with that IV%%\n\n");

    // printintarray(array, 46);
    // graphintarray(array, 46);
    fclose(f);
    fclose(f2);

    char *command = "/usr/local/bin/gnuplot";
    char *arguments[] = {"gnuplot", "script.sc", NULL};
    char* command2 = "/bin/rm";
    char* arguments2[] = {"rm", "./script.sc", "./myfile.dat", NULL};
    if(!fork()){
        sleep(1);
        execvp(command2, arguments2);
    }
    else{
        execvp(command, arguments);
    }

    return 0;
}

///////////////////////// END OF MAIN /////////////////////////


void emptyintarray(int* arr, int size){
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = 0;
    }
}

void printintarray(int* arr, int size){
    int i;
    for (i = 0; i < size; i++) {
        printf("%.2f%%\t- %d\n", i/0.45, arr[i]);
    }
}

void graphintarray(int* arr, int size){
    int i;
    int j;
    int c = TESTCASES/arr[23];
    for (i = 0; i < size; i++) {
        printf("%.2f%%\t- ", i/0.45);
        int count = arr[i]/(3000*c);
        for (j = 0; j < count; j++) {
            putchar('*');
        }
        printf(" (%d)        chances: 1 out of %d\n", arr[i], TESTCASES/arr[i]);
    }
}
/*
array[0] - 0.00
array[1] - 2.22
array[2] - 4.44
array[3] - 6.67
array[4] - 8.89
array[5] - 11.11
array[6] - 13.33
array[7] - 15.56
array[8] - 17.78
array[9] - 20.00
array[10] - 22.22
array[11] - 24.44
array[12] - 26.67
array[13] - 28.89
array[14] - 31.11
array[15] - 33.33
array[16] - 35.56
array[17] - 37.78
array[18] - 40.00
array[19] - 42.22
array[20] - 44.44
array[21] - 46.67
array[22] - 48.89
array[23] - 51.11
array[24] - 53.33
array[25] - 55.56
array[26] - 57.78
array[27] - 60.00
array[28] - 62.22
array[29] - 64.44
array[30] - 66.67
array[31] - 68.89
array[32] - 71.11
array[33] - 73.33
array[34] - 75.56
array[35] - 77.78
array[36] - 80.00
array[37] - 82.22
array[38] - 84.44
array[39] - 86.67
array[40] - 88.89
array[41] - 91.11
array[42] - 93.33
array[43] - 95.56
array[44] - 97.78
array[45] - 100.00
*/

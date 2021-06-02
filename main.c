#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "pQueueLib.c"

#define landingTime 3
#define disembarkTime 2
#define maxAirTime 6
#define possibility 10//0-100;

#define msg "Justas Stonkus 4 grupė, 2 pogrupis, 3 užduotis 4 variantas\n\n\
4. Aerouostas (ADT: prioritetinė eilė, ilgas sveikas skaičius). Aerouostas turi 1 pakilimo/nusileidimo\n\
taką, besileidžiantys lėktuvai turi prioritetą, t. y. jei takas laisvas, tai pirmiausia priimamas\n\
besileidžiantis lėktuvas, bet jei kažkuris lėktuvas pradėjo pakilimą, tai visi kiti, tame tarpe ir norintys\n\
nusileisti, lėktuvai turi laukti; lėktuvas, norintis nusileisti, negali laukti labai ilgai, nes jam baigsis\n\
degalai. Tikslas: patyrinėti prie kokio apkrovimo aerouostui pakanka vieno tako. Pradiniai duomenys:\n\
nusileidimo laikas (trukmė), pakilimo laikas (trukmė), laikas, kurį norintis leistis lėktuvas, dar gali\n\
išbūti ore, lėktuvo panorusio kilti/leistis einamuoju momentu tikimybė (galima realizacija:\n\
generuojamas atsitiktinis skaičius ir tikrinama, ar jis tenkina tam tikrą sąlygą), besileidžiantys ir\n\
kylantys lėktuvai pasirodo su vienoda tikimybe. Rezultatai: nukritęs lėktuvas (modeliavimas iš karto\n\
baigiamas), maksimalus ir vidutinis norinčio nusileisti lėktuvo laukimo laikas, maksimalus ir vidutinis\n\
norinčio pakilti lėktuvo laukimo laikas.\n\n\
--------------------------------------------------\n\n\
I DALIS - DUOMENYS\n\n"


int main()
{
    FILE *rp;
    rp = fopen("rezultatai3.txt", "w");
    fprintf(rp, msg);
    fprintf(rp, "1) Nusileidimo laikas: %d min.\n2) Pakilimo laikas: %d min.\n3) Laikas, kuri lektuvas gali buti ore: %d min.\n4) Tikimybe, kad atsiras lektuvas norintis pakilti ar nusileisti: %d%%.\n\n", landingTime, disembarkTime, maxAirTime, possibility);
    fprintf(rp, "II DALIS - VYKDYMAS\n");
    struct Node *start;
    initializeList(&start);
    int biggestWaitTime = 0;
    double averageWaitTime = 0;
    int biggestWaitTimeD = 0;
    double averageWaitTimeD = 0;
    int landed = 0;
    int disembarked = 0;

    int random, landingPlanes = 0, disembarkingPlanes = 0, inAction = 0, timeUntilDone = 0, moment = 0;
    int waitingTimes[9999] = {0};
    int waitingTimesD[9999] = {0};
    bool crashed = false;

    srand(time(NULL));

    do
	{
        random = rand()%100;
        if(random < possibility) //land
            addElement(&start, ++landingPlanes, 1);
        random = rand()%100;
        if(random < possibility) //disembark
            addElement(&start, --disembarkingPlanes, 2);

        fprintf(rp, "\nT = %d\n\n", moment++);
        int wantLand = landingPlanes - landed;
        if (inAction > 0)
            wantLand--;
        if(wantLand)
        {
            fprintf(rp, "\tLektuvai norintys leistis: ");
            printQueue(start, true, rp);
        }
        else
            fprintf(rp, "\tNera lektuvu norinciu leistis.");

        int wantDisembark = abs(disembarkingPlanes) - disembarked;
        if (inAction < 0)
            wantDisembark--;

        if(wantDisembark)
        {
            fprintf(rp, "\n\tLektuvai norintys kilti:  ");
            printQueue(start, false, rp);
        }
        else
            fprintf(rp, "\n\tNera lektuvu norinciu kilti.");

        if(!checkEmpty(&start) && readFirst(&start) > 0)
        {
            for(int i = readFirst(&start); i <= landingPlanes; i++)
            {
                waitingTimes[i]++;
                if(waitingTimes[i] >= maxAirTime)
                {
                    fprintf(rp, "\n\tL%d Lektuvas suduzo.\n", i);
                    crashed = true;
                }
            }
        }
        if(!checkEmpty(&start) && giveFirstOfGivenPrio(start, 2) != 0)
        {
            for(int i = abs(giveFirstOfGivenPrio(start, 2)); i <= abs(disembarkingPlanes); i++)
                waitingTimesD[i]++;
        }

        if(crashed)
            break;
        fprintf(rp, "\n");

        if(!checkEmpty(&start) && !inAction)
        {
            inAction = takeFirst(&start);
            if(waitingTimes[inAction] > biggestWaitTime)
            {
                if(inAction > 0)
                {
                    biggestWaitTime = waitingTimes[inAction];
                }
            }
            if(waitingTimesD[abs(inAction)] > biggestWaitTimeD)
            {
                if(inAction < 0)
                {
                    //printf("%d\n", waitingTimesD[abs(inAction)]);
                    biggestWaitTimeD = waitingTimesD[abs(inAction)];
                }
            }
            if(inAction > 0)
            {
                averageWaitTime += waitingTimes[inAction];
            }
            if(inAction < 0)
            {
                averageWaitTimeD += waitingTimesD[abs(inAction)];
            }
            //printf("%.1lf\n", averageWaitTimeD);
            timeUntilDone = (inAction > 0) ? landingTime : disembarkTime;
            if(inAction > 0)
                fprintf(rp, "\tLektuvas L%d pradeda leistis.\n", inAction);
            if(inAction < 0)
                fprintf(rp, "\tLektuvas K%d pradeda kilti.\n", abs(inAction));
            timeUntilDone--;
        }
        else if(inAction)
        {
            if(timeUntilDone <= 1)
            {
                if(inAction > 0)
                {
                    fprintf(rp, "\tLektuvas L%d nusileido.\n", inAction);
                    landed++;
                }
                if(inAction < 0)
                {
                    fprintf(rp, "\tLektuvas K%d pakilo.\n", abs(inAction));
                    disembarked++;
                }
                inAction = 0;
            }
            if(inAction > 0 && timeUntilDone > 1)
                fprintf(rp, "\tLektuvas L%d leidziasi, kol nusileis liko laiko: %d.\n", inAction, --timeUntilDone);
            else if (inAction < 0 && timeUntilDone > 1)
                fprintf(rp, "\tLektuvas K%d kyla, kol pakils liko laiko: %d.\n", abs(inAction), --timeUntilDone);;
        }

        if(timeUntilDone == 0)
        {
            if(inAction > 0)
            {
                fprintf(rp, "\tLektuvas L%d nusileido.\n", inAction);
                landed++;
            }
            if(inAction < 0)
            {
                fprintf(rp, "\tLektuvas K%d pakilo.\n", abs(inAction));
                disembarked++;
            }
            inAction = 0;
        }

    }
	while(1);
    fprintf(rp, "\nIII - REZULTATAI\n\n1) %d lektuvai norejo nusileisti, o nusileido: %d lektuvai\n", landingPlanes, landed);
    fprintf(rp, "2) %d lektuvai norejo pakilti, o pakilo: %d lektuvai\n", abs(disembarkingPlanes), disembarked);
    fprintf(rp, "3) Didziausias norincio nusileisti lektuvo laukimo laikas: %d\n", biggestWaitTime);
    fprintf(rp, "4) Vidutinis norincio nusileisti lektuvo laukimo laikas: %.1lf\n", averageWaitTime / (double)landed);
    if(disembarked)
    {
        fprintf(rp, "5) Didziausias norincio pakilti lektuvo laukimo laikas: %d\n", biggestWaitTimeD);
        fprintf(rp, "6) Vidutinis norincio pakilti lektuvo laukimo laikas: %.1lf\n", averageWaitTimeD / (double)disembarked);
    }
    else
    {
        fprintf(rp, "5) Didziausias norincio pakilti lektuvo laukimo laikas: nepakilo nei vienas lektuvas\n");
        fprintf(rp, "6) Vidutinis norincio pakilti lektuvo laukimo laikas: nepakilo nei vienas lektuvas\n");
    }
	fclose(rp);
    return 0;
}

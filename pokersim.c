#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIMS 20000
#define PLAYERS 3

int rank(int c){ return c % 13; }
int suit(int c){ return c / 13; }

void shuffle(int deck[])
{
    for(int i=0;i<52;i++)
    {
        int r = rand()%52;
        int t = deck[i];
        deck[i] = deck[r];
        deck[r] = t;
    }
}

int contains(int arr[], int n, int v)
{
    for(int i=0;i<n;i++)
        if(arr[i]==v) return 1;
    return 0;
}

void countRanks(int cards[], int rc[])
{
    for(int i=0;i<13;i++) rc[i]=0;

    for(int i=0;i<7;i++)
        rc[rank(cards[i])]++;
}

int flush(int cards[])
{
    int s[4]={0};

    for(int i=0;i<7;i++)
        s[suit(cards[i])]++;

    for(int i=0;i<4;i++)
        if(s[i]>=5) return 1;

    return 0;
}

int straight(int cards[])
{
    int used[13]={0};

    for(int i=0;i<7;i++)
        used[rank(cards[i])] = 1;

    for(int i=0;i<=8;i++)
    {
        int ok=1;

        for(int j=0;j<5;j++)
            if(!used[i+j]) ok=0;

        if(ok) return 1;
    }

    return 0;
}

int evaluate(int cards[])
{
    int rc[13];
    countRanks(cards,rc);

    int pair=0,three=0,four=0;

    for(int i=0;i<13;i++)
    {
        if(rc[i]==4) four=1;
        if(rc[i]==3) three=1;
        if(rc[i]==2) pair++;
    }

    int f = flush(cards);
    int s = straight(cards);

    if(f && s) return 8;
    if(four) return 7;
    if(three && pair>=1) return 6;
    if(f) return 5;
    if(s) return 4;
    if(three) return 3;
    if(pair>=2) return 2;
    if(pair==1) return 1;

    return 0;
}

int main()
{
    srand(time(NULL));

    int my[2];
    int board[5];

    printf("Enter your two cards (0-51):\n");
    scanf("%d %d",&my[0],&my[1]);

    printf("Enter community cards (-1 unknown):\n");

    for(int i=0;i<5;i++)
        scanf("%d",&board[i]);

    int wins=0;

    for(int sim=0; sim<SIMS; sim++)
    {
        int deck[52];
        for(int i=0;i<52;i++) deck[i]=i;

        shuffle(deck);

        int used[9];
        int uc=0;

        used[uc++]=my[0];
        used[uc++]=my[1];

        int myhand[7];

        myhand[0]=my[0];
        myhand[1]=my[1];

        int di=0;

        for(int i=0;i<5;i++)
        {
            if(board[i]!=-1)
            {
                myhand[i+2]=board[i];
                used[uc++]=board[i];
            }
        }

        for(int i=0;i<5;i++)
        {
            if(board[i]==-1)
            {
                while(contains(used,uc,deck[di])) di++;

                myhand[i+2]=deck[di];
                used[uc++]=deck[di];
                di++;
            }
        }

        int myscore = evaluate(myhand);

        int win=1;

        for(int p=0;p<PLAYERS-1;p++)
        {
            int opp[7];

            while(contains(used,uc,deck[di])) di++;
            opp[0]=deck[di];
            used[uc++]=deck[di];
            di++;

            while(contains(used,uc,deck[di])) di++;
            opp[1]=deck[di];
            used[uc++]=deck[di];
            di++;

            for(int i=0;i<5;i++)
                opp[i+2]=myhand[i+2];

            int oppscore = evaluate(opp);

            if(oppscore > myscore)
                win=0;
        }

        if(win) wins++;
    }

    double equity = (double)wins / SIMS;

    printf("\nEstimated equity: %.3f\n",equity);

    return 0;
}
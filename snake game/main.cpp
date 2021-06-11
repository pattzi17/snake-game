#include <iostream>
#include <conio.h>
#include<cstdlib>
#include<time.h>
#include <fstream>

using namespace std;
bool gameOver;
int currArHS=0,currClHS=0;

void highscore()
{
	ifstream file;
	file.open("ArcadeHS.dat");
	file>>currArHS;
	file.close();
	file.open("ClassicHS.dat");
	file>>currClHS;
	file.close();
}

class sgame
{
protected:
	int x, y, fruitX, fruitY, score,score1,width,height;
	int tailX[100], tailY[100],nTail;
	enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
	eDirecton dir;
public:
    int getHS()
        {
            return score;
        }
    sgame()
    {
        width=16;
        height=16;
        nTail=0;
    }
	void Setup()
	{
        srand(time(NULL));
    	gameOver = false;
    	dir = STOP;
    	x = width / 2;
    	y = height / 2;
    	fruitX = rand() % width;
    	fruitY = rand() % height;
    	score = 0;
    	score1=0;
	}
virtual	void Draw()
{
    system("cls");
    for (int i = 0; i < width+2; i++)
      cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;

}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logicclassic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
                x--;
                break;
    case RIGHT:
                x++;
                break;
    case UP:
                y--;
                break;
    case DOWN:
                y++;
                break;
    default:
                break;
    }
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
};
class sgamearcade:  public sgame
{
	ofstream file1;
public:
        int getHS1()
        {
            return score1;
        }
       void Logicarcade()
       {
          int prevX = tailX[0];
          int prevY = tailY[0];
          int prev2X, prev2Y;
          tailX[0] = x;
          tailY[0] = y;
          for (int i = 1; i < nTail; i++)
          {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
          }
    switch (dir)
    {
    case LEFT:
                x--;
                break;
    case RIGHT:
                x++;
                break;
    case UP:
                y--;
                break;
    case DOWN:
                y++;
                break;
    default:
                break;
    }
    if (x > width || x < 0 || y > height || y < 0)
      gameOver = true;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score1 += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
  }
	void Draw()
  {
      system("cls"); //system("clear");
      for (int i = 0; i < width+2; i++)
      cout << "#";
      cout << endl;

      for (int i = 0; i < height; i++)
      {
          for (int j = 0; j < width; j++)
          {
              if (j == 0)
                  cout << "#";
                  if (i == y && j == x)
                    cout << "O";
                  else if (i == fruitY && j == fruitX)
                      cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score1 << endl;
}
};

int main(int argc, char** argv)
{
    int y,score,score1;
    ofstream file1;
    cout<<"*****SNAKE GAME****"<<endl;
    cout<<"enter your choice"<<endl;
    highscore();
    cout<<"1.Arcade mode\n2.Classic mode\n3.High Scores"<<endl;
    cin>>y;

    if(y==1)
    {
      	sgamearcade s1;
        s1.Setup();
        while (!gameOver)
        {
            s1.Draw();
            s1.Input();
            s1.Logicarcade();
            _sleep(100);
        }
        		if (gameOver)
		{
            score1=s1.getHS1();
			if(score1>currArHS)
			{
					file1.open("ArcadeHS.dat");
					file1<<score1;
					file1.close();
					cout<<"High Score has been updated"<<endl;
			}
		}
    }
    else if (y==2)
    {
      	sgame s;
        s.Setup();
        while (!gameOver)
        {
            s.Draw();
            s.Input();
            s.Logicclassic();
            _sleep(100);
        }
        if (gameOver)
		{
		    score=s.getHS();
			if(score>currClHS)
			{
					file1.open("ClassicHS.dat");
					file1<<score;
					file1.close();
					cout<<"High Score has been updated"<<endl;
			}
		}
    }
		else
		{
				system("cls");
				cout<<"High Scores\n";
				cout<<"Arcade  - "<<currArHS<<endl;
				cout<<"Classic - "<<currClHS<<endl;
		}
	return 0;
}


/*

Крестики-нолики, компьютер играет за крестики и ходит первым.

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

#define WIN 1000
#define	DRAW 0
#define LOSS -1000

#define AI_MARKER 'O'
#define PLAYER_MARKER 'X'
#define EMPTY_SPACE '-'

#define START_DEPTH 0

#define NS (cout << "\n")
#define Start (cout << "┌" << "───" << "┬" << "───" << "┬" << "───" << "┐")
#define End (cout << "└" << "───" << "┴" << "───" << "┴" << "───"<< "┘")
#define Separetor (cout << "├" << "───" << "┼" << "───" << "┼" << "───"<< "┤")

struct Move {
  int cell;
  int score;
};


 

  void printBoard(char board[])
 {
  
  
  std::cout << endl;
  Start;
  std::cout << endl;

  for (int i=0; i<3; i++)
  {
  if (i>0) 
  {Separetor;
  std::cout << endl;
  }
  cout << "│" << " " <<  board[3*i]<< " " << "│" << " " << board[1+3*i] << " " << "│" << " " <<board[2+3*i] << " " << "│";
  std::cout << endl;
  

  }

  End;
  std::cout << endl;
}
    

  bool winning(char board[],char player)
  {
    if (
      (board[0] == player && board[1] == player && board[2] == player) ||
      (board[3] == player && board[4] == player && board[5] == player) ||
      (board[6] == player && board[7] == player && board[8] == player) ||
      (board[0] == player && board[4] == player && board[8] == player) ||
      (board[2] == player && board[4] == player && board[6] == player) ||
      (board[0] == player && board[3] == player && board[6] == player) ||
      (board[1] == player && board[4] == player && board[7] == player) ||
      (board[2] == player && board[5] == player && board[8] == player)
    ) {
      return true;
    } else {
      return false;
    }
  }

std::vector<int> get_legal_moves(char board[9])
{
	std::vector<int> legal_moves;
	for (int i = 0; i < 9; i++)
	{
			
			if (board[i] != AI_MARKER && board[i] != PLAYER_MARKER)
			{
				legal_moves.push_back(i);
			}
		
	}

	return legal_moves;
}

bool board_is_full(char board[])
{
  return (0 == get_legal_moves(board).size());
}


bool game_is_done(char _board[])
{
  if (winning(_board, PLAYER_MARKER))
  {
    cout << "Поздравляю вы выиграли \n";
    return true;

  } else if (winning(_board, AI_MARKER))
  {
     cout << "Вы проиграли \n";
   return true;
  } else if (board_is_full(_board))
	{
    cout << "Ничья \n";
		return true;
	}
  	return false;
}

bool legalMove(char _board[], int move)
{
    vector<int> free_cells = get_legal_moves(_board);
    auto it =  find (free_cells.begin(), free_cells.end(), move);
    return it!=free_cells.end();
    
}

void humanStep(char _board[])
{
  cout << "\nВведите номер ячейки для вашего хода: ";
   int userStep;
  cin >> userStep;
  std::cin.clear();
  std::cin.ignore();
  if ((userStep>=1)||(userStep<=9))
  {
       if (legalMove(_board,userStep-1))
    {
      _board[userStep-1] = PLAYER_MARKER;
      return;
    }
    else
    {
      cout <<"Данная клетка уже занята";
       humanStep(_board);
    }
  }
    cout <<"Ошибка ввода";
   humanStep(_board);

}

int minimax(char newBoard[], char player)
{
  
  //Получаем список свободных ячеек
  auto availCells = get_legal_moves(newBoard);

  //Проверяем терминальные состояния
  if (winning(newBoard, PLAYER_MARKER)){
     return -10;
  }
	else if (winning(newBoard, AI_MARKER)){
    return 10;
	}
  else if (availCells.size() == 0){
  	return 0;
  }

 vector<Move> moves;
 
  for (int i = 0; i < availCells.size(); i++){
   
    Move move;
    move.cell = availCells[i];
    newBoard[availCells[i]] = player;

     if (player == AI_MARKER){
      move.score = minimax(newBoard, AI_MARKER);
    }
    else{ 
      move.score = minimax(newBoard, PLAYER_MARKER);
    }

     newBoard[availCells[i]] = char('1')+move.cell;
      moves.push_back(move);
  }
     
     int bestMove;
  if(player == AI_MARKER){
    int bestScore = -10000;
    for(int i = 0; i < moves.size(); i++){
       // cout << "Moves:"  <<endl;
       // cout <<"Cell: " << moves[i].cell<<endl;
      //  cout <<"Score: " << moves[i].score<<endl;
      if(moves[i].score > bestScore){
       
        bestScore = moves[i].score;
        bestMove = i;
      }
    }
  }else{

// else loop over the moves and choose the move with the lowest score
    int bestScore = 10000;
    for(int i = 0; i <  moves.size(); i++){
       //cout << "Moves:"  <<endl;
       // cout <<"Cell: " << moves[i].cell<<endl;;
       // cout <<"Score: " << moves[i].score<<endl;;
      if(moves[i].score < bestScore){
        bestScore = moves[i].score;
        bestMove = i;
      }
    }
  }
  
  
    cout <<moves[bestMove].cell;
   return moves[bestMove].cell;

    

}

void AiStep(char _board[])
{
  if (get_legal_moves(_board).size() == 0)
  {
      return;
  }
   int r = minimax(_board, AI_MARKER);
    _board[r-1] = AI_MARKER;
  
}

int main() {
  
char board[]  {'1','2','3','4','5','6','7','8','9'};
  
  system("clear");
  AiStep(board);
  printBoard(board);

  while (!game_is_done(board))
	{
    for (char c : board)
    {
        cout<<int(c)<< " ";
    };
    cout<<endl;
   
           
    
    
    
    humanStep(board);
    AiStep(board);
    
    system("clear");
    printBoard(board);

  
    
  }
  }
  
  
   

  


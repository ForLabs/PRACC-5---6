#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;
 
class Matrix{
    int **mtx;   // хранится матрица
    int size;    // хранится размер матрицы
public:
   
    Matrix(char type ,int size);
    Matrix(){};
 
 /*  int  determ( int size)
{
        int i,j;
        double det=0;
        
        if(size==1)
        {
                det=mtx[0][0];
        }
        else if(size==2)
        {
                det=mtx[0][0]mtx[1][1]-mtx[0][1]mtx[1][0];
        }
        else
        {
                mtx=new int*[size-1];
                for(i=0;i<size;++i)
                {
                        for(j=0;j<size-1;++j)
                        {
                                if(j<i) 
                                        matr[j]=mtx[j];
                                else
                                        matr[j]=mtx[j+1];
                        }
                        det+=pow((double)-1, (i+j))*determ( size-1)*mtx[i][size-1];
                }
                delete[] matr;
        }
        return det;
   }*/
  int Matrix::GetOpr(){
	if (size == 1) return mtx[0][0];
	if (size == 2) 
		return (mtx[0][0]*mtx[1][1] - mtx[1][0]*mtx[0][1]);
	float y;
	int x;
	int sum12=0,sum22=0;
	for (int i=0;i<size;i++){
		int sum11=1;
		x=2*size-1-i;
		int sum21=1;
	for (int j=0;j<size;j++){
		sum21*=mtx[j][x%size];
		x--;
		sum11*=mtx[j][(j+1)%size];
	}
	sum22+=sum21;
	sum12+=sum11;
	}
	y=sum12-sum22;
	return y;
	}
	Matrix operator+ (const Matrix & rhs){
		Matrix result('0',size);
		for(int i=0; i<size;i++){
        for(int j=0;j<size;j++){
            result.mtx[i][j] = mtx[i][j] + rhs.mtx[i][j];
		}
		}
		return result;
	}
	Matrix operator- (const Matrix & rhs){
		Matrix result('0',size);
		for(int i=0; i<size;i++){
        for(int j=0;j<size;j++){
            result.mtx[i][j] = mtx[i][j] - rhs.mtx[i][j];
		}
		}
		return result;
	}
          
	Matrix operator*(const Matrix & rhs){
	Matrix result('0',size);
		  for(int i=0;i<size;i++){
          for(int j=0;j<size;j++)  {
				result.mtx[i][j] = 0;
				for(int k=0; k<size;k++){   
		result.mtx[i][j]  += mtx[i][k] * rhs.mtx[k][j];    

				}
			}
		}
    return result;
	}
	Matrix operator/( Matrix & rhs){
	Matrix result('0',size);
	Matrix _res('0',size-1);
	if (rhs.GetOpr() == 0){
		cout<< "Деление невозможно"<<endl;
		return rhs;
	}
	else {
	int c,d;
	for (c=0;c<size;c++)
		for (d=0;d<size;d++){
			for (int i=0;i<size;i++)
				for (int j=0;j<size;j++){
					if ((i!=c)&&(j!=d)){
						if ((i>c)&&(j>d))
							_res.mtx[i-1][j-1]=rhs.mtx[i][j];
						if ((i>c)&&(j<d))
							_res.mtx[i-1][j]=rhs.mtx[i][j];
						if ((i<c)&&(j>d))
							_res.mtx[i][j-1]=rhs.mtx[i][j];
						if ((i<c)&&(j<d))
							_res.mtx[i][j]=rhs.mtx[i][j];
					}
				}
				result.mtx[d][c]=_res.GetOpr()*pow(-1.,(c+d))*(1./(rhs.GetOpr()));
		}
			Matrix _result('0',size);
			_result = (*this)*result;
			return _result;
	}
	}
	
    int GetSize(){ return size; }
    void SetVal(int i, int j, int val) {
        mtx[i][j] = val;
    }
    int GetVal(int i, int j){ return mtx[i][j]; }
 
    //проверяет является ли индекс допустимым
    bool isValidIndex(int x){ 
        if(x < 0 || x > size - 1) return false;
        return true;
    }
};
 

Matrix::Matrix(char type,int s){
    int i,j;
 
    if(s < 1) size = 1;
    else if(s > 10) size = 10;
    else size = s;
 
    mtx = new int *[size];
    for(i=0; i<size; i++)
        mtx[i] = new int[size];
 
    switch(type){
   
   
    case'r':
        srand(time(NULL));
        for(i=0; i<size; i++)
            for(j=0; j<size; j++)
                mtx[i][j] = rand() % 10 ;
        break;
    case'm':
        cout << "\n";
        for(i=0; i<size; i++)
            for(j=0; j<size; j++){
                do{
                    cout << "Введите элемента mtx[" << i << "][" << j << "]: "; 
                    fflush(stdin);
                }while(scanf( "%i",&mtx[i][j])!=1 || cin.rdbuf()->in_avail()!=1);
               mtx[i][j]%=100;
            }
        break;
    }
}
 

void ShowMatrix(Matrix &ob){
    int i,j;
    
    for(i=0; i<ob.GetSize(); i++){
        for(j=0; j<ob.GetSize(); j++){
            cout.width(6);
            cout << ob.GetVal(i, j) << ' ';
        }
        cout << "\n";   
    }
    cout << "\n";
}
 

void FillMatrix(char &ch){
    cout 
         << "r-Случайная матриц.\n"
         << "m-Ручной ввод элементов.\n";
    do{
        cout << "Выберите один из пунктов: ";
        fflush(stdin);
    }while(scanf("%c",&ch)!=1 || cin.rdbuf()->in_avail()!=1 ||
        ch!='r' && ch!='m');
}
 
void main(){
    char ch_fill1;        
    char ch_fill2;        
    char ch_operations;   //выбор операции
    int size;
 
    setlocale(LC_ALL,"Rus");
    
    for(;;){
        system("cls");
        
        cout   << "1.Сумма матриц.\n"
               << "2.Разность матриц.\n"
               << "3.Умножение матриц.\n"
			   << "4.Деление матриц. \n";
               
        do{
            cout << "Выберите один из пунктов (0 - для выхода): ";
            fflush(stdin);
        }while(scanf("%c", &ch_operations)!=1 || cin.rdbuf()->in_avail()!=1 ||
            ch_operations < '0' || ch_operations > '4');    
        
        if(ch_operations == '0') break; //если надо, то выходим
 
        //узнаем размер матриц
        do{
            cout << "\nВведите размер матриц: ";
            fflush(stdin);
        }while(scanf("%i", &size)!=1 || cin.rdbuf()->in_avail()!=1);
 
        Matrix result;  //матрица для хранения результата операций
		int res;
        if(ch_operations > '0' && ch_operations < '5'){
            cout << "\nМатрица 1:\n";
            FillMatrix(ch_fill1);       //узнаем способ заполнения 1 матрицы
            Matrix ob(ch_fill1,size);   //создали 1 матрицу
			
            cout << "\n";
			ShowMatrix(ob);
            cout << "\n";
 
 
           
    
            cout << "\nМатрица 2:\n";
            FillMatrix(ch_fill2);         //заполнили матрицу 2
            Matrix ob2(ch_fill2,size);	  //создали 2 матрицу
			
            cout << "\n";
			ShowMatrix(ob2);
            cout << "\n";
 


            //выполнение операции 1,2 или 3
            switch(ch_operations){
            case'1':
                result = ob+ob2     ;  
                cout << "Результат сложения:\n";
                ShowMatrix(result); 
				res=result.GetOpr();
				cout<< "Детерменант полученной матрицы:"<<res<<endl;
                break;
            case'2':
                result = ob-ob2;          
                cout << "Результат вычитания :\n";
                ShowMatrix(result);
				res=result.GetOpr();
				cout<< "Детерменант полученной матрицы:"<<res<<endl;
                break;
            case'3':
                result = ob*ob2 ;
                cout << "Результат умножения\n";
                ShowMatrix(result);
				res=result.GetOpr();
				cout<< "Детерменант полученной матрицы:"<<res<<endl;
                break;
			case'4':
				result = ob2/ob;
				cout<< "Результат деления\n";
				if (result.GetOpr() == 0) cout<<"Деление не возможно "; else ShowMatrix(result);
			
				
            }
        }
		getch();
	}
}

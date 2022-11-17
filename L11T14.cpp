#include <iostream>//библиотека ввода/вывода
#include <math.h>//библиотека для работы с мат. ф.
#include <cstdlib>//библиотека для работы со случайными числами
#include <string>//библиотека для работы со строками
#include <fstream>//библиотека для работы с файлами
#include <iomanip>//библиотека для отступов
using namespace std;//пространство имен std

class MComp{//класс комплексных чисел
public:
    int Re, Im;//вещественная и мнимая части
    MComp operator=(MComp x){//перегрузка опператора присваивания
        Re=x.Re;
        Im=x.Im;
        return *this;
    }
    void ShowComp(){//вывод числа на экран с выравниванием по центру
        if(Re<0){
            if(Re>-1000 & Re<-99)cout << Re;
            else if(Re>-100 & Re<-9 )cout <<" "<<Re;
            else if(Re>-10 & Re<0 )cout <<"  "<<Re;
        }
        else if(Re>=0){
            if(Re<1000 & Re>99)cout <<" "<< Re;
            else if(Re<100 & Re>9 )cout <<"  "<<Re;
            else if(Re<10 & Re>=0 )cout <<"   "<<Re;
        }

        if(Im<0){
            cout <<"-i";
            if(Im>-1000 & Im<-99)cout << (-1)*Im;
            else if(Im>-100 & Im<-9 )cout <<(-1)*Im<<" ";
            else if(Im>-10 & Im<0 )cout <<(-1)*Im<<"  ";
        }
        else if(Im>=0){
            cout<<"+i";
            if(Im<1000 & Im>99)cout <<Im;
            else if(Im<100 & Im>9 )cout <<Im <<" ";
            else if(Im<10 & Im>=0 )cout <<Im << "  ";
        }
    }
    MComp GetRandComp(){//генерация числа
        Re=rand()%20 - 10;
        Im=rand()%20 - 10;
        return *this;
    }
};

class Matrix: public MComp{//класс матриц с наследованием клааса комплексных чисел
public:
    int size;//размер матрицы
    MComp z;//оъект комплексных чисел
    MComp **dinamic_array;//динамический масив
    Matrix (int size){//инициализация массива
        this->size=size;
        dinamic_array = new MComp* [size];
        for (int i = 0; i < size; i++) {
            dinamic_array[i] = new MComp [size];  
        }
        z.Re=0;
        z.Im=0;  
        for(int i = 0; i<size;i++){//заполнение массива
            for(int j=0; j<size; j++){
                dinamic_array[i][j]=z;
            }
        }
    }
    
    MComp* &operator[](int i){//перегрузка умножения
        return dinamic_array[i];
    };

    void SetMatrix(){//заполнение матрицы
        for(int i = 0; i<size;i++){
            for(int j=0; j<size; j++){
                dinamic_array[i][j]=z.GetRandComp();
            }
        }
    }
    void GetMatrix(){//вывод матрицы
        for(int i = 0; i<size;i++){
            for(int j=0; j<size; j++){
                z=dinamic_array[i][j];
                z.ShowComp();
                cout.width(3);
                cout << " ";
            }
            cout << endl;
        }
    }
    
}; 

MComp operator+(MComp x, MComp y){//Операторная функция для сложения двух объектов:
    MComp z;
    z.Re=x.Re+y.Re;
    z.Im=x.Im+y.Im;
    return z;}

MComp operator-(MComp x, MComp y){//Операторная функция для вычитания двух комплексных чисел:
    MComp z;
    z.Re=x.Re-y.Re;
    z.Im=x.Im-y.Im;
    return z;}

MComp operator*(MComp x, MComp y){//Операторная функция для умножения двух комплексных чисел:
    MComp z;
    z.Re = x.Re * y.Re;
    z.Im = x.Im * y.Im;
    return z;}    

Matrix operator*(Matrix x, Matrix y){//Операторная функция для умножения двух матриц:
    Matrix z(x.size);
    for(int i =0;i<z.size;i++){
        for(int j=0;j<z.size;j++){
            for(int k=0; k<z.size;k++){
                z[i][j]=z[i][j]+x[i][k]*y[k][j];
            }
        }
    }
    return z;
}

Matrix DataFromFile(string file_name);//ф. для данных их файла
void WriteToFile(Matrix x, Matrix y, Matrix z, bool enter);//ф. для записи в файл
void WriteMatrix(Matrix x, int step);//ф. для записи матриц в файл
void ReadingFile();//ф. для чтеия файла
void DeleteLog();//ф. удаления данных

int main()
{
    setlocale(LC_ALL, "RUSSIAN");//добавления русского языка
    srand(time(NULL));//ф. для случайных чисел
    string choice=" ";//переменная выбора
    int size;//размер
    cout << "Программа для расчета пероизведения квадратных матриц комплексных чисел." << endl;
    cout << "Выполнил Осетров А.А. гр.ОБ-10.03.01-11" << endl << endl;
    for(;;){//зацикливание
        cout << "Меню:" << endl << "| 1 | Задать размер квадратных матриц случайных комплексных чисел генерируемых в пределе от -10 до 10 по вещественной и мнимой частям" << endl <<"| 2 | Получить матрицы из файлов matrix_first.txt и matrix_second.txt (наход. в папке программы)"<<endl<<"| 3 | История вычислений"<<endl<<"| 4 | Очистиь историю"<< endl <<"|   | Выйти - введите любую клавишу"<< endl << "Ввод --->";
        cin >> choice;
        if (choice=="1"){
            cout << "Введите размер матриц (от 2 до 10) --->";
            cin >> size;
            Matrix A(size);
            Matrix B(size);
            Matrix C(size);
            A.SetMatrix();
            B.SetMatrix();
            cout << endl << "Первая матрица:" << endl;
            A.GetMatrix();
            cout << endl << "Вторая матрица:" << endl;
            B.GetMatrix();
            cout << endl << "Результат произведения (расчитанный методом 'строка на столбец'): " << endl;
            C=A*B;  
            C.GetMatrix();
            cout << endl;
            WriteToFile(A,B,C,true);
        }
        else if(choice=="2"){
            Matrix A(2);
            Matrix B(2);
            Matrix C(2);
            cout << endl << endl << "Первая матрица: " << endl;
            A=DataFromFile("matrix_first.txt");
            A.GetMatrix();
            cout << endl << "Вторая матрица: " << endl;
            B=DataFromFile("matrix_second.txt");
            B.GetMatrix();
            cout<<endl<<"Результат произведения (расчитанный методом 'строка на столбец'): "<<endl;
            C=A*B;
            C.GetMatrix();
            cout << endl << endl;
            WriteToFile(A,B,C,false);
        }
        else if(choice=="3"){
            ReadingFile();
        }
        else if(choice=="4"){
            DeleteLog();
        }
        else break;
    }

}

Matrix DataFromFile(string file_name){
    ifstream file;//объект для чтения файла
	file.open(file_name);//путь к файлу
    string buf;//буфер
    string number;//буфер
    int size;//размер
    for (file >> buf; !file.eof(); file >> buf)//перебор файла по словам=========
	{
            size=stoi(buf);
            break;
	}
    Matrix M(size);
    MComp C;
        for(int i=0;i<size;i++){//заполниение массива
            for(int j=0;j<size;j++){
                for (file >> buf; !file.eof(); file >> buf){
                    number=buf[0];
                    C.Re=stoi(number);
                    number=buf[2];
                    C.Im=stoi(number);
                    M.dinamic_array[i][j]=C;
                    break;
                }
            }
        }
    file.close();//закрытие файла
    return M;
}

void WriteToFile(Matrix x, Matrix y, Matrix z, bool enter){
    ofstream file;//объект для записи в файл
	file.open("data_output.txt", ios_base::app);//открытие файла для дополнительной записи
    file << endl<<endl<<"================================================================================="<<endl;
    if(enter==true)file << "Размер матрицы задан пользователем, числа сгенерированны случайно (от -10 до 10)" <<endl<<endl;
    else if(enter==false)file << "Введено из файлов matrix_second.txt и matrix_first.txt (наход. в папке программы)" <<endl<<endl;                                
    file.close();//закрытие файла
    WriteMatrix(x,1);
    WriteMatrix(y,2);
    WriteMatrix(z,3);
}

void WriteMatrix(Matrix x, int step){
    ofstream file;//объект для записи в файл
	file.open("data_output.txt", ios_base::app);//открытие файла для дополнительной записи
    if(step==1)file << "Первая матрица: " << endl;
    else if(step==2)file << endl <<"Вторая матрица: " << endl;
    else if(step==3)file << endl <<"Результат произведения матриц: " << endl;
    MComp a;//комплексное число
    for(int i=0;i<x.size;i++){//запись данных в файл с выравниванием
        for(int j=0;j<x.size;j++){
            a=x.dinamic_array[i][j];
            if(a.Re<0){
                if(a.Re>-1000 & a.Re<-99)file << a.Re;
                else if(a.Re>-100 & a.Re<-9 )file <<" "<<a.Re;
                else if(a.Re>-10 & a.Re<0 )file <<"  "<<a.Re;
                }
            
            else if(a.Re>=0){
                if(a.Re<1000 & a.Re>99)file <<" "<< a.Re;
                else if(a.Re<100 & a.Re>9 )file <<"  "<<a.Re;
                else if(a.Re<10 & a.Re>=0 )file <<"   "<<a.Re;
            }

            if(a.Im<0){
                file <<"-i";
                if(a.Im>-1000 & a.Im<-99)file << (-1)*a.Im;
                else if(a.Im>-100 & a.Im<-9 )file <<(-1)*a.Im<<" ";
                else if(a.Im>-10 & a.Im<0 )file <<(-1)*a.Im<<"  ";
            }
            else if(a.Im>=0){
                file<<"+i";
                if(a.Im<1000 & a.Im>99)file <<a.Im;
                else if(a.Im<100 & a.Im>9 )file <<a.Im <<" ";
                else if(a.Im<10 & a.Im>=0 )file <<a.Im << "  ";
            }
            file << " ";
        }
        file << endl;
    }
    file.close();//закрытие файла
}

void ReadingFile(){
	ifstream file;//объект для чтения файла
	file.open("data_output.txt");//путь к файлу
	string line = " ";//буфер для строки
	while (!file.eof())//проверка на конец файла
	{
		getline(file, line);//запись в строки файла в буфер
		cout << line << endl;//вывод содержимого буфера
	}
	file.close();//закрытие файла
}

void DeleteLog(){
	ofstream file;//объект для записи в файл
	file.open("data_output.txt");//открытие файла
	file << endl <<"================================================================================="<<endl<<"Файл data_output.txt находится в папке программы" << endl <<"================================================================================="<<endl;//запись
	file.close();//закрытие файла
}